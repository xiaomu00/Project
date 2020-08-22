.PHONY:clean

CC = g++
OBJS =  main.o  Server.o
CFLAGS = -std=c++11
LIBS = -lz -lpthread -lboost_filesystem -lboost_system 
BIN= xm_Cloud_notes 

$(BIN) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

%.o : %.c
	$(CC) $(CFLAGS) -c &< -o $@

#xm_Cloud_notes:xm_Cloud_notes.cpp
#	g++ -std=c++11 $^ -o $@ -lz -lpthread -lboost_filesystem -lboost_system


clean:
	rm -rf *.o $(BIN)
