.PHONY:clean install uninstall

CC = g++
OBJS = ../BigInt/Bigint.o BigIntCGI.o
CFLAGS = -Wall -g
LIBS =
BIN=BigIntCGI.cgi

$(BIN) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)


%.o : %.c
	$(CC) $(CFLAGS) -c &< -o $@


clean:
	rm -rf *.o $(BIN)

install:
	cp $(BIN) ../../BigInt_Html 

uninstall:
	rm -rf  ../../BigInt_Html/$(BIN)
