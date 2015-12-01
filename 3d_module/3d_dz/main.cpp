#include <iostream>

using namespace std;

struct NodeBST{
    NodeBST() {}
    NodeBST(int val) : value(val){}
    NodeBST(const NodeBST& obj) : value(obj.value) {
        left = new NodeBST;
        left = obj.left;
        right = new NodeBST;
        right = obj.right;
    }
    ~NodeBST() {}

    int value;
    NodeBST* left = 0;
    NodeBST* right = 0;
};

class BSTree {
public:
    BSTree() {}
    ~BSTree(){
        deleting(head);
        delete head;
    }

    void adding(int x){
        addElement(head, x);
    }
    int getMaxWidth();
    void goThroughLevels(NodeBST **, int size );

private:
    void deleting( NodeBST* );
    NodeBST* addElement( NodeBST* , int );

    NodeBST* head = 0;
    int maxLevelWidth = 0;
};

void BSTree::deleting(NodeBST* root)
{
    if(root == 0) return;
    deleting(root->left);
    deleting(root->right);
    delete root->left;
    delete root->right;
}

NodeBST* BSTree::addElement(NodeBST* root, int toAdd)
{
    if(head == 0)
    {
        NodeBST* temp = new NodeBST(toAdd);
        head = temp;
        return 0;
    }
    if(root == 0)
    {
        NodeBST* temp = new NodeBST(toAdd);
        return temp;
    }
    if(root->value <= toAdd) root->right = addElement(root->right, toAdd);
    else root->left = addElement (root->left, toAdd);
    return root;
}

int BSTree::getMaxWidth()
{
    goThroughLevels( &head, 1);
    return maxLevelWidth;
}

void BSTree::goThroughLevels(NodeBST** arr, int size)
{
    if( size == 0 ) return;
    NodeBST** temp  = new NodeBST*[size * 2];
    int cntr = 0;
    for(int i = 0; i < size; ++i) {
        if( arr[i]->left != 0 ) {
            temp[cntr++] = arr[i]->left;
        }
        if( arr[i]->right != 0 ) {
            temp[cntr++] = arr[i]->right;
        }
    }
    if ( cntr > maxLevelWidth ) maxLevelWidth = cntr;
    goThroughLevels( temp, cntr );
    delete[] temp;
}


///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////


struct Node {
    Node() {}
    ~Node() {}
    Node(int x, int y) : key(x), priority(y){}

    int key = 0;
    int priority = 0;
    int subHeight = 0;
    Node* left = 0;
    Node* right = 0;
};

class Treap{
public:
    Treap() {}
    ~Treap() {
        deleting(head);
        delete head;
    }

    void addElement(int key, int priority);
    int getMaxWidth();

private:
    Node* head = 0;

    void merzh(Node*& T,Node* L, Node* R);
    void split(Node* T, int key, Node *&L, Node *&R);

    void deleting(Node*);
    void goThroughLevels(Node** arr, int size );
    int maxLevelWidth = 0;
};

void Treap::split(Node *T, int key, Node*& L, Node*& R){
    if(T == 0){
        L = R = 0;
        return;
    }
    if(T->key < key) {
        split(T->right, key, T->right, R);
        L = T;
    } else {
        split(T->left, key, L, T->left);
        R = T;
    }
}

void Treap::merzh(Node*& T, Node *L, Node *R){
    if(L == 0 || R == 0){
        if(L != 0) T = L;
        else T = R;
        return;
    }
    if(L->priority > R->priority)
    {
        merzh(L->right, L->right, R);
        T = L;
    } else {
        merzh(R->left, L, R->left);
        T = R;
    }
}

void Treap::addElement(int key, int priority){
    if(head == 0){
        head = new Node(key, priority);
        return;
    }
    Node* L, *R, *res ;
    split(head, key, L, R);
    Node* temp = new Node(key, priority);
    merzh(res, L, temp);
    merzh(head, res, R);
}

void Treap::deleting(Node* root){
    if(root == 0) return;
    deleting(root->left);
    deleting(root->right);
    delete root->left;
    delete root->right;
}

void Treap::goThroughLevels(Node** arr, int size)
{
    if( size == 0 ) return;
    Node** temp  = new Node*[size * 2];
    int cntr = 0;
    for(int i = 0; i < size; ++i) {
        if( arr[i]->left != 0 ) {
            temp[cntr++] = arr[i]->left;
        }
        if( arr[i]->right != 0 ) {
            temp[cntr++] = arr[i]->right;
        }
    }
    if ( cntr > maxLevelWidth ) maxLevelWidth = cntr;
    goThroughLevels( temp, cntr );
    delete[] temp;
}

int Treap::getMaxWidth()
{
    goThroughLevels( &head, 1);
    return maxLevelWidth;
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////


int main()
{
    int n;
    cin >> n;
    int inputX = 0;
    int inputY = 0;
    Treap* treap = new Treap;
    BSTree* tree = new BSTree;
    for( int i = 0; i < n; ++i ) {
        cin >> inputX;
        cin >> inputY;
        treap->addElement( inputX, inputY );
        tree->adding( inputX );
    }
    cout << treap->getMaxWidth() - tree->getMaxWidth();

    delete treap;
    delete tree;
    return 0;
}

