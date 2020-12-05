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

        Node(int val, Node* par, Node* right, Node* left) : value(val), parent(par), rightChild(right), leftChild(left) {}      // Typical constr

        Node(int val, Node* right, Node* left) : value(val), parent(NULL), rightChild(right), leftChild(left) {}                // Root constr

        Node(int val, Node* par) : value(val), parent(par), rightChild(NULL), leftChild(NULL) {}                                // Leaf constr

        Node() : value(NULL), parent(NULL), rightChild(NULL), leftChild(NULL) {}                                                // Default constr

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

template <typename T>
class stack {
        
        vector<T> stk;
        T top;

    public:

        stack() : stk({}) {}

        stack(vector<T> v) : stk(v), top(stk.back()) {}

        /**
         * Pushes given element onto the stack
         * @param e the new top element
         */
        void push(T e) {
            stk.push_back(e);
            top = stk.back();
        }

        /**
         * Pops (removes) the top of the stack
         * @return the element that was removed
         */
        T pop() {
            T n = stk.pop_back();
            top = stk.back();
            return n;
        }

        /**
         * Returns top of the stack
         * @return the top element
         */
        T top() {
            return top;
        }
};

/**
 * Searches the BST and returns the node to be looked for
 * @param k the key to be found
 * @param n the node from which to begin the search
 * @return the node once it is found (or not)
 */
Node* search(int k, Node* n) {
    if(n == NULL) return NULL;
    else if(n->getValue() < k) return search(k, n->getRightChild());
    else if(n->getValue() > k) return search(k, n->getLeftChild());
    else return n;
}

/**
 * Enumerates through the tree as a stack
 * @param n the head node
 * @param e the address to the stack
 */
void enumerate(Node* n, stack<Node*> &e) {
    if(n != NULL) e.push(n);
    if(n->getRightChild() != NULL) enumerate(n->getRightChild(), e);
    if(n->getLeftChild() != NULL) enumerate(n->getLeftChild(), e);
}

/**
 * Outputs the stack given
 * @param stack the stack of nodes
 */
void outputStack(stack<Node*>* stack) {
    cout << stack->top()->getValue();
    stack->pop();

    while(stack->empty() == false) {
      cout << " " << stack->top()->getValue();
      stack->pop();
    }
}

/**
 * Outputs the result of a search
 * @param k the key
 * @param h the head node (for enumerate)
 */
void outputSearch(int k, Node* h) {
    if(search(k, h) == NULL) cout << -1;
    else {
        stack<Node*>* s = new stack<Node*>();
        enumerate(h, *s);
        outputStack(s);
    }
}

/**
 * Inserts a Node into a binary search tree
 * @param c the iterable node
 * @param n the new node
 * @return a redunency code (-1 if node is already there)
 */
int insertNode(Node* c, int k) {
    if(k == c->getValue()) return -1;
    else if(c->getValue() == NULL) {
        c->setValue(k);
    } else if(k < c->getValue()) {
        if(c->getLeftChild() == NULL) {
            c->setLeftChild(new Node());
            c->getLeftChild()->setParent(c);
        } return insertNode(c->getLeftChild(), k);
    } else {
        if(c->getRightChild() == NULL) {
            c->setRightChild(new Node());
            c->getRightChild()->setParent(c);
        } return insertNode(c->getRightChild(), k);
    } return 0;
}

/**
 * Removes a node from the binary search tree
 * @param k the key of the node to be removed
 * @param h the head node of the tree
 */
int removeNode(int k, Node* h) {
    Node* n = search(k, h);

    if(n == NULL) return -1;
    else if(n->getLeftChild() == NULL && n->getRightChild() == NULL) {                                   // Leaf node
        if(n->getParent()->getLeftChild() == n) n->getParent()->setLeftChild(NULL);
        else n->getParent()->setRightChild(NULL);
    } else if(n->getLeftChild() == NULL && n->getRightChild() != NULL) {                                 // Only left child
        n->setValue(n->getLeftChild()->getValue());
        n->setLeftChild(NULL);
    } else if(n->getLeftChild() != NULL && n->getRightChild() == NULL){                                  // Only right child
        n->setValue(n->getRightChild()->getValue());
        n->setRightChild(NULL);
    } else {                                                                                             // Two children
        Node* tmp = h->getLeftChild();
        while(tmp->getRightChild() != NULL) tmp = tmp->getRightChild();

        n->setValue(tmp->getValue());
        tmp->getParent()->setRightChild(NULL);
        tmp->setValue(NULL);
    } return 0;
}

/**
 * Creates a binary search tree based on vector of keys
 * @param keys the keys
 * @return the head node
 */
Node* createTree(vector<int> keys) {
    Node* head = new Node(keys[0], NULL, NULL);

    for(int i=1; i < keys.size(); i++) insertNode(head, keys[i]);
    return head;
}

int main() {
    string val;
    int op, key;
    vector<int> init;

    while(!cin.fail()) {                        // Takes input for initial tree
        cin >> val;
        if(val == "s") break;
        init.push_back(strToInt(val));
    }

    cin.ignore(1, '\n');
    cin >> op;

    cin.ignore(1, '\n');
    cin >> key;

    Node* head = createTree(init);              // Creates inital tree
    switch(op) {                                // Operation
        case 1:                 // Search
        {
            outputSearch(key, head);
        } break;

        case 2:                 // Insert
        {
            if(insertNode(head, key) == -1) cout << -1;
            else {
                stack<Node*>* s = new stack<Node*>();
                enumerate(head, *s);
                outputStack(s);
            }
        } break;

        case 3:                 // Delete
        {
            if(removeNode(key, head) == -1) cout << -1;
            else {
                stack<Node*>* s = new stack<Node*>();
                enumerate(head, *s);
                outputStack(s);
            }            
        } break;

        default: break;
    }
}