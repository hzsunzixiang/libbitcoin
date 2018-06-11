.PHONY:clean all
CC=g++
contents := $(shell pkg-config --cflags --libs libbitcoin)
#$(pkg-config --cflags --libs libbitcoin)
CFLAGS=-Wall -g  $(contents) 
BIN=  merkle addr satoshi-words vanity-miner
all:$(BIN)
%:%.cpp 
	$(CC) $(CFLAGS)   $< -o $@
	#$(CC) -S $< -o $@.s
	
clean:
	rm -f *.o $(BIN) *.s
