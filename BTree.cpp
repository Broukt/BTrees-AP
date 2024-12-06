#include "BTree.h"

// Constructor for BTree class
BTree::BTree(int t) {
	this->root = nullptr;
	this->t = t;
}

void BTree::traverse() {
	if (root != nullptr)
		root->traverse();
}

// Function to search key k in this B-Tree
BTreeNode* BTree::search(int k) {
	return (root == nullptr) ? nullptr : root->search(k);
}

void BTree::insert(int k) {
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    }
    else {
        // If root is full, then tree grows in height
        if (root->n == 2 * t - 1) {
            // Allocate memory for new root
            BTreeNode* s = new BTreeNode(t, false);

            // Make old root as child of new root
            s->C[0] = root;

            // Split the old root and move one key to the new root
            s->splitChild(0, root);

            // New root has two children now. Decide which of the two children
            // is going to have new key
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);

            // Change root
            root = s;
        }
        else {
            // If root is not full, call insertNonFull for root
            root->insertNonFull(k);
        }
    }
}

// Function to remove key k from the subtree rooted with this node
void BTree::remove(int k) {
    if (!root) {
        std::cout << "The tree is empty\n";
        return;
    }

    // Call the remove function for root
    root->remove(k);

    // If the root node has 0 keys, make its first child as the new root
    // if it has a child, otherwise set root as NULL
    if (root->n == 0) {
        BTreeNode* tmp = root;
        if (root->leaf)
            root = nullptr;
        else
            root = root->C[0];

        // Free the old root
        delete tmp;
    }
}