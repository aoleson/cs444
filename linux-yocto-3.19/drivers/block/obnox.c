/*
 * A sample, extra-simple block driver. Updated for kernel 2.6.31.
 *
 * (C) 2003 Eklektix, Inc.
 * (C) 2010 Pat Patterson <pat at superpat dot com>
 * Redistributable under the terms of the GNU GPL.
 */

/* 
 * Edited by Jacob Mahugh & Alannah Oleson 
 * 
 * Special thanks to Chris Mendez
 */

/**
 * REFS:
 * http://blog.superpat.com/2010/05/04/a-simple-block-driver-for-linux-kernel-2-6-31/
 *    - This also formed the base of our implementation.
 * https://lwn.net/Articles/58719/
 * https://lwn.net/Kernel/LDD3
 * https://kernel.readthedocs.io/en/sphinx-samples/crypto-API.html#code-examples
 * https://github.com/bowenjos/cs444-020/blob/master/assignment3.patch
 * https://github.com/fahlmant/cs444/blob/master/patches/proj3/proj3.patch
 * https://github.com/zainkai/CS444/blob/master/Assignment3/cipher/sbd_enc.c
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/kernel.h> /* printk() */
#include <linux/fs.h>     /* everything... */
#include <linux/errno.h>  /* error codes */
#include <linux/types.h>  /* size_t */
#include <linux/vmalloc.h>
#include <linux/genhd.h>
#include <linux/blkdev.h>
#include <linux/hdreg.h>

#include <linux/crypto.h> /* Encryption library */

MODULE_LICENSE("Dual BSD/GPL");

static struct crypto_cipher *ciph;

static int major_num = 0;
module_param(major_num, int, 0);
static int logical_block_size = 512;
module_param(logical_block_size, int, 0);
static int nsectors = 1024; /* How big the drive is */
module_param(nsectors, int, 0);

static char* key = "FrEnChToAsT";
module_param(key, charp, 0);

/*
 * We can tweak our hardware sector size, but the kernel talks to us
 * in terms of small sectors, always.
 */
#define KERNEL_SECTOR_SIZE 512

/*
 * Our request queue.
 */
static struct request_queue *Queue;

/*
 * The internal representation of our device.
 */
static struct obnox_enc_device {
        unsigned long size;
        spinlock_t lock; /* prevents drivers from fighting over device. */
        u8 *data; /* similar to unit8_t or unsigned int */
        struct gendisk *gd; /* ??? */
} Device;

/**
 * prints hex data at a address
 * Special thanks to Zainkai for this gem
 */
static void hexdump(u8 *ptr, unsigned int length) {
        int i;

        for (i = 0 ; i < length ; i++){
                printk(KERN_DEBUG "%02x", ptr[i]);
        }
        printk(KERN_DEBUG "\n");
}


/*
 * Handle an I/O request.
 */
static void obnox_enc_transfer(struct obnox_enc_device *dev, sector_t sector,
	unsigned long nsect, char *buffer, int write) {

	unsigned long offset = sector * logical_block_size;
	unsigned long nbytes = nsect * logical_block_size;

	u8 *hex_str, *hex_buf, *hex_disk;
	unsigned int i;

	hex_disk = dev->data + offset;
	hex_buf = buffer;
	printk(KERN_DEBUG "obnox: Key = %s, write=%d in sector=%llu\n",key, write, sector);

	if ((offset + nbytes) > dev->size) {
		printk (KERN_NOTICE "obnox: Beyond-end write (%ld %ld)\n", offset, nbytes);
		return;
	} if (write) {
		printk(KERN_DEBUG "obnox: Write Begin\n");
		
		printk(KERN_DEBUG "obnox: Original Hex\n");
		hexdump(buffer,10);

		/* Encrypt, block by block. */
		for(i = 0; i < nbytes; i += crypto_cipher_blocksize(ciph)){
		   	//printk(KERN_DEBUG "obnox: encrypting block %d\n", i);
			crypto_cipher_encrypt_one(ciph, dev->data + offset + i, buffer + i);
		}


		hex_str = dev->data + offset;
		printk(KERN_DEBUG "obnox: Encrypted Hex\n");
		hexdump(hex_str,10);

	} else {
		printk(KERN_DEBUG "obnox: Read Begin\n");

		printk(KERN_DEBUG "obnox: Original Hex\n");
		hex_str = dev->data + offset;
		hexdump(hex_str,10);

		/* Decrypt, block by block */
		for(i = 0; i < nbytes; i += crypto_cipher_blocksize(ciph)){
		   	//printk(KERN_DEBUG "obnox: decrypting block %d\n", i);
			crypto_cipher_decrypt_one(ciph, buffer + i, dev->data + offset + i);
		}


		printk(KERN_DEBUG "obnox: Decrypted Hex\n");
		hexdump(buffer,10);
	}
}

static void obnox_enc_request(struct request_queue *q) {
	struct request *req;

	req = blk_fetch_request(q);
	while (req != NULL) {
		// blk_fs_request() was removed in 2.6.36 - many thanks to
		// Christian Paro for the heads up and fix...
		//if (!blk_fs_request(req)) {
		if (req == NULL || (req->cmd_type != REQ_TYPE_FS)) {
			printk (KERN_NOTICE "Skip non-CMD request\n");
			__blk_end_request_all(req, -EIO);
			continue;
		}

		obnox_enc_transfer(&Device, blk_rq_pos(req), blk_rq_cur_sectors(req),
			bio_data(req->bio), rq_data_dir(req));

		if ( ! __blk_end_request_cur(req, 0) ) {
			req = blk_fetch_request(q);
		}
	}
}

/*
 * The HDIO_GETGEO ioctl is handled in blkdev_ioctl(), which
 * calls this. We need to implement getgeo, since we can't
 * use tools such as fdisk to partition the drive otherwise.
 */
int obnox_enc_getgeo(struct block_device * block_device, struct hd_geometry * geo) {
	long size;

	size = Device.size * (logical_block_size / KERNEL_SECTOR_SIZE);
	geo->cylinders = (size & ~0x3f) >> 6;
	geo->heads = 4;
	geo->sectors = 16;
	geo->start = 0;
	return 0;
}

/*
 * The device operations structure.
 */
static struct block_device_operations obnox_enc_ops = {
		.owner  = THIS_MODULE,
		.getgeo = obnox_enc_getgeo
};

static int __init obnox_enc_init(void) {

	printk(KERN_DEBUG "obnox: Starting!\n");

	/*
	 * Set up our internal device.
	 */
	Device.size = nsectors * logical_block_size;
	spin_lock_init(&Device.lock);
	Device.data = vmalloc(Device.size);
	if (Device.data == NULL)
		return -ENOMEM;
	/*
	 * Get a request queue.
	 */
	Queue = blk_init_queue(obnox_enc_request, &Device.lock);
	if (Queue == NULL)
		goto goodbye;
	blk_queue_logical_block_size(Queue, logical_block_size);
	/*
	 * Get registered.
	 */
	major_num = register_blkdev(major_num, "obnox_enc");
	if (major_num < 0) {
		printk(KERN_WARNING "obnox: ERROR - major_num < 0\n");
		goto goodbye;
	}

	/* Allocating the cipher */
	ciph = crypto_alloc_cipher("aes",0,0);
	if(!ciph){
		printk(KERN_WARNING "obnox: ERROR - can't alloc crypto cipher!\n");
		goto goodbye;
	}

	printk(KERN_DEBUG "obnox: Key = %s\n",key);
	crypto_cipher_setkey(ciph,key,strlen(key));

	/*
	 * And the gendisk structure.
	 */
	Device.gd = alloc_disk(16);
	if (!Device.gd)
		goto bye_unregister;
	Device.gd->major = major_num;
	Device.gd->first_minor = 0;
	Device.gd->fops = &obnox_enc_ops;
	Device.gd->private_data = &Device;
	strcpy(Device.gd->disk_name, "obnox_enc0");
	set_capacity(Device.gd, nsectors);
	Device.gd->queue = Queue;
	add_disk(Device.gd);

	printk(KERN_DEBUG "obnox: All initilaized!\n");

	return 0;

bye_unregister:
	unregister_blkdev(major_num, "obnox_enc");
goodbye:
	vfree(Device.data);
	return -ENOMEM;
}

static void __exit obnox_enc_exit(void)
{
	printk(KERN_DEBUG "obnox: Leaving.\n");

	/* Freeing crypto */
	crypto_free_cipher(ciph);

	del_gendisk(Device.gd);
	put_disk(Device.gd);
	unregister_blkdev(major_num, "obnox_enc");
	blk_cleanup_queue(Queue);

	printk(KERN_DEBUG "obnox: Goodbye!\n");
}

module_init(obnox_enc_init);
module_exit(obnox_enc_exit);
