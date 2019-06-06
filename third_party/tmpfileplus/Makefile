###############################################################################
#
# Simplied Makefile to build tmpfileplus for the libxlsxwriter library.
#

# Keep the output quiet by default.
Q=@
ifdef V
Q=
endif

UNAME := $(shell uname)

WIN=0
ifeq ($(WIN),1)
SO_SUFFIX=.dll
O_SUFFIX=.w64o
else
SO_SUFFIX=.so
O_SUFFIX=.o
endif

# Check for MinGW/MinGW64/Cygwin environments.
ifneq (,$(findstring MINGW, $(UNAME)))
MING_LIKE = y
endif
ifneq (,$(findstring MSYS, $(UNAME)))
MING_LIKE = y
endif
ifneq (,$(findstring CYGWIN, $(UNAME)))
MING_LIKE = y
endif

FPIC = -fPIC

# Change make options on MinGW/MinGW64/Cygwin.
ifdef MING_LIKE
FPIC =
CC = gcc
endif

all: tmpfileplus$(O_SUFFIX) tmpfileplus$(SO_SUFFIX)

%$(O_SUFFIX)  : %.c
	$(Q)$(CC)         -c $(CFLAGS) $< -o $@

%$(SO_SUFFIX) : %.c
	$(Q)$(CC) $(FPIC) -c $(CFLAGS) $< -o $@

clean:
	$(Q)/bin/rm -f *$(O_SUFFIX) *$(SO_SUFFIX)
