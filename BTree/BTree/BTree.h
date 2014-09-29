#ifndef BTREE_H
#define BTREE_H

#include <vector>

struct TreeNode
{
	int len;
	TreeNode *parent;
	std::vector<TreeNode*> child;
	std::vector<int> key;
};

struct Result
{
	TreeNode *pR;
	int index;
	bool flag;

	Result(TreeNode *p, int num, bool tag) : pR(p), index(num), flag(tag)
	{}
};

class BTree
{
public:
	explicit BTree(int num);
	~BTree();
	int searchNode(TreeNode *root, int value);
	Result searchBTree(TreeNode *root, int value);
	int insertBTree(TreeNode **root, int value, TreeNode *q, int index);
	int deleteBTree();
private:
	const int m;
	TreeNode *root;
};

#endif