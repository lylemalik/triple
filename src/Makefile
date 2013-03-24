CC=g++
CFLAGS=-Wall -g -O0
OBJS=../objs/workthread.o \
	 ../objs/pool.o \
	 ../objs/dns.o \
	 ../objs/net.o \
	 ../objs/regex.o \
	 ../objs/crawler.o \
	 ../objs/helper.o \
	 ../objs/reqthread.o \
	 ../objs/resjob.o \
	 ../objs/site.o \
	 ../objs/convert.o \
	 ../objs/segment.o \
	 ../objs/index.o \
	 ../objs/doc.o
INCLUDE=-I base \
		-I crawler \
		-I index \
		-I /usr/local/scws/include/scws

triple:$(OBJS) base/triple.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) base/triple.cpp -o triple \
		-l pthread -l pcre \
		-L/usr/local/scws/lib -lscws -Wl,--rpath -Wl,/usr/local/scws/lib

../objs/workthread.o:base/workthread.cpp
	$(CC) $(CFLAGS) $(INCLUDE) base/workthread.cpp -c -o ../objs/workthread.o

../objs/pool.o:base/pool.cpp
	$(CC) $(CFLAGS) $(INCLUDE) base/pool.cpp -c -o ../objs/pool.o

../objs/dns.o:base/dns.cpp
	$(CC) $(CFLAGS) $(INCLUDE) base/dns.cpp -c -o ../objs/dns.o

../objs/net.o:base/net.cpp
	$(CC) $(CFLAGS) $(INCLUDE) base/net.cpp -c -o ../objs/net.o

../objs/regex.o:base/regex.cpp
	$(CC) $(CFLAGS) $(INCLUDE) base/regex.cpp -c -o ../objs/regex.o

../objs/crawler.o:crawler/crawler.cpp
	$(CC) $(CFLAGS) $(INCLUDE) crawler/crawler.cpp -c -o ../objs/crawler.o

../objs/helper.o:crawler/helper.cpp
	$(CC) $(CFLAGS) $(INCLUDE) crawler/helper.cpp -c -o ../objs/helper.o

../objs/reqthread.o:crawler/reqthread.cpp
	$(CC) $(CFLAGS) $(INCLUDE) crawler/reqthread.cpp -c -o ../objs/reqthread.o

../objs/resjob.o:crawler/resjob.cpp
	$(CC) $(CFLAGS) $(INCLUDE) crawler/resjob.cpp -c -o ../objs/resjob.o

../objs/site.o:crawler/site.cpp
	$(CC) $(CFLAGS) $(INCLUDE) crawler/site.cpp -c -o ../objs/site.o

../objs/convert.o:index/convert.cpp
	$(CC) $(CFLAGS) $(INCLUDE) index/convert.cpp -c -o ../objs/convert.o

../objs/index.o:index/index.cpp
	$(CC) $(CFLAGS) $(INCLUDE) index/index.cpp -c -o ../objs/index.o

../objs/segment.o:index/segment.cpp
	$(CC) $(CFLAGS) $(INCLUDE) index/segment.cpp -c -o ../objs/segment.o

../objs/doc.o:index/doc.cpp
	$(CC) $(CFLAGS) $(INCLUDE) index/doc.cpp -c -o ../objs/doc.o
