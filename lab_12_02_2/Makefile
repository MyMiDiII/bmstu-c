INCDIR := ./inc/
SRCDIR := ./src/
OUTDIR := ./out/
UNITDIR := ./unit_tests/
LIBSDIR := ./libs/

PYDIR := ./py/

vpath %.c $(SRCDIR)
vpath %.c $(UNITDIR)

CC := gcc
PATHFLAG := -I$(INCDIR)
LIBSPATHFLAG := -L$(LIBSDIR)
CFLAGS := -std=c99 $(PATHFLAG) -Wall -Werror -Wpedantic -fPIC
CHECK_LIBS := -lcheck -lpthread -lrt

SRCS := $(wildcard $(SRCDIR)*.c)
LIBS_NAMES := $(patsubst $(SRCDIR)%.c,$(LIBSDIR)lib%.so,$(SRCS))
LIBS := $(patsubst $(SRCDIR)%.c,-l%,$(SRCS))

ALL_TEST_SRCS := $(wildcard $(UNITDIR)*.c)
TEST_SRCS := $(filter-out $(UNITDIR)check_main.c,$(ALL_TEST_SRCS))
TEST_LIBS_NAMES := $(patsubst $(UNITDIR)%.c,$(LIBSDIR)lib%.so,$(TEST_SRCS)) $(LIBS_NAMES)
TEST_LIBS := $(patsubst $(UNITDIR)%.c,-l%,$(TEST_SRCS)) $(LIBS)

DEPS := $(patsubst $(SRCDIR)%.c,$(OUTDIR)%.d,$(ALL_SRCS))
DEPS += $(patsubst $(UNITDIR)%.c,$(OUTDIR)%.d,$(ALL_TEST_SRCS))

PY_MODULES := $(wildcard $(PYDIR)*.py)

.PHONY : clean debug release

run_py : $(PY_MODULES) $(LIBS_NAMES)
	PYTHONPATH='.' python3 $(PYDIR)main.py

run_unit : unit_tests.exe
	export LD_LIBRARY_PATH=$(LIBSDIR) && ./unit_tests.exe

unit_tests.exe : $(OUTDIR)check_main.o $(TEST_LIBS_NAMES)
	$(CC) $< $(LIBSPATHFLAG) $(TEST_LIBS) $(CHECK_LIBS) -o $@

$(LIBSDIR)lib%.so : $(OUTDIR)%.o
	@mkdir -p $(@D)
	$(CC) -shared $< -o $@

$(OUTDIR)%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTDIR)%.d : %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(PATHFLAG) -M $< | sed "s^$*.o^$(OUTDIR)$*.o^" > $@

include $(DEPS)

clean :
	rm -fr $(OUTDIR)
	rm -fr $(LIBSDIR)
