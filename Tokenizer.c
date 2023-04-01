#include "Tokenizer.h"

typedef struct Token Token;
struct Token{
    TokenType tag;
    union {
        char* function;
        int value;
        char* param;
    };
    char* expression;
    Token* next;
};

typedef struct TokenStack TokenStack;
struct TokenStack{
    Token* first;
};

Token* make_token(char* expressiom, TokenType tag, Token* next){
//     printf("make token\n");
    Token* t = malloc(sizeof(Token));
    t->tag = tag;
    t->expression = s_copy(expressiom);
    t->next = next;
    return t;
}

bool end_of_token(char c){
    return c == ' ' || c == 0;
}

bool is_whitespace(char c){
    return c == ' ';
}

void add_token(TokenStack* stack, Token* new_token){
    if(stack->first == NULL) {
//         printf("put in first place\n");
        stack->first = new_token;
        return;
    }
    Token* list = stack->first;
    for(; list->next != NULL; list = list->next);
    list->next = new_token;
//     printf("added token\n");
}

//skips whitespaces and returns the new position
int skip_whitespace(char* expression, int idx){
    while(expression[idx] == ' ') idx++;
    return idx;
}

int jump_end_of_token(char* expression, int idx){
    while(expression[idx] != ' ' && expression[idx] != 0) idx++;
    return idx;
}

bool is_operator(char* expression){
    return (strcmp(expression, "/")==0) || (strcmp(expression, "*")==0) || (strcmp(expression, "+")==0) || (strcmp(expression, "-")==0);
}

//for now only intergers ie no floating point
bool is_operand(char* expression){
    for(int idx = 0; expression[idx] != 0; idx++){
        if(!('0' <= expression[idx] && expression[idx]  <= '9')) return false;
    }
    return true;
}

bool is_assignment(char* expression){
    if(strcmp(expression, "=") == 0) return true;
    return false;
}

TokenType determine_type(char* expression){
    if (is_operator(expression)) return OPERATOR;
    if( is_assignment(expression)) return ASSSIGNEMENT;
    if (is_operand(expression)) return OPERAND;
    if(strcmp(expression, "\n") == 0) return NEW_LINE;
    return PARAMETER;
}

TokenStack tokenize_expression(char* expression){
    printf("\nTOKENIZE EXPRESSION\n");
    TokenStack t;
    t.first = NULL;

    int start = 0;
    int end = 0;
    int idx = 0;
    while(expression[idx] != 0 && idx < strlen2(expression)){
        idx = skip_whitespace(expression, idx);
//         printf("skip whitespace idx: %d\n", idx);
        start = idx;
        idx = jump_end_of_token(expression, idx);
        end = idx-1;

        char* string = copy_substring(expression, start, end);
        int type = determine_type(string);
        Token* token = make_token(string, type, NULL);


        switch(type){
            case OPERAND:
                token->value = atoi(string);
//                 printf("number is %d\n", token->value);
                break;
            case OPERATOR:
                token->function = string;
                break;
            case ASSSIGNEMENT:
                token->function = string;
                break;
            case PARAMETER:
                token->param = string;
                break;
            case NEW_LINE:
                token->expression = s_copy("LINE BREAK");
                break;
        }
//         printf("type of %s is %s\n", string, TokenTypeArr[type]);

        add_token(&t, token);
//         printf("end of token idx: %d\n", idx);
    }

    return t;
}

void print_token_value(Token* t){
    printf("%s : %s\n", t->expression, TokenTypeArr[t->tag]);
}

void print_Token(Token* t){
    if(t == NULL) return;
    print_token_value(t);
    print_Token(t->next);
}

void free_tokens(Token* t){
    if(t == NULL) return;
    free_tokens(t->next);
    free(t->expression);
    free(t);
//     printf("token freed");
}

void print_Stack(TokenStack* t){
    printf("print stack\n");
    print_Token(t->first);
}


TreeNode* new_tree_node(int type, void* expression, TreeNode* left, TreeNode* right){
    TreeNode* t = malloc(sizeof(TreeNode));
    t->left = left;
    t->right = right;
    t->type = type;
    switch(type){
        case OPERAND:
            t->value = *(int*)expression;
            break;
        case OPERATOR:
            t->function = (char*)expression;
            break;
        case ASSSIGNEMENT:
            t->function = (char*)expression;
            break;
        case PARAMETER:
            t->param = (char*)expression;
            break;
    }
    return t;
}

TokenType get_hierarchy(TreeNode* tree){
    switch(tree->type){
        case OPERAND: return 100;
        case OPERATOR:
            if(strcmp(tree->function, "/") == 0) return 80;
            if(strcmp(tree->function, "*") == 0) return 70;
            if(strcmp(tree->function, "+") == 0) return 10;
            if(strcmp(tree->function, "-") == 0) return 10;
            return 5;
            break;
        case PARAMETER: return 100;
        case ASSSIGNEMENT: return 4;
    }
    return TypeHierarchy[tree->type];
}

void print_node_value(TreeNode* t){
    switch(t->type){
        case OPERAND:
//             snprintf(buffer, 10, "%d", t->value);
            printf("( %d )", t->value);
            break;
        case OPERATOR:
//             return t->function;
            printf("( %s )", t->function);
            break;
        case PARAMETER:
            printf("( %s )", t->param);            
            break;
        case ASSSIGNEMENT:
            printf("( %s )", t->function);            
            break;
    }
}

void print_two_nodes(TreeNode* t1, TreeNode* t2, char* text){
    print_node_value(t1);
    printf("%s", text);
    print_node_value(t2);
    printf("\n");
}

TreeNode* copy_tree_node(TreeNode* t){
    printf("tree copying...\n");
    void* expression;
    switch(t->type){
        case OPERAND:
            expression = &(t->value);
            break;
        case OPERATOR:
            expression = t->function;
            break;
        case PARAMETER:
            expression = t->param;
            break;
        case ASSSIGNEMENT:
            expression = t->function;
    }
    return new_tree_node(t->type, expression, t->left, t->right);
}

void overwrite_node_values(TreeNode* dst, TreeNode* src){
    printf("\noverwrite values\n");
    dst->type = src->type;
    dst->left = src->left;
    dst->right = src->right;
    switch(dst->type){
        case OPERAND:
            dst->value = src->value;
            break;
        case OPERATOR:
            dst->function = src->function;
            break;
        case PARAMETER:
            dst->param = src->param;
        case ASSSIGNEMENT:
            dst->function = src->function;
    }
}

void append_node(TreeNode* tree, TreeNode* newNode){
    if(tree == NULL) tree = newNode;
    int old_hierarchy = get_hierarchy(tree);
    int new_hierarchy = get_hierarchy(newNode);
    print_two_nodes(tree, newNode, " comparision ");
    if(old_hierarchy >= new_hierarchy){
        print_two_nodes(tree, newNode, " becomes the child of ");

        //make a copy of tree node with the old values and tree node takes over the values of newNode
        TreeNode* copy = copy_tree_node(tree);
        overwrite_node_values(tree, newNode);

        tree->left = copy;
        free_tree_node(newNode);

    }
    if(old_hierarchy < new_hierarchy){
        print_two_nodes(newNode, tree, " becomes the child of ");
        if(tree->left == NULL){
            if(tree->left == NULL) tree->left = newNode;
            else append_node(tree->left, newNode);

        }//tree->left = newNode;
        else {
            if(tree->right == NULL) tree->right = newNode;
            else append_node(tree->right, newNode);

        }
    }
//     printf("appended\n");
}

//attaches nodes acording their code hirarchy
void attach_to_tree(TreeNode* newNode, Tree* t){
    printf("attach");
    print_node_value(newNode);
    printf("\n");

    if(t->root == NULL) {
        t->root = newNode;
        return;
    }
    append_node(t->root, newNode);

}

void print_tree_node(TreeNode* t){
    if(t == NULL) return;
    printf("(");
    print_tree_node(t->left);
    switch(t->type){
        case OPERAND:
            printf("%d ", t->value);
            break;
        case ASSSIGNEMENT:
            printf("%s ", t->function);
            break;
        case OPERATOR:
            printf("%s ", t->function);
            break;
        case PARAMETER:
            printf("%s ", t->param);
            break;
        default: printf("UNKNOWN TOKEN");
    }
    print_tree_node(t->right);
    printf(")");
}

void print_tree(Tree* t){
    printf("print TREE: \n\n");
    print_tree_node(t->root);
    printf("\n");
}

Vector* stack_to_tree(TokenStack* stack){
    printf("\nSTACK TO TREE\n");
    Vector* v = new_vector(1);
    Tree* tree = new_Tree(NULL);
    add_element(v, tree);
    for(Token* t = stack->first; t != NULL; t = t->next){
        void* expression;
        switch(t->tag){
            case OPERAND:
                expression = &t->value;
                break;
            case OPERATOR:
                expression = t->function;
                break;
            case ASSSIGNEMENT:
                expression = t->function;
                break;
            case PARAMETER:
                expression = t->param;
                break;
            case NEW_LINE: //end of line aka start a new tree
                printf("\nstart new line\n");
                tree = new_Tree(NULL);
                add_element(v, tree);
                continue;
                break;
        }
        TreeNode* node = new_tree_node(t->tag, expression, NULL, NULL);
        attach_to_tree(node, tree);
        // print_tree(tree);
    }
    printf("stack to tree converted\n");
    return v;
}


Function get_function(char* expression){
    if(strcmp(expression, "+") == 0) return add;
    if(strcmp(expression, "-") == 0) return sub;
    if(strcmp(expression, "*") == 0) return mul;
    if(strcmp(expression, "/") == 0) return divide;
}

int evaluate_node(TreeNode* t, Parameter_node** paramters){
    if(t== NULL) return -1;
    switch(t->type){
    case OPERAND: 
        return t->value;
    case OPERATOR: 
        return get_function(t->function)(evaluate_node(t->left, paramters), evaluate_node(t->right, paramters));
    case ASSSIGNEMENT: {
            // char *key = t->left->param;
        int value = evaluate_node(t->right, paramters);
        printf("assign %s the value %d\n", t->left->param, value);
        *paramters = set_parameter(*paramters, t->left->param, value, INTEGER);
        return 1;}
    case PARAMETER: return *(int*)get_parameter(*paramters, t->param);
    }
    return -1;
}

void evaluate_tree(Tree* tree, Parameter_node** parameters){
    printf("\nEVALUATE TREE\n");
    print_parameter_nodes(*parameters);
    int result = evaluate_node(tree->root, parameters);
    // printf("paramters: ");
    // print_parameter_nodes(*parameters);
    printf("result is %d\n", result);
    print_parameter_nodes(*parameters);
}

void evaluate_vector(Vector* v, Parameter_node** parameters){
    printf("\nEVALUATE VECOTR\n");

    for(int i = 0; i < v->size; i++){
        evaluate_tree(v->data[i], parameters);
    }
}

void evaluate_expression(char* expression){
    TokenStack t = tokenize_expression(expression);
    print_Stack(&t);
    Parameter_node* parameter_list = NULL;
    Vector* trees = stack_to_tree(&t);
    for(int i = 0; i < trees->size; i++){
        printf("TREE %d:\n", i+1);
        print_tree(trees->data[i]);
    }
    // evaluate_tree(comp_tree, &parameter_list);
    // print_parameter_nodes(parameter_list);
    evaluate_vector(trees, &parameter_list);
    free_node_list(parameter_list);
    free_vector(trees);
    // free_tree(comp_tree);
    free_tokens(t.first);
}

int main(int argc, char* argv){
    // char* expression = get_file_content();
    evaluate_expression("x = 15 \n 15 + x");    
}