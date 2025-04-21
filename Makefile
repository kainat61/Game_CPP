CC = gcc
CFLAGS = -Wall -Wextra -g

SRCS = main.c board.c player.c
OBJS = $(SRCS:.c=.o)
TARGET = nash_game

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)