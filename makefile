CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = vector_calc
SRCS = vector_calc.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET) *.o
