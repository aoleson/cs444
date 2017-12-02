#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define frag_check syscall(359)

int main () {

   printf("Testing frag_check\n");

   printf("frag_check result: %lu\n", frag_check);

   printf("Done testing frag_check\n");

   return 0;

}
