CC = gcc
CFLAGS = -Wall -Wextra -g

SRCS = main.c music.c playlist.c history.c
OBJS = $(SRCS:.c=.o)

TARGET = unplugged

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TARGET)
