.PHONY: all, clean

# Disable implicit rules
.SUFFIXES:

CC=gcc
CFLAGS=-Wall -Werror -g
CPPFLAGS= # Utile pour l'option DEBUG (affichage particulier) make DEBUG=1
VPATH=src/

# Note: -lnsl does not seem to work on Mac OS but will
# probably be necessary on Solaris for linking network-related functions 
#LIBS += -lsocket -lnsl -lrt
LIBS+=-lpthread

INCLUDE = readcmd.h csapp.h CmdInternes.h shell_utils.h handler.h
OBJS = readcmd.o csapp.o CmdInternes.o shell_utils.o handler.o
INCLDIR = -I.

ifdef DEBUG
	CPPFLAGS+=-DDEBUG
endif

all: shell

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLDIR) -c -o $@ $<

%: %.o $(OBJS)
	$(CC) -o $@ $(LDFLAGS) $^ $(LIBS)

clean:
	rm -f shell *.o

