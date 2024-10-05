#include <stdio.h>
#include <stdlib.h>

typedef int Data;

typedef struct _treenode
{
	Data data;
	struct _treenode* left;
	struct _treenode* right;
}TreeNode;

TreeNode* make_node(Data data)
{
	TreeNode* newnode = (TreeNode*)malloc(sizeof(TreeNode));

	newnode->data = data;
	newnode->left = NULL;
	newnode->right = NULL;

	return newnode;
}
TreeNode* make_root()
{
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->left = NULL;
	root->right = NULL;

	return root;
}

TreeNode* left_child(TreeNode* node)
{
	return node->left;
}
TreeNode* right_child(TreeNode* node)
{
	return node->right;
}
void preorder(TreeNode* node)
{
	if (node == NULL)
		return;
	printf(" %d", node->data);
	preorder(left_child(node));
	preorder(right_child(node));
}

TreeNode* match_id(TreeNode* node, Data data)
{
	if (node == NULL)
		return NULL;
	if (node->data == data)
		return node;
	TreeNode* p;
	p = match_id(left_child(node), data);
	if (p != NULL)
		return p;
	p = match_id(right_child(node), data);
	if (p != NULL)
		return p;

	return NULL;
}

int main()
{
	int n, cnt;
	Data data, left_data, right_data;
	char str[101];
	TreeNode* root = make_root();
	TreeNode* tmp;

	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		scanf("%d %d %d", &data, &left_data, &right_data);
		if (i == 0)
		{
			root->data = data;
			root->left = make_node(left_data);
			root->right = make_node(right_data);
		}
		else
		{
			tmp = match_id(root, data);
			if(left_data !=0)
				tmp->left = make_node(left_data);
			if(right_data !=0)
				tmp->right = make_node(right_data);
		}
	}

	scanf("%d", &cnt);

	for (int i = 0; i < cnt; i++)
	{
		scanf("%s", str);
		
		int len = strlen(str);
		TreeNode* traverse = root;
		printf(" %d", traverse->data);
		for (int i = 0; i < len; i++)
		{
			if (str[i] == 'L')
				traverse = left_child(traverse);
			else if (str[i] == 'R')
				traverse = right_child(traverse);
			printf(" %d", traverse->data);
		}
		printf("\n");
	}
}