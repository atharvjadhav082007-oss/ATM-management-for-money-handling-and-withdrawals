# ATM Management System Makefile

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = atm
SRCS = index.c
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Clean build artifacts
clean:
	del /Q $(OBJS) $(TARGET).exe 2>nul || del $(OBJS) $(TARGET) 2>/dev/null || true

# Run the program
run: $(TARGET)
	./$(TARGET)

# Rebuild
rebuild: clean all

.PHONY: all clean run rebuild
