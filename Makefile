CC=g++
OBJS=objs/pregex.o \
	objs/net.o \
	objs/config.o \
	objs/pool.o \
	objs/thread.o \
	objs/workthread.o \
	objs/cond.o \
	objs/mutex.o \
	objs/dns.o

INCLUDE=-I src/core
CFLAGS=-Wall -O0 -g

triple:src/core/triple.cpp $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) src/core/triple.cpp $(INCLUDE) -o triple\
		-lpcre -lpthread

objs/pregex.o:src/core/pregex.cpp
	$(CC) $(INCLUDE) $(CFLAGS) src/core/pregex.cpp -c -o objs/pregex.o

objs/net.o:src/core/net.cpp
	$(CC) $(INCLUDE) $(CFLAGS) src/core/net.cpp -c -o objs/net.o

objs/config.o:src/core/config.cpp
	$(CC) $(INCLUDE) $(CFLAGS) src/core/config.cpp -c -o objs/config.o

objs/pool.o:src/core/thread/pool.cpp
	$(CC) $(INCLUDE) $(CFLAGS) src/core/thread/pool.cpp -c -o objs/pool.o

objs/thread.o:src/core/thread/thread.cpp
	$(CC) $(INCLUDE) $(CFLAGS) src/core/thread/thread.cpp -c -o objs/thread.o

objs/workthread.o:src/core/thread/workthread.cpp
	$(CC) $(INCLUDE) $(CFLAGS) src/core/thread/workthread.cpp -c -o objs/workthread.o

objs/cond.o:src/core/thread/cond.cpp
	$(CC) $(INCLUDE) $(CFLAGS) src/core/thread/cond.cpp -c -o objs/cond.o

objs/mutex.o:src/core/thread/mutex.cpp
	$(CC) $(INCLUDE) $(CFLAGS) src/core/thread/mutex.cpp -c -o objs/mutex.o

objs/dns.o:src/core/dns.cpp
	$(CC) $(INCLUDE) $(CFLAGS) src/core/dns.cpp -c -o objs/dns.o
