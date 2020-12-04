#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/**
 * Converts a string number into an integer -- (ex. "-140" == -140)
 * @param str The string number
 */
int strToInt(string str) {
    int val = 0;
    for(int i=0 ;i < str.length(); i++) {
        if(str[i] != '-')
            val += pow(10, str.length()-i) * (str[i] - 48);
    } if(str[0] == '-') val *= -1;
    
    return val/10;
}

class Node {
        int value;
        Node* parent;
        Node* rightChild;
        Node* leftChild;

    public:

        Node(int val, Node* par, Node* right, Node* left) {
            value = val;
            rightChild = right;
            leftChild = left;
            parent = par;
        }

        Node(int val, Node* right, Node* left) {                 // Root constr
            value = val;
            rightChild = right;
            leftChild = left;
            parent = NULL;
        }

        Node(int val, Node* par) {                              // Leaf constr
            value = val;
            rightChild = NULL;
            leftChild = NULL;
            parent = par;
        }

        /**
         * Returns the value
         * @return the value
         */
        int getValue() {
            return value;
        }

        /**
         * Sets value
         * @param v new value
         */
        void setValue(int v) {
            value = v;
        }

        /**
         * Returns ptr to the right child (>)
         * @return the right child
         */
        Node* getRightChild() {
            return rightChild;
        }

        /**
         * Sets right child
         * @param r new right child
         */
        void setRightChild(Node* r) {
            rightChild = r;
        }

        /**
         * Returns ptr to the left child (<)
         * @return the left child
         */
        Node* getLeftChild() {
            return leftChild;
        }

        /**
         * Sets left child
         * @param l new left child
         */
        void setLeftChild(Node* l) {
            leftChild = l;
        }

        /**
         * Returns ptr to the parent node
         * @return the parent node
         */
        Node* getParent() {
            return parent;
        }
};

/**
 * Creates a binary search tree based on vector of keys
 * @param keys the keys
 * @return the head node
 */
Node* createTree(vector<int> keys) {
    Node* head = new Node(keys[0], NULL, NULL);

    return head;
}

/**
 * Enumerates through the tree as a stack
 * @param n the head node
 * @return a string of the enumeration
 */
string enumerate(Node* n, string s) {
    if(n->getLeftChild() != NULL) enumerate(n->getLeftChild(), s);
    else if(n->getRightChild() != NULL) enumerate(n->getRightChild(), s);
    else s += n->getValue() + " ";
    return s;
}

/**
 * Outputs the result of a search
 * @param k the key
 */
void search(int k, Node* head, Node* n) {
    if(n == NULL) cout << -1;
    else if(n->getValue() < k) search(k, n->getRightChild());
    else if(n->getValue() > k) search(k, n->getLeftChild());
    else cout << enumerate(head, "").pop_back();
}

int main() {
    string val;
    int op, key;
    vector<int> init;

    while(!cin.fail()) {                        // Takes input and creates initial tree
        cin >> val;
        if(val == "s") break;
        init.push_back(strToInt(val));
    } Node* head = createTree(init);

    cin.ignore(1, '\n');
    cin >> op;

    cin.ignore(1, '\n');
    cin >> key;

    switch(op) {                                // Operation
        case 1:
        {
            // Search
        } break;

        case 2:
        {
            // Insert
        } break;

        case 3:
        {
            // Delete
        } break;

        default: break;
    }
}