/*
 * Дано число N < 10​и последовательность целых чисел из [­2​..2​] длиной N.
 * Требуется построить бинарное дерево, заданное наивным порядком вставки.
 * Т.е., при добавлении очередного числа K в дерево с корнем root, если
 * root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в
 * левое поддерево root.
 * Выведите элементы в порядке post­order (снизу вверх).
 */

#include <iostream>
#include <stack>

using namespace std;

struct Node
{
    Node() : left(0), right(0), value(0) {}
    Node(int val) : left(0), right(0),value(val) {}
    Node(const Node& obj): value(obj.value) {
        left = new Node;
        left = obj.left;
        right = new Node;
        right = obj.right;
    }
    ~Node() {}

    Node* left;
    Node* right;
    int value;
};

class BST
{
public:
    BST();
    ~BST();

    void adding(int x) {
        addElement( head, x );
    }
    void postSeqCall(){
        postSeq( head );
    }

private:
    Node* addElement(Node* , int );
    void deleting(Node*);
    void postSeq(Node*);

    int hight;
    Node* head;
};

BST::BST()
{
    head = 0;
    hight = 0;
}

BST::~BST()
{
    deleting (head);
    delete head;
}

void BST::deleting(Node* root)
{
    if(root == 0) return;
    deleting(root->left);
    deleting(root->right);
    delete root->left;
    delete root->right;
}

Node* BST::addElement(Node* root, int toAdd)
{
    if(head == 0) {
        Node* temp = new Node(toAdd);
        head = temp;
        return 0;
    }
    Node* temp = 0;
    while( root != 0 ) {
        temp = root;
        if ( root->value <= toAdd ) root = root->right;
        else root = root->left;
    }
    if(temp->value <= toAdd) temp->right = new Node(toAdd);
    else temp->left = new Node(toAdd);
}

void BST::postSeq(Node* root)
{
    if(root == 0) return;
    stack<Node*> theStack;
    Node* prev = NULL;
    theStack.push( root );
    while( !theStack.empty() ) {
        Node* current = theStack.top();

        if( !prev || prev->left == current || prev->right == current) {
            if( current->left ) theStack.push( current->left );
            else if ( current->right ) theStack.push( current->right );
            else {
                cout << current->value << " ";
                theStack.pop();
            }
        }
        else if ( current->left == prev ) {
            if( current->right ) theStack.push( current->right );
            else {
                cout << current->value << " ";
                theStack.pop();
            }
        }
        else if( current->right == prev ) {
            cout << current->value << " ";
            theStack.pop();
        }
        prev = current;
    }
}

int main()
{
    BST* mine = new BST;
    int n = 0;
    cin >> n;
    int* arr = new int[n];
    for(int i =0; i < n; ++i) {
        cin >> arr[i];
        mine->adding( arr[i] );
    }
    mine->postSeqCall();

    delete mine;
    delete[] arr;
    return 0;
}
