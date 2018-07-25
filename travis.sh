#!/bin/bash
echo
echo
echo "Running: g++ CPU.cc -Wall -DEBUG" 
echo `g++ CPU.cc -Wall -DEBUG`
echo
echo "Running: g++ child.cc -Wall"
echo `g++ child.cc -Wall -DEBUG -o child`
echo
echo
echo
echo "Running clang-tidy on CPU.cc" 
echo `clang-tidy CPU.cc -- -Imy_project/include -DMY_DEFINES ...`
echo
echo "Running clang-tidy on child.cc"
echo `clang-tidy CPU.cc -- -Imy_project/include -DMY_DEFINES ...`
echo  
echo
echo
echo "Running valgrind on CPU.cc" 
echo `valgrind --leak-check=full --show-leak-kinds=all  ./a.out ./child ./child ./child`
echo
echo
./a.out ./child ./child ./child

exit 0
