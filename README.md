


-CPU.cc is a round-robining process selector that creates pipes and acts upon them
-child.cc writes to pipes, sends traps and receives relevant messages that will eventually be passed back and printed by CPU.cc


Requirements:
```g++```

Optional:
```
valgrind
clang-tidy```

Run on a Unix system with:
`./bashme.sh`


Run on a Linux system (if optional components installed) with:
`./travis.sh
