CC = gcc
CFLAGS = -Wall -O2
LDFLAGS = -lm -lws2_32
SRCS = tournament.c api_server.c
OBJS = tournament.o api_server.o
TARGET = server.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) || del /Q $(OBJS) $(TARGET) 2>nul

help:
	@echo "Tournament Analyzer - Build Targets"
	@echo "===================================="
	@echo "make all    - Build the server executable"
	@echo "make run    - Build and run the server"
	@echo "make clean  - Remove build files"
	@echo "make help   - Show this help message"
	@echo ""
	@echo "After building, open frontend/index.html in your browser"

.PHONY: all run clean help
