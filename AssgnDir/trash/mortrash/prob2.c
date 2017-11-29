#include<stdlib.h>
#include<stdio.h>
#include<sys/queue.h>
#include<pthread.h>

#define NUMSEARCH 4
#define NUMINSERT 3
#define NUMDELETE 2
#define DIE_AFTER 500

struct my_list {
	struct my_list *n;
	int id;
};

LIST_HEAD(listhead, entry) head;
struct entry {
	LIST_ENTRY(entry) entries;
	int id;
};

int listLen = 0;
int numSearch = 0;
int numInsert = 0;
int numDelete = 0;

int isInsLock = 0;
pthread_mutex_t lock;
int isDelLock = 0;

void *search(void *hp) {
	numSearch++;
	int myId = numSearch;
	struct entry *viewer;
	int cnt, cnt2=0;
	int move;
	
	for (cnt = 0; cnt < DIE_AFTER; cnt++){
		cnt2=0;
		while (isDelLock){}
		move = rand()%(listLen);
		for (viewer = head.lh_first;
			   	viewer != NULL; viewer = viewer->entries.le_next){
			if (move == cnt2)
				printf("S%d searched %d\t\t|\t\tInsLock:%d - DelLock:%d\n", 
						myId, viewer->id, isInsLock, isDelLock);
			cnt2++;
		}
		sleep(rand() % 5);
	}
	return NULL;
}

void *delete(void *hp) {
	numDelete++;
    int myId = numDelete;
	struct entry *viewer;
	int cnt, cnt2, move;
	for (cnt = 0; cnt < DIE_AFTER; cnt++) {
		while(isInsLock || isDelLock){}
		if (!isInsLock && !isDelLock) {
			pthread_mutex_lock(&lock);
			isDelLock = 1;
			cnt2=0;
			move = rand()%(listLen);
			for (viewer = head.lh_first;
			   	viewer != NULL; viewer = viewer->entries.le_next){
				if (move == cnt2) {
					printf("D%d deleted  %d\t\t|\t\tInsLock:%d - DelLock:%d\n",
						myId, viewer->id, isInsLock, isDelLock);
						listLen--;
						LIST_REMOVE(viewer, entries);
				}
					cnt2++;
			}
			pthread_mutex_unlock(&lock);
			isDelLock = 0;
		}
		sleep(rand()%9);
	}
	return NULL;
}

void *insert(void *hp) {
	numInsert++;
    int myId = numInsert;
	int cnt;
	for (cnt = 0; cnt < DIE_AFTER; cnt++){
		//Triple checking of lock just in case.
		while(isInsLock || isDelLock){}
		if (!isInsLock && !isDelLock) {
			pthread_mutex_lock(&lock);
			isInsLock = 1; //Let everyone else know who has the lock
			listLen++; //oh look. We are making something new!
			struct entry *new;
			new = malloc(sizeof(struct entry));
			new->id = listLen;
			LIST_INSERT_HEAD(&head, new, entries);//added!
			printf("I%d inserted %d\t\t|\t\tInsLock:%d - DelLock:%d\n",
				   	myId, new->id, isInsLock, isDelLock);
			pthread_mutex_unlock(&lock);
			isInsLock = 0;
		}
		sleep(rand()%7);
	}
	return NULL;
}

int main() {

	int cnt;
	
	struct listhead *headp;

	LIST_INIT(&head);
	struct entry *n1, *n2, *n3;
	
	listLen++;
	n1 = malloc(sizeof(struct entry));
	n1->id = listLen;
	LIST_INSERT_HEAD(&head, n1, entries);

	listLen++;
	n2 = malloc(sizeof(struct entry));
	n2->id = listLen;
	LIST_INSERT_HEAD(&head, n2, entries);
	
	listLen++;
	n3 = malloc(sizeof(struct entry));
	n3->id = listLen;
	LIST_INSERT_HEAD(&head, n3, entries);
	
	srand(time(NULL));	

	pthread_t searchers[NUMSEARCH];
	pthread_t inserters[NUMINSERT];
	pthread_t deleters[NUMDELETE];

	for (cnt = 0; cnt < NUMSEARCH; cnt++) {
		pthread_create(&(searchers[cnt]),
						NULL,
						search,
						NULL);
	}
	
	for (cnt = 0; cnt < NUMINSERT; cnt++) {
		pthread_create(&(inserters[cnt]),
						NULL,
						insert,
						NULL);
	}

	for (cnt = 0; cnt < NUMDELETE; cnt++) {
		pthread_create(&(deleters[cnt]),
						NULL,
						delete,
						NULL);
	}
	for (cnt = 0; cnt < NUMSEARCH; cnt++) {
		pthread_join(searchers[cnt], NULL);
	}
	for (cnt = 0; cnt < NUMINSERT; cnt++) {
		pthread_join(inserters[cnt], NULL);
	}
	for (cnt = 0; cnt < NUMDELETE; cnt++) {
		pthread_join(deleters[cnt], NULL);
	}
	return 0;
}

