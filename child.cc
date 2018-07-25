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

#define READ 0
#define WRITE 1

int main(int argc, char *argv[]) {
    int child2parent[2], parent2child[2];
  
    assertsyscall(pipe(child2parent), == 0);
    assertsyscall(pipe(parent2child), == 0);
 
    pid_t parent = getppid();

    //child2parent = strtol(argv[1], NULL, 10);
    //parent2child = strtol(argv[2], NULL, 10);

    // 
    assertsyscall(write(child2parent[WRITE], '1', 4), != -1);
    assert(kill(parent, SIGTRAP) == 0); 
 
    // 1. Should read and print sys_time from pipe 
    char buffer[1024];
    int len;
    assertsyscall((len = read(child2parent[READ], buffer, sizeof(buffer))), != -1);
    buffer[len] = 0;
    assertsyscall(printf("%s", buffer), > 0);


    // 2. Should read and print the calling (parent) process's info
    assertsyscall(write(child2parent[WRITE], 2, 4), != -1);
    assert(kill(parent, SIGTRAP) == 0);
    assertsyscall((len = read(parent2child[READ], buffer, sizeof(buffer))), != -1);
    buffer[len] = 0;
    assertsyscall(printf("%s", buffer), > 0);


    // 3. Should read and print the list of all processes
    assertsyscall(write(child2parent[WRITE], 3, 4), != -1);
    assert(kill(parent, SIGTRAP) == 0);
    assertsyscall((len = read(parent2child[READ], buffer, sizeof(buffer))), != -1);
    buffer[len] = 0;
    assertsyscall(printf("%s", buffer), > 0);


    // 4. Should read and print to stdout until null found
    assertsyscall(write(child2parent[WRITE], 4, 4), != -1);
    assert(kill(parent, SIGTRAP) == 0);
    assertsyscall((len = read(parent2child[READ], buffer, sizeof(buffer))), != -1); 
    buffer[len] = 0;
    assertsyscall(printf("%s", buffer), > 0);

    // Assert >= 0, error is -1
    exit(0);

}
