CC = gcc
CFLAGS = -Wall -g
SRCS = main.c vector.c
TARGET = vector_calc

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)