//!< \file
//!< \brief Main file of project that solves equation of the form a*x^2 + b*x + c = 0 and tests itself

#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include "sq_sol.h"
#include "get.h"
#include <windows.h>

int tester (void);

/*! \brief Implements the solving

    Starts the program

    \returns code-of-exit
*/

int main (int argc, char *argv[])
{
    //assert (tester ());

    int e = 0;
    double a_coef = 0, b_coef = 1, c_coef = 0;  // coefficients of the equation

    if (argc == 1)   {

        tester ();
        input (&a_coef, &b_coef, &c_coef);
    }
    else   {

        int test = 0, flag = 0;
        flag = cons_get(&a_coef, &b_coef, &c_coef, argv++, argc - 1, &test, &e);

        if (test) tester();
        if (!flag) {printf("INPUTERROR"); return 10;}
        else if (flag == -1) return -10;
    }

    double sol1 = 0, sol2 = 0;
    int num_roots = Solve (a_coef, b_coef, c_coef , &sol1, &sol2);
    return output (sol1, sol2, num_roots, e);
}

//=============================================================================

/*! \brief Implements the testing

    Enters several tests to the Solve function and checks output

    \returns If there any mistakes
*/

int tester(void){

    HANDLE  hConsole;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    struct test {

        double a;
        double b;
        double c;

        int nroots;

        double sol1;
        double sol2;
    };

    struct test tests[] = {

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

    int t_nroots = TOXIC;
    double t1 = TOXIC, t2 = TOXIC;

    for (long unsigned int i = 0; i < sizeof (tests) / sizeof (tests[0]); i++){

        t_nroots = Solve(tests[i].a, tests[i].b, tests[i].c, &t1, &t2);

        if ((compare2 (tests[i].sol1, t1) &&
             compare2 (tests[i].sol2, t2) &&
             tests[i].nroots == t_nroots) == false) {


            printf ("Test %.3lu:  ", i);
            // txSetConsoleAttr(0x0c);
            SetConsoleTextAttribute(hConsole, 12);
            printf("Failed \n");
            SetConsoleTextAttribute(hConsole, 4);
            printf ("Out: x1 = %g x2 = %g nroots = %d\n", t1, t2, t_nroots);
            SetConsoleTextAttribute(hConsole, 11);
            printf ("Expected: x1 = %g x2 = %g nroots = %d\n", tests[i].sol1, tests[i].sol2, tests[i].nroots);
            SetConsoleTextAttribute(hConsole, 7);;

        }
        else{

            printf("Test %.3lu:  ", i);
            SetConsoleTextAttribute(hConsole, 2);
            printf("OK \n");
            SetConsoleTextAttribute(hConsole, 7);
        }
    }

    return 1;
}













