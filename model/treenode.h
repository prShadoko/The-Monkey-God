#ifndef TREENODE_H
#define TREENODE_H

#include <QList>

template<class N>
class TreeNode
{
public:
	// --- Constructor & destructor --- //
	TreeNode(TreeNode<N> * parent, N * node);
	~TreeNode(); //Do not destruct parent and children nodes

	// --- Accessors --- //
	inline void							addChild(TreeNode<N> * child)	{ _children.append(child); }
	inline QList<TreeNode<N> *> const	getChildren()					{ return _children; }
	inline TreeNode<N> const *			getParent()						{ return _parent; }
	inline N const *					getNode()						{ return _node; }

private:
	//--- Members ---//
	N *					_node;
	TreeNode<N> *		_parent;
	QList<TreeNode *>	_children;
};

#endif // TREENODE_H
