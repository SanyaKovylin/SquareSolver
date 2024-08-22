//! \file
//! \brief Checking input file
//!

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>
#include "get.h"


/* main (void){
    double v = 0;
    int res = big_get (&v);
    printf ("%lg %d \n", v, res);
}  */

int get_num(double *var, char str[]);
int comp_str (char line1[], char line2[]);

//! @brief Bilds double from the line of chars
//!
//! @param *var Pointer to input's cell
//!
//! @return the code of output
//!
static int pos = 0;

int big_get (double *a_coef, double *b_coef, double *c_coef, char *argv[], int cou,int *test,int *e){

    while (cou > 3 && (*++argv)[0] == '-'){
        char c ='\0';

            c = (*argv)[1];

            switch (c){

                case 't':{ *test = 1; break;}

                case 'e':{ *e    = 1; break;}

                case '-':{

                    if (comp_str((*argv),"--test")) *test = 1;
                    else return 0;
                    break;
                }

                default : return 0;
            }
        cou -= 1;

    }

    if (cou == 3){

        get_num (a_coef, argv[1]);
        get_num (b_coef, argv[2]);
        get_num (c_coef, argv[3]);
        return 1;
    }
    else
        return 0;
}


int get_num (double *var, char str[]){

    const int MAXLENGTH = 1000;
    int c = '\0';
    int len = 0;
    for (len = 0; len < MAXLENGTH && *(str + len) != '\0' && c != '\n'; len++);
    double val = 0;

    if (len) {

        int i = 0;
        while ( *(str + i) == ' ') i++;
        int sign = ( *(str + i) == '-') ? -1 : 1;
        int s_flag = 0;
        s_flag = (*(str + i) == '+' || *(str + i) == '-');

        for (i += s_flag; i < len              &&
                        *(str + i) != '.' &&
                        *(str + i) != ' ' &&
                        *(str + i) != 'e' &&
                        *(str + i) != 'E'; i++) {


            if (isdigit (*(str + i))) {
                val = 10.0 * val + (*(str + i) - '0');

                if (!isfinite (val))
                    return 2; }
            else {

                return 0; }
        }

//-----------------------------------------------------------------------------

        double power = 1;
        int d_flag = 0;
        d_flag = (*(str + i) == '.');

        for(i += d_flag; i < len &&  *(str + i) != ' ' &&
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



//-----------------------------------------------------------------------------


        int epower = 0;
        int e_flag = 0;

        e_flag = (*(str + i) == 'e' || *(str + i) == 'E');
        i += e_flag;
        int esign = (*(str + i) == '-') ? -1 : 1;
        s_flag = (*(str + i) == '+' || *(str + i) == '-');

        for(i += s_flag; i < len && *(str + i) != ' '; i++){

            if (isdigit (*(str + i))){

                epower += epower * 10 + (*(str + i) - '0');
                if (!isfinite (val)) return 2;
            }
            else
                return 0;
        }

        while (*(str + len - 1) == ' ') len--;

        if (len != i)  return 0;
        *var = val * sign * pow (10, epower * esign) ;
        return 1;
    }

    else
        return 0;
}

int comp_str(char line1[], char line2[]){

    int i = 0;
    for (; line1[i] != '\0' && line2[i] != '\0' && line1[i] == line2[i];i++);

    return line1[i] == '\0' && line2[i] == '\0';

}

