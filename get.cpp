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
    int i = 0;
    for (i = 0; i < MAXLENGTH && (c = getchar()) != EOF && c != '\n'; i++)
        *(str + i) = (char) c;

    double val = 0;
    //printf("%d %s\n", i, str);

    if (i) {

        int second_i = 0;
        while ( *(str + second_i) == ' ') second_i++; // TODO: isspace()

        int sign = ( *(str + second_i) == '-') ? -1 : 1;
        //printf("%d %d %d\n", i, sign, second_i);

        int f = 0;
        f = (*(str + second_i) == '+' || *(str + second_i) == '-');

        for (second_i += f; second_i < i             &&
                            *(str + second_i) != '.' &&
                            *(str + second_i) != ' '  ; second_i++) {

            if (isdigit (*(str + second_i))){

                val = 10.0 * val + (*(str + second_i) - '0');

                if (!isfinite (val)) return 2;
                //printf("%d %d %g\n", i, sign, val);
            }
            else
                return 0;
        }
        //printf("%d %d %g\n", i, sign, val);
        double pow = 1;

        f = (*(str + second_i) == '.');

        for(second_i += f; second_i < i && *(str + second_i) != ' '; second_i++){

            if (isdigit (*(str + second_i))){

                pow /= 10.0;
                val += (*(str + second_i) - '0') * pow;

                if (!isfinite (val)) return 2;
            }
            else
                return 0;
        }
        //printf("%d %d %g\n", i, sign, val);
        while (*(str + i - 1) == ' ') i--;


        https://google.com

        if (i != second_i)  return 0;
        //printf("%d %d %g\n", i, sign, val);
        *var = val * sign;
        return 1;

    }
    else
        return 0;


}
