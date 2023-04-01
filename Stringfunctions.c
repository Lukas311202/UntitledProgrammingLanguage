#include "Stringfunctions.h"

int strlen2(char* text){
    int count = 0;
    while(text[count++]!=0);
    return count-1;
}

//dynamicly allocated copy of the string
char* s_copy(char* text){
    char* s = malloc(strlen2(text) * sizeof(char));
    char* t = text;
    char* d = s;
    while(*d++ = *t++);

//     printf("string copied\n");
    return s;
}

char* copy_substring(char* text, int start, int end){
    char* s = malloc(sizeof(char) * (end - start) + 1);
    int i = start;
    for(; i< end + 1; i++){
        s[i-start] = text[i];
    }
    s[end-start+1] = 0;
    return s;
}
