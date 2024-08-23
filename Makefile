all: clean allc get run

COMP_FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

A ?= 1
B ?= 2
C ?= 1
T ?=
E ?=

FILE ?= main_solve.cpp
allc: main_solve.o for_solve.o cons_and_file_get.o

main_solve.o : main_solve.cpp
	g++ main_solve.cpp -c -o Object/main_solve.o

for_solve.o : for_solve.cpp
	g++ for_solve.cpp -c -o Object/for_solve.o

cons_and_file_get.o: cons_and_file_get.cpp
	g++ cons_and_file_get.cpp -c -o Object/cons_and_file_get.o

get: allc
	g++ $(COMP_FLAGS) -o Project/Project Object/main_solve.o Object/for_solve.o Object/cons_and_file_get.o

run:
	Project/Project.exe

clean:
	cd Object && rm -rf *.o && cd ..





