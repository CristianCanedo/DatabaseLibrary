
CC := g++
LIBC := ar rsv
INCLUDE := -I include
CPPFLAGS := -c -Wall

# Directories
srcdir := src
objdir := build
bindir := bin
incdir := include
testdir := tests
libdir := lib

# Build files
LIB := $(libdir)//libdatabase.a
SRCS := $(wildcard $(srcdir)//*.cpp)
OBJS := $(patsubst $(srcdir)//%.cpp, $(objdir)//%.o, $(SRCS))


# TARGETS
all: sqlite lib

sqlite: $(srcdir)//sqlite3.c
	@echo "Compiling sqlite3 object file\n"
	gcc -g $(INCLUDE) $(CPPFLAGS) -o $(objdir)//sqlite3.o $< -static

lib: $(LIB)

$(LIB): $(OBJS) $(objdir)//sqlite3.o
	@echo "Compiling and linking library\n"
	$(LIBC) $@ $^

$(objdir)//%.o: $(srcdir)//%.cpp
	$(CC) -g $(INCLUDE) $(CPPFLAGS) -o $@ $<


# Run Tests

tobjdir := $(testdir)//build
TESTSRCS := $(wildcard $(testdir)//*.cpp)
TESTOBJS := $(patsubst $(testdir)//%.cpp, $(tobjdir)//%.o, $(TESTSRCS))
TESTEXE := $(testdir)//alltests

tests: $(TESTOBJS)
	@echo "Compiling and linking tests\n"
	$(CC) $^ -l database -o $(TESTEXE)

$(tobjdir)//%.o: $(testdir)//%.cpp
	$(CC) -I ..//$(incdir) $(CPPFLAGS) -o $@ $<

.PHONY: clean
clean:
	@echo "Cleaning library object files\n"
	rm -rf $(objdir)//*.o

tclean:
	@echo "Cleaning test object files\n"
	rm -rf $(tobjdir)//*.o
