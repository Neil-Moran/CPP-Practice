struct Node
{
    int value;
    Node *left, *right;

    Node(int v);

    void add(Node *n);
    int findRecursive(int target, int depth);
    int calcDepthRecursive(int currentDepth);
    void printRecursive();
    void printTree(int depth);
};

struct BinaryTree
{
    Node *root = 0;

    void add(Node *n);
    void find(int target);
    int calcDepth();
    void print();
    void printAsTree();
};