/*! \file
    \brief File with ALL solving functions
*/

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include "sq_sol.h"
#include "get.h"


Cases SquareSolve (double CoefA, double CoefB, double CoefC, double *Sol1, double *Sol2); //< Solver for square equations by coefficients
Cases LinearSolve (double CoefB, double CoefC, double* Sol1); //< Solver for linear equations by coefficients
Cases SpecialCase (double CoefC); //< Solver for 0-power equation by coefficient

/** \defgroup Main_part Main_part

    \brief General functions of solving

    @{
*/

//-----------------------------------------------------------------------------

/*! ---------------------------------------------------------------------------
    \brief Implementing branching between solving Cases and unificating answers

    If equation has more or less than 2 roots, take it as a standart that
    Sol1 = Sol2

    And if they are undefined (0 or INF) assign them 0-valued

    \param [in] CoefA, CoefB, CoefC  Value of coefficient a, b, c
    \param [in] *Sol1, *Sol2            Pointers to the answers' cells

    \returns Number of roots
-------------------------------------------------------------------------------*/

Cases Solve(double CoefA, double CoefB, double CoefC, double *Sol1, double *Sol2){

    assert (isfinite (CoefA));
    assert (isfinite (CoefB));
    assert (isfinite (CoefC));

    assert (Sol1 != NULL);
    assert (Sol2 != NULL);
    assert (Sol1 != Sol2);

    Cases NumOfRoots = TOXIC;

    //  isZero
    if (IsZero (CoefA)) {

        if (IsZero (CoefB)){

            NumOfRoots = SpecialCase (CoefC);
            *Sol1 = 0.0;
            *Sol2 = 0.0;
        }
        else {
            NumOfRoots = LinearSolve (CoefB, CoefC, Sol1);

            *Sol2 = *Sol1;
        }

    }
    else {
        NumOfRoots = SquareSolve (CoefA, CoefB, CoefC, Sol1, Sol2);
    }

    return NumOfRoots;
}

//-----------------------------------------------------------------------------


/*!
    \brief Solver for square equations by coefficients

    \param [in] CoefA, CoefB, CoefC      Value of coefficient a, b, c
    \param [in] *Sol1, *Sol2                Pointers to the answers' cells

    \warning CoefA != 0 (We assume that equation actually is Square)

    \returns Number of roots
*/

// return enum
Cases SquareSolve(double CoefA, double CoefB, double CoefC, double *Sol1, double *Sol2){

    assert (isfinite (CoefA));
    assert (isfinite (CoefB));
    assert (isfinite (CoefC));
    assert (!IsZero (CoefA));

    assert (Sol1 != NULL);
    assert (Sol2 != NULL);
    assert (Sol1 != Sol2);

    double Discr = 0;  // The discriminant of equation and its square root
    double InvCoefAx2 = 1 / (CoefA * 2); // Due to inevitability of computation we take it once

    Discr = CoefB * CoefB - 4 * CoefA * CoefC;// compute the discriminant of equation

    if (IsZero (Discr)){

        *Sol1 = -CoefB * InvCoefAx2;
        *Sol2 = *Sol1;

        return ONE_ROOT; // And I'm Groot. // ??????
    }

    else if (Discr > 0){

        Discr = sqrt (Discr);
        *Sol1 = (-CoefB + Discr) * InvCoefAx2;
        *Sol2 = (-CoefB - Discr) * InvCoefAx2;

        return TWO_ROOTS; // And we are Groots.
    }

    *Sol1 = 0;
    *Sol2 = *Sol1;

    return NO_ROOTS;
}

//-----------------------------------------------------------------------------

/*!
    \brief Solver for linear equations by coefficients

    \param [in] CoefB, CoefC    Value of coefficient a, b, c
    \param [in] *Sol1             Pointer to the answer's cell

    \warning CoefB != 0 (We assume that equation actually is Linear)

    \returns Number of roots
*/

Cases LinearSolve (double CoefB, double CoefC, double *Sol1) {

    assert (isfinite (CoefB)); assert (!IsZero (CoefB));

    assert (isfinite (CoefC));

    assert (Sol1 != NULL);

    *Sol1 = -CoefC / CoefB;

    return ONE_ROOT;
}

//-----------------------------------------------------------------------------

/*!
    \brief Solver for case of 0-power polynomial

    \param [in] CoefC  Value of coefficient c

    \returns Number of roots
*/

Cases SpecialCase (double CoefC){

    assert (isfinite (CoefC));

    if (IsZero (CoefC)) return INFROOTS;

    return NO_ROOTS;
}

// @}


//-----------------------------------------------------------------------------

/** \defgroup Additional Comparing
    \ingroup Main_part

    \brief Functions for comparing doubles and floats

    @{
*/

const double EPS = 0.00001;///< defines the accuracy of comparing


/*!
    \brief Comparing double with 0

    \param [in] Value

    \returns Result of comparing (True <==> (Value == 0))
*/

// isZero
int IsZero (double Value){

    assert (isfinite(Value));

    return EPS > fabs (Value);
}

//-----------------------------------------------------------------------------

/*!
    \brief Comparing 2 doubles

    \param [in] val1, val2   Doubles to compare

    \returns Result of comparing (True <==> (val1 == val2))
*/

int CompareDoubles(double val1, double val2){

    assert (isfinite (val1));
    assert (isfinite (val2));

    return EPS > fabs (val1 - val2);
}
// @}

