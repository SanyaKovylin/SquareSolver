//! \file
//! \brief Checking input file
//!

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>
#include "get.h"
#include "sq_sol.h"




/* main (void){
    double v = 0;
    int res = big_get (&v);
    printf ("%lg %d \n", v, res);
}  */


int comp_str (char line1[],const char line2[]);
int check_add_input(char *argv[], int cou, int *test, int *e);
void help(void);

//! @brief Bilds double from the line of chars
//!
//! @param *var Pointer to input's cell
//!
//! @return the code of output
//!

/*!
    \brief Adjusts alternately input of 3 coefficients

    \param [in] *a_coef      Pointer for coefficient a's cell
    \param [in] *b_coef      Pointer for coefficient b's cell
    \param [in] *c_coef      Pointer for coefficient c's cell
*/
void input(double *a_coef, double *b_coef, double *c_coef){

    printf ("Please, enter the coefficients of your equation of the form a*x^2 + b*x + c = 0\n");

    check_input (a_coef, 'a');
    check_input (b_coef, 'b');
    check_input (c_coef, 'c');

    //printf ("%lg %lg %lg", *a_coef, *b_coef, *c_coef);
}

int cons_get (double *a_coef, double *b_coef, double *c_coef, char *argv[], int cou, int *test,int *e){
    int add = 0;
    add = check_add_input (argv, cou, test, e);

    if (cou - add == 3){

        get_num (a_coef, argv[1+add]);
        get_num (b_coef, argv[2+add]);
        get_num (c_coef, argv[3+add]);

        return 1;
    }
    else if (cou - add == -1)
        return -1;
    return 0;
}

/*!
    \brief Processing input of one variable

    \param [in]  *coef    Pointer for coefficient cell
    \param [in] letter    Name of coef that will be printed
*/

void check_input (double *coef, char letter){

    printf ("%c: ", letter);

    int error_type = 0;
    char str [MAXLENGTH] = {0};

    while ((error_type = get_num (coef, arm_inp(str))) != 1){
        switch (error_type){
            case 0: {
                printf ("Your input has wrong type, please, reenter coefficient %c\n", letter);
                printf ("%c: ", letter);
                break;
            }
            case 2: {
                printf ("Your input is too big, because you are pig. Please, reenter coefficient %c for this program edition.\n", letter);
                printf ("%c: ", letter);
                break;
            }
            default: printf ("Error: InputError: error_type = %d", error_type);
        }
        for (int i = 0; i<MAXLENGTH;i++) str[i] = '\0';
    }
}

int get_num (double *var, char str[]){

    int c = '\0';
    int len = 0;

    for (len = 0; len < MAXLENGTH && (*(str + len) != '\0') && c != '\n'; len++);

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

int comp_str(char line1[],const char line2[]){


    int i = 0;
    for (; line1[i] != '\0' && line2[i] != '\0' && line1[i] == line2[i];i++);

    return line1[i] == '\0' && line2[i] == '\0';

}


char *arm_inp(char str[]){

    int len = 0, c = 0;

    for (len = 0; len < MAXLENGTH && (c = getchar()) != EOF && c != '\n'; len++)
        *(str + len) = (char) c;

    return str;
}



int check_add_input(char *argv[], int cou, int *test, int *e){
    int c;
    int add = 0;

    while ( (*++argv)[0] == '-' && !isdigit ((*argv)[0])){

        while (c = *++argv[0]){

                switch (c){

                    case 'h':{help(); return cou + 1;}

                    case 't':{ *test = 1; break;}

                    case 'e':{ *e    = 1; break;}

                    case '-':{

                        if (comp_str((*argv), "-test")) {*test = 1; goto skip;}
                        else if (comp_str((*argv), "-help")) {help(); return cou + 1;}
                        else return 0;
                        break;
                    }

                    default : return 0;
                }
        }
        skip:
        cou -= 1;
        add++;
    }
    return add;
}


void help(void){
    printf(
        "Project [options] [coefs]  usage information\n"
        "Options\n"

        "\t-h/--help     Display this information\n"
        "\t-t/--test     Do Unit-test at the star of solving\n"
        "\t-e            Display roots in exponental form\n"

        "\n\n\n"

        "\tAFTER optional arguments enter 3 coefficients splitted with <Space>\n"

    );
}
