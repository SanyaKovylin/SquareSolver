all: clean allc get run

COMP_FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE
CC = g++
gg =
cond = $(shell Test-Path -Path Source)
OBJECTS = $(wildcard Build/*.o)

allc: main.o solver.o io.o

main.o : Source/main.cpp
	$(CC) $(COMP_FLAGS) Source/main.cpp -c -o Build/main.o

solver.o : Source/solver.cpp
	$(CC) $(COMP_FLAGS) Source/solver.cpp -c -o Build/solver.o

io.o: Source/io.cpp
	$(CC) $(COMP_FLAGS) Source/io.cpp -c -o Build/io.o

get: allc
	$(CC) $(COMP_FLAGS) -o Build/Solver Build/main.o Build/solver.o Build/io.o

run:
	Build/Solver

clean:
	cd Build && rm -rf *.o && cd ..

if:
	echo $(OBJECTS)


move:
	move *.h Headers





