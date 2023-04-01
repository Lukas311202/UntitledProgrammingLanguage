#include "Parameter_stack.h"

Parameter_node* new_node(char* key, int value, int type, Parameter_node* next){
    Parameter_node* n = malloc(sizeof(Parameter_node));
    n->key = key;
    n->next = next;
    n->type = type;
    n->value = value;
    return n;
}

ParameterStack* new_parameter_stack(){
    ParameterStack* stack = malloc(sizeof(ParameterStack));
}

void* get_parameter(Parameter_node* list, char* key){
    for (Parameter_node* node = list; node != NULL; node = node->next)
    {
        if(strcmp(node->key, key) == 0) return &node->value;
    }
    return NULL;
}

bool has_parameter(Parameter_node* list, char* key){
    return get_parameter(list, key) != NULL;
}

int get_parameter_type(Parameter_node* list, char* key){
    for (Parameter_node* node = list; node != NULL; node = node->next)
    {
        if(strcmp(node->key, key) == 0) return node->type;
    }
    return -1;
}

Parameter_node* add_parameter(Parameter_node* list, char* key, int value, int type){
    if(list == NULL) return new_node(key, value, type, NULL);
    Parameter_node* count = list;
    while(count->next != NULL) count = count->next;
    count->next = new_node(key, value, type, NULL);
    printf("parameter added\n");
    return list;
}

//similiar to add_parameter only that this one first searches for the paramter and will just replace him before adding a new one
Parameter_node* set_parameter(Parameter_node* list, char* key, int value, int type){
    if(!has_parameter(list, key)) return add_parameter(list, key, value, type);
    for(Parameter_node* n = list; n != NULL; n = n->next){
        if(strcmp(n->key, key) == 0){
            printf("overwrite existing parameter\n");
            n->value = value;
            n->type = type;
            break;
        }
    }
    return list;
}

void free_node(Parameter_node* node){
    free(node);
}

void free_node_list(Parameter_node* node){
    if(node == NULL) return;
    free_node_list(node->next);
    free_node(node);
    printf("node freed\n");
}

void free_stack(ParameterStack* stack){
    for(Parameter_node* node = stack->top; node != NULL; node = node->next){
        Parameter_node* next = node->next;
        free_node(node);
        node = next;
    }
}

void print_parameter_nodes(Parameter_node* node){
    if(node == NULL) return;
    printf("%s : ", node->key);
    switch (node->type){
    // case STRING:
    //     printf("%s", (char*)node->value);
    //     break;
    case INTEGER:
        printf("%d", node->value);
        break;
    
    default:
        break;
    }
    printf("\n");
    print_parameter_nodes(node->next);
}