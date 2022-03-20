#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main(int argc, void *argv) {

  for(int i=0; i<4; i++) {

    int ret = fork();
    if(ret == 0) {
      printf("child %d\n", i);
    }

  }
}
