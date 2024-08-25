//! \file
//! \brief Checking input file
//!

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>
#include "sq_sol.h"
#include "get.h"


#define NextSym (*(Buffer+*Position))

int CompStr (char line1[],const char line2[]);
int CheckInputFlags(char *argv[], int ArgNum, int *test, int *e);
MainRespond Print(double Sol1, double Sol2, int NumRoots, const char Form);
void Help(void);

/*!
    \brief Adjusts alternately input of 3 coefficients

    \param [in] *a_coef      Pointer for coefficient a's cell
    \param [in] *b_coef      Pointer for coefficient b's cell
    \param [in] *c_coef      Pointer for coefficient c's cell
*/
void InputCoefficients(double *a_coef, double *b_coef, double *c_coef){

    printf ("Please, enter the coefficients of your equation of the Form a*x^2 + b*x + c = 0\n");

    CheckInput (a_coef, 'a');
    CheckInput (b_coef, 'b');
    CheckInput (c_coef, 'c');
}

InputStatus ConsoleInput (double *a_coef, double *b_coef, double *c_coef, char *argv[], int ArgNum, int *TestFlag,int *FormFlag){

    int ArgGet = 0;
    const int HelpFlag = -1;
    ArgGet = CheckInputFlags (argv, ArgNum, TestFlag, FormFlag);

    if (ArgNum - ArgGet == NumOfCoefs){ // 3? numOfCoefficients

        InputStatus Status = OK;

        if ((Status = InputToDouble (a_coef, argv[ArgGet++])) != OK) return Status;
        if ((Status = InputToDouble (b_coef, argv[ArgGet++])) != OK) return Status;
        if ((Status = InputToDouble (c_coef, argv[ArgGet++])) != OK) return Status;

        return Status;
    }
    else if (ArgNum - ArgGet == HelpFlag) {
        return Help;
    }
    return ERROR;
}

/*!
    \brief Processing input of one CoefValueiable

    \param [in]  *coef    Pointer for coefficient cell
    \param [in] letter    Name of coef that will be printed
*/

void CheckInput (double *coef, char letter){

    printf ("%c: ", letter);

    InputStatus status = OK;
    char Buffer[MAXLENGTH] = {0};

    while ((status = InputToDouble (coef, ManualInput(Buffer))) != OK){
        switch (status) {
            case ERROR: { // magic consts
                printf ("Your input has wrong type, please, reenter coefficient %c\n", letter);
                printf ("%c: ", letter);
                break;
            }
            case TOOBIG: {
                printf ("Your input is too big, because you are pig. Please, reenter coefficient %c for this program edition.\n", letter);
                printf ("%c: ", letter);
                break;
            }
            case OK: {
                 printf("LogicError");
                 break;
            }
            case HELP: break;

            default: printf ("Error: InputError: status = %d", status);
        }

        for (int i = 0; i < MAXLENGTH; i++) Buffer[i] = '\0'; // Buffer clean
    }
}

InputStatus InputToDouble (double *CoefValue, char Buffer[]){

    int c = '\0';
    int Length = 0;

    for (Length = 0; Length < MAXLENGTH && (*(Buffer + Length) != '\0') && c != '\n'; Length++)
        ;

    double Value = 0;

    if (Length) {

        int Position = 0;
        // Bufferip()
        while ( Buffer[Position] == ' ') Position++;

        int Sign = 0;
        double Power = 1;
        int EPower = 0;
        int ESign = 0;

        InputStatus Status = OK ;

        if ((Status = IntPart(&Sign, &Value, Buffer, &Position, Length))!= OK)
            return Status;

        if ((Status = DecimalPart(&Power, &Value, Buffer, &Position, Length)) != OK)
            return Status;

        if ((Status = ExponentalPart(&ESign, &EPower, Buffer, &Position, Length))!= OK)
            return Status;

        // tripSpaces()
        while (*(Buffer + Length - 1) == ' ') Length--;

        if (Length != Position)
            return ERROR;

        *CoefValue = Value * Sign * pow (10, EPower * ESign) ;
        return  OK;
    }
    else
        return ERROR;
}

InputStatus DecimalPart(double *Power, double *Value,char *Buffer, int *Position, int Length){
        int DotFlag = 0;
        DotFlag = (NextSym == '.');

        // ne ponyantno
        for(*Position += DotFlag; *Position < Length   &&
                                        NextSym != ' ' &&
                                        NextSym != 'e' &&
                                        NextSym != 'E'; (*Position)++) {

            if (isdigit (NextSym)) {

                *Power /= 10.0;
                *Value += (NextSym - '0') * *Power;
                if (!isfinite (*Value))
                    return TOOBIG;
            }
            else {
                return ERROR;
            }
        }
    return OK;
}

InputStatus ExponentalPart (int *ESign, int *EPower, char *Buffer, int *Position, int Length){

    int SignFlag = 0;
    int EFlag = 0;

    EFlag = (NextSym == 'e' || NextSym == 'E');
    *Position += EFlag;

    *ESign = (NextSym == '-') ? -1 : 1;

    SignFlag = (NextSym == '+' || NextSym == '-');

    for(*Position += SignFlag; *Position < Length && NextSym != ' '; (*Position)++){

        if (isdigit (NextSym)) {
            *EPower += (*EPower) * 10 + (NextSym - '0');
        }
        else {
            return ERROR;
        }
    }
    return OK;
}

InputStatus IntPart(int *Sign, double *Value,char *Buffer, int *Position, int Length) {

    *Sign = (NextSym == '-') ? -1 : 1;
    int SignFlag = 0;
    SignFlag = (NextSym == '+' || NextSym == '-');

    for (*Position += SignFlag; *Position < Length  &&
                                    NextSym != '.'  &&
                                    NextSym != ' '  &&
                                    NextSym != 'e'  &&
                                    NextSym != 'E'; (*Position)++) {

        if (isdigit (NextSym)) {

            *Value = 10.0 * *Value + (NextSym - '0');

            if (!isfinite (*Value))
                return TOOBIG;
        }
        else {
            return ERROR;
        }
    }

    return OK;
}

int CompStr(char line1[],const char line2[]){


    int Position = 0;
    for (; line1[Position] != '\0' && line2[Position] != '\0'
                                   && line1[Position] == line2[Position]; Position++);

    return line1[Position] == '\0' && line2[Position] == '\0';

}

char *ManualInput(char Buffer[]){

    int Length = 0, c = 0;

    for (Length = 0; Length < MAXLENGTH && (c = getchar()) != EOF && c != '\n'; Length++)
        *(Buffer + Length) = (char) c;

    return Buffer;
}

int CheckInputFlags(char *argv[], int ArgNum, int *TestFlag, int *FormFlag){
    int c = 0; // uninit
    int ArgGet = 0;

    while ((*++argv)[0] == '-' && !isdigit ((*argv)[0])){

        while ((c = *++argv[0])){

                switch (c){

                    case 'h':{Help(); return ArgNum + 1;}

                    case 't':{ *TestFlag = 1; break;}

                    case 'e':{ *FormFlag = 1; break;}

                    case '-':{

                        if      (CompStr((*argv), "-test")) { *FormFlag = 1; goto skip;  }
                        else if (CompStr((*argv), "-help")) { Help(); return ArgNum + 1; }
                        else return 0;
                        break;
                    }

                    default : return 0;
                }
        }
        skip:
        ArgNum -= 1;
        ArgGet++;
    }
    return ArgGet;
}

/*!
    \brief Adjusts onput of solutions

    Use case branch by the type of output

    \param [in] Sol1,Sol2    Solutions to print
    \param [in] NumRoots    Number of roots
    \param [in] e    Is out in E-Form

    \return code-of-exit
*/


MainRespond FormOutput(double Sol1, double Sol2, int NumRoots, int EFlag){

    assert (isfinite (Sol1));
    assert (isfinite (Sol2));

    if (EFlag){
        const char Form = 'e';
        return Print(Sol1, Sol2, NumRoots, Form);
    }
    else{
        const char Form = 'g';
        return Print(Sol1, Sol2, NumRoots, Form);
    }

}

#pragma GCC diagnostic ignored "-Wformat-nonliteral"

MainRespond Print(double Sol1, double Sol2, int NumRoots, const char Form){

    switch (NumRoots){

            case 1 : {

                char Format[LENGTH] = "";
		        sprintf (Format, "The equation has only one root: \nx1 = %%%c", Form);
		        printf (Format, Sol1);

                return MAIN;
            }

            case 2 : {

                char Format[LENGTH] = "";
		        sprintf (Format, "The equation has only one root: \nx1 = %%%c" "\nx2 = %%%c", Form, Form);
		        printf (Format, Sol1, Sol2);

                return MAIN;
            }

            case 0 : {

                printf ("Your equation has no roots");

                return MAIN;
            }

            case INFROOTS : {

                printf ("Your equation has INFROOTS roots. Go away in your dirty boots.");

                return MAIN;
            }

            default : return MISTAKE;
        }
}

#pragma GCC diagnostic error "-Wformat-nonliteral"

void Help(void){
    printf(
        "Project [options] [coefs]  usage information\n"
        "Options\n"

        "\t-h/--help     Display this information\n"
        "\t-t/--test     Do Unit-test at the star of solving\n"
        "\t-e            Display roots in exponental Form\n"

        "\n\n\n"

        "\tAFTER optional arguments enter 3 coefficients splitted with <Space>\n"
    );
}
