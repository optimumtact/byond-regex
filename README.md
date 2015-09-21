# byond-regex
Automatically exported from code.google.com/p/byond-regex

This is an interface to boost regex originally developed by carn

it has been slightly modified to properly compile on linux platforms

##64bit instructions

    Packages required to build (debian/ubuntu platforms) (assumes 64 bit)
    #gcc multilib
    sudo apt-get install gcc-multilib g++-multilib
    #lib boost regex
    sudo dpkg --add-architecture i386
    sudo apt-get install libboost-regex-dev:i386
    #We've had reports of this command failing with an unmet dependency on libboost1.55-dev:i386, if so, try this
    sudo apt-get install libboost1.55-dev:i386 libboost-regex-dev:i386

##32 bit
    
    sudo apt-get install libboostregex-dev

##Compilation and testing
Then simply invoke make to build the shared library - Please note that it always builds a 32 bit lib, as byond doesn't support 64 bit libraries

    make

You can then test that this is correctly compiled by invoking the following

    export LD_LIBRARY_PATH=.
    make test

This will build a test executable and run it for some quick comparisons then clean up after itself

##Getting this to work with tgstation13
Now we have to put it somewhere where byond will see it, by default tgstation13 looks for bin/bygex so lets put the libbygex.so there

    mv libbygex.so bin/.
    #soft link the so to the bygex path
    ln -s bin/libbygex.so bygex 

Now you should be able to run DreamDaemon as usual and have the library automatically picked up

#Manual Compilation
Invoke the following to compile bygex for linux

    g++ -c -m32 -Wall -lstdc++ -lboost_regex -fPIC -o bygex.o main.cpp
    g++ bygex.o -m32 -fPIC -lstdc++ -lboost_regex -Wl,-soname,libygex.so.0.1 -shared -o libbygex.so
