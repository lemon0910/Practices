#include "BTree.h"

BTree::BTree(int num) : m(num), root(nullptr)
{
}

BTree::~BTree()
{
}

int BTree::searchNode(TreeNode *root, int value)
{
	for (int i = 0; i <= root->len; ++i)
	{
		if (i == 0)
		{
			if (root->key[i] > value)
				return i;
		}
		else if (root->key[i - 1] == value)
		{
			return i - 1;
		}
		else if (i == root->len)
			return root->len;
		else if (root->key[i - 1] < value && root->key[i] > value)
			return i;
	}
}

Result BTree::searchBTree(TreeNode *root, int value)
{
	TreeNode *p = root, *q = nullptr;
	bool found = false;
	int index = 0;

	while (p && !found)
	{
		int n = p->len;
		index = searchNode(p, value);
		if (index >= 0 && p->key[index] == value)
			found = true;
		else
		{
			q = p;
			p = p->child[index];
		}
	}
	if (found)
		return Result(p, index, true);
	return Result(q, index, false);
}

int BTree::insertBTree(TreeNode **root, int value, TreeNode *q, int index)
{
	int v = value;
	TreeNode *son = nullptr;
	bool finished = false;

	while (q && !finished)
	{
		insert(q, index, v, son);
		if (q->len < m)
			finished = true;
		else
		{
			int mid = m / 2;
			split(q, son);
			v = q->key[mid];
			q = q->parent;
			if (q)
				index = searchNode(q, value);
		}
	}

	if (!finished)
		NewRoot(root, q, v, son);
}

int BTree::deleteBTree()
{}