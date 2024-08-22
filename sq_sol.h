/*!
\file
\brief Header with description of main functions
*/
#ifndef SQ_SOL_H_INCLUDED
#define SQ_SOL_H_INCLUDED


void input (double *a_coef, double *b_coef, double *c_coef);//< Input function
int Solve (double a_coef, double b_coef, double c_coef, double *sol1, double *sol2);//< Solver for all cases of 2-power polynomial
int output (double sol1, double sol2, int num_roots);//< Output function

int compare (double dble); // Function for approx comparing double and 0
int compare2 (double dble1, double dble2); //< Function for approx comparing two doubles



/// \brief Defined vars for case identification
enum cases {
    TOXIC    = -100, /// For errors
    INFROOTS =  100, /// For case of infinity of roots
};


#endif // SQ_SOL_H_INCLUDED
