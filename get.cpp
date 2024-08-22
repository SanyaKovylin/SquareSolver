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


int getw (double *var){

    const int MAXLENGTH = 1000;
    char str [MAXLENGTH] = {0};
    int c = '\0';
    int len = 0;
    for (len = 0; len < MAXLENGTH && (c = getchar()) != EOF && c != '\n'; len++)
        *(str + len) = (char) c;

    double val = 0;
    //printf("%d %s\n", i, str);

    if (len) {

        int i = 0;
        while ( *(str + i) == ' ') i++;
        int sign = ( *(str + i) == '-') ? -1 : 1;
        int f = 0;
        f = (*(str + i) == '+' || *(str + i) == '-');

        for (i += f; i < len              &&
                        *(str + i) != '.' &&
                        *(str + i) != ' ' &&
                        *(str + i) != 'e' &&
                        *(str + i) != 'E'; i++) {

            if (isdigit (*(str + i))) {
                val = 10.0 * val + (*(str + i) - '0');
                if (!isfinite (val))
                    return 2; }
            else
                return 0;
        }
        //printf("%d %d %g\n", i, sign, val);
//-----------------------------------------------------------------------------

        double power = 1;
        f = (*(str + i) == '.');

        for(i += f; i < len &&  *(str + i) != ' ' &&
                                *(str + i) != 'e' &&
                                *(str + i) != 'E'; i++){

            if (isdigit (*(str + i))){

                power /= 10.0;
                val += (*(str + i) - '0') * power;
                if (!isfinite (val)) return 2;
            }
            else
                return 0;
        }

        //printf("%d %d %g\n", i, sign, val);

//-----------------------------------------------------------------------------


        int epower = 0;
        int ff = 0;

        f = (*(str + i) == 'e' || *(str + i) == 'E');
        i += f;

        int esign = (*(str + i) == '-') ? -1 : 1;

        ff = (*(str + i) == '+' || *(str + i) == '-');

        for(i += ff; i < len && *(str + i) != ' '; i++){

            if (isdigit (*(str + i))){

                epower += epower * 10 + (*(str + i) - '0');
                if (!isfinite (val)) return 2;
            }
            else
                return 0;
        }


        //printf("%d %d %g\n", i, sign, val);
        while (*(str + len - 1) == ' ') len--;

        if (len != i)  return 0;
        *var = val * sign * pow (10, epower * esign) ;
        return 1;

    }
    else
        return 0;



}


