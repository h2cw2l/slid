#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STACK_SIZE 32

/*
        a
    /       \
   b          c
 /   \      /   \
d     e    h     i
     /          / \
    f          j   k
*/
char *tib = "a(b(d,e(f)),c(h,i(j,k)))";
char result[STACK_SIZE] = {'\0'};
int ri = 0;

struct node {
    char data;
    struct node *left;
    struct node *right;
};

struct node *stack[STACK_SIZE] = {NULL};
int idx = 0;

struct node *bracket_to_list(char *str);
void preOrder(struct node *root);

int stack_push(struct node *np)
{
    printf("stack push idx %d, data %c\n", idx, np->data);
    stack[idx] = np;
    idx++;
    return 0;
}

struct node *stack_pop()
{
    printf("stack pop idx %d, data %c\n", idx, stack[idx -1]->data);
    struct node *ret = stack[idx -1];
    idx--;

    return ret;
}

struct node *stack_get()
{
    return stack[idx - 1];
}

int main()
{
    struct node *root = bracket_to_list(tib);
    printf("root %c\n", root->data);
    preOrder(root);
    return 0;
}
struct node *bracket_to_list(char *str)
{
    struct node *last = NULL;
    struct node *root = NULL;
    int i = 0;
    int left_right_flag = 0;
    int len = strlen(tib);

    for (i = 0; i < len; i++) {
        if ((tib[i] != '(') && (tib[i] != ')') && (tib[i] != ',') && (tib[i] < 'a') && (tib[i] > 'z')) {
            printf("str %s illegal\n", str);
            exit(-1);
        }
    }

    for (i = 0; i < len; i++) {
        switch(tib[i]) {
            case '(': 
                stack_push(last);
                left_right_flag = 1;
                break;
            case ',':   
                left_right_flag = 2;
                break;
            case ')':
                stack_pop();
                break;
            default:
                last = (struct node *)malloc(sizeof(struct node));
                if (last == NULL) {
                    printf("malloc for node failed\n");
                    exit(-1);
                }
                last->data = tib[i];
                last->left = NULL;
                last->right = NULL;

                if (root == NULL) {
                    root = last;
                } else {
                     if (left_right_flag == 1) {
                         stack_get()->left = last;
                     } else {
                         stack_get()->right = last;
                     }
                }
                break;
        }
    }

    return root;
}

void preOrder(struct node *root)
{
    if (root == NULL) {
        return;
    }

    printf("%c", root->data);
    preOrder(root->left);
    preOrder(root->right);

    return;
}

void list_to_bracket(struct node *root, int lr_flag)
{
    if (root == NULL) {
        return;
    }
    
    


}
