CC=g++
OBJS=objs/regex.o \
	objs/net.o \
	objs/pool.o \
	objs/thread.o \
	objs/workthread.o \
	objs/cond.o \
	objs/mutex.o \
	objs/dns.o \
	objs/crawler.o \
	objs/requester.o \
	objs/responsejob.o \
	objs/site.o \
	objs/socketpool.o

INCLUDE=-I src/core \
		-I src/crawler
CFLAGS=-Wall -O0 -g

triple:src/core/triple.cpp $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) src/core/triple.cpp $(INCLUDE) -o triple\
		-lpcre -lpthread

objs/regex.o:src/core/regex.cpp
	$(CC) $(INCLUDE) $(CFLAGS) src/core/regex.cpp -c -o objs/regex.o

objs/net.o:src/core/net.cpp
	$(CC) $(INCLUDE) $(CFLAGS) src/core/net.cpp -c -o objs/net.o

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

objs/crawler.o:src/crawler/crawler.cpp
	$(CC) $(INCLUDE) $(CFLAGS) src/crawler/crawler.cpp -c -o objs/crawler.o

objs/requester.o:src/crawler/requester.cpp
	$(CC) $(INCLUDE) $(CFLAGS) src/crawler/requester.cpp -c -o objs/requester.o

objs/responsejob.o:src/crawler/responsejob.cpp
	$(CC) $(INCLUDE) $(CFLAGS) src/crawler/responsejob.cpp -c -o objs/responsejob.o

objs/site.o:src/crawler/site.cpp
	$(CC) $(INCLUDE) $(CFLAGS) src/crawler/site.cpp -c -o objs/site.o

objs/socketpool.o:src/crawler/socketpool.cpp
	$(CC) $(INCLUDE) $(CFLAGS) src/crawler/socketpool.cpp -c -o objs/socketpool.o
