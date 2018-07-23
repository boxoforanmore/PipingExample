#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>

#define assertsyscall(x, y) if((x) y){int err = errno; {perror(#x); exit(err);}}


int main(int argc, char *argv[]) {
    int child2parent, parent2child;
   
    pid_t parent = getpid();

    child2parent = strtol(argv[1], NULL, 10);
    parent2child = strtol(argv[2], NULL, 10);

    assert(kill(parent, SIGTRAP) == 0);
    write(child2parent, 1, 4);
    
    // read
    // print
    // write
    // read...

    // Assert >= 0, error is -1
    

}
