#ifndef TREENODE_H
#define TREENODE_H

#include <QList>

template<class N>
class TreeNode
{
public:
	// --- Constructor & destructor --- //
	TreeNode(TreeNode * parent, N * node);
	~TreeNode(); //Do not destruct parent and children nodes

	// --- Accessors --- //
	inline void						addChild(TreeNode * child)	{ _children.append(child); }
	inline QList<TreeNode *> const	getChildren()				{ return _children; }
	inline TreeNode const *			getParent()					{ return _parent; }
	inline N const *				getNode()					{ return _node; }

private:
	N *					_node;
	TreeNode *			_parent;
	QList<TreeNode *>	_children;
};

#endif // TREENODE_H
