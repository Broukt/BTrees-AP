#pragma once
#include <iostream>

class BTreeNode {
public:
    int* keys;
    int t;
    BTreeNode** C;
    int n;
    bool leaf;

    BTreeNode(int _t, bool _leaf);
    void traverse();
    BTreeNode* search(int k);
    void insertNonFull(int k);
    void splitChild(int i, BTreeNode* y);
    void remove(int k);

    void removeFromLeaf(int idx);

    void removeFromNonLeaf(int idx);

    int getPredecessor(int idx);

    int getSuccessor(int idx);

    void fill(int idx);

    void borrowFromPrev(int idx);

    void borrowFromNext(int idx);

    void merge(int idx);

    friend class BTree;
};