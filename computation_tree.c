#include "computation_tree.h"

Tree* new_Tree(TreeNode* root){
    Tree* t = malloc(sizeof(Tree));
    t->root = root;
    return t;
}

void free_tree_node(TreeNode* t){
    if(t == NULL) return;
    free_tree_node(t->left);
    free_tree_node(t->right);
    free(t);
}

void free_tree(Tree* t){
    free_tree_node(t->root);
    free(t);
    printf("tree freed\n");
}

Vector* new_vector(int capacity){
    Vector* v = malloc(sizeof(Vector));
    v->capacity = capacity;
    v->data = malloc(capacity * sizeof(Tree*));
    v->size = 0;
    return v;
}

void free_vector(Vector* v){
    for(int i = 0; i < v->size; i++){
        free_tree(v->data[i]);
    }
    free(v->data);
    free(v);
    printf("vector freed\n");
}

void add_element(Vector* v, void* element){
    if(v->size >= v->capacity){
        printf("capacity exceeded, resize to %d\n", v->capacity * 2);
        v->capacity *= 2;
        void* new_data = malloc(sizeof(Tree) * v->capacity);
        memcpy(new_data, v->data, v->size * sizeof(Tree));
        free(v->data);
        v->data = new_data;
    }
    v->data[v->size++] = element;
    printf("element added\n");
}