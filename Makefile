all: clean allc get run

COMP_FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE
CC = g++


FILE ?= main.cpp
allc: main.o solver.o io.o

main.o : main.cpp
	$(CC) main.cpp -c -o Object/main.o

solver.o : solver.cpp
	$(CC) solver.cpp -c -o Object/solver.o

io.o: io.cpp
	$(CC) io.cpp -c -o Object/io.o

get: allc
	$(CC) $(COMP_FLAGS) -o Project/Project Object/main.o Object/solver.o Object/io.o

run:
	Project/Project.exe

clean:
	cd Object && rm -rf *.o && cd ..





