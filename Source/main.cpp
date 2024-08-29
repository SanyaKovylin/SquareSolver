//!< \file
//!< \brief Main file of project that solves equation of the form a*x^2 + b*x + c = 0 and Tests itself

#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <windows.h>
#include "solver.h"
#include "io.h"
#include "colors.h"
#include "test.h"

/*! \brief Implements the solving

    Starts the programs

    \returns code-of-exit
*/

int main (const int argc, const char *argv[]){

    struct Flags ConsoleFlags = {0, 0, 0};
    double CoefA = 0, CoefB = 0, CoefC = 0;  // coefficients of the equation

    if (argc == 1)   {

        TestofSolver();

        InputCoefficients(&CoefA, &CoefB, &CoefC);
    }
    else {

        int InputStatus = ConsoleInput(&CoefA,  &CoefB,    &CoefC,
                                         argv,    argc,    &ConsoleFlags);

        if (ConsoleFlags.NeedTest){
            TestofSolver();
        }

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

    double Solution1 = 0.0;
    double Solution2 = 0.0;

    Cases NumOfRoots = Solve (CoefA, CoefB, CoefC , &Solution1, &Solution2);

    return FormOutput (Solution1, Solution2, NumOfRoots, ConsoleFlags.IsExp);
}






