#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ParameterStack ParameterStack;
typedef struct Parameter_node Parameter_node;

struct Parameter_node
{
    int type;
    int value;
    char* key;
    Parameter_node* next;
};

typedef enum{
    STRING, 
    INTEGER,
    DOUBLE
} parameter_type;

struct ParameterStack
{
    Parameter_node* top;
};

void* get_parameter(Parameter_node* list, char* key);
bool has_parameter(Parameter_node* list, char* key);

int get_parameter_type(Parameter_node* list, char* key);
Parameter_node* add_parameter(Parameter_node* list, char* key, int value, int type);
Parameter_node* set_parameter(Parameter_node* list, char* key, int value, int type);
Parameter_node* new_node(char* key, int value, int type, Parameter_node* next);
void free_stack(ParameterStack* stack);
void free_node_list(Parameter_node* node);
void print_parameter_nodes(Parameter_node* node);