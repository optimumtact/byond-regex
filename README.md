# byond-regex
Automatically exported from code.google.com/p/byond-regex

This is an interface to boost regex originally developed by carn

it has been slightly modified to support linux compilation

Invoke the following to compile bygex for linux - you'll need to have 32 bit cross compilation libs installed

    g++ -c -m32 -Wall -lstdc++ -lboost_regex -fPIC -o bygex.o main.cpp
    g++ bygex.o -m32 -lstdc++ -lboost_regex -shared -o bygex.so

You can then place bygex.so somewhere ld can see it (either usr/lib) or set LD_LIBRARY_PATH to point to your .so file

Note you'll have to modify core tgstation (instructions coming soon hopefully) to look for bygex.so and not bygex.dll.
