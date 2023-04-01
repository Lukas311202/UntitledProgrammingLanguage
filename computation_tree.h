#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct TreeNode TreeNode;
struct TreeNode{
    TreeNode* left;
    TreeNode* right;
    union{
        char* function;
        int value;
        char* param;
    };
    int type;
};

typedef struct Tree Tree;
struct Tree{
    TreeNode* root;
};
Tree* new_Tree(TreeNode* root);

typedef struct Vector Vector;
struct Vector
{
    void** data;
    int size; //how many elements are currently in the list
    int capacity; //how many elements can be max in the list before has to reallocated
};


int mul(int x, int y);
int add(int x, int y);
int sub(int x, int y);
int divide(int x, int y);

typedef int (*Function)(int x, int y);

//takes a computation tree as an argument and prints the result in the command line
void evaluate(Tree* t);

void free_tree_node(TreeNode* t);
void free_tree(Tree* t);

Vector* new_vector(int capacity);
void free_vector(Vector* v);
void add_element(Vector* v, void* element);