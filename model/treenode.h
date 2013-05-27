#ifndef TREENODE_H
#define TREENODE_H

#include <vector>

template <typename N>
class TreeNode
{
public:
    // --- Constructor & destructor --- //
    TreeNode(TreeNode * parent, N * node);
    ~TreeNode(); //Do not destruct parent and children's node

    // --- Methods --- //
    void addChild(TreeNode * child);

    // --- Accessors --- //
    void setChildren(std::vector<*TreeNode> children);
    const std::vector<*TreeNode> getChildren();

    void setParent(TreeNode * parent);
    const TreeNode * getParent();

    void setNode(N * node);
    const N * getNode();

private:
    N * _node;
    TreeNode * _parent;
    std::vector<*TreeNode > _children;
};

#endif // TREENODE_H
