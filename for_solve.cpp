/*! \file
    \brief File with ALL solving functions
*/

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "sq_sol.h"
#include "get.h"

void get_input (double *coef, char letter); //< Function for one var input + correct check
int square_solve (double a_coef, double b_coef, double c_coef, double *sol1, double *sol2); //< Solver for square equations by coefficients
int linear_solve (double b_coef, double c_coef, double* sol1); //< Solver for linear equations by coefficients
int special_case (double c_coef); //< Solver for 0-power equation by coefficient

/** \defgroup Main_part Main_part

    \brief General functions of solving

    @{
*/



/*!
    \brief Adjusts alternately input of 3 coefficients

    \param [in] *a_coef      Pointer for coefficient a's cell
    \param [in] *b_coef      Pointer for coefficient b's cell
    \param [in] *c_coef      Pointer for coefficient c's cell
*/
void input(double *a_coef, double *b_coef, double *c_coef){

    printf ("Please, enter the coefficients of your equation of the form a*x^2 + b*x + c = 0\n");

    get_input (a_coef, 'a');
    get_input (b_coef, 'b');
    get_input (c_coef, 'c');

    //printf ("%lg %lg %lg", *a_coef, *b_coef, *c_coef);
}

/*!
    \brief Processing input of one variable

    \param [in]  *coef    Pointer for coefficient cell
    \param [in] letter    Name of coef that will be printed
*/

void get_input (double *coef, char letter){

    printf ("%c: ", letter);

    int flag = 0;
    /*while ((flag = scanf ("%lf", coef)) == EOF || !flag){

        printf ("Your input has wrong type, please, reenter coefficient %c\n", letter);
        printf ("%c: ", letter);

        if (flag != EOF)
            while (getchar () != '\n')  // buffer clean
                ;
    }*/
        while ((flag = getw (coef)) != 1){
        switch (flag){
            case 0: {
                printf ("Your input has wrong type, please, reenter coefficient %c\n", letter);
                printf ("%c: ", letter);
                break;
            }
            case 2: {
                printf ("Your input is too big, please, reenter coefficient %c\n", letter);
                printf ("%c: ", letter);
                break;
            default: printf ("Error: InputError");
            }
        }


        }
}

//-----------------------------------------------------------------------------

/*!
    \brief Implementing branching between solving cases and unificating answers

    If equation has more or less than 2 roots, take it as a standart that
    sol1 = sol2

    And if they are undefined (0 or INF) assign them 0-valued

    \param [in] a_coef, b_coef, c_coef  Value of coefficient a, b, c
    \param [in] *sol1, *sol2            Pointers to the answers' cells

    \returns Number of roots
*/

int Solve(double a_coef,double b_coef, double c_coef, double *sol1, double *sol2){

    assert (isfinite (a_coef));
    assert (isfinite (b_coef));
    assert (isfinite (c_coef));

    assert (sol1 != NULL);
    assert (sol2 != NULL);
    assert (sol1 != sol2);

    int num_roots = TOXIC;

    if (compare (a_coef)) {

        if (compare (b_coef)){

            num_roots = special_case (c_coef);
            *sol1 = 0;
            *sol2 = *sol1;
        }

        else{
            num_roots = linear_solve (b_coef, c_coef, sol1);

            *sol2 = *sol1;
        }

    }
    else num_roots = square_solve (a_coef, b_coef, c_coef, sol1, sol2);

    return num_roots;
}

//-----------------------------------------------------------------------------


/*!
    \brief Solver for square equations by coefficients

    \param [in] a_coef, b_coef, c_coef      Value of coefficient a, b, c
    \param [in] *sol1, *sol2                Pointers to the answers' cells

    \warning a_coef != 0 (We assume that equation actually is Square)

    \returns Number of roots
*/
int square_solve(double a_coef, double b_coef, double c_coef, double *sol1, double *sol2){

    assert (isfinite (a_coef));
    assert (isfinite (b_coef));
    assert (isfinite (c_coef));
    assert (!compare (a_coef));

    assert (sol1 != NULL);
    assert (sol2 != NULL);
    assert (sol1 != sol2);

    double discr = 0;  // The discriminant of equation and its square root
    double inv_a_coefx2 = 1 / (a_coef * 2); // Due to inevitability of computation we take it once

    discr = b_coef * b_coef - 4 * a_coef * c_coef;// compute the discriminant of equation

    if (compare (discr)){

        *sol1 = -b_coef * inv_a_coefx2;
        *sol2 = *sol1;

        return 1;
    }

    else if (discr > 0){

        discr = sqrt (discr);
        *sol1 = (-b_coef + discr) * inv_a_coefx2;
        *sol2 = (-b_coef - discr) * inv_a_coefx2;

        return 2;
    }

    *sol1 = 0;
    *sol2 = *sol1;

    return 0;
}

//-----------------------------------------------------------------------------

/*!
    \brief Solver for linear equations by coefficients

    \param [in] b_coef, c_coef    Value of coefficient a, b, c
    \param [in] *sol1             Pointer to the answer's cell

    \warning b_coef != 0 (We assume that equation actually is Linear)

    \returns Number of roots
*/

int linear_solve (double b_coef, double c_coef, double *sol1) {
    assert (isfinite (b_coef));
    assert (isfinite (c_coef));
    assert (!compare (b_coef));

    assert (sol1 != NULL);

    *sol1 = -c_coef / b_coef;

    return 1;
}

//-----------------------------------------------------------------------------

/*!
    \brief Solver for case of 0-power polynomial

    \param [in] c_coef  Value of coefficient c

    \returns Number of roots
*/

int special_case (double c_coef){

    assert (isfinite (c_coef));

    if (compare(c_coef)) return INFROOTS;

    return 0;
}

//-----------------------------------------------------------------------------

/*!
    \brief Adjusts onput of solutions

    Use case branch by the number of roots

    \param [in] sol1,sol2    Solutions to print
    \param [in] num_roots    Number of roots

    \return code-of-exit
*/

int output(double sol1, double sol2, int num_roots, int e){

    assert (isfinite (sol1));
    assert (isfinite (sol2));
    if (!e){
    switch (num_roots){

    case 1 : {

        printf ("Your equation has only one root: %g", sol1);

        return 0;
    }

    case 2 : {

        printf ("Your equation has two roots: \nx1 = %g \nx2 = %g", sol1, sol2);

        return 0;
    }

    case 0 : {

        printf ("Your equation has no roots");

        return 0;
    }

    case INFROOTS : {
        printf ("Your equation has INFROOTS roots");

        return 0;
    }

    default : return 2;
    }}
    else{
    switch (num_roots){

    case 1 : {

        printf ("Your equation has only one root: %e", sol1);

        return 0;
    }

    case 2 : {

        printf ("Your equation has two roots: \nx1 = %e \nx2 = %e", sol1, sol2);

        return 0;
    }

    case 0 : {

        printf ("Your equation has no roots");

        return 0;
    }

    case INFROOTS : {
        printf ("Your equation has INFROOTS roots");

        return 0;
    }

    default : return 2;
    }
    }
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

    \param [in] dble

    \returns Result of comparing (True <==> (dble == 0))
*/
int compare (double dble){

    assert (isfinite(dble));

    return EPS > fabs (dble);
}

//-----------------------------------------------------------------------------

/*!
    \brief Comparing 2 doubles

    \param [in] dble1, dble2   Doubles to compare

    \returns Result of comparing (True <==> (dble1 == dble2))
*/

int compare2(double dble1, double dble2){

    assert (isfinite (dble1));
    assert (isfinite (dble2));

    return EPS > fabs (dble1 - dble2);
}
// @}

