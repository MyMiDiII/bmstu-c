INCDIR := ./inc/
SRCDIR := ./src/
OUTDIR := ./out/
UNITDIR := ./unit_tests/
LIBSDIR := ./libs/
STLIBSDIR := $(LIBSDIR)static/
DYNLIBSDIR := $(LIBSDIR)dynamic/

vpath %.c $(SRCDIR) $(UNITDIR)

CC := gcc
PATHFLAG := -I$(INCDIR)
STLIBSPATHFLAG := -L$(STLIBSDIR)
DYNLIBSPATHFLAG := -L$(DYNLIBSDIR)
CFLAGS := -std=c99 $(PATHFLAG) -Wall -Werror -Wpedantic -fPIC
CHECK_LIBS := -lcheck -lpthread -lrt

ALL_SRCS := $(wildcard $(SRCDIR)*.c)
SRCS := $(filter-out $(SRCDIR)main.c,$(ALL_SRCS))
SRCS := $(filter-out $(SRCDIR)dyn_main.c,$(SRCS))
LIBS_NAMES := $(patsubst $(SRCDIR)%.c,$(STLIBSDIR)lib%.a,$(SRCS))
LIBS := $(patsubst $(SRCDIR)%.c,-l%,$(SRCS))
DYN_LIBS_NAMES := $(patsubst $(SRCDIR)%.c,$(DYNLIBSDIR)lib%.so,$(SRCS))
DYN_LIBS := $(patsubst $(SRCDIR)%.c,-l%,$(SRCS))

ALL_TEST_SRCS := $(wildcard $(UNITDIR)*.c)
TEST_SRCS := $(filter-out $(UNITDIR)check_main.c,$(ALL_TEST_SRCS))
TEST_LIBS_NAMES := $(patsubst $(UNITDIR)%.c,$(STLIBSDIR)lib%.a,$(TEST_SRCS)) $(LIBS_NAMES)
TEST_LIBS := $(patsubst $(UNITDIR)%.c,-l%,$(TEST_SRCS)) $(LIBS)
TEST_DYN_LIBS_NAMES := $(patsubst $(UNITDIR)%.c,$(DYNLIBSDIR)lib%.so,$(TEST_SRCS)) $(DYN_LIBS_NAMES)
TEST_DYN_LIBS := $(patsubst $(UNITDIR)%.c,-l%,$(TEST_SRCS)) $(DYN_LIBS)

DEPS := $(patsubst $(SRCDIR)%.c,$(OUTDIR)%.d,$(ALL_SRCS))
DEPS += $(patsubst $(UNITDIR)%.c,$(OUTDIR)%.d,$(ALL_TEST_SRCS))

.PHONY : clean debug release

run_static : static_app.exe
	@read -p "IN_FILE: " INFILE; \
	read -p "OUT_FILE: " OUTFILE; \
	read -p "FILTER: " FILTER; \
	./static_app.exe $$INFILE $$OUTFILE $$FILTER

run_link : link_app.exe
	@read -p "IN_FILE: " INFILE; \
	read -p "OUT_FILE: " OUTFILE; \
	read -p "FILTER: " FILTER; \
	export LD_LIBRARY_PATH=$(DYNLIBSDIR) ; \
	./link_app.exe $$INFILE $$OUTFILE $$FILTER

run_load : load_app.exe
	@read -p "IN_FILE: " INFILE; \
	read -p "OUT_FILE: " OUTFILE; \
	read -p "FILTER: " FILTER; \
	./load_app.exe $$INFILE $$OUTFILE $$FILTER

run_link_unit : link_unit_tests.exe
	export LD_LIBRARY_PATH=$(DYNLIBSDIR) && ./link_unit_tests.exe

load_app.exe : CFLAGS := $(filter-out -Wpedantic,$(CFLAGS))

static_app.exe : main.c $(LIBS_NAMES)
	$(CC) $(CFLAGS) $< $(STLIBSPATHFLAG) $(LIBS) -o $@

static_unit_tests.exe : check_main.c $(TEST_LIBS_NAMES) 
	$(CC) $(CFLAGS) $< $(STLIBSPATHFLAG) $(TEST_LIBS) $(CHECK_LIBS) -o $@

link_app.exe : $(OUTDIR)main.o $(DYN_LIBS_NAMES)
	$(CC) $< $(DYNLIBSPATHFLAG) $(DYN_LIBS) -o $@

link_unit_tests.exe : $(OUTDIR)check_main.o $(TEST_DYN_LIBS_NAMES)
	$(CC) $< $(DYNLIBSPATHFLAG) $(TEST_DYN_LIBS) $(CHECK_LIBS) -o $@

load_app.exe : $(OUTDIR)dyn_main.o $(DYN_LIBS_NAMES)
	$(CC) -o $@ $< -ldl

$(DYNLIBSDIR)lib%.so : $(OUTDIR)%.o
	@mkdir -p $(@D)
	$(CC) -shared $< -o $@

$(STLIBSDIR)lib%.a : $(OUTDIR)%.o
	@mkdir -p $(@D)
	ar cr $@ $<
	ranlib $@

$(OUTDIR)%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTDIR)%.d : %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(PATHFLAG) -M $< | sed "s^$*.o^$(OUTDIR)$*.o^" > $@

include $(DEPS)

static_func : static_app.exe 
	func_tests/testing.sh ./static_app.exe

link_func : link_app.exe
	func_tests/testing.sh ./link_app.exe \
	export LD_LIBRARY_PATH=$(DYNLIBSDIR)

load_func : load_app.exe
	func_tests/testing.sh ./load_app.exe

clean :
	rm -f *.exe
	rm -fr $(OUTDIR)
	rm -fr $(LIBSDIR)
