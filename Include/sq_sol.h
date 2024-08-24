/*!
\file
\brief Header with description of main functions
*/
#ifndef SQ_SOL_H_INCLUDED
#define SQ_SOL_H_INCLUDED

enum MainRespond {
    MAIN = 1,
    HELP_CALL = 2,
    MISTAKE = 0,
};

enum InputStatus {
    ERROR  = 0,
    OK     = 1,
    TOOBIG = 2,
    HELP   = 3,
};

/// \brief Defined vars for case identification
enum Cases {
    TOXIC      = -100, /// For errors
    INFROOTS   =  100, /// For case of infinity of roots
    ONE_ROOT   =    1,
    TWO_ROOTS  =    2,
    NO_ROOTS   =    0,
};

void InputCoefficients (double *a_coef, double *b_coef, double *c_coef);//< Input function
Cases Solve (double a_coef, double b_coef, double c_coef, double *sol1, double *sol2);//< Solver for all cases of 2-power polynomial
MainRespond FormOutput (double sol1, double sol2, int num_roots, int e);//< Output function

int IsZero (double dble); // Function for approx comparing double and 0
int CompareDoubles (double dble1, double dble2); //< Function for approx comparing two doubles

static const int NumOfCoefs = 3;

#endif // SQ_SOL_H_INCLUDED
