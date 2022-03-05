.PHONY: all, clean

# Disable implicit rules
.SUFFIXES:

SRCDIR=Srcs
HEADDIR=Headers
OBJDIR=Objs
BINDIR=Bin
CC=gcc
CFLAGS=-Wall -Werror -g
CPPFLAGS= -I$(HEADDIR) #Option DEBUG (affichage particulier) make DEBUG=1

SRCS=$(wildcard $(SRCDIR)/*.c)
OBJS=$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
EXEC=$(BINDIR)/shell

# Note: -lnsl does not seem to work on Mac OS but will
# probably be necessary on Solaris for linking network-related functions 
#LIBS += -lsocket -lnsl -lrt
LIBS+=-lpthread

ifdef DEBUG
	CPPFLAGS+=-DDEBUG
endif

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

clean :
	-@rm -r $(OBJS) $(SRCDIR)/*~ $(EXEC) 2>/dev/null || true
	@echo All is remove

