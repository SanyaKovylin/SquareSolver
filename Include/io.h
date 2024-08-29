/*!
\file
\brief Header with description of io functions
*/
#ifndef SQ_SOL_H_INCLUDED
#define SQ_SOL_H_INCLUDED

#include "solver.h"

// FIXME: error-code
enum MainRespond {
    MAIN      = 1,
    HELP_CALL = 2,
    MISTAKE   = 3,
};

enum InputStatus {
    INPERROR = 0,
    OK       = 1,
    TOOBIG   = 2,
    HELP     = 3,
    NOSOLVE  = 4,
};

struct Flags {
    int NeedTest;
    int    IsExp;
    int NeedHelp;
};



void InputCoefficients   (double *a_coef, double *b_coef, double *c_coef);
InputStatus ConsoleInput (double *a_coef,     double *b_coef, double *c_coef,
                          const char *argv[], const int argc, struct Flags *ConsoleFlags);

MainRespond FormOutput (double sol1, double sol2, Cases num_roots, int e);

InputStatus InputToDouble (double *CoefValue, char Buffer[]);

int IsZero         (double Value);
int CompareDoubles (double Value1, double Value2);

static const int NumOfCoefs = 3;

//=========================================================================
//Flags
#define HelpFlag "--help"

#define TestFlag "--test"

const char HFlag = 'h';
#define HFlagStr "h"

const char TFlag = 't';
#define TFlagStr "t"

const char EFlag = 'e';
#define EFlagStr "e"
//==========================================================================


#endif // SQ_SOL_H_INCLUDED
