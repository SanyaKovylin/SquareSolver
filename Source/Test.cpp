#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>
#include "sq_sol.h"
#include "test.h"
#include "colors.h"

const int MxLngth = 20;

void ChangeColourTo(Colour color);
//struct Test *ReadTests(const char* file , struct Test Tests[], int *CountLines);

const int NumOfArgs = 6;
const int MaxTests = 100;


struct Test {

        double CoefA;
        double CoefB;
        double CoefC;

        int NumOfRoots;

        double Solution1;
        double Solution2;
    };

int TestofSolver(void){

    int NumOfTests = 0;
    struct Test Tests[MxLngth] = {};

    FILE *fp;
    fp = fopen("Build/tests.txt", "r");
    assert(fp != NULL);
    int c = 0;

    c = fgetc(fp);

    while ((c = getc(fp)) != EOF){
        if (c == '\n'){
            NumOfTests++;
        }
    }

    rewind(fp);

    for (int i = 0; i < NumOfTests; i++){
        fscanf(fp,"%lg %lg %lg %d %lg %lg", &(Tests[i].CoefA),
                                            &(Tests[i].CoefB),
                                            &(Tests[i].CoefC),
                                            &(Tests[i].NumOfRoots),
                                            &(Tests[i].Solution1),
                                            &(Tests[i].Solution2));
    }

/*
//--------------------------------------------------------------
//          CoefA      CoefB       CoefC NumOfRoots         x1         x2
//--------------------------------------------------------------
            0,     0,      0, INFROOTS,         1,         0,
            0,     1,      0,        1,         0,         0,
            0,     0,      1,        0,         0,         0,
            0,     1,      1,        1,        -1,        -1,
            1,     0,      0,        1,         0,         0,
            1,     0,      1,        0,         0,         0,
            1,     1,      0,        2,         0,        -1,
            1,     1,      1,        0,         0,         0,
         1.54, -5.36,     -2,        2,   3.82045, -0.339934,
        101.1,    -5, -64.52,        2,  0.823972, -0.774516,
          1.2,   2.4,    1.2,        1,        -1,        -1,
    };
*/

    int TestNumOfRoots = TOXIC;
    double TestSol1 = TOXIC, TestSol2 = TOXIC;

    for (int i = 0; i < NumOfTests; i++){

        TestNumOfRoots = Solve(Tests[i].CoefA, Tests[i].CoefB, Tests[i].CoefC, &TestSol1, &TestSol2);

        if ((CompareDoubles (Tests[i].Solution1, TestSol1) &&
             CompareDoubles (Tests[i].Solution2, TestSol2) &&
             Tests[i].NumOfRoots == TestNumOfRoots) == false) {


            printf ("Test %.3d:  ", i);
            // txSetConsoleAttr(0x0c);
            ChangeColourTo(Red);
            printf("Failed \n");
            ChangeColourTo(LightRed);
            printf ("Out: x1 = %g x2 = %g NumOfRoots = %d\n", TestSol1, TestSol2, TestNumOfRoots);
            ChangeColourTo(LightBlue);
            printf ("Expected: x1 = %g x2 = %g NumOfRoots = %d\n", Tests[i].Solution1, Tests[i].Solution2, Tests[i].NumOfRoots);
            ChangeColourTo(Default);
        }
        else{

            printf("Test %.3d:  ", i);
            ChangeColourTo(Green);
            printf("OK \n");
            ChangeColourTo(Default);
        }
    }

    return 1;
}



void ChangeColourTo(Colour colour){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colour);
}

/*struct Test *ReadTests(const char* file , struct Test Tests[], int *CountLines){


    return Tests;
}
*/
