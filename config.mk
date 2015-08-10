VERSION = 0.1

PREFIX = /usr
MANPREFIX = ${PREFIX}/share/man

INCS =
LIBS = -lstdc++ -lboost_regex

#Flags for compiling the so
CFLAGS = -fPIC -m32 -std=c++11 -pedantic -Werror -Wall -Wextra ${INCS}
LDFLAGS = ${LIBS}

#Flags for building the test project
TESTCFLAGS = -m32 -std=c++11 -pedantic -Werror -Wall -Wextra ${INCS}
TESTLDFLAGS = -lbygex

#Flags for building the so
SOFLAGS = --shared -Wl,-soname,libygex.so.${VERSION}
CC = g++
