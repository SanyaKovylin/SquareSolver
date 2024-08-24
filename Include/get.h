#ifndef GET_H_INCLUDED
#define GET_H_INCLUDED

InputStatus ConsoleInput (double *a_coef, double *b_coef, double *c_coef, char *line[], int cou, int *test, int *e);
InputStatus InputToDouble (double *CoefValue, char Buffer[]);
void CheckInput (double *coef, char letter);

InputStatus DecimalPart(double *power, double *val, char *str, int *i, int len);
InputStatus ExponentalPart (int *esign, int *epower, char *str, int *i, int len);
InputStatus IntPart(int *sign, double *val,char *str, int *i, int len);
char *ManualInput(char str[]);

enum Length {MAXLENGTH = 1000, LENGTH = 150,SHRT = 3};


#endif // GET_H_INCLUDED
