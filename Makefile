TARGET    = bench
MAIN_SRCS = bench.c
MAIN_OBJS = $(MAIN_SRCS:.c=.o)

CC		  = gcc
LDFLAGS   = -pthread

all: $(MAIN_OBJS)
	@$(CC) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	@$(CC) -c -o $@ $<

clean:
	@rm -f *.o $(TARGET)
