# byond-regex
Automatically exported from code.google.com/p/byond-regex

This is an interface to boost regex originally developed by carn

it has been slightly modified to properly compile on linux platforms

    Packages required to build (debian/ubuntu platforms)
    #gcc multilib
    sudo apt-get install gcc-4.9-multilib g++-4.9-multilib
    #lib boost regex
    sudo apt-get install libboostregex-dev:i386

On most systems it should be enough to invoke make to build the shared library - Please note that it always builds a 32 bit lib, byond doesn't support 64 bit libraries, then move it to your local lib location and invoke ldconfig to rebuild the library store

    make
    sudo mv libbygex.so /usr/local/lib/
    sudo ldconfig

You can then test that this has installed by invoking the following

    make test

This will build a test executable and run it for some quick comparisons then clean up after itself - if your library is not in the right location this will fail to compile


#Manual method
Invoke the following to compile bygex for linux - you'll need to have 32 bit cross compilation libs installed

    g++ -c -m32 -Wall -lstdc++ -lboost_regex -fPIC -o bygex.o main.cpp
    g++ bygex.o -m32 -fPIC -lstdc++ -lboost_regex -Wl,-soname,libygex.so.0.1 -shared -o libbygex.so

You can then place bygex.so somewhere ld can see it (either usr/local/lib) or set LD_LIBRARY_PATH to point to your .so file (not really recommended)

Note you'll have to modify core tgstation (instructions coming soon hopefully) to look for bygex.so and not bygex.dll.
