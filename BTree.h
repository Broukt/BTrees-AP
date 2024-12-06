#pragma once
#include "BTreeNode.h"
class BTree
{
public:
    BTreeNode* root;
    int t;

    BTree(int t);
    void traverse();
    BTreeNode* search(int k);
    void insert(int k);
    void remove(int k);
};

