#include <iostream>

using namespace std;

struct Node
{
    Node() {}
    Node(int val)
    {
        value = val;
    }
    Node(const Node& obj)
    {
        value = obj.value;
        left = new Node;
        left = obj.left;
        right = new Node;
        right = obj.right;
    }
    ~Node() {}
    int value;
    Node* left = 0;
    Node* right = 0;
    int subNodes = 0;
};

class BST
{
public:
    BST();
    ~BST();
    Node* addElement(Node* , int );
    void inSeq(Node*);
    void preSeq(Node*);
    void postSeq(Node*);
    void levSeq(Node*, int);
    int findMe(Node*, int);
    Node* head;
//private:
    void deleting(Node*);
    int hight;
};

BST::BST()
{
    head = 0;
    hight = 0;
}

BST::~BST()
{
    deleting(head);
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
    if(head == 0)
    {
        Node* temp = new Node(toAdd);
        temp->subNodes = 0;
        head = temp;
        return 0;
    }
    if(root == 0)
    {
        Node* temp = new Node(toAdd);
        temp->subNodes = 0;
        return temp;
    }
    if(root->value <= toAdd) root->right = addElement(root->right, toAdd);
    else root->left = addElement (root->left, toAdd);
    root->subNodes +=1;
    return root;
}

void BST::inSeq(Node* root)
{
    if(root == 0) return;
    inSeq(root->left);
    cout << root->value << " ";
    inSeq(root->right);
}

void BST::preSeq(Node* root)
{
    if(root == 0) return;
    cout << root->value << " ";
    preSeq(root->left);
    preSeq(root->right);
}

void BST::postSeq(Node* root)
{
    if(root == 0) return;
    postSeq(root->left);
    postSeq(root->right);
    cout << root->value << " ";
}

void BST::levSeq(Node* root, int num)
{
    for(int i = 0; i < num; ++i)
    {
        cout << root[i].value << " " <<root[i].subNodes << endl;
    }
    int iter = 0;
    Node* arr = new Node[num*2];
    for(int i = 0; i < num; ++i)
    {
        if(root[i].left != 0  && root[i].right != 0)
        {
            arr[iter++] = *root[i].left;
            arr[iter++] = *root[i].right;
        }
        else if(root[i].left == 0 && root[i].right != 0)
        {
            arr[iter++] = *root[i].right;
        }
        else if(root[i].right == 0 && root[i].left != 0)
        {
            arr[iter++] = *root[i].left;
        }
    }
    if(iter == 0) return;
    levSeq(arr, iter);
    delete[] arr;
}

int BST::findMe(Node* root, int num)
{
    if(num < 0 || num > root->subNodes) return -1;
    if(root->left == 0 || root->left->subNodes + 1 == num)
        return root->value;
    if(root->left->subNodes < num)
        return findMe(root->right, (num - root->left->subNodes - 2));
    else return findMe(root->left, num);
}

int main()
{
    BST mine;
    int n = 0;
    cin >> n;
    int* arr = new int[n];
    for(int i =0; i < n; ++i) {
        cin >> arr[i];
        mine.addElement(mine.head, arr[i]);
    }
    mine.postSeq(mine.head);
    return 0;
}
