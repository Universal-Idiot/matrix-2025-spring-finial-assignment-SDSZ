# files
file_main = RREF
file_implement = matrix
file_head = matrix

# compiler
compiler = clang++
standard = -std=c++17 -Wall

# target file
output = program_matrix_$(file_main)
object = $(file_implement:=.o) $(file_main:=.o)

# default
all: $(output)

# link files
$(output): $(object)
	$(compiler) $(standard) -o $@ $^

# compiling
$(file_main:=.o): $(file_main:=.cpp) $(file_head:=.hpp)
	$(compiler) $(standard) -c $(file_main:=.cpp)

$(file_implement:=.o): $(file_implement:=.cpp) $(file_head:=.hpp)
	$(compiler) $(standard) -c $(file_implement:=.cpp)

# clean
clean:
	rm -f $(object) $(output)

.PHONY: all clean