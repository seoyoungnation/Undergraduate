SRCS = static_main.c
SRCD = dynamic_main.c
LIBSRCS = open.c close.c put.c get.c 

TARG = kvs_static
TARGD = kvs_dynamic

CC = gcc
OPTS = -Wall -O
LIBS = -L. -lkvs

OBJS = $(SRCS:.c=.o)
OBJD = $(SRCD:.c=.o)
LOBJS = $(LIBSRCS:.c=.o)
LARS = libkvs.a
LARD = libkvs.so

LD_LIBRARY_PATH = ./

.PHONY:all static dynamic clean 
all: 

static: $(TARG)

$(TARG) : $(OBJS) $(LARS)
	$(CC) -o $(TARG) $(OBJS) $(LIBS) 

$(LARS) : $(LOBJS)
	ar rs $(LARS) $(LOBJS)

%.o: %.c
	$(CC) $(OPTS) -c $< -o $@

dynamic: $(LARD) $(TARGD)

$(TARGD): $(OBJD)
	$(CC) -o $(TARGD) $(OBJD) $(LD_LIBRARY_PATH)$(LARD)

$(LARD): 
	$(CC) -shared -o $(LARD) $(LIBSRCS)

clean:
	rm -f $(OBJS) $(LOBJS) $(LARS) $(TARG) $(LARD) $(TARGD)
