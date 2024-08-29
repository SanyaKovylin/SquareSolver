#ifndef SOLVER_H_INCLUDED
#define SOLVER_H_INCLUDED


/// \brief Defined vars for case identification
enum Cases {
    TOXIC      = -100, /// For errors
    INFROOTS   =  100, /// For case of infinity of roots
    ONE_ROOT   =    1,
    TWO_ROOTS  =    2,
    NO_ROOTS   =    0,
};

Cases Solve (double a_coef, double b_coef, double c_coef, double *sol1, double *sol2);

#endif //SOLVER_H_INCLUDED
