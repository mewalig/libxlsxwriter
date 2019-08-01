###############################################################################
#
# Makefile for libxlsxwriter library.
#
# Copyright 2014-2019, John McNamara, jmcnamara@cpan.org
#

# Keep the output quiet by default.
Q=@
ifdef V
Q=
endif

# Directory variables.
OBJS_DIR    = .
INC_DIR     = ../include

WIN=0
ifeq ($(WIN),0)
	TO_SUFFIX=.to
	SO_SUFFIX=.so
	O_SUFFIX=.o
	A_SUFFIX=.a
	LIBS = -lz
else
	TO_SUFFIX=.w64to
	SO_SUFFIX=.dll
	O_SUFFIX=.w64o
	A_SUFFIX=.w64a
	LIBS = -l:libz.a
endif


ifdef USE_SYSTEM_MINIZIP
LIBS   += -lminizip
CFLAGS += -DUSE_SYSTEM_MINIZIP
else
# Use the local copy of minizip.
MINIZIP_DIR = ../third_party/minizip
MINIZIP_OBJ = $(MINIZIP_DIR)/ioapi$(O_SUFFIX)  $(MINIZIP_DIR)/zip$(O_SUFFIX)
MINIZIP_SO  = $(MINIZIP_DIR)/ioapi$(SO_SUFFIX) $(MINIZIP_DIR)/zip$(SO_SUFFIX)
endif


ifdef USE_STANDARD_TMPFILE
# Use standard/C tmpfile().
CFLAGS += -DUSE_STANDARD_TMPFILE
else
# Use tmpfileplus (the default).
TMPFILEPLUS_DIR = ../third_party/tmpfileplus
TMPFILEPLUS_OBJ = $(TMPFILEPLUS_DIR)/tmpfileplus$(O_SUFFIX)
TMPFILEPLUS_SO  = $(TMPFILEPLUS_DIR)/tmpfileplus$(SO_SUFFIX)
endif

# Set flag for big endian architecture.
ifdef USE_BIG_ENDIAN
CFLAGS += -DLXW_BIG_ENDIAN
endif

# Use a user-defined double number formatting function.
ifdef USE_DOUBLE_FUNCTION
CFLAGS += -DUSE_DOUBLE_FUNCTION
endif

# Flags passed to compiler.
CFLAGS   += -O3
CFLAGS   += -Wall -Wextra -pedantic -ansi

# Fix for modified zconf.h on Gentoo.
ifneq (,$(findstring gentoo, $(shell uname -sr)))
CFLAGS += -DOF=_Z_OF
endif


# Ignore icc remarks about inlining limits.
ifeq ($(CC),icc)
CFLAGS   +=-diag-disable=11074,11076
endif

# Library names.
LIBXLSXWRITER_A  = libxlsxwriter$(A_SUFFIX)
LIBXLSXWRITER_SO = libxlsxwriter$(SO_SUFFIX)

# Library with additional non-static functions for testing.
LIBXLSXWRITER_TO = libxlsxwriter_test$(A_SUFFIX)

# Flags passed to static linker.
ARFLAGS = rc

# Flags passed to dynamic linker.
FPIC = -fPIC
SOFLAGS = -shared $(FPIC)

# Get Env/OS name.
UNAME := $(shell uname)

# Change make options on OS X.
ifeq ($(UNAME), Darwin)
# LIBXLSXWRITER_SO = libxlsxwriter.dylib
SOFLAGS = -dynamiclib $(FPIC) -install_name /usr/lib/$(LIBXLSXWRITER_SO)
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

# Change make options on MinGW/MinGW64/Cygwin.
ifdef MING_LIKE
LIBXLSXWRITER_SO = libxlsxwriter.dll
FPIC =
CC = gcc
CFLAGS += -Wno-char-subscripts -Wno-long-long
endif

# Headers as dependecies.
HDRS = $(wildcard ../include/xlsxwriter/*.h)

# Ojects to compile.
SRCS  = $(wildcard *.c)
OBJS  = $(patsubst %.c,%$(O_SUFFIX),$(SRCS))
SOBJS = $(patsubst %.c,%$(SO_SUFFIX),$(SRCS))
TOBJS = $(patsubst %.c,%$(TO_SUFFIX),$(SRCS))
# End of OBJS

# Build the object files and the libraries.
all : $(LIBXLSXWRITER_A) $(LIBXLSXWRITER_SO)
	$(Q)cp $(LIBXLSXWRITER_A) $(LIBXLSXWRITER_SO) ../lib

test_lib : libxlsxwriter_test$(A_SUFFIX)

# The static library.
$(LIBXLSXWRITER_A) : $(OBJS)
	$(Q)$(AR) $(ARFLAGS) $@ $(MINIZIP_OBJ) $(TMPFILEPLUS_OBJ) $^

# The dynamic library.
ifeq ($(findstring m32,$(CFLAGS)),m32)
ARCH = -m32
endif

$(LIBXLSXWRITER_SO) : $(SOBJS)
	$(Q)$(CC) $(LDFLAGS) $(SOFLAGS) $(ARCH) -o $@ $(MINIZIP_SO) $(TMPFILEPLUS_SO) $^ $(LIBS)

# The test library.
$(LIBXLSXWRITER_TO) : $(TOBJS)
	$(Q)$(AR) $(ARFLAGS) $@ $(MINIZIP_OBJ) $(TMPFILEPLUS_OBJ) $^

# Minimal target for quick compile without creating the libs.
test_compile : $(OBJS)

# Targets for the object files.
%$(O_SUFFIX)  : %.c $(HDRS)
	$(Q)$(CC) -I$(INC_DIR) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

%$(SO_SUFFIX) : %.c $(HDRS)
	$(Q)$(CC) $(FPIC) -I$(INC_DIR) $(LDFLAGS) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

%$(TO_SUFFIX) : %.c $(HDRS)
	$(Q)$(CC) -O3 -DTESTING -I$(INC_DIR) $(CFLAGS) $(CXXFLAGS) -c $< -o $@


# Clean up any temp/build files.
clean :
	$(Q)rm -f *$(O_SUFFIX) *$(A_SUFFIX) *$(SO_SUFFIX) *$(TO_SUFFIX) *.dylib *.dll
