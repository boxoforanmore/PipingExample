#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <iostream>
#include <cstring>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <fcntl.h>
#include <string.h>

#define assertsyscall(x, y) if((x) y){int err = errno; {perror(#x); exit(err);}}

#define READ 4
#define WRITE 3

int main(int argc, char *argv[]) {
    //int child2parent[2], parent2child[2];
  
    //assertsyscall(pipe(child2parent), == 0);
    //assertsyscall(pipe(parent2child), == 0);
 
    pid_t parent = getppid();

    //child2parent = strtol(argv[1], NULL, 10);
    //parent2child = strtol(argv[2], NULL, 10);

    char one[2] = "1"; 
    printf("I'm ogre here");
    fflush(stdout);
    assertsyscall(write(WRITE, one, strlen(one)), > 0);
    //sleep(.5);
    assert(kill(parent, SIGTRAP) == 0); 
 
    // 1. Should read and print sys_time from pipe 
    char buffer[1024];
    int len;
    assertsyscall((len = read(READ, buffer, sizeof(buffer))), != -1);
    buffer[len] = 0;
    assertsyscall(printf("%s", buffer), > 0);


    // 2. Should read and print the calling (parent) process's info
    assertsyscall(write(WRITE, "2", 2), != -1);
    assert(kill(parent, SIGTRAP) == 0);
    assertsyscall((len = read(READ, buffer, sizeof(buffer))), != -1);
    buffer[len] = 0;
    assertsyscall(printf("%s", buffer), > 0);


    // 3. Should read and print the list of all processes
    assertsyscall(write(WRITE, "3", 2), != -1);
    assert(kill(parent, SIGTRAP) == 0);
    assertsyscall((len = read(READ, buffer, sizeof(buffer))), != -1);
    buffer[len] = 0;
    assertsyscall(printf("%s", buffer), > 0);


    // 4. Should read and print to stdout until null found
    //strcat(four, buffer);
    assertsyscall(write(WRITE, "4", 2), != -1);
    assert(kill(parent, SIGTRAP) == 0);
    assertsyscall((len = read(READ, buffer, sizeof(buffer))), != -1); 
    buffer[len] = 0;

    // Assert >= 0, error is -1
    exit(0);

}
