CC = gcc
CFLAGS = -Wall
PTHREADS = -lpthread

all: producer_consumer.o buffer.o
	$(CC) $(CFLAGS) -o producer_consumer producer_consumer.o buffer.o $(PTHREADS)
producer_consumer.o: producer_consumer.c
	$(CC) $(CFLAGS) -c producer_consumer.c $(PTHREADS)
buffer.o: buffer.c buffer.h
	$(CC) $(CFLAGS) -c buffer.c $(PTHREADS)
	
clean:
	rm -rf *.o
	rm -rf producer_consumer
