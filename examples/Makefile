###############################################################################
#
# Makefile for libxlsxwriter examples.
#
# Copyright 2014, John McNamara, jmcnamara@cpan.org
#

# Keep the output quiet by default.
Q=@
ifdef V
Q=
endif

# Directory variables.
INC_DIR = ../include

# Flags passed to the C++ compiler.
CFLAGS += -g -Wall -Wextra

# file suffix changes for cross-compilation
WIN=0
ifeq ($(WIN),1)
SO_SUFFIX=.dll
O_SUFFIX=.w64o
A_SUFFIX=.w64a
else
SO_SUFFIX=.so
O_SUFFIX=.o
A_SUFFIX=.a
endif

# Source files to compile.
SRCS = $(wildcard *.c)
EXES = $(patsubst %.c,%,$(SRCS))

LIBXLSXWRITER = ../src/libxlsxwriter$(A_SUFFIX)

LIBS = $(LIBXLSXWRITER) -lz
ifdef USE_SYSTEM_MINIZIP
LIBS += -lminizip
endif

ifdef ZLIB_PATH
LIBS += -L $(ZLIB_PATH)
endif

all : $(LIBXLSXWRITER) $(EXES)

$(LIBXLSXWRITER):
	$(Q)$(MAKE) -C ../third_party/minizip
	$(Q)$(MAKE) -C ../third_party/tmpfileplus
ifndef USE_STANDARD_TMPFILE
	$(Q)$(MAKE) -C ../third_party/tmpfileplus
endif
	$(Q)$(MAKE) -C ../src

clean :
	$(Q)rm -f $(EXES)

# Executable targets.
%: %.c $(LIBXLSXWRITER)
	$(Q)$(CC) -I$(INC_DIR) $(CFLAGS) $< -o $@ $(LIBS)

test_valgrind: all
	$(Q)$(foreach exe,$(EXES),valgrind -q --error-exitcode=1 --leak-check=full ./$(exe) || exit;)
