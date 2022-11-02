#include <iostream>
using namespace std;
#define ll long long

typedef struct treeNode {
    int data;
    struct treeNode *left;
    struct treeNode *right;
} Node;

void constructTree(Node** head)
{
    char c;
    int val;

    getchar();
    if((*head)==NULL)
    {
        c = getchar();
        if(c == ')')
            return;

        ungetc(c, stdin);
        cin >> val;

        (*head) = new Node;
        (*head)->data = val;
        (*head)->left = (*head)->right = NULL;

        if((*head)->left == NULL)
            constructTree( &(*head)->left);
        if((*head)->right == NULL)
            constructTree( &(*head)->right);
    }
    getchar();
}

void freeTree(Node *root)
{
    if (root!=NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    }
}

void printPrefix(Node *root)
{
    if(root == NULL)
        return;

    cout << root->data << ' ';
    printPrefix(root->left);
    printPrefix(root->right);
}

void printInfix(Node *root)
{
    if(root == NULL)
        return;

    printInfix(root->left);
    cout << root->data << ' ';
    printInfix(root->right);
}

void printPostfix(Node *root)
{
    if(root == NULL)
        return;

    printPostfix(root->left);
    printPostfix(root->right);
    cout << root->data << ' ';
}

ll weightSum(Node* root)
{
    if(root == NULL)
        return (ll)0;

    return (ll)root->data + weightSum(root->left) + weightSum(root->right);
}

ll maxPathSum(Node* root)
{
    if(root == NULL)
        return (ll)0;

    return (ll)root->data + max(maxPathSum(root->left), maxPathSum(root->right));
}

string cmd;

int main()
{
    Node* root = NULL;
    constructTree(&root);

    printPrefix(root);
    cout << '\n';
    printInfix(root);
    cout << '\n';
    printPostfix(root);
    cout << '\n';
    cout << weightSum(root);
    cout << '\n';
    cout << maxPathSum(root);
    cout << '\n';
}
