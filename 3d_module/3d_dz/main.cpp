/*
 * Дано число N < 10​и последовательность пар целых чисел из [­2​..2​] длиной N.
 * Построить декартово дерево из N узлов, характеризующихся парами чисел {X​, Y​}.
 * Каждая пара чисел {X​, Y​} определяет ключ X​и приоритет Y​в декартовом дереве.
 */

#include <iostream>

using namespace std;

struct NodeBST {
    NodeBST() : left(0), right(0), value(0) { }

    NodeBST(int val) : left(0), right(0), value(val) { }

    NodeBST(const NodeBST &obj) : value(obj.value) {
        left = new NodeBST;
        left = obj.left;
        right = new NodeBST;
        right = obj.right;
    }

    ~NodeBST() { }

    NodeBST *left;
    NodeBST *right;
    int value;
};

class BSTree {
public:
    BSTree() : head(0), maxLevelWidth(0) { }

    ~BSTree() {
        NodeBST* temp;
        deleting( &head, 1, &temp, 0 );
    }

    void adding(int x) {
        addElement( head, x );
    }

    int getMaxWidth();

private:
    void deleting(NodeBST **one, int sizeOne, NodeBST **two, int sizeTwo);
    NodeBST *addElement(NodeBST *, int);
    void goThroughLevels(NodeBST **one, int sizeOne, NodeBST **two, int sizeTwo);

    NodeBST *head;
    int maxLevelWidth;
};

void BSTree::deleting(NodeBST** one, int sizeOne, NodeBST** two, int sizeTwo) {
    while( sizeOne != 0 && sizeTwo != 0) {
        int cntr = 0;
        if ( sizeOne > 0 ) {
            for( int i = 0; i < sizeOne; ++i ) {
                if( one[i]->left != 0) two[cntr++] = one[i]->left;
                if( one[i]->right != 0 ) two[cntr++] = one[i]->right;
                delete one[i];
            }
            one = 0;
            sizeOne = 0;
            sizeTwo  = cntr;
        } else {
            for( int i = 0; i < sizeTwo; ++i ) {
                if( two[i]->left ) one[cntr++] = two[i]->left;
                if( two[i]->right ) one[cntr++] = two[i]->right;
                delete two[i];
            }
            two = 0;
            sizeTwo = 0;
            sizeOne = cntr;
        }
    }
}

NodeBST *BSTree::addElement(NodeBST *root, int toAdd) {
    if (head == 0) {
        NodeBST *temp = new NodeBST(toAdd);
        head = temp;
        return 0;
    }
    if (root == 0) {
        NodeBST *temp = new NodeBST(toAdd);
        return temp;
    }
    if (root->value <= toAdd) root->right = addElement(root->right, toAdd);
    else root->left = addElement(root->left, toAdd);
    return root;
}


void BSTree::goThroughLevels(NodeBST **one, int sizeOne, NodeBST** two, int sizeTwo) {

    while( sizeOne != 0 || sizeTwo != 0) {
        int cntr = 0;
        if ( sizeOne > 0 ) {
            for( int i = 0; i < sizeOne; ++i ) {
                if( one[i]->left != 0 ) two[cntr++] = one[i]->left;
                if( one[i]->right != 0 ) two[cntr++] = one[i]->right;
            }
            sizeOne = 0;
            sizeTwo  = cntr;
        } else {
            for( int i = 0; i < sizeTwo; ++i ) {
                if( two[i]->left != 0 ) one[cntr++] = two[i]->left;
                if( two[i]->right != 0 ) one[cntr++] = two[i]->right;
            }
            sizeTwo = 0;
            sizeOne = cntr;
        }
        if (cntr > maxLevelWidth) maxLevelWidth = cntr;
    }
}

int BSTree::getMaxWidth() {
    NodeBST** tempOne = new NodeBST*[10000];
    NodeBST** tempTwo = new NodeBST*[10000];
    if( head != 0 ) {
        tempOne[0] = head;
        maxLevelWidth = 1;
    }
    goThroughLevels( tempOne, 1, tempTwo, 0 );
    delete[] tempOne;
    delete[] tempTwo;
    return maxLevelWidth;
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////


struct Node {
    Node() : key(0), priority(0), left(NULL), right(NULL) { }

    Node(int x, int y) : key(x), priority(y), left(NULL), right(NULL) { }

    ~Node() { }

    int key;
    int priority;
    Node *left;
    Node *right;
};

class Treap {
public:
    Treap() {
        head = 0;
        maxLevelWidth = 0;
    }

    ~Treap() {
        deleting(head);
        delete head;
    }

    void adding(int key, int priority) {
        addElement(head, key, priority);
    }

    int getMaxWidth();

    void printing() {
        print(head);
    }

    void print(Node *node) {
        if (node == 0) return;
        print(node->left);
        cout << node->key << " " << node->priority << endl;
        print(node->right);
    }

private:
    Node *head;

    void merzh(Node *&T, Node *L, Node *R);

    void split(Node *T, int key, Node *&L, Node *&R);

    void deleting(Node *);

    void addElement(Node *, int key, int priority);

    void goThroughLevels(Node **one, int sizeOne, Node **two, int sizeTwo);

    int maxLevelWidth;
};

void Treap::split(Node *T, int key, Node *&L, Node *&R) {
    if (T == NULL) {
        L = R = 0;
        return;
    }
    if (T->key <= key) {
        split(T->right, key, T->right, R);
        L = T;
    } else {
        split(T->left, key, L, T->left);
        R = T;
    }
}

void Treap::merzh(Node *&T, Node *L, Node *R) {
    if (L == 0 || R == 0) {
        if (L != 0) T = L;
        else T = R;
        return;
    }
    if (L->priority > R->priority) {
        merzh(L->right, L->right, R);
        T = L;
    } else {
        merzh(R->left, L, R->left);
        T = R;
    }
}

Node *findLessPriority(Node **root, int priority, int size) {
    if (root == NULL || size == 0) return 0;
    Node **temp = new Node *[size * 2];
    int cntr = 0;
    for (int i = 0; i < size; ++i) {
        if (root[i]->priority < priority) return root[i];

        if (root[i]->left != 0) {
            temp[cntr++] = root[i]->left;
        }
        if (root[i]->right != 0) {
            temp[cntr++] = root[i]->right;
        }
    }
    Node *ret = findLessPriority(temp, priority, cntr);
    delete[] temp;
    return ret;
}


void Treap::addElement(Node *root, int key, int priority) {
    if (head == 0) {
        head = new Node(key, priority);
        return;
    }

    Node *prev = 0;
    while (root != 0) {
        if (root->priority < priority) {
            Node *newNode = new Node(key, priority);
            split(root, key, newNode->left, newNode->right);
            if (prev != 0 && prev->key > key) prev->left = newNode;
            else if (prev != 0)prev->right = newNode;
            else head = newNode;
            return;
        }
        prev = root;
        if (key < root->key) {
            root = root->left;
        } else {
            root = root->right;
        }
    }

    if (key < prev->key) prev->left = new Node(key, priority);
    else prev->right = new Node(key, priority);
}

void Treap::deleting(Node *root) {
    if (root == 0) return;
    deleting(root->left);
    deleting(root->right);
    delete root->left;
    delete root->right;
}

void Treap::goThroughLevels(Node **one, int sizeOne, Node** two, int sizeTwo) {
    while( sizeOne != 0 || sizeTwo != 0) {
        int cntr = 0;
        if ( sizeOne > 0 ) {
            for( int i = 0; i < sizeOne; ++i ) {
                if( one[i]->left ) two[cntr++] = one[i]->left;
                if( one[i]->right ) two[cntr++] = one[i]->right;
            }
            //one = 0;
            sizeOne = 0;
            sizeTwo  = cntr;
        } else {
            for( int i = 0; i < sizeTwo; ++i ) {
                if( two[i]->left ) one[cntr++] = two[i]->left;
                if( two[i]->right ) one[cntr++] = two[i]->right;
            }
            sizeTwo = 0;
            sizeOne = cntr;
        }
        if (cntr > maxLevelWidth) maxLevelWidth = cntr;
    }
}

int Treap::getMaxWidth() {
    Node** tempOne = new Node*[10000];
    Node** tempTwo = new Node*[10000];
    if( head != 0 ) {
        tempOne[0] = head;
        maxLevelWidth = 1;
    }
    goThroughLevels( tempOne, 1, tempTwo, 0 );
    delete[] tempOne;
    delete[] tempTwo;
    return maxLevelWidth;
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

int main() {
    int n;
    cin >> n;
    int inputX = 0;
    int inputY = 0;
    Treap *treap = new Treap;
    BSTree *tree = new BSTree;
    for (int i = 0; i < n; ++i) {
        cin >> inputX;
        cin >> inputY;
        treap->adding(inputX, inputY);
        tree->adding(inputX);
    }
    //treap->printing();
    cout << treap->getMaxWidth() - tree->getMaxWidth();

    delete treap;
    delete tree;
    return 0;
}
