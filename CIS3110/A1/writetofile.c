#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE* file;
    file = fopen("test.txt","w");

    fputc(2,file);
    fputc(49,file);
    fputc(130,file);
    fputc(49,file);
    fputc(16,file);
    fputc(49,file);
    fputc(128,file);
    fputc(49,file);


    return 0;
}