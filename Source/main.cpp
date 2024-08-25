//!< \file
//!< \brief Main file of project that solves equation of the form a*x^2 + b*x + c = 0 and Tests itself

#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <windows.h>
#include "sq_sol.h"
#include "get.h"

int TestofSolver(void);

/*! \brief Implements the solving

    Starts the programs

    \returns code-of-exit
*/

int main (int argc, char *argv[]){

    int FormFlag = 0;
    double CoefA = 0, CoefB = 1, CoefC = 0;  // coefficients of the equation

    if (argc == 1)   {

        TestofSolver();

        InputCoefficients(&CoefA, &CoefB, &CoefC);
    }
    else {

        int TestFlag = 0;  // shouldTest needTest bool  expForm  isDebug  DebugActive
        int InputStatus = ConsoleInput(&CoefA, &CoefB, &CoefC, argv++, argc--, &TestFlag, &FormFlag);
                                                              //Avoid Path
        if (TestFlag)
            TestofSolver();

        if (!InputStatus) {
            printf("INPUTERROR");
            return MISTAKE;
        }
        else if (InputStatus == HELP) {
            return HELP;
        }
    }

    // solution1, solution2
    double Sol1 = 0.0;
    double Sol2 = 0.0;
    int NumOfRoots = Solve (CoefA, CoefB, CoefC , &Sol1, &Sol2);
    return FormOutput (Sol1, Sol2, NumOfRoots, FormFlag);
}

//=============================================================================

/*! \brief Implements the Testing

    Enters several Tests to the Solve function and checks output

    \returns If there any mistakes
*/

int TestofSolver(void){

    HANDLE hConsole == GetStdHandle(STD_OUTPUTestHANDLE);

    struct Test {

        double a;
        double b;
        double c;

        int NumOfRoots;

        double Sol1;
        double Sol2;
    };

    struct Test Tests[] = {
//--------------------------------------------------------------
//          a      b       c NumOfRoots         x1         x2
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

    int TestNumOfRoots = TOXIC;
    double TestSol1 = TOXIC, TestSol2 = TOXIC;

    for (size_t i = 0; i < sizeof (Tests) / sizeof (Tests[0]); i++){

        TestNumOfRoots = Solve(Tests[i].a, Tests[i].b, Tests[i].c, &TestSol1, &TestSol2);

        if ((CompareDoubles (Tests[i].Sol1, TestSol1) &&
             CompareDoubles (Tests[i].Sol2, TestSol2) &&
             Tests[i].NumOfRoots == TestNumOfRoots) == false) {


            printf ("Test %.3llu:  ", i);
            // txSetConsoleAttr(0x0c);
            SetConsoleTextAttribute(hConsole, 12);
            $r printf("Failed \n");
            SetConsoleTextAttribute(hConsole, 4);
            $b printf ("Out: x1 = %g x2 = %g NumOfRoots = %d\n", TestSol1, TestSol2, TestNumOfRoots);
            SetConsoleTextAttribute(hConsole, 11);
            printf ("Expected: x1 = %g x2 = %g NumOfRoots = %d\n", Tests[i].Sol1, Tests[i].Sol2, Tests[i].NumOfRoots);
            SetConsoleTextAttribute(hConsole, 7);;
            $d
        }
        else{

            printf("Test %.3llu:  ", i);
            SetConsoleTextAttribute(hConsole, 2);
            printf("OK \n");
            SetConsoleTextAttribute(hConsole, 7);
        }
    }

    return 1;
}













