#ifndef nodeST
#define nodeST

struct node{
	struct node *right;
	struct node *left;
	struct node *perant;
	int data;
	char color;
};

#endif
