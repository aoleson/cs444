/*
 * Sample disk driver, from the beginning.
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/sched.h>
#include <linux/kernel.h>	/* printk() */
#include <linux/slab.h>		/* kmalloc() */
#include <linux/fs.h>		/* everything... */
#include <linux/errno.h>	/* error codes */
#include <linux/timer.h>
#include <linux/types.h>	/* size_t */
#include <linux/fcntl.h>	/* O_ACCMODE */
#include <linux/hdreg.h>	/* HDIO_GETGEO */
#include <linux/kdev_t.h>
#include <linux/vmalloc.h>
#include <linux/genhd.h>
#include <linux/blkdev.h>
#include <linux/buffer_head.h>	/* invalidate_bdev */
#include <linux/bio.h>
#include <linux/crypto.h>

MODULE_LICENSE("Dual BSD/GPL");

static char *key="OnceMoreUntoTheBreach";
struct crypto_cipher *cip;

module_param(key, charp, S_IRUGO);
static int obnox_major = 0;
module_param(obnox_major, int, 0);
static int hardsect_size = 512;
module_param(hardsect_size, int, 0);
static int nsectors = 1024;	/* How big the drive is */
module_param(nsectors, int, 0);
static int ndevices = 4;
module_param(ndevices, int, 0);

/*
 * The different "request modes" we can use.
 */
enum {
	RM_SIMPLE  = 0,	/* The extra-simple request function */
	RM_FULL    = 1,	/* The full-blown version */
	RM_NOQUEUE = 2,	/* Use make_request */
};
static int request_mode = RM_SIMPLE;
module_param(request_mode, int, 0);

/*
 * Minor number and partition management.
 */
#define SBULL_MINORS	16
#define MINOR_SHIFT	4
#define DEVNUM(kdevnum)	(MINOR(kdev_t_to_nr(kdevnum)) >> MINOR_SHIFT

/*
 * We can tweak our hardware sector size, but the kernel talks to us
 * in terms of small sectors, always.
 */
#define KERNEL_SECTOR_SIZE	512

/*
 * After this much idle time, the driver will simulate a media change.
 */
#define INVALIDATE_DELAY	30*HZ

#define KEY_SIZE 32
static char *crypto_key[KEY_SIZE];
static int key_size = 0;


/*
 * The internal representation of our device.
 */
struct obnox_dev {
        int size;                       /* Device size in sectors */
        u8 *data;                       /* The data array */
        short users;                    /* How many users */
        short media_change;             /* Flag a media change? */
        spinlock_t lock;                /* For mutual exclusion */
        struct request_queue *queue;    /* The device request queue */
        struct gendisk *gd;             /* The gendisk structure */
        struct timer_list timer;        /* For simulated media changes */
};

static struct obnox_dev *Devices = NULL;

void print_nulless_str(char *str, int l) {
	for (l; l > 0; l--) {
	   printk("%c", *str++);
	}
	printk("\n");
}

/*
 * Handle an I/O request.
 */
static void obnox_transfer(struct obnox_dev *dev, unsigned long sector,
		unsigned long nsect, char *buffer, int write)
{
	unsigned long offset = sector*KERNEL_SECTOR_SIZE;
	unsigned long nbytes = nsect*KERNEL_SECTOR_SIZE;
	int i = 0;

	if ((offset + nbytes) > dev->size) {
		printk (KERN_NOTICE "Beyond-end write (%ld %ld)\n", offset, nbytes);
		return;
	}
	crypto_cipher_clear_flags(cip, ~0);
	crypto_cipher_setkey(cip, key, strlen(key));
	if (write) {
	   	printk("Before cipher:\n");
		print_nulless_str(buffer, nbytes);
		for (i = 0; i < nbytes; i += crypto_cipher_blocksize(cip)) {
		   memset(dev->data + offset + i, 0, crypto_cipher_blocksize(cip));
		   crypto_cipher_encrypt_one(cip, dev->data + offset + i, buffer + i);
		}
		//memcpy(dev->data + offset, buffer, nbytes);
		printk("Post cipher:\n");
		print_nulless_str(dev->data + offset, nbytes);

	}else{
	   	printk("Pre decoding:\n");
		print_nulless_str(dev->data + offset, nbytes);
		for (i = 0; i < nbytes; i += crypto_cipher_blocksize(cip)) {
		   crypto_cipher_decrypt_one(cip, buffer + i, dev->data + offset + i);
		}
		printk("Post decoding:\n");
		print_nulless_str(buffer, nbytes);
		//memcpy(buffer, dev->data + offset, nbytes);

	}
}

/*
 * The simple form of the request function.
 */
static void obnox_request(struct request_queue *q)
{
	struct request *req;

	char *buffer = ""; //hacky
	while ((req = blk_fetch_request(q)) != NULL) {
		struct obnox_dev *dev = req->rq_disk->private_data;
		if (req->cmd_type != REQ_TYPE_FS) {
			printk (KERN_NOTICE "Skip non-fs request\n");
			__blk_end_request_cur(req, -EIO);
			continue;
		}
    //    	printk (KERN_NOTICE "Req dev %d dir %ld sec %ld, nr %d f %lx\n",
    //    			dev - Devices, rq_data_dir(req),
    //    			req->sector, req->current_nr_sectors,
    //    			req->flags);
		obnox_transfer(dev, blk_rq_pos(req), blk_rq_cur_sectors(req),
				buffer, rq_data_dir(req));
		__blk_end_request_cur(req, 0);
	}
}


/*
 * Transfer a single BIO.
 */
static int obnox_xfer_bio(struct obnox_dev *dev, struct bio *bio)
{
	struct bio_vec bvec;
	struct bvec_iter iter;
	sector_t sector = bio->bi_iter.bi_sector;

	/* Do each segment independently. */
	bio_for_each_segment(bvec, bio, iter) {
		char *buffer = __bio_kmap_atomic(bio, iter);
		obnox_transfer(dev, sector, bio_cur_bytes(bio),
				buffer, bio_data_dir(bio) == WRITE);
		sector += bio_cur_bytes(bio);
		__bio_kunmap_atomic(bio);
	}
	return 0; /* Always "succeed". Always. */
}

/*
 * Transfer a full request.
 */
static int obnox_xfer_request(struct obnox_dev *dev, struct request *req)
{
	struct bio *bio;
	int nsect = 0;
    
	__rq_for_each_bio(bio, req) {
		obnox_xfer_bio(dev, bio);
		nsect += bio->bi_iter.bi_size/KERNEL_SECTOR_SIZE;
	}
	return nsect;
}



/*
 * Smarter request function that "handles clustering".
 */
static void obnox_full_request(struct request_queue *q)
{
	struct request *req;
	int sectors_xferred;
	struct obnox_dev *dev = q->queuedata;

	while ((req = blk_fetch_request(q)) != NULL) {
		if (req->cmd_type != REQ_TYPE_FS) {
			printk (KERN_NOTICE "Skip non-fs request\n");
			__blk_end_request(req, -EIO, blk_rq_cur_bytes(req));
			continue;
		}
		sectors_xferred = obnox_xfer_request(dev, req);
		__blk_end_request(req, 0, sectors_xferred);
	}
}



/*
 * The direct make request version.
 */
static void obnox_make_request(struct request_queue *q, struct bio *bio)
{
	struct obnox_dev *dev = q->queuedata;
	int status;

	status = obnox_xfer_bio(dev, bio);
	bio_endio(bio, status);
}


/*
 * Open and close.
 */

static int obnox_open(struct block_device *bdev, fmode_t mode)
{
	struct obnox_dev *dev = bdev->bd_disk->private_data;

	del_timer_sync(&dev->timer);
	//filp->private_data = dev;
	spin_lock(&dev->lock);
	if (! dev->users) 
		check_disk_change(bdev);
	dev->users++;
	spin_unlock(&dev->lock);
	return 0;
}

static void obnox_release(struct gendisk *disk, fmode_t mode)
{
	struct obnox_dev *dev = disk->private_data;

	spin_lock(&dev->lock);
	dev->users--;

	if (!dev->users) {
		dev->timer.expires = jiffies + INVALIDATE_DELAY;
		add_timer(&dev->timer);
	}
	spin_unlock(&dev->lock);
}

/*
 * Look for a (simulated) media change.
 */
int obnox_media_changed(struct gendisk *gd)
{
	struct obnox_dev *dev = gd->private_data;
	
	return dev->media_change;
}

/*
 * Revalidate.  WE DO NOT TAKE THE LOCK HERE, for fear of deadlocking
 * with open.  That needs to be reevaluated.
 */
int obnox_revalidate(struct gendisk *gd)
{
	struct obnox_dev *dev = gd->private_data;
	
	if (dev->media_change) {
		dev->media_change = 0;
		memset (dev->data, 0, dev->size);
	}
	return 0;
}

/*
 * The "invalidate" function runs out of the device timer; it sets
 * a flag to simulate the removal of the media.
 */
void obnox_invalidate(unsigned long ldev)
{
	struct obnox_dev *dev = (struct obnox_dev *) ldev;

	spin_lock(&dev->lock);
	if (dev->users || !dev->data) 
		printk (KERN_WARNING "obnox: timer sanity check failed\n");
	else
		dev->media_change = 1;
	spin_unlock(&dev->lock);
}

/*
 * The ioctl() implementation
 */

int obnox_ioctl (struct block_device *bdev, fmode_t mode,
                 unsigned int cmd, unsigned long arg)
{
	long size;
	struct hd_geometry geo;
	struct obnox_dev *dev = bdev->bd_disk->private_data;

	switch(cmd) {
	    case HDIO_GETGEO:
        	/*
		 * Get geometry: since we are a virtual device, we have to make
		 * up something plausible.  So we claim 16 sectors, four heads,
		 * and calculate the corresponding number of cylinders.  We set the
		 * start of data at sector four.
		 */
		size = dev->size*(hardsect_size/KERNEL_SECTOR_SIZE);
		geo.cylinders = (size & ~0x3f) >> 6;
		geo.heads = 4;
		geo.sectors = 16;
		geo.start = 4;
		if (copy_to_user((void __user *) arg, &geo, sizeof(geo)))
			return -EFAULT;
		return 0;
	}

	return -ENOTTY; /* unknown command */
}



/*
 * The device operations structure.
 */
static struct block_device_operations obnox_ops = {
	.owner           = THIS_MODULE,
	.open 	         = obnox_open,
	.release 	 = obnox_release,
	.media_changed   = obnox_media_changed,
	.revalidate_disk = obnox_revalidate,
	.ioctl	         = obnox_ioctl
};


/*
 * Set up our internal device.
 */
static void setup_device(struct obnox_dev *dev, int which)
{
	/*
	 * Get some memory.
	 */
	memset (dev, 0, sizeof (struct obnox_dev));
	dev->size = nsectors*hardsect_size;
	dev->data = vmalloc(dev->size);
	if (dev->data == NULL) {
		printk (KERN_NOTICE "vmalloc failure.\n");
		return;
	}
	spin_lock_init(&dev->lock);
	
	/*
	 * The timer which "invalidates" the device.
	 */
	init_timer(&dev->timer);
	dev->timer.data = (unsigned long) dev;
	dev->timer.function = obnox_invalidate;
	
	/*
	 * The I/O queue, depending on whether we are using our own
	 * make_request function or not.
	 */
	switch (request_mode) {
	    case RM_NOQUEUE:
		dev->queue = blk_alloc_queue(GFP_KERNEL);
		if (dev->queue == NULL)
			goto out_vfree;
		blk_queue_make_request(dev->queue, obnox_make_request);
		break;

	    case RM_FULL:
		dev->queue = blk_init_queue(obnox_full_request, &dev->lock);
		if (dev->queue == NULL)
			goto out_vfree;
		break;

	    default:
		printk(KERN_NOTICE "Bad request mode %d, using simple\n", request_mode);
        	/* fall into.. */
	
	    case RM_SIMPLE:
		dev->queue = blk_init_queue(obnox_request, &dev->lock);
		if (dev->queue == NULL)
			goto out_vfree;
		break;
	}
	blk_queue_logical_block_size(dev->queue, hardsect_size);
	dev->queue->queuedata = dev;
	/*
	 * And the gendisk structure.
	 */
	dev->gd = alloc_disk(SBULL_MINORS);
	if (! dev->gd) {
		printk (KERN_NOTICE "alloc_disk failure\n");
		goto out_vfree;
	}
	dev->gd->major = obnox_major;
	dev->gd->first_minor = which*SBULL_MINORS;
	dev->gd->fops = &obnox_ops;
	dev->gd->queue = dev->queue;
	dev->gd->private_data = dev;
	snprintf (dev->gd->disk_name, 32, "obnox%c", which + 'a');
	set_capacity(dev->gd, nsectors*(hardsect_size/KERNEL_SECTOR_SIZE));
	add_disk(dev->gd);
	return;

  out_vfree:
	if (dev->data)
		vfree(dev->data);
}



static int __init obnox_init(void)
{
	int i;
	
	cip = crypto_alloc_cipher("aes", 0, 16);
	if (IS_ERR(cip)) {
	   printk(KERN_ERR "seek: cipher alloc error");
	   return PTR_ERR(cip);
	}
	obnox_major = register_blkdev(obnox_major, "obnox");
	if (obnox_major <= 0) {
		printk(KERN_WARNING "obnox: unable to get major number\n");
		return -EBUSY;
	}
	/*
	 * Allocate the device array, and initialize each one.
	 */
	Devices = kmalloc(ndevices*sizeof (struct obnox_dev), GFP_KERNEL);
	if (Devices == NULL)
		goto out_unregister;
	for (i = 0; i < ndevices; i++) 
		setup_device(Devices + i, i);
    
	return 0;

  out_unregister:
	unregister_blkdev(obnox_major, "sbd");
	return -ENOMEM;
}

static void obnox_exit(void)
{
	int i;

	for (i = 0; i < ndevices; i++) {
		struct obnox_dev *dev = Devices + i;

		del_timer_sync(&dev->timer);
		if (dev->gd) {
			del_gendisk(dev->gd);
			put_disk(dev->gd);
		}
		if (dev->queue) {
			if (request_mode == RM_NOQUEUE)
				kobject_put (&dev->queue->kobj);
			else
				blk_cleanup_queue(dev->queue);
		}
		if (dev->data)
			vfree(dev->data);
	}
	unregister_blkdev(obnox_major, "obnox");
	kfree(Devices);
}
	
module_init(obnox_init);
module_exit(obnox_exit);
