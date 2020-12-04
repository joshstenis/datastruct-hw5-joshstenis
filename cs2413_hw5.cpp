#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
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

        /**
         * Sets the parent node
         * @param p the new parent node
         */
        void setParent(Node* p) {
            parent = p;
        }
};

/**
 * Enumerates through the tree as a stack
 * @param n the head node
 * @return a stack of the enumeration
 */
stack<Node*>* enumerate(Node* n, stack<Node*>* e) {
    if(n->getLeftChild() != NULL) enumerate(n->getLeftChild(), e);
    else if(n->getRightChild() != NULL) enumerate(n->getRightChild(), e);
    else e->push(n);

    return e;
}

/**
 * Outputs the stack given
 * @param stack the stack of nodes
 */
void outputStack(stack<Node*>* stack) {
    cout << stack->top();
    stack->pop();

    while(stack->empty() == false) {
      cout << " " << stack->top();
      stack->pop();
    }
}

/**
 * Outputs the result of a search
 * @param k the key
 * @param h the head node (for enumerate)
 * @param n the iterable node
 */
void outputSearch(int k, Node* h, Node* n) {
    if(n == NULL) cout << -1;
    else if(n->getValue() < k) outputSearch(k, h, n->getRightChild());
    else if(n->getValue() > k) outputSearch(k, h, n->getLeftChild());
    else outputStack(enumerate(h, new stack<Node*>()));
}

/**
 * Searches the BST and returns the node to be looked for
 * @param k the key to be found
 * @param n the node from which to begin the search
 * @return the node once it is found (or not)
 */
Node* search(int k, Node* n) {
    if(n == NULL) return NULL;
    else if(n->getValue() < k) search(k, n->getRightChild());
    else if(n->getValue() > k) search(k, n->getLeftChild());
    else return n;
}

/**
 * Inserts a Node into a binary search tree
 * @param c the iterable node
 * @param n the new node
 * @return a redunency code (-1 if node is already there)
 */
int insertNode(Node* c, Node* n) {
    if(n->getValue() == c->getValue()) return -1;
    else if(c->getValue() == NULL) {
        n->setLeftChild(c->getLeftChild());
        n->setRightChild(c->getRightChild());
        n->setParent(c->getParent());
        c = n;
    } else if(n->getValue() < c->getValue()) insertNode(c->getLeftChild(), n);
    else insertNode(c->getRightChild(), n);
    return 0;
}

/**
 * Removes a node from the binary search tree
 * @param k the key of the node to be removed
 * @param h the head node of the tree
 */
void removeNode(int k, Node* h) {
    Node* n = search(k, h);
}

/**
 * Creates a binary search tree based on vector of keys
 * @param keys the keys
 * @return the head node
 */
Node* createTree(vector<int> keys) {
    Node* head = new Node(keys[0], NULL, NULL);
    for(int i=1; i < keys.size(); i++) {
        Node* n = new Node(keys[i], NULL, NULL, NULL);
        insertNode(head, n);
    } return head;
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
        case 1:                 // Search
        {
            outputSearch(key, head, head);
        } break;

        case 2:                 // Insert
        {
            if(insertNode(head, new Node(key, NULL, NULL, NULL)) == -1) cout << -1;
            else enumerate(head, new stack<Node*>());
        } break;

        case 3:                 // Delete
        {
            removeNode(key, head);
        } break;

        default: break;
    }
}