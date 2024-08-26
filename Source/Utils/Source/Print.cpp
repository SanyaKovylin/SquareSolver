#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <windows.h>
#include <stdarg.h>

enum Codes {OK = 1, TTT = 0, TOOBIG = 2};
enum Length {BUFFERLENGTH = 1000};

HANDLE hConsole = GetStdHandle (STD_OUTPUT_HANDLE);

Codes ColorPrint(const char *Line, ...);
void CleanBuf(char *Buffer);
Codes PrintfFlags(const char *Line, int *LinePoint);
Codes ColorFlags(const char *Line, int *LinePoint);

int main (void){
    Codes ret = OK;
    ret = ColorPrint ("Here is text of print%d", 10);
    if (ret == OK) return 0;
}

// % s c d g lld llg lg ld lu llu e E f lf llf llud
Codes ColorPrint(const char *Line, ...){

    va_list Pointer;
    va_start (Pointer, Line);

    char Buffer[BUFFERLENGTH] = {'\0'};
    Codes e = OK;

    int BufPoint  = 0;
    int LinePoint = 0;
    while (Line[LinePoint] != '\0'){

        while (Line[LinePoint] != '%' || Line[LinePoint] != '$'){
            Buffer[BufPoint++] = Line[LinePoint++];
        }
        printf("OOOO");
        #pragma GCC diagnostic ignored "-Wformat-nonliteral"
        printf(Buffer);
        #pragma GCC diagnostic error "-Wformat-nonliteral"

        switch (Line[LinePoint]){

            case '%': e = PrintfFlags(Line, &LinePoint);

            case '$': e = ColorFlags(Line, &LinePoint);
        }


        LinePoint++;
        CleanBuf(Buffer);

    }
     return e;
}


void CleanBuf(char *Buffer){
    for (int point = 0; Buffer[point] != '\0' && point < BUFFERLENGTH; point++)
        Buffer[point] = '\0';
}

Codes PrintfFlags(const char *Line, int *LinePoint){
    printf("\t%\n");
    return OK;
}

Codes ColorFlags(const char *Line, int *LinePoint){
    printf("\t$\n");
    return OK;
}






