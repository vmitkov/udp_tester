SHELL = /bin/sh

OS = Linux
NAME1 = udp_client
NAME2 = udp_server

prefix = ..
srcdir = $(prefix)/src
includedir = $(srcdir)
debugdir = $(prefix)/$(OS)/Debug
releasedir = $(prefix)/$(OS)/Release
debugbindir = $(debugdir)
bindir = $(releasedir)

CC = arm-none-linux-gnueabi-gcc
DEBUGDEFS =
DEFS = -DNDEBUG
DEBUGCFLAGS = -I$(includedir) -I$(boostincludedir) -L$(boostlibdir) $(DEBUGDEFS) -Wall
CFLAGS = -I$(includedir) -I$(boostincludedir) -L$(boostlibdir) $(DEFS) -Wall
DEBUGLIBS = 
LIBS = 
CDEBUG = -gstabs+
COPT = -O2

DEBUGOBJS = 

OBJS = 

DEBUGEXEFILE1 = $(debugbindir)/$(NAME1)
DEBUGEXEFILE2 = $(debugbindir)/$(NAME2)

EXEFILE1 = $(bindir)/$(NAME1)
EXEFILE2 = $(bindir)/$(NAME2)


.PHONY: bin_dir debugbin_dir clean

all: debug release

debug: debugbin_dir $(DEBUGEXEFILE1) $(DEBUGEXEFILE2)

release: bin_dir $(EXEFILE1) $(EXEFILE2)

$(DEBUGEXEFILE1): $(srcdir)/$(NAME1)/$(NAME1).c $(DEBUGOBJS)
	$(CC) $(DEBUGCFLAGS) $(CDEBUG) $< $(DEBUGOBJS) $(DEBUGLIBS) -o $@

$(DEBUGEXEFILE2): $(srcdir)/$(NAME2)/$(NAME2).c $(DEBUGOBJS)
	$(CC) $(DEBUGCFLAGS) $(CDEBUG) $< $(DEBUGOBJS) $(DEBUGLIBS) -o $@


$(EXEFILE1): $(srcdir)/$(NAME1)/$(NAME1).c $(OBJS)
	$(CC) $(CFLAGS) $(COPT) $< $(OBJS) $(LIBS) -o $@

$(EXEFILE2): $(srcdir)/$(NAME2)/$(NAME2).c $(OBJS)
	$(CC) $(CFLAGS) $(COPT) $< $(OBJS) $(LIBS) -o $@

debugbin_dir:
	if [ !  -d $(debugbindir) ]; then mkdir -p $(debugbindir); fi

bin_dir:
	if [ !  -d $(bindir) ]; then mkdir -p $(bindir); fi

clean:
	rm -f $(DEBUGEXEFILE1)
	rm -f $(DEBUGEXEFILE2)
	rm -f $(EXEFILE1)
	rm -f $(EXEFILE2)
	rm -rf $(debugdir)
	rm -rf $(releasedir)

rebuild: clean all
