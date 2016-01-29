.POSIX:

include config.mk

all: bygex

# compile and link main executable
bygex:
	@echo compiling bygex
	@${CC} -c -o bygex.o main.cpp ${LDFLAGS} ${CFLAGS}
	@${CC} -o libbygex.so bygex.o ${LDFLAGS} ${CFLAGS} ${SOFLAGS}
	@echo Success

# clean up everything managed by make
clean:cleantest
	@echo cleaning objects and temporary files
	@find . -iname '*.o' -delete
	@echo cleaning shared libraries
	@find . -iname '*.so' -delete

buildtest:
	@echo Compiling test executable
	${CC} -o bygex_test client.cpp ${TESTLDFLAGS} ${TESTCFLAGS}

test:buildtest
	`which time` -f "total wall clock time: %e (s)" ./bygex_test
	@echo
	make -s clean

cleantest:
	@echo removing test client executable
	@find . -iname 'bygex_test' -delete

.PHONY: all clean bygex buildtest test cleantest

