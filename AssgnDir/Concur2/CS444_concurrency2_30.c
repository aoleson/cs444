#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>

struct philosopher {
	int lchopstick_id;
	int rchopstick_id;
	char[] name;
}

int chopstick_list[5] = [1,1,1,1,1];//Chopsticks 1-5
struct philosopher nerds[5];
pthread_mutex_t waiter;

void think() {
	srand(time(NULL));
	sleep(rand()%20 + 1);
}

void eat() {
	srand(time(NULL));
	sleep(rand()%8 + 2);
}

void grab(struct philosopher *nerd) {
	//if both left and right fork are free
	//eat
	//otherwise wait
	//use a mutex here
	//arbitrator solution
}

void set(struct philosopher *nerd) {
	//set chopsticks down
}

void print_state(struct philosophers *nerds) {
	//may not be needed?	
}

int main() {
	nerds[0].name = "Paul Of Tarsis";
	nerds[0].lchopstick_id = 0;
	nerds[0].rchopstick_id = 1;
	struct philosopher Jesus;
	nerds[1].name = "Jesus Christ of Nazareth";//is it blasphemous to call
	//Jesus a nerd? He kinda was a Bible nerd... 
	nerds[1].lchopstick_id = 1;
	nerds[1].rchopstick_id = 2;
	nerds[2].name = "__";
	nerds[2].lchopstick_id = 2;
	nerds[2].rchopstick_id = 3;
	nerds[3].name = "__";
	nerds[3].lchopstick_id = 3;
	nerds[3].rchopstick_id = 4;
	nerds[4].name = "__";
	nerds[4].lchopstick_id = 4;
	nerds[4].rchopstick_id = 0;

	//fork em boss
	//run the loop
	//think, grab, eat, set
	//print during each step, philosopher, step, forks held?
	
	return 0;
}
