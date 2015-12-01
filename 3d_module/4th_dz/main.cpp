#include <iostream>
#include <stdlib.h>
using namespace std;

struct Node
{
    Node() {}
    ~Node() {}
    Node(int k) : key(k), height(1), subNodes(0), left(0), right(0) {}
    Node(const Node* obj) : key(obj->key), height(obj->height),
        subNodes(obj->subNodes), left(obj->left), right(obj->right) {}

    int key;
    int height;
    int subNodes;

    Node* left;
    Node* right;
};

int getHeight(Node* root)
{
    if(!root) return 0;
    return root->height;
}

int bfactor(Node* root)
{
    if(!root) return 0;
    return (getHeight(root->right) - getHeight(root->left));
}

void fixHeight(Node* root)
{
    int hLeft = getHeight(root->left);
    int hRight = getHeight(root->right) ;
    root->height = 1 + (hLeft > hRight ? hLeft : hRight);
}


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


class AVL
{
public:
    AVL() { head = 0; }
    ~AVL() {}
    void adding(int x){
        head  = add(head, x);
    }
    void deliting(int x){
        head = del(head, x);
    }
    int findStatist(Node*, int);
    int remake(int place);

private:
    Node* add(Node* root, int x);
    Node* del(Node*root, int x);

    Node* rotateRight(Node* root);
    Node* rotateLeft(Node* root);
    Node* balance(Node* root);

    Node* findMin(Node* root);
    Node* removeMin(Node* root);

    Node* head;
    int setSubnodes(Node *root);
};

Node* AVL::rotateRight(Node* root)
{
    Node* q = root->left;
    root->left = q->right;
    q->right = root;
    fixHeight(root);
    fixHeight(q);
    return q;
}

Node* AVL::rotateLeft(Node* root)
{
    Node* p = root->right;
    root->right = p->left;
    p->left = root;
    fixHeight(root);
    fixHeight(p);
    return p;
}

Node* AVL::balance(Node* root)
{
    fixHeight(root);
    if(bfactor(root) == 2)
    {
        if(bfactor(root->right) < 0) root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    else if(bfactor(root) == -2)
    {
        if(bfactor(root->left) > 0) root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    else return root;
}

Node* AVL::add(Node* root,int x)
{
    if(root == 0) return new Node(x);
    if(x < root->key) root->left = add(root->left, x);
    else root->right = add(root->right, x);
    return balance(root);
}

Node* AVL::del(Node* root, int x)
{
    if(root == 0) return 0;
    if(x < root->key) root->left = del(root->left, x);
    else if(x > root->key) root->right = del(root->right, x);
    else
    {
        Node* l = root->left;
        Node* r = root->right;
        delete root;
        if(!r) return l;
        Node* temp = findMin(r);
        temp->right = removeMin(r);
        temp->left = l;
        return balance(temp);
    }
    return balance(root);
}

Node* AVL::findMin(Node* root)
{
    if(root->left == 0) return root;
    return findMin(root->left);
}

Node* AVL::removeMin(Node* root)
{
    if(root->left == 0) return root->right;
    root->left = removeMin(root->left);
    return balance(root);
}

int AVL::setSubnodes(Node* root)
{
    if(root == 0) return 0;
    setSubnodes( root->left );
    setSubnodes( root->right );
    root->subNodes = 0;
    if(root->left != 0 ) root->subNodes += 1 + root->left->subNodes;
    if(root->right != 0) root->subNodes += 1 + root->right->subNodes;
    return root->subNodes;
}

int AVL::findStatist(Node* root, int place)
{
    if( root->left == 0) {
        if( place == 0 ) return root->key;
        return findStatist( root->right, place - 1);
    } else {
        if( root->left->subNodes + 1  == place) return root->key;
        if ( root->left->subNodes < place )
            return findStatist( root->right, place - root->left->subNodes - 2 );
        else return findStatist( root->left, place );
    }
}

int AVL::remake(int place) {
    setSubnodes(head);
    return findStatist( head, place );
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

int main()
{
    int n = 0;
    cin >> n;
    int* values = new int[n];
    int* statist = new int[n];
    for( int i = 0; i < n; ++i ) {
        cin >> values[i] >> statist[i];
    }
    AVL tree;
    for(int i = 0; i < n; ++i)
    {
        if( values[i] < 0 ) tree.deliting( abs( values[i] ));
        else tree.adding( values[i] );

        cout << tree.remake( statist[i] ) << '\n';
    }
    delete[] values;
    delete[] statist;
    return 0;
}
