#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// Define a Node class representing a node in the interval tree
class Node {
public:
    pair<int, int> interval;
    int max;
    Node* left;
    Node* right;

    // default init
    Node(pair<int, int> interval) : interval(interval), max(interval.second), left(nullptr), right(nullptr) {}
};

// Define an IntervalTree class to manage the interval tree operations
class IntervalTree {
public:
    Node* root;

    IntervalTree() : root(nullptr) {}

    // Insert a new interval into the interval tree
    Node* insert(Node* root, pair<int, int> interval) 
    {
        if (!root) // i.e. if root is null, interval becomes the new root
        {
            return new Node(interval);
        }

        if (interval.first < root->interval.first) 
        {
            root->left = insert(root->left, interval);
        } 
        else 
        {
            root->right = insert(root->right, interval);
        }

        root->max = max(root->max, interval.second);
        return root;
    }

    // Check for interval overlap in the interval tree
    pair<int, int> overlap(Node* root, pair<int, int> interval) 
    {
        if (!root) 
        {
            return make_pair(-1, -1); // No overlap
        }

        if (root->interval.first <= interval.second && root->interval.second >= interval.first) 
        {
            return root->interval; // Overlaps
        }

        if (root->left && root->left->max >= interval.first) 
        {
            return overlap(root->left, interval);
        }

        return overlap(root->right, interval);
    }

    // Delete an interval from the interval tree
    Node* deleteNode(Node* root, pair<int, int> interval) 
    {
        if (!root) 
        {
            return root;
        }

        if (interval.first < root->interval.first) 
        {
            root->left = deleteNode(root->left, interval);
        } 
        else if (interval.first > root->interval.first) 
        {
            root->right = deleteNode(root->right, interval);
        } 
        else 
        {
            if (!root->left) 
            {
                Node* temp = root->right;
                delete root;
                return temp;
            } 
            else if (!root->right) 
            {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* temp = minValueNode(root->right);
            root->interval = temp->interval;
            root->right = deleteNode(root->right, temp->interval);
        }

        return root;
    }

private:
    // Helper function to find the node with the minimum value in a subtree
    Node* minValueNode(Node* root) {
        Node* current = root;
        while (current->left) {
            current = current->left;
        }
        return current;
    }
};

// Example usage of the IntervalTree
int main() {
    vector<pair<int, int>> intervals = {{15, 20}, {10, 30}, {17, 19}, {5, 20}, {12, 15}, {30, 40}};
    IntervalTree IT;

    for (const auto& interval : intervals) {
        IT.root = IT.insert(IT.root, interval);
    }

    // Search for an interval and print the result
    pair<int, int> to_search = {25, 29};
    cout << "Searching for interval (" << to_search.first << ", " << to_search.second << ")\n";
    pair<int, int> res = IT.overlap(IT.root, to_search);
    if (res.first != -1) {
        cout << "Overlaps with (" << res.first << ", " << res.second << ")\n";
    } else {
        cout << "No Overlapping Interval\n";
    }

    // Delete an interval and print the result
    pair<int, int> to_erase = {10, 30};
    cout << "Deleting interval (" << to_erase.first << ", " << to_erase.second << ")\n";
    IT.root = IT.deleteNode(IT.root, to_erase);

    // Search for an interval again after deletion and print the result
    cout << "Searching for interval (" << to_search.first << ", " << to_search.second << ")\n";
    res = IT.overlap(IT.root, to_search);
    if (res.first != -1) {
        cout << "Overlaps with (" << res.first << ", " << res.second << ")\n";
    } else {
        cout << "No Overlapping Interval\n";
    }

    return 0;
}
