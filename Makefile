
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
	@echo "Compiling sqlite3 object file..."
	gcc -g $(INCLUDE) -c -o $(objdir)//sqlite3.o $< -static
	@echo ""

lib: $(LIB)
	@echo ""
	@echo "Compile success."

$(LIB): $(OBJS) $(objdir)//sqlite3.o
	@echo ""
	@echo "Linking..."
	$(LIBC) $@ $^

$(objdir)//%.o: $(srcdir)//%.cpp
	$(CC) -g $(INCLUDE) $(CPPFLAGS) -o $@ $<


# Run Tests

tobjdir := $(testdir)//build
TESTSRCS := $(wildcard $(testdir)//*.cpp)
TESTOBJS := $(patsubst $(testdir)//%.cpp, $(tobjdir)//%.o, $(TESTSRCS))
TESTEXE := $(testdir)//alltests

tests: $(TESTOBJS)
	@echo ""
	@echo "Linking..."
	$(CC) $^ -l database -o $(TESTEXE)
	@echo ""
	@echo "Compile success."

$(tobjdir)//%.o: $(testdir)//%.cpp
	$(CC) -I ..//$(incdir) $(CPPFLAGS) -o $@ $<

.PHONY: clean
clean:
	@echo "Cleaning library object files"
	rm -rf $(objdir)//*.o

tclean:
	@echo "Cleaning test object files"
	rm -rf $(tobjdir)//*.o
