#include "Stringfunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "basicfunctions.h"
#include "Parameter_stack.h"
#include "reader.h"

typedef enum TokenType TokenType;
enum TokenType{
    OPERAND,
    OPERATOR,
    UNKNOWN,
    END,
    ASSSIGNEMENT,
    PARAMETER,
    NEW_LINE
};

char* TokenTypeArr[] = {"OPERAND", "OPERATOR", "UNKNOWN", "END", "ASSIGNMENT", "Parameter", "NEW_LINE"};

unsigned int TypeHierarchy[] = {10, 5, 0, 0, 20, 0};

typedef int (*Function)(int x, int y);

void evaluate_expression(char* text);