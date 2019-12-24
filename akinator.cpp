#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MARKER -1

struct tree_node
{
    char* s;
    tree_node* left;
    tree_node* right;
    tree_node* root;
};
void delete_tree(tree_node* root)
{
        if (root->right != NULL) {
            delete_tree(root->right);
        }
        if (root->left != NULL) {
            delete_tree(root->left);
        }
    free(root);
}
tree_node* make_node(tree_node* parent,char* value)
{
    tree_node* out = (tree_node *)calloc(1, sizeof(tree_node));
    if(parent == NULL)
    {
        out -> root = NULL;
    }
    else
    {
        out->root = parent;
    }
    out -> left = NULL;
    out -> right = NULL;
    size_t a = strlen(value);
    out -> s = (char *) calloc(a,sizeof(char));
    for(size_t i = 0;i < a;i++)
    {
        out -> s[i] = value[i];
    }
    return out;
}

void serialize(tree_node *root, FILE *fp)
{
    if (root == NULL)
    {
        fprintf(fp, "%d\n", MARKER);
        return;
    }

    fprintf(fp, "%s\n", root -> s);
    serialize(root->left, fp);
    serialize(root->right, fp);
}

void deSerialize(tree_node *&root, FILE *fp, tree_node* parent)
{
    char buf[100];
    int readed = fscanf(fp, "%s", buf);
    if ( !readed || buf[0] == '-')
        return;

    root = make_node(parent, buf);
    deSerialize(root -> left, fp, root);
    deSerialize(root -> right, fp, root);
}
void visitor( FILE *f, const tree_node* start)
{
    if(start -> left != NULL)
    {
        fprintf(f,"\"%s\"->",start ->s);
        visitor(f, start -> left);
        if(start -> left -> left == NULL)
        fprintf(f,";\n");
    }
    if(start -> right != NULL)
    {
        fprintf(f,"\"%s\"->",start ->s);
        visitor(f, start -> right);
        if(start -> right -> right == NULL)
        fprintf(f,";\n");
    }
     if(start -> right == NULL && start -> left == NULL)
     {
        fprintf(f,"\"%s\"",start ->s);
     }
}
void new_answer(tree_node* root)
{
    char* temp = root -> s;
    char buff[100];
    printf("Name difference\n");
    scanf("%s",buff);
    size_t a = strlen(buff);
    root -> s = (char *) calloc(a,sizeof(char));
    for(size_t i = 0;i < a;i++)
    {
        root -> s[i] = buff[i];
    }
    printf("Name your object\n");
    scanf("%s",buff);
    root -> left = make_node(root,buff);
    root -> right = make_node(root,temp);
    return;
}
void dump_me_pls(tree_node* root)
{
    FILE *fp = fopen("text.dot","w");
    fprintf(fp,"digraph G{\n");
    visitor(fp,root);
    fprintf(fp,"}");
    fclose(fp);
}
bool the_game(tree_node* node)
{
    printf("Is your object ");
    printf("%s?\n",node -> s);
    int anwser;
    scanf("%d", &anwser);
    switch (anwser){
        case 1: 
            if(node -> left != NULL)
            {
                the_game(node -> left);
            } else
            {
                printf("That was your object?\n");
                scanf("%d",&anwser);
                if(anwser==0)
                {   
                    new_answer(node);
                }
            }
            break;
        case 0:
            if(node -> right != NULL)
            {
                the_game(node -> right);
            } else
            {
                printf("That was your object?\n");
                scanf("%d",&anwser);
                if(anwser==0)
                {
                    new_answer(node);
                }
            }
            break;
    }
    return  0;
}   
void find_hero(const tree_node* root, char* s,tree_node* temp)
{
    if(root -> left != NULL)
    {
        find_hero(root -> left, s, temp);
    }
    if(root -> right != NULL)
    {
       find_hero(root -> right, s, temp);
    }
    if(strcmp(root -> s,s) == 0)
    {
        temp -> s = root -> s;
        temp -> root = root -> root;
        temp -> left = root -> left;
        temp -> right = root -> right;  
    }
}
void compare_hero(tree_node* root)
{
    printf("Name your two objects\n");
    char** hero1 = (char **)calloc(20, sizeof(char*));
    char** hero2 = (char **)calloc(20, sizeof(char*));
    for(int i = 0; i < 20; i++)
    {
        hero1[i] = (char *)calloc(30, sizeof(char));
        hero2[i] = (char *)calloc(30, sizeof(char));
    }
    tree_node* temp1 = (tree_node *)calloc(1,sizeof(tree_node));
    char* buff1;
    buff1 = (char *)calloc(20,sizeof(char));
    scanf("%s",buff1);
    find_hero(root, buff1, temp1);
    tree_node* temp2 = (tree_node *)calloc(1,sizeof(tree_node));
    char* buff2;
    buff2 = (char *)calloc(20,sizeof(char));
    scanf("%s",buff2);
    find_hero(root, buff2, temp2);
    size_t size1 = 0, size2 = 0;
    while(temp1 -> root != NULL)
    {
        if(temp1 == temp1 -> root -> right || temp1 -> s == temp1 -> root -> right -> s)
        {
            hero1[size1][0] = 'n';
            hero1[size1][1] = 'e';
            hero1[size1][2] = ' ';
            for(size_t i = 3; i < strlen(temp1 -> s) + 3; i++)
            {
                hero1[size1][i] = temp1 -> root -> s[i-3];
            }
            size1++;
        }
        if(temp1 == temp1 -> root -> left || temp1 -> s == temp1 -> root -> left -> s)
        {
           for(size_t i = 0; i < strlen(temp1 -> s); i++)
            {
                hero1[size1][i] = temp1 -> root -> s[i];
            }
            size1++;
        }
        temp1 = temp1 -> root;
    }
        while(temp2 -> root != NULL)
    {
        if(temp2 == temp2 -> root -> right || temp2 -> s == temp2 -> root -> right -> s)
        {
            hero2[size2][0] = 'n';
            hero2[size2][1] = 'e';
            hero2[size2][2] = ' ';
            for(size_t i = 3; i < strlen(temp2 -> s) + 3; i++)
            {
                hero2[size2][i] = temp2 -> root -> s[i-3];
            }
            size2++;
        }
        if(temp2 == temp2 -> root -> left || temp2 -> s == temp2 -> root -> left -> s)
        {
           for(size_t i = 0; i < strlen(temp2 -> s); i++)
            {
                hero2[size2][i] = temp2 -> root -> s[i];
            }
            size2++;
        }
        temp2 = temp2 -> root;
    }
    printf("Same:\n");
    for(size_t i = 0; i < size1; i++)
    {
        for(size_t j = 0; j < size2; j++)
        {
            if(strcmp(hero2[j],hero1[i]) == 0)
            {
                printf("%s, ", hero2[j]);
                break;
            }
        }
    }
    printf("\nDifference first object: ");
    for(size_t i = 0; i < size2; i++)
    {
        bool k = 1;
        for(size_t j = 0; j < size1; j++)
        {
            if(strcmp(hero2[i],hero1[j]) == 0)
            {
                k = 0;
                break;    
            }
        }
        if(k)
        {
            printf("%s, ", hero2[i]);
        }
    }
    printf("\nDifference second object: ");
    for(size_t i = 0; i < size1; i++)
    {
        bool k = 1;
        for(size_t j = 0; j < size2; j++)
        {
            if(strcmp(hero2[j],hero1[i]) == 0)
            {
                k = 0;
                break;
            }
        }
        if(k)
        {
            printf("%s, ", hero1[i]);
        }
    }
     for(int i = 0; i < 20; i++)
    {
        free(hero1[i]);
        free(hero2[i]);
    }
    temp1 = NULL;
    free(temp1);
    temp2 = NULL;
    free(temp2);
    free(hero1);
    free(hero2);
    free(buff1);
    free(buff2);
}
void character(tree_node* root)
{
    printf("Name your object\n");
    tree_node* temp = (tree_node *)calloc(1,sizeof(tree_node));
    char* buff;
    buff = (char *)calloc(20,sizeof(char));
    scanf("%s",buff);
    find_hero(root, buff, temp);
    while(temp -> root != NULL)
    {
        if(temp == temp -> root -> right || temp -> s == temp -> root -> right -> s)
        {
            printf("ne %s, ", temp -> root -> s);
        }
        if(temp == temp -> root -> left || temp -> s == temp -> root -> left -> s)
        {
            printf("%s, ", temp -> root -> s);
        }
        temp = temp -> root;
    }
    temp = NULL;
    free(temp);
    free(buff);
}
void game(tree_node* root)
{
    int answer = 1;
    while(answer != 0)
    {
    printf("\nCharcteristick  1\n");
    printf("Guess 2\n");
    printf("Compare 3\n");
    printf("exit 0\n");
    scanf("%d", &answer);
    switch (answer)
    {
    case 1:
        character(root);
        break;
    case 2:
        the_game(root);
        break;
    case 3:
        compare_hero(root);
        break;    
    }
    }
}
int main()
{
    FILE *fp = fopen("tree.txt", "r+");
    tree_node *root1 = NULL;
    deSerialize(root1, fp, NULL);
    fp = fopen("tree.txt", "w");
        if (fp == NULL)
    {
        puts("Could not open file");
        return 0;
    }
    printf("Wellcome to Akinator");
    game(root1); 
    fp = fopen("tree.txt", "w");  
    serialize(root1, fp);
    dump_me_pls(root1);
    fclose(fp);
    delete_tree(root1);
    return 0;//ne 666, ne 5, ne 2
}