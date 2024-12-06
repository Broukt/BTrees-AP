#include <iostream>
#include "BTree.h"

int main()
{
    int degree;
    std::cout << "Enter the degree of B-Tree: ";
    std::cin >> degree;

    BTree t(degree); // A B-Tree with user-defined degree

    int choice, key;
    while (true) {
        std::cout << "\nB-Tree Operations:\n";
        std::cout << "1. Insert\n2. Delete\n3. Search\n4. Traverse\n5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter key to insert: ";
            std::cin >> key;
            t.insert(key);
            break;
        case 2:
            std::cout << "Enter key to delete: ";
            std::cin >> key;
            t.remove(key);
            break;
        case 3:
            std::cout << "Enter key to search: ";
            std::cin >> key;
            if (t.search(key))
                std::cout << "Key " << key << " found in the tree.\n";
            else
                std::cout << "Key " << key << " not found.\n";
            break;
        case 4:
            std::cout << "B-Tree traversal:\n";
            t.traverse();
            std::cout << "\n";
            break;
        case 5:
            return 0;
        default:
            std::cout << "Invalid choice!\n";
        }
    }

    return 0;
}
