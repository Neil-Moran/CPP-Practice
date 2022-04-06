struct Node
{
    int value;
    Node *left, *right;

    Node(int v);
};


struct BinaryTree
{
    Node *root = 0;

    void add(Node *n);
};