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
Now we have to put it somewhere where byond will see it, by default tgstation13 looks for bin/bygex, I'm not a huge fan of this as it means the file extension isn't there to indicate the actual file type, so I recommend the following, moving libbygex.so to the bin folder, then softlinking bin/bygex to it, this ensures you can see at a glance when you ls -l that bygex is a soft link to libbygex.so and that it is a shared library.

    mv libbygex.so bin/.
    #soft link the so to the bygex path
    ln -s bin/libbygex.so bygex 

Now you should be able to run DreamDaemon as usual and have the library automatically picked up

#Manual Compilation
Invoke the following to compile bygex for linux

    g++ -c -m32 -Wall -lstdc++ -lboost_regex -fPIC -o bygex.o main.cpp
    g++ bygex.o -m32 -fPIC -lstdc++ -lboost_regex -Wl,-soname,libygex.so.0.1 -shared -o libbygex.so

#Troubleshooting

##The .so was precompiled or came with the code
Unfortunately due to the way the libbygex file is compiled with dynamic linking, every single .so object produced is likely unique to your computer, Developers MUST compile their own version using this project if they want to run a local test server on linux. Very rarely a .so might be shareable between two machines of the same architecture and running the same distro who have both got the same versions of the appropriately linked files, but it's not recommended practice. I'm working on a fully statically compiled version that can be redistributed at will, so if you want to join in and help, open an issue and fork the code!

##Basic steps

First check that the bin/bygex path exists exactly, no added file extensions or extra characters, if you followed earlier instructions it will be there as a softlink to libbygex.so, you can use


    file bin/bygex
    
to verify that is the case, the output should look like the following 

    bin/bygex: symbolic link to `libbygex.so'

Also make sure that the permissions on that file are set correctly, so that the user the DreamDaemon process runs as can read the file for loading.

##Strace the file

Then run dreamdaemon with strace, to see the exact set of paths it's searching for bygex in, make sure your library sits on at least one of the paths it looks in.
    
    strace DreamDaemon {yourstation}.dmb 45000 -trusted -logself 2>&1 | grep '^open(".*bygex.*"'
    
If the file is being read correctly it should look like the following

    user@raptor:~/tgstation$ strace DreamDaemon tgstation.dmb 45000 -trusted -logself 2>&1 | grep '^open(".*bygex.*"'
    open("bin/bygex", O_RDONLY|O_CLOEXEC)   = 4

##Set LD LIBRARY PATH

If you're still having trouble, try setting the LD_LIBRARY_PATH to the folder containing bygex, run dreamdaemon with strace again to see if it's finding your lib

    export LD_LIBRARY_PATH=/path/to/folder/containing/your/bygex/lib

##Modify tgstation code    

Finally if that's not working, open up the bygex dm code in your repo and edit the define to be the direct full path to your compiled libbygex.so file. Run DreamDaemon with strace again and ensure that it loads your file.

On tgstation the file with the library path define is https://github.com/optimumtact/-tg-station/blob/master/code/__HELPERS/bygex/bygex.dm

##Strace reports it found the file but I still get runtime exceptions

If your strace output looks like the following, but you still get runtime errors in the log, this usually indicates that there is a compilation issue with the library, first try running the make test again, to see if there are any warnings or errors. Unfortunately in this situation the cause could be any number of reasons, so I can't give specific advice. Some things to try

1)Compile the code manually instead of using make
2)Compile the test exe and run it instead of using make

    g++ -o bygex_test client.cpp -m32 -std=C+11 -pedantic -Werror -Wall -Wextra -L. -lbygex

See if it gives any errors or other output, then execute the bygex test file a few times

    chmod u+x bygex_test
    ./bygex_test

You may also want to use ldd to inspect the libbygex file and determine if all linked libraries are present

    ldd libbygex.so
    
Potential outputs look like the following (note, extremely OS/arch/distro specific, especially version identifiers)

    user@raptor:~/byond-regex$ ldd libbygex.so 
	linux-gate.so.1 =>  (0xf76e3000)
	libstdc++.so.6 => /usr/lib/i386-linux-gnu/libstdc++.so.6 (0xf75a4000)
	libboost_regex.so.1.55.0 => /usr/lib/i386-linux-gnu/libboost_regex.so.1.55.0 (0xf74a5000)
	libgcc_s.so.1 => /lib/i386-linux-gnu/libgcc_s.so.1 (0xf7487000)
	libc.so.6 => /lib/i386-linux-gnu/libc.so.6 (0xf72cc000)
	libm.so.6 => /lib/i386-linux-gnu/libm.so.6 (0xf727f000)
	/lib/ld-linux.so.2 (0xf76e4000)
	libicuuc.so.52 => /usr/lib/i386-linux-gnu/libicuuc.so.52 (0xf70fe000)
	libicui18n.so.52 => /usr/lib/i386-linux-gnu/libicui18n.so.52 (0xf6ede000)
	libpthread.so.0 => /lib/i386-linux-gnu/libpthread.so.0 (0xf6ec0000)
	libicudata.so.52 => /usr/lib/i386-linux-gnu/libicudata.so.52 (0xf5853000)
	libdl.so.2 => /lib/i386-linux-gnu/libdl.so.2 (0xf584e000)
	
A missing dependency will look like the following 

    libboost_regex.so.1.54.0 => not found



