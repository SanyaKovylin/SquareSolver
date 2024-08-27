//! \file
//! \brief Checking input file
//!

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>
#include "sq_sol.h"

#define NextSym (*(Buffer+*Position))

enum Length {MAXLENGTH = 1000, LENGTH = 150,SHRT = 3};

struct Flags {

    int NeedTest;
    int IsExp;
    int NeedHelp;

    };

int CheckInputFlags(char *argv[], int ArgNum, int *NeedTest, int *IsExp);
void BufStrip(char *Buffer, int *Length, int *Position);

void CheckInput (double *coef, char letter);
char *ManualInput(char str[]);

MainRespond Print(double Solution1, double Solution2, int NumRoots, const char Form);

InputStatus DecimalPart(double *power, double *val, char *str, int *i, int len);
InputStatus ExponentalPart (int *esign, int *epower, char *str, int *i, int len);
InputStatus IntPart(int *sign, double *val,char *str, int *i, int len);

void Help(void);
bool CompStr(const char Line1[], const char Line2[]);

int ParseConsoleArgument(char *argv[], int CurrentPos, int CurrentArg, struct Flags *ConsFlags);

const int ConsFlagErr = -2;

/*!
    \brief Adjusts alternately input of 3 coefficients

    \param [in] *CoefA, *Coef B, CoefC     Pointers to coefficients' cells

*/
void InputCoefficients(double *CoefA, double *CoefB, double *CoefC){

    assert(CoefA != NULL);
    assert(CoefB != NULL);
    assert(CoefC != NULL);

    printf ("Please, enter the coefficients of your equation of the form a*x^2 + b*x + c = 0\n");

    CheckInput (CoefA, 'a');
    CheckInput (CoefB, 'b');
    CheckInput (CoefC, 'c');
}

/*!
    \brief Adjusts input of coefficients and flags from console

    \param [in] *CoefA, *Coef B, CoefC     Pointers to coefficients' cells
    \param [in] *argv[], ArgNum            Standart console input (ArgNum = argc - 1)
    \param [in] *NeedTest *IsExp           Pointers to console flags' cells

*/

InputStatus ConsoleInput (double *CoefA, double *CoefB, double *CoefC,
                            char *argv[], int ArgNum,
                            int *NeedTest, int *IsExp){

    assert(CoefA != NULL);
    assert(CoefB != NULL);
    assert(CoefC != NULL);
    assert(argv != NULL);
    assert(NeedTest != NULL);
    assert(IsExp != NULL);

    int ArgGet = 0;
    const int NeedHelp = -1;
    ArgGet = CheckInputFlags (argv, ArgNum, NeedTest, IsExp);
    if (ArgNum - ArgGet == NumOfCoefs){ // 3? numOfCoefficients

        InputStatus Status = OK;

        if ((Status = InputToDouble (CoefA, argv[ArgGet++])) != OK) return Status;
        if ((Status = InputToDouble (CoefB, argv[ArgGet++])) != OK) return Status;
        if ((Status = InputToDouble (CoefC, argv[ArgGet++])) != OK) return Status;

        return Status;
    }
    else if (ArgNum - ArgGet == NeedHelp) {
        return HELP;
    }
    else if (ArgNum - ArgGet == 0) {
        return NOSOLVE;
    }
    return INPERROR;
}

/*!
    \brief Processing input of one Coefficient Variable

    \param [in]  *Coef    Pointer for coefficient cell
    \param [in]  Letter    Name of Coef that will be printed
*/

void CheckInput (double *Coef, char Letter){

    assert(Coef != NULL);

    printf ("%c: ", Letter);

    InputStatus Status = OK;
    char Buffer[MAXLENGTH] = {0};

    while ((Status = InputToDouble (Coef, ManualInput(Buffer))) != OK){
        switch (Status) {
            case INPERROR: {
                printf ("Your input has wrong type, please,"
                                        "reenter coefficient %c\n", Letter);
                printf ("%c: ", Letter);
                break;
            }
            case TOOBIG: {
                printf ("Your input is too big, because you are pig."
                                        "Please, reenter coefficient %c"
                                        "for this program edition.\n", Letter);
                printf ("%c: ", Letter);
                break;
            }
            case OK: {
                 printf("LogicError");
                 break;
            }
            case HELP: break;

            case NOSOLVE: break;

            default: printf ("Error: InputError: Status = %d", Status);
        }

        for (int i = 0; i < MAXLENGTH; i++) Buffer[i] = '\0'; // Buffer clean
    }
}

/** \defgroup StrToD All

    \brief String to double

    @{
*/

/*!
    \brief My strtod

    \param [in] Buffer          From char
    \param [out] *CoefValue     To double

*/

InputStatus InputToDouble (double *CoefValue, char Buffer[]){

    assert(CoefValue != NULL);

    int Length = 0;

    for (Length = 0; Length < MAXLENGTH && (*(Buffer + Length) != '\0')
                                        &&  *(Buffer + Length) != '\n'; Length++) ;

    double Value = 0;

    if (Length) {

        int Position = 0;

        BufStrip(Buffer, &Length, &Position);

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

        if (Length != Position)
            return INPERROR;

        *CoefValue = Value * Sign * pow (10, EPower * ESign) ;
        return  OK;
    }
    else {
        return INPERROR;
    }
}

/**  \brief Processes part of double between the dot and the exponental part

    \param [out] *Power             Pointer to var that contains number of digits after dot
    \param [out] *Value             Pointer to var that contains the (Value of double) * Power
    \param [in]  *Buffer, Position  Pointers to char and its processing point
    \param [in]  Length             Length of the char

    \returns Status of processing
*/

InputStatus DecimalPart(double *Power, double *Value,
                        char *Buffer, int *Position, int Length){

    assert(Power != NULL);
    assert(Value != NULL);
    assert(Buffer != NULL);
    assert(Position != NULL);

    bool WasDot = (NextSym == '.');

    for(*Position += WasDot; *Position < Length &&
                              NextSym != ' '    &&
                              NextSym != 'e'    &&
                              NextSym != 'E'; (*Position)++) {

        if (isdigit (NextSym)) {

            *Power /= 10.0;
            *Value += (NextSym - '0') * *Power;
            if (!isfinite (*Value))
                return TOOBIG;
        }
        else {
            return INPERROR;
        }
    }
    return OK;
}

void BufStrip(char *Buffer, int *Length, int *Position){

    assert(Buffer != NULL);
    assert(Length != NULL);

    while (Buffer[*Position] == ' ') (*Position) += 1;
    while (*(Buffer + *Length - 1) == ' ') (*Length)--;
}

/**  \brief Processes part of double after the exponental part

    \param [out] *EPower            Pointer to var that contains Value of power of 10 by which we must multiply the Value
    \param [out] *ESign             Pointer to var that contains the sign of power of 10
    \param [out] *Value             Pointer to var that contains the Value of double
    \param [in]  *Buffer, Position  Pointers to char and its processing point
    \param [in]  Length             Length of the char

    \returns Status of processing
*/

InputStatus ExponentalPart (int *ESign, int *EPower,
                            char *Buffer, int *Position, int Length){

    assert(ESign != NULL);
    assert(EPower != NULL);
    assert(Position != NULL);
    assert(Buffer != NULL);

    int WasSign = 0;
    int IsExp = 0;

    IsExp = (NextSym == 'e' || NextSym == 'E');
    *Position += IsExp;

    *ESign = (NextSym == '-') ? -1 : 1;

    WasSign = (NextSym == '+' || NextSym == '-');

    for(*Position += WasSign; *Position < Length && NextSym != ' '; (*Position)++){

        if (isdigit (NextSym)) {
            *EPower += (*EPower) * 10 + (NextSym - '0');
        }
        else {
            return INPERROR;
        }
    }
    return OK;
}

/**  \brief Processes part of double between the dot and the exponental part

    \param [out] *Sign              Pointer to var that contains the sign of the double
    \param [out] *Value             Pointer to var that contains the (Value of double) * Power
    \param [in]  *Buffer, Position  Pointers to char and its processing point
    \param [in]  Length             Length of the char

    \returns Status of processing
*/

InputStatus IntPart(int *Sign, double *Value,
                    char *Buffer, int *Position, int Length) {

    assert(Buffer != NULL);
    assert(Sign != NULL);
    assert(Value != NULL);
    assert(Position != NULL);

    *Sign = (NextSym == '-') ? -1 : 1;
    bool WasSign = (NextSym == '+' || NextSym == '-');

    for (*Position += WasSign; *Position < Length  &&
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
            return INPERROR;
        }
    }

    return OK;
}

// }@

/** \brief Function for comparing two strings

    \param [in] Line1, Line2     Chars to compare

    \returns The result of compare
*/

bool CompStr(const char *Line1, const char *Line2){

    assert(Line1 != NULL);
    assert(Line2 != NULL);

    int Position = 0;
    for (; Line1[Position] != '\0' && Line2[Position] != '\0'
                                   && Line1[Position] == Line2[Position]; Position++);

    return Line1[Position] == '\0' && Line2[Position] == '\0';

}

/** \brief Function for inputing the string from the stdin

    \param [in] Buffer     Pointer to the container where should put the string

    \returns Inputed string
*/

char *ManualInput(char *Buffer){

    assert(Buffer != NULL);

    int Length = 0, c = 0;

    for (Length = 0; Length < MAXLENGTH && (c = getchar()) != EOF && c != '\n'; Length++)
        *(Buffer + Length) = (char) c;

    return Buffer;
}

/** \brief Processing Console flags

    \param [in] argv, ArgNum        Standart console input (ArgNum = (argc - 1))
    \param [out] NeedTest, IsExp    Flags from console

    \returns number of collected flags or ArgNm + 1 if Help called
*/


int CheckInputFlags(char *argv[], int ArgNum, int *NeedTest, int *IsExp){

    assert(NeedTest != NULL);
    assert(argv != NULL);
    assert(IsExp != NULL);

    int ArgGet = 0;
    int CurrentArg = 1;
    struct Flags ConsoleFlags = {0, 0, 0};

    int argc = ArgNum;
    while (CurrentArg < argc && (argv)[CurrentArg][0] == '-'
                             && !isdigit ((argv)[CurrentArg][1])){

        int CurrentPos = 0;
        CurrentPos++;

        int Status = ParseConsoleArgument(argv, CurrentPos, CurrentArg, &ConsoleFlags);

        ArgGet++;
        CurrentArg++;

        if (!Status) {
            return 0;
        }
    }

    *NeedTest = ConsoleFlags.NeedTest;
    *IsExp = ConsoleFlags.IsExp;

    if (ConsoleFlags.NeedHelp) {
        Help();
        return ArgNum + 1;
    }

    return ArgGet;
}

/** \brief Processing each Console flag

    \param [in] argv                        Standart console input
    \param [in] CurrentPos, CurrentFlag     Pointers to the processing symbol
    \param [out] ConsFlags                  Contains the values of all flags

    \returns if the flag was got correctly
*/

int ParseConsoleArgument(char *argv[], int CurrentPos, int CurrentArg, struct Flags *ConsFlags){

    assert(argv != NULL);
    assert(ConsFlags != NULL);

    char c = '\0';
    while ((c = argv[CurrentArg][CurrentPos])){
        switch (c){

            case 'h':{
                ConsFlags->NeedHelp = 1;
                break;
            }

            case 't':{
                ConsFlags->NeedTest = 1;
                break;
            }

            case 'e':{
                ConsFlags->IsExp = 1;
                break;
            }

            case '-':{

                if (CompStr((argv[CurrentArg]), "--test")) {
                    ConsFlags->NeedTest = 1;
                    return 1;
                }
                else if (CompStr((argv[CurrentArg]), "--help")) {
                    ConsFlags->NeedHelp = 1;
                    return 1;
                }
                else return 0;
            }

            default : return 0;
        }
    }
    return 1;
}

/*!
    \brief Adjusts branch of output by the its form

    \param [in] Solution1,Solution2     Solutions to print
    \param [in] NumRoots                Number of roots
    \param [in] IsExp                   Is out in Exsponental form

    \return code-of-exit
*/


MainRespond FormOutput(double Solution1, double Solution2, int NumRoots, int IsExp){

    assert (isfinite (Solution1));
    assert (isfinite (Solution2));

    if (IsExp){
        const char Form = 'e';
        return Print(Solution1, Solution2, NumRoots, Form);
    }
    else{
        const char Form = 'g';
        return Print(Solution1, Solution2, NumRoots, Form);
    }

}

/*!
    \brief Adjusts branch of output by the its form

    \param [in] Solution1, Solution2    Solutions to print
    \param [in] NumRoots                Number of roots
    \param [in] Form                    Form in which solutions should be printed

    \return code-of-exit
*/

#pragma GCC diagnostic ignored "-Wformat-nonliteral"

MainRespond Print(double Solution1, double Solution2, int NumRoots, const char Form){

    switch (NumRoots){

            case 1 : {

                char Format[LENGTH] = "";
		        sprintf (Format, "The equation has only one root: \nx1 = %%%c\n", Form);
		        printf (Format, Solution1);

                return MAIN;
            }

            case 2 : {

                char Format[LENGTH] = "";
		        sprintf (Format, "Your equation has two roots: \nx1 = %%%c" "\nx2 = %%%c\n", Form, Form);
		        printf (Format, Solution1, Solution2);

                return MAIN;
            }

            case 0 : {

                printf ("Your equation has no roots\n");

                return MAIN;
            }

            case INFROOTS : {

                printf ("Your equation has INFROOTS roots. Go away in your dirty boots.\n");

                return MAIN;
            }

            default : return MISTAKE;
        }
}

#pragma GCC diagnostic error "-Wformat-nonliteral"

///  \brief    Prints --help for console flag

void Help(void){
    printf(
        "Project [options] [coefs]  usage information\n"
        "Options\n"

        "\t-h/--help     Display this information\n"
        "\t-t/--test     Do Unit-test at the star of solving\n"
        "\t-e            Display roots in exponental Form\n"

        "\n\n\n"

        "\tAFTER optional arguments enter 3 coefficients splitted with <Space>\n\n\n"
    );
}
