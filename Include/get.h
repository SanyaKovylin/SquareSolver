#ifndef GET_H_INCLUDED
#define GET_H_INCLUDED


int get_input (double *var);
int cons_get (double *a_coef, double *b_coef, double *c_coef, char *line[], int cou,int *test,int *e);
void check_input (double *coef, char letter);

int get_num(double *var, char str[] = {0});

int dot_check(double *power, double *val, char *str, int *i, int len);
int e_check (int *esign, int *epower, char *str, int *i, int len);
int pre_check(int *sign, double *val,char *str, int *i, int len);
char *arm_inp(char str[]);

enum length {MAXLENGTH = 1000};


#endif // GET_H_INCLUDED
