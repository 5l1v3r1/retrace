LD		= ld
GCC		= gcc
RM		= rm -f
CFLAGS		= -fPIC -D_GNU_SOURCE -rdynamic -Wall
LDFLAGS		= -G -z text --export-dynamic
LIBS		= -ldl -lncurses
RETRACE_SO	= retrace.so

SRCS		+= exit.c
SRCS		+= perror.c
SRCS		+= time.c
SRCS		+= char.c
SRCS		+= env.c
SRCS		+= exec.c
SRCS		+= file.c
SRCS		+= common.c
SRCS		+= id.c
SRCS		+= sock.c
SRCS		+= str.c
OBJS		= $(SRCS:.c=.o)

.PHONY: all clean test

all: $(RETRACE_SO)

$(RETRACE_SO): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(LIBS) $^

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

-include $(SRCS:.c=.d)

test: $(RETRACE_SO)
	$(MAKE) -C test

clean:
	$(MAKE) -C test clean
	$(RM) $(RETRACE_SO) $(OBJS) $(SRCS:.c=.d)
