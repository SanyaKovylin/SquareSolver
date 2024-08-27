//!< \file
//!< \brief Main file of project that solves equation of the form a*x^2 + b*x + c = 0 and Tests itself

#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <windows.h>
#include "sq_sol.h"
#include "colors.h"
#include "test.h"

/*! \brief Implements the solving

    Starts the programs

    \returns code-of-exit
*/

int main (int argc, char *argv[]){

    int IsExp = 0;
    double CoefA = 0, CoefB = 1, CoefC = 0;  // coefficients of the equation

    if (argc == 1)   {

        TestofSolver();

        InputCoefficients(&CoefA, &CoefB, &CoefC);
    }
    else {

        int NeedTest = 0;  // shouldTest needTest bool  expForm  isDebug  DebugActive
        int InputStatus = ConsoleInput(&CoefA,  &CoefB,    &CoefC,
                                                argv++,    argc--,
                                             &NeedTest,    &IsExp);

        if (NeedTest)
            TestofSolver();
                                                               //Avoid Path
        if (InputStatus == 0) {
            printf("INPUTERROR");
            return MISTAKE;
        }
        else if (InputStatus == HELP) {
            return HELP;
        }
        else if (InputStatus == NOSOLVE) {
            return NOSOLVE;
        }

    }

    // solution1, solution2
    double Solution1 = 0.0;
    double Solution2 = 0.0;
    int NumOfRoots = Solve (CoefA, CoefB, CoefC , &Solution1, &Solution2);
    return FormOutput (Solution1, Solution2, NumOfRoots, IsExp);
}






