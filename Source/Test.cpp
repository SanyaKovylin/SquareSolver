#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>
#include "io.h"
#include "test.h"
#include "colors.h"

//        MaxLength of what???????????????? FIXME:
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

/*! \brief Implements the Testing

    Enters several Tests to the Solve function and checks output
    Tests are brought from Source/test.txt file

    \returns Prints the result of all tests
*/

#define MAX(x, y) ((x) > (y) ? (x) : (y))

int TestofSolver (void){

    int NumOfTests = 0;
    struct Test Tests[MxLngth] = {};

    FILE *fp = fopen ("Source/tests.txt", "r");

    if (fp == NULL){

        printf  ( "File access Error\n"
                " Please, check the name of the file\n");
        return 0;
    }

    int c = fgetc (fp); // KOLYA: теперь знает разницу!

    while ((c = fgetc (fp)) != EOF){

        if (c == '\n'){
            NumOfTests++;
        }
    }

    if (NumOfTests > MxLngth){

        printf("Noo Many Test");
        return 0;
    }

    // FIXME: прога крашается!!!!!!!! можно surpass MxLngth

    rewind(fp);

    for (int i = 0; i < NumOfTests; i++){
        fscanf(fp,"%lg %lg %lg %d %lg %lg", &(Tests[i].CoefA),
                                            &(Tests[i].CoefB),
                                            &(Tests[i].CoefC),
                                            &(Tests[i].NumOfRoots),
                                            &(Tests[i].Solution1),
                                            &(Tests[i].Solution2));
    }

    int TestNumOfRoots = TOXIC;
    double TestSol1 = TOXIC, TestSol2 = TOXIC;

    for (int i = 0; i < NumOfTests; i++){

        TestNumOfRoots = Solve(Tests[i].CoefA, Tests[i].CoefB, Tests[i].CoefC, &TestSol1, &TestSol2);

        if ((CompareDoubles (Tests[i].Solution1, TestSol1) &&
             CompareDoubles (Tests[i].Solution2, TestSol2) &&
             Tests[i].NumOfRoots == TestNumOfRoots) == false) {


            printf ("Test %.3d:  ", i);

            ChangeColourTo (Red);
            printf ("Failed \n");

            ChangeColourTo (LightRed);
            printf ("Out: x1 = %g x2 = %g NumOfRoots = %d\n", TestSol1, TestSol2, TestNumOfRoots);

            ChangeColourTo (LightBlue);
            printf ("Expected: x1 = %g x2 = %g NumOfRoots = %d\n", Tests[i].Solution1, Tests[i].Solution2, Tests[i].NumOfRoots);

            ChangeColourTo (Default);
        }
        else{

            printf ("Test %.3d:  ", i);

            ChangeColourTo (Green);
            printf("OK \n");

            ChangeColourTo (Default);
        }
    }

    return 1;
}


void ChangeColourTo (Colour colour){
    HANDLE hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute (hConsole, colour);
}

