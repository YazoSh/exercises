/*
	makes a red-black tree and does nothing with it

	compile and use stdinput for data entry
*/


#include <stdio.h>

enum {RED,BLACK};

#include "lib/nodestruct.h"

void *alloc(int);
struct node *nil = NULL;

void leftrotate(struct node **root,struct node *z)
{
	struct node *tmp,*x;

	x = z->right;
	x->perant = z->perant;

	if(z == *root)
		*root = x;
	else if(z == z->perant->left)
		z->perant->left = x;
	else	z->perant->right = x;

	tmp = x->left;
	x->left = z;
	z->perant = x;
	z->right = tmp;
	tmp->perant = z;
}


void rightrotate(struct node **root,struct node *z)
{
	struct node *tmp,*x;

	x = z->left;
	x->perant = z->perant;

	if(z == *root)
		*root = x;
	else if(z == z->perant->left)
		z->perant->left = x;
	else	z->perant->right = x;

	tmp = x->right;
	x->right = z;
	z->perant = x;
	z->left = tmp;
}

void treefix(struct node **root, struct node *z)
{
	// Reached the end if the tree
	if(!(z == NULL || z->perant == NULL || z->perant->perant == NULL))
	{
		// If Z's perant is a left child
		if(z->perant == z->perant->perant->left){
			// Case 1
			if(z->perant->perant->right->color == RED){
				z->perant->color = BLACK;
				z->perant->perant->right->color = BLACK;
				z->perant->perant->color = RED;
				treefix(root,z->perant->perant);
			}else{
				// Case 2
				if(z == z->perant->right)
				{
					leftrotate(root,z->perant);
					z = z->left;
				}
				//Case 3
				z->perant->color = BLACK;
				z->perant->perant->color = RED;
				rightrotate(root,z->perant->perant);
			}
			} else 	{
				// Case 1
				if(z->perant->perant->left->color == RED){
					z->perant->color = BLACK;
					z->perant->perant->left->color = BLACK;
					z->perant->perant->color = RED;
					treefix(root, z->perant->perant);
				}else{
				// Case 2
				if(z == z->perant->left)
				{
					rightrotate(root,z->perant);
					z = z->right;
				}
				//Case 3
				z->perant->color = BLACK;
				z->perant->perant->color = RED;
				leftrotate(root,z->perant->perant);
			}
		}
	}
	(*root)->color = BLACK;
}

struct node *insertnode(struct node **root,int data)
{
	struct node *nn = alloc(sizeof(struct node));
	struct node *trav = *root;

	if(*root == NULL)
	{
		*root = nn;
		nn->right = nn->left = nil;
		nn->perant = NULL;
		nn->data = data;
		nn->color = BLACK;
		return nn;
	}

	while(trav != nil)
		if(data >= trav->data){
			if(trav->right == nil){
				trav->right = nn;
				nn->perant = trav;
				break;
			}
			trav = trav->right;
		}else{
			if(trav->left == nil){
				trav->left = nn;
				nn->perant = trav;
				break;
			}
			trav = trav->left;
		}
	nn->data = data;
	nn->color = RED;
	nn->left = nn->right = nil;
	treefix(root, nn);
	return nn;
}

char buffer[1000];
char *bufferp = buffer;

void *alloc(int n)
{
	bufferp += n;
	return (void *)(bufferp - n);
}

#include "lib/treeprint.h"
#include <stdlib.h>

int main()
{
	nil = alloc(sizeof(struct node));
	nil->color = BLACK;
	nil->data = -1;
	struct node *root = NULL;

	int getnum(char *);
	char s[10];
	while(getnum(s) != EOF)
		insertnode(&root,atoi(s));

	rdtreeprint(root);
}

int getnum(char* s)
{
	char *t = s;
	int c;
	if((c = getchar()) == '-')
		*s++ = c,c = getchar();
	for(;(c >= '0' && c <= '9' && c != EOF)? *s++ = c:0; c = getchar())
		;
	*s = '\0';
	return c;
}
