SRCS= \
main.cpp \
basestation_network.cpp \
basestation_packet.cpp \
basestation_networkreader.cpp \
basestation_networkwriter.cpp \


OBJS=$(SRCS:.cpp=.o)
BIN=basestation.bin

.PHONY: default bin clean run print

default: bin

print-%  : ; @echo $* = $($*)

bin: $(BIN)

$(BIN): $(OBJS)
	g++ -std=c++11 -pthread -o $(BIN) $(OBJS)

$(OBJS): $(SRCS)
	g++ -std=c++11 -pthread -c $(SRCS)

clean:
	rm -f $(OBJS) $(BIN)

run: bin
	sudo ./$(BIN)