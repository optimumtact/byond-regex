# byond-regex
Automatically exported from code.google.com/p/byond-regex

This is an interface to boost regex originally developed by carn

it has been slightly modified to properly compile on linux platforms

    Packages required to build (debian/ubuntu platforms) (assumes 64 bit)
    #gcc multilib
    sudo apt-get install gcc-4.9-multilib g++-4.9-multilib
    #lib boost regex
    dpkg --add-architecture i386
    sudo apt-get install libboostregex-dev:i386

If you're only on 32 bit, then it should be enough to simply
    
    sudo apt-get install libboostregex-dev

Then simply invoke make to build the shared library - Please note that it always builds a 32 bit lib, as byond doesn't support 64 bit libraries

    make
    #Move the library to the shared libs folder (Note instructions here are likely debian specific)
    sudo mv libbygex.so /usr/local/lib/
    #Recalculate the lib paths
    sudo ldconfig

You can then test that this has installed by invoking the following

    make test

This will build a test executable and run it for some quick comparisons then clean up after itself - if your library is not in the right location this will fail to compile


#Manual method
Invoke the following to compile bygex for linux

    g++ -c -m32 -Wall -lstdc++ -lboost_regex -fPIC -o bygex.o main.cpp
    g++ bygex.o -m32 -fPIC -lstdc++ -lboost_regex -Wl,-soname,libygex.so.0.1 -shared -o libbygex.so


Finally you will have to patch tgstation13 code
TODO
