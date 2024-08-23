//! \file
//! \brief Checking input file
//!

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>
#include "get.h"


/* main(void){
    double v = 0;
    int res = getw (&v);
    printf("%lg %d \n", v, res);
}  */

//! @brief Bilds double from the line of chars
//!
//! @param *var Pointer to input's cell
//!
//! @return the code of output
//!


int get_input (double *var){

    const int MAXLENGTH = 1000;
    char str [MAXLENGTH] = {0};
    int c = '\0';
    int len = 0;
    for (len = 0; len < MAXLENGTH && (c = getchar()) != EOF && c != '\n'; len++)
        *(str + len) = (char) c;

    double val = 0;

    if (len) {

        int i = 0;
        while ( *(str + i) == ' ') i++;
        int sign = 0;

        int retr = pre_check(&sign, &val, str, &i, len);
        //retr = dot_check(&power, &val, str, i, len);

        switch (retr){

            case 2  : return 2;

            case 0  : return 0;

            default : break;
        }

//-----------------------------------------------------------------------------

        double power = 1;
        retr = dot_check(&power, &val, str, &i, len);
        //retr = dot_check(&power, &val, str, i, len);

        switch (retr){

            case 2  : return 2;

            case 0  : return 0;

            default : break;
        }

//-----------------------------------------------------------------------------

        int epower = 0;
        int esign = 0;

        retr = e_check(&esign, &epower, str, &i, len);
        //retr = dot_check(&power, &val, str, i, len);

        switch (retr){

            case 0  : return 0;

            default : break;
        }


        while (*(str + len - 1) == ' ') len--;

        if (len != i)  return 0;
        *var = val * sign * pow (10, epower * esign) ;
        return 1;

    }
    else
        return 0;
}


int dot_check(double *power, double *val,char *str, int *i, int len){
        int dot_flag = 0;
        dot_flag = (*(str + *i) == '.');

        for(*i += dot_flag; *i < len &&   *(str + *i) != ' ' &&
                                        *(str + *i) != 'e' &&
                                        *(str + *i) != 'E'; (*i)++){

            if (isdigit (*(str + *i))){

                *power /= 10.0;
                *val += (*(str + *i) - '0') * *power;
                if (!isfinite (*val)) return 2;
            }
            else
                return 0;
        }
    return 1;
}


int e_check (int *esign, int *epower, char *str, int *i, int len){

    int sign_flag = 0;
    int e_flag = 0;

    e_flag = (*(str + *i) == 'e' || *(str + *i) == 'E');
    *i += e_flag;

    *esign = (*(str + *i) == '-') ? -1 : 1;

    sign_flag = (*(str + *i) == '+' || *(str + *i) == '-');

    for(*i += sign_flag; *i < len && *(str + *i) != ' '; (*i)++){
        if (isdigit (*(str + *i))){
            *epower += (*epower) * 10 + (*(str + *i) - '0');
        }
        else
            return 0;
    }
    return 1;
}


int pre_check(int *sign, double *val,char *str, int *i, int len) {

    *sign = ( *(str + *i) == '-') ? -1 : 1;
    int sign_flag = 0;
    sign_flag = (*(str + *i) == '+' || *(str + *i) == '-');

    for (*i += sign_flag; *i < len      &&
                    *(str + *i) != '.'  &&
                    *(str + *i) != ' '  &&
                    *(str + *i) != 'e'  &&
                    *(str + *i) != 'E'; (*i)++) {

        if (isdigit (*(str + *i))) {
            *val = 10.0 * *val + (*(str + *i) - '0');
            if (!isfinite (*val))
                return 2; }
        else
            return 0;
    }

    return 1;
}


