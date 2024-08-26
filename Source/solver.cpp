/*! \file
    \brief File with ALL solving functions
*/

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include "sq_sol.h"


Cases SquareSolve (double CoefA, double CoefB, double CoefC, double *Solution1, double *Solution2); //< Solver for square equations by coefficients
Cases LinearSolve (double CoefB, double CoefC, double* Solution1); //< Solver for linear equations by coefficients
Cases SpecialCase (double CoefC); //< Solver for 0-power equation by coefficient

/** \defgroup Main_part Main_part

    \brief General functions of solving

    @{
*/

//-----------------------------------------------------------------------------

/*! ---------------------------------------------------------------------------
    \brief Implementing branching between solving Cases and unificating answers

    If equation has more or less than 2 roots, take it as a standart that
    Solution1 = Solution2

    And if they are undefined (0 or INF) assign them 0-valued

    \param [in] CoefA, CoefB, CoefC  Value of coefficient a, b, c
    \param [in] *Solution1, *Solution2            Pointers to the answers' cells

    \returns Number of roots
-------------------------------------------------------------------------------*/

Cases Solve(double CoefA, double CoefB, double CoefC, double *Solution1, double *Solution2){

    assert (isfinite (CoefA));
    assert (isfinite (CoefB));
    assert (isfinite (CoefC));

    assert (Solution1 != NULL);
    assert (Solution2 != NULL);
    assert (Solution1 != Solution2);

    Cases NumOfRoots = TOXIC;

    //  isZero
    if (IsZero (CoefA)) {

        if (IsZero (CoefB)){

            NumOfRoots = SpecialCase (CoefC);
            *Solution1 = 0.0;
            *Solution2 = 0.0;
        }
        else {
            NumOfRoots = LinearSolve (CoefB, CoefC, Solution1);

            *Solution2 = *Solution1;
        }

    }
    else {
        NumOfRoots = SquareSolve (CoefA, CoefB, CoefC, Solution1, Solution2);
    }

    return NumOfRoots;
}

//-----------------------------------------------------------------------------


/*!
    \brief Solver for square equations by coefficients

    \param [in] CoefA, CoefB, CoefC      Value of coefficient a, b, c
    \param [in] *Solution1, *Solution2                Pointers to the answers' cells

    \warning CoefA != 0 (We assume that equation actually is Square)

    \returns Number of roots
*/

// return enum
Cases SquareSolve(double CoefA, double CoefB, double CoefC, double *Solution1, double *Solution2){

    assert (isfinite (CoefA));
    assert (isfinite (CoefB));
    assert (isfinite (CoefC));
    assert (!IsZero (CoefA));

    assert (Solution1 != NULL);
    assert (Solution2 != NULL);
    assert (Solution1 != Solution2);

    double Discr = 0;  // The discriminant of equation and its square root
    double InvCoefAx2 = 1 / (CoefA * 2); // Due to inevitability of computation we take it once

    Discr = CoefB * CoefB - 4 * CoefA * CoefC;// compute the discriminant of equation

    if (IsZero (Discr)){

        *Solution1 = -CoefB * InvCoefAx2;
        *Solution2 = *Solution1;

        return ONE_ROOT; // And I'm Groot. // ??????
    }

    else if (Discr > 0){

        Discr = sqrt (Discr);
        *Solution1 = (-CoefB + Discr) * InvCoefAx2;
        *Solution2 = (-CoefB - Discr) * InvCoefAx2;

        return TWO_ROOTS; // And we are Groots.
    }

    *Solution1 = 0;
    *Solution2 = *Solution1;

    return NO_ROOTS;
}

//-----------------------------------------------------------------------------

/*!
    \brief Solver for linear equations by coefficients

    \param [in] CoefB, CoefC    Value of coefficient a, b, c
    \param [in] *Solution1             Pointer to the answer's cell

    \warning CoefB != 0 (We assume that equation actually is Linear)

    \returns Number of roots
*/

Cases LinearSolve (double CoefB, double CoefC, double *Solution1) {

    assert (isfinite (CoefB)); assert (!IsZero (CoefB));

    assert (isfinite (CoefC));

    assert (Solution1 != NULL);

    *Solution1 = -CoefC / CoefB;

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

    \param [in] Value1, Value2   Doubles to compare

    \returns Result of comparing (True <==> (Value1 == Value2))
*/

int CompareDoubles(double Value1, double Value2){

    assert (isfinite (Value1));
    assert (isfinite (Value2));

    return EPS > fabs (Value1 - Value2);
}
// @}

