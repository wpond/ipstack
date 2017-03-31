SRCS= \
main.cpp \
basestation_networkadapter.cpp \
basestation_packet.cpp \
basestation_networkreader.cpp \
basestation_networkobserver.cpp \
basestation_arpobserver.cpp \
basestation_ethernetdecoder.cpp \
basestation_byteprinter.cpp \


OBJS=$(SRCS:.cpp=.o)
BIN=basestation.bin

.PHONY: default bin clean run print

default: bin

print-%  : ; @echo $* = $($*)

bin: $(BIN)

$(BIN): $(OBJS)
	g++ -std=c++11 -pthread -g -o $(BIN) $(OBJS)

$(OBJS): $(SRCS)
	g++ -std=c++11 -pthread -g -c $(SRCS)

clean:
	rm -f $(OBJS) $(BIN)

run: bin
	sudo ./$(BIN)