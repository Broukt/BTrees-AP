#include "BTreeNode.h"

// Constructor for BTreeNode class
BTreeNode::BTreeNode(int _t, bool _leaf) {
    t = _t;
    leaf = _leaf;

    // Allocate memory for maximum number of possible keys and child pointers
    keys = new int[2 * t - 1];
    C = new BTreeNode * [2 * t];

    n = 0;
}

// Function to traverse all nodes in a subtree rooted with this node
void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        // If this is not leaf, then before printing keys[i],
        // traverse the subtree rooted with child C[i].
        if (leaf == false)
            C[i]->traverse();
        std::cout << " " << keys[i];
    }

    // Print the subtree rooted with last child
    if (leaf == false)
        C[i]->traverse();
}

// Function to search key k in subtree rooted with this node
BTreeNode* BTreeNode::search(int k) {
    // Find the first key greater than or equal to k
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    // If the found key is equal to k, return this node
    if (keys[i] == k)
        return this;

    // If the key is not found here and this is a leaf node
    if (leaf == true)
        return nullptr;

    // Go to the appropriate child
    return C[i]->search(k);
}

// A utility function to insert a new key in this node
// The node must be non-full when this function is called
void BTreeNode::insertNonFull(int k) {
    int i = n - 1;

    // If this is a leaf node
    if (leaf == true) {
        // The following loop does two things:
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one position ahead
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }

        // Insert the new key at found location
        keys[i + 1] = k;
        n = n + 1;
    }
    else {
        // Find the child which is going to have the new key
        while (i >= 0 && keys[i] > k)
            i--;

        // See if the found child is full
        if (C[i + 1]->n == 2 * t - 1) {
            // If the child is full, split it
            splitChild(i + 1, C[i + 1]);

            // After split, the middle key of C[i+1] goes up and
            // C[i+1] is split into two. See which of the two
            // is going to have the new key
            if (keys[i + 1] < k)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

// Function to split the child y of this node
// Note that y must be full when this function is called
void BTreeNode::splitChild(int i, BTreeNode* y) {
    // Create a new node which is going to store (t-1) keys of y
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    // Copy the last (t-1) keys of y to z
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    // Copy the last t children of y to z
    if (y->leaf == false) {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    // Reduce the number of keys in y
    y->n = t - 1;

    // Since this node is going to have a new child,
    // create space of new child
    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    // Link the new child to this node
    C[i + 1] = z;

    // A key of y will move to this node. Find the location of
    // new key and move all greater keys one space ahead
    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    // Copy the middle key of y to this node
    keys[i] = y->keys[t - 1];

    // Increment count of keys in this node
    n = n + 1;
}

// Remove the key k from the sub-tree rooted with this node
void BTreeNode::remove(int k) {
    int idx = 0;
    while (idx < n && keys[idx] < k)
        ++idx;

    // The key to be removed is present in this node
    if (idx < n && keys[idx] == k) {
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    }
    else {
        // If this node is a leaf node, then the key is not present in tree
        if (leaf) {
            std::cout << "The key " << k << " is not present in the tree\n";
            return;
        }

        // The key to be removed is present in the sub-tree rooted with this node
        // The flag indicates whether the key is present in the sub-tree rooted
        // with the last child of this node
        bool flag = ((idx == n) ? true : false);

        // If the child where the key is supposed to exist has less than t keys,
        // we fill that child
        if (C[idx]->n < t)
            fill(idx);

        // If the last child has been merged, it must have merged with the previous
        // child and so we recurse on the (idx-1)th child. Else, we recurse on the
        // (idx)th child which now has at least t keys
        if (flag && idx > n)
            C[idx - 1]->remove(k);
        else
            C[idx]->remove(k);
    }
}

// A function to remove the key present in idx-th position in this node which is a leaf
void BTreeNode::removeFromLeaf(int idx) {
    // Move all the keys after the idx-th position one step backward
    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];

    // Reduce the count of keys
    n--;
}

// A function to remove the key present in idx-th position in this node which is a non-leaf node
void BTreeNode::removeFromNonLeaf(int idx) {
    int k = keys[idx];

    // If the child that precedes k (C[idx]) has at least t keys,
    // find the predecessor 'pred' of k in the subtree rooted at C[idx]
    // Replace k by pred and recursively delete pred in C[idx]
    if (C[idx]->n >= t) {
        int pred = getPredecessor(idx);
        keys[idx] = pred;
        C[idx]->remove(pred);
    }

    // If the child C[idx] has fewer than t keys, examine C[idx+1]
    // If C[idx+1] has at least t keys, find the successor 'succ' of k in C[idx+1]
    // Replace k by succ and recursively delete succ in C[idx+1]
    else if (C[idx + 1]->n >= t) {
        int succ = getSuccessor(idx);
        keys[idx] = succ;
        C[idx + 1]->remove(succ);
    }

    // If both C[idx] and C[idx+1] have fewer than t keys, merge k and all of C[idx+1]
    // into C[idx]. Now C[idx] contains 2t - 1 keys. Free C[idx+1] and recursively delete k from C[idx]
    else {
        merge(idx);
        C[idx]->remove(k);
    }
}

// A function to get predecessor of keys[idx]
int BTreeNode::getPredecessor(int idx) {
    // Keep moving to the rightmost node until we reach a leaf
    BTreeNode* cur = C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];

    // Return the last key of the leaf
    return cur->keys[cur->n - 1];
}

// A function to get successor of keys[idx]
int BTreeNode::getSuccessor(int idx) {
    // Keep moving to the leftmost node starting from C[idx+1] until we reach a leaf
    BTreeNode* cur = C[idx + 1];
    while (!cur->leaf)
        cur = cur->C[0];

    // Return the first key of the leaf
    return cur->keys[0];
}

// A function to fill child C[idx] which has less than t-1 keys
void BTreeNode::fill(int idx) {
    // If the previous child(C[idx-1]) has more than t-1 keys, borrow a key from that child
    if (idx != 0 && C[idx - 1]->n >= t)
        borrowFromPrev(idx);

    // If the next child(C[idx+1]) has more than t-1 keys, borrow a key from that child
    else if (idx != n && C[idx + 1]->n >= t)
        borrowFromNext(idx);

    // Merge C[idx] with its sibling
    else {
        if (idx != n)
            merge(idx);
        else
            merge(idx - 1);
    }
}

// A function to borrow a key from C[idx-1] and insert it into C[idx]
void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode* child = C[idx];
    BTreeNode* sibling = C[idx - 1];

    // Moving all key in C[idx] one step ahead
    for (int i = child->n - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];

    // If C[idx] is not a leaf, move all its child pointers one step ahead
    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i)
            child->C[i + 1] = child->C[i];
    }

    // Setting child's first key equal to keys[idx-1] from the current node
    child->keys[0] = keys[idx - 1];

    // Moving sibling's last child as C[idx]'s first child
    if (!child->leaf)
        child->C[0] = sibling->C[sibling->n];

    // Moving the key from the sibling to the parent
    keys[idx - 1] = sibling->keys[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;
}

// A function to borrow a key from the C[idx+1] and place it in C[idx]
void BTreeNode::borrowFromNext(int idx) {
    BTreeNode* child = C[idx];
    BTreeNode* sibling = C[idx + 1];

    // keys[idx] is inserted as the last key in C[idx]
    child->keys[child->n] = keys[idx];

    // Sibling's first child is inserted as the last child of C[idx]
    if (!(child->leaf))
        child->C[child->n + 1] = sibling->C[0];

    // The first key from sibling is inserted into keys[idx]
    keys[idx] = sibling->keys[0];

    // Moving all keys in sibling one step behind
    for (int i = 1; i < sibling->n; ++i)
        sibling->keys[i - 1] = sibling->keys[i];

    // Moving the child pointers one step behind
    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->C[i - 1] = sibling->C[i];
    }

    child->n += 1;
    sibling->n -= 1;
}

// A function to merge C[idx] with C[idx+1]
void BTreeNode::merge(int idx) {
    BTreeNode* child = C[idx];
    BTreeNode* sibling = C[idx + 1];

    // Pulling a key from the current node and inserting it into (t-1)th position of C[idx]
    child->keys[t - 1] = keys[idx];

    // Copying the keys from sibling to child
    for (int i = 0; i < sibling->n; ++i)
        child->keys[i + t] = sibling->keys[i];

    // Copying the child pointers from sibling to child
    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i)
            child->C[i + t] = sibling->C[i];
    }

    // Moving all keys after idx in the current node one step before
    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];

    // Moving the child pointers after (idx+1) in the current node one step before
    for (int i = idx + 2; i <= n; ++i)
        C[i - 1] = C[i];

    // Updating the key count of child and the current node
    child->n += sibling->n + 1;
    n--;

    // Free the memory of sibling
    delete sibling;
}