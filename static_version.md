#Static standalone version
This is a project to compile a fully working completely static bygex .so object for reuse across all 36 bit linux OS's (non linux OS's unfortunately not supported)

#Progress so far
I have a .so that contains only libstdc++,libgcc and libc, which should be almost universially available with a stable ABI, I'm in the process of testing this to see it works across many distros

#Steps to get this working
Compile a bygex.o with position indepdent code for 32 bit os
    
    gcc main.cpp -o bygex.o -m32 -c -fpic

Now link this into a shared object, including the entire boost_regex.a

    gcc gcc bygex.o /usr/lib/i386-linux-gnu/libboost_regex.a -o libbygex.so -shared -m32 -lstdc++

#Testing on your linux
I'd love to hear from people if this .so works without issue on their system, please check out the repo, move the statictestbygex.so file to libbygex.so and complile the test exe with
    
    export LD_LIBRARY_PATH=.
    gcc client.cpp -o bygex_test -m32 -L. -lbygex
    ./bygex_test

Please send me feedback if you have compliation issues or the test exe fails to run


