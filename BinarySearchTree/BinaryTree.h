struct Node
{
    int value;
    Node *left, *right;

    Node(int v);

    void add(Node *n);
    int findRecursive(int target, int depth);
    void printRecursive();
    void printTree(int depth);
};

struct BinaryTree
{
    Node *root = 0;

    void add(Node *n);
    void find(int target);
    void print();
    void printAsTree();
};