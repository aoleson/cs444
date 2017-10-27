#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>

struct philosopher {
	int lchopstick_id;
	int rchopstick_id;
	char *name;
};

int chopstick_list[5];//Chopsticks 1-5
//if chopstick = 0, in use
struct philosopher nerds[5];
pthread_mutex_t miyagi;

void think(struct philosopher n) {
	int slptm = (rand()%20) + 1;
//	int slptm = (rand()%5) + 1;
	printf("%s is thinking for %d seconds! Go %s!\n", n.name,
		   	slptm, n.name);
	srand(time(NULL));
	sleep(slptm);
	return;
}

void eat(struct philosopher n) {
	int eattm = (rand()%8) + 2;
//	int eattm = (rand()%1) + 2;
	printf("%s is eating for %d seconds! Delicious!\n", n.name,
			eattm);
	//srand(time(NULL));
	sleep(eattm);
	return;
}

void grab(struct philosopher n) {
WAX_ON:
	while(can_i_miyagi(n) == 0){}
	pthread_mutex_lock(&miyagi);
	if (can_i_miyagi(n) == 0) {
		pthread_mutex_unlock(&miyagi);
		goto WAX_ON;	
	}
	sleep(0.5);
	chopstick_list[n.lchopstick_id] = 0;
	chopstick_list[n.rchopstick_id] = 0;
	printf("%s is grabbing chopsticks %d, %d! Dinner time!\n", n.name, 
			n.lchopstick_id,
			n.rchopstick_id);
/*	printf("SET: %d %d\n",
			chopstick_list[n.lchopstick_id],
			chopstick_list[n.rchopstick_id]);*/
	pthread_mutex_unlock(&miyagi);
	return;
}

void set(struct philosopher n) {
	chopstick_list[n.lchopstick_id] = 1;
	chopstick_list[n.rchopstick_id] = 1;
	//srand(time(NULL));
	printf("%s is letting go of chopsticks %d, %d. He ate about %d noodles!\n", 
			n.name, 
			n.lchopstick_id,
			n.rchopstick_id,
			rand()%5000+1);
}

int can_i_miyagi(struct philosopher n) {
	if (chopstick_list[n.lchopstick_id] == 1 
			&& chopstick_list[n.rchopstick_id] == 1) {
		return 1;
	} else
		return 0;
}

void *philosophize(void *na) {
	struct philosopher *nat = (struct philosopher*)na;
	struct philosopher n = *nat;
	int cntr = 0;
	//int *tid = (int*)pid;
	//int id = *tid;
	for (;;){
		think(n);
		grab(n);
		eat(n);
		set(n);
	}
	return NULL;
}

int main() {
	srand(time(NULL));
	chopstick_list[0] = 1;
	chopstick_list[1] = 1;
	chopstick_list[2] = 1;
	chopstick_list[3] = 1;
	chopstick_list[4] = 1;
	nerds[0].name = "Paul Of Tarsis";
	nerds[0].lchopstick_id = 0;
	nerds[0].rchopstick_id = 1;
	nerds[1].name = "Jesus Christ of Nazareth";//is it blasphemous to call
	//Jesus a nerd? He kinda was a Bible nerd... 
	nerds[1].lchopstick_id = 1;
	nerds[1].rchopstick_id = 2;
	nerds[2].name = "Sophocles";
	nerds[2].lchopstick_id = 2;
	nerds[2].rchopstick_id = 3;
	nerds[3].name = "Friedreich Heinrich Jacobi";
	nerds[3].lchopstick_id = 3;
	nerds[3].rchopstick_id = 4;
	nerds[4].name = "Caspar John Hare";//Egocentric Presentism, Google him
	nerds[4].lchopstick_id = 4;
	nerds[4].rchopstick_id = 0;

	pthread_t nerd_threads[5];
	int cnt = 0;
	for (cnt = 0; cnt < 5; cnt++) {
		pthread_create(&(nerd_threads[cnt]),
						NULL,
						philosophize,
						(void*)&nerds[cnt]);
	}
	for (cnt = 0; cnt < 5; cnt++) {
		pthread_join(nerd_threads[cnt], NULL);
	}
	//fork em boss
	//run the loop
	//think, grab, eat, set
	//print during each step, philosopher, step, forks held?
	
	return 0;
}
