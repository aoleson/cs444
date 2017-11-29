/* HAPPY HUNGER GAMES!
 * And may the odds be ever in your favor.
 *
 *           /|   \
 *          /_|_{)/
 * <---<<   | |  )
 *          \ |  (
 *           \|  )
 *              /|
 *              \ \
 *              ~ ~
 *
 * Problem 1 - Concurrency 3
 * Alannah Oleson / Jacob Mahugh
 *
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_TRIBUTES 12		//A R B I T R A R Y number of threads
				//but not really cos there's 12 districts

//Everyone can see these globals
sem_t cornucopia;		//Everyone wants the good stuff
int tributes_at_crncpa = 0;	//It's too small for > 3
int crncpa_is_full = 0;		//If there are too many tributes at the
				//cornucopia, you have to wait and hide


void * let_the_games_begin(void *district) {

   //How long you dare to scavenge before running back to safety
   int scav_time = rand() % 5 + 1;
   int items_gained = rand() % 10;

   //Each tribute is defined by their district
   int trib_district = *((int *)district) + 1;

   //Let the games...begin!!
   while(1) {

      //The first few tributes to get to the cornucopia head in
      sem_wait(&cornucopia);
      tributes_at_crncpa += 1;

      //Check to see if there are spots left for other tributes
      if (tributes_at_crncpa == 3) {
	 crncpa_is_full = 1;
      }

      else {
          crncpa_is_full = 0;
      }

      //Scavenge what you can, as quickly as you can
      printf("Tribute %d raids the cornucopia for %d minutes\n", trib_district, scav_time);
      sleep(scav_time);

      printf("Tribute %d leaves the cornucopia with %d useful items\n", trib_district, items_gained);


      //Get out - the careers are on the way back!
      if (crncpa_is_full == 1) {

	 //Leave...or the canon will fire :(
	 tributes_at_crncpa -= 1;

	 //If all three tributes are cleared out, three new ones can take their place
         if (tributes_at_crncpa == 0) {
              sem_post(&cornucopia);
              sem_post(&cornucopia);
              sem_post(&cornucopia);
	 }
      
      }
      
      //Else, the careers are still out - leave at your leisure
      else {
	 tributes_at_crncpa -= 1;
	 sem_post(&cornucopia);
      }

   }

}


int main () {

   //Set up the staduim for this year's games
   srand(time(NULL));
   pthread_t tributes[NUM_TRIBUTES];
   sem_init(&cornucopia, 0, 3);
   int district;

   //Reap the tributes from the districts
   for (district = 0; district < NUM_TRIBUTES; district++) {
       pthread_create(&tributes[district], NULL, let_the_games_begin, &district);
   }

   //Send the deceased home with highest honors
   for (district = 0; district < NUM_TRIBUTES; district++) {
       pthread_join(tributes[district], NULL);
   }

   return 0;

}
