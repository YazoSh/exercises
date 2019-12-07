#ifndef treeprint
#define treeprint

#define ANSI_COLOR_RED   "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

void padding ( char ch, int n ){
  int i;
  for ( i = 0; i < n; i++ )
    putchar ( ch );
}

void treeprintt(struct node *n,int level){
  if (n == nil || n == NULL) {
    padding ('\t',level);
    puts ("");
  } else {
    treeprintt(n->right, level + 1);
    padding ('\t', level);
    if(n->color == RED)
	printf(ANSI_COLOR_RED);
    printf ("%d\n",n->data);
    printf(ANSI_COLOR_RESET);
    treeprintt(n->left, level + 1);
  }
}

void rdtreeprint(struct node *root)
{
	return treeprintt(root,0);
}

#endif
