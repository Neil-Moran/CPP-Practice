struct Node
{
    int value;
    Node *left, *right;

    Node(int v);

    void add(Node *n);
};


struct BinaryTree
{
    Node *root = 0;

    void add(Node *n);
};