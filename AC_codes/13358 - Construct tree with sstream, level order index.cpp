#include <iostream>
#include <sstream>
using namespace std;
#define ll long long

template<class T>
class queue // A finite ordered list
{
public:
    // Constructor
    queue(int queueCapacity = 10);

    // Check if the queue is empty
    bool empty() const;

    // Return the front element
    T& front() const;

    // Return the back element
    T& back() const;

    // Insert a new element at back
    void push(const T& element);

    // Delete one element from front
    void pop();

    // Return the number of elements
    int size() const;

    // Print all elements
    void print() const;
private:
    T* _queue;
    int front_idx, back_idx; // initial value = 0
    // (front_idx, back_idx]
    int capacity;
    int _size;
};

template<class T>
queue<T>::queue(int queueCapacity)
{
    if(queueCapacity < 1)
        throw "queueCapacity must be > 0.";

    _queue = new T[queueCapacity];
    front_idx = 0;
    back_idx = 0;
    capacity = queueCapacity;
    _size = 0;
}

template<class T>
bool queue<T>::empty() const
{
    return front_idx == back_idx;
}

template<class T>
T& queue<T>::front() const
{
    if(empty())
        throw "Queue is empty. No front element.";

    return _queue[(front_idx+1)%capacity];
}

template<class T>
T& queue<T>::back() const
{
    if(empty())
        throw "Queue is empty. No back element.";

    return _queue[back_idx];
}

template<class T>
void queue<T>::push(const T& element)
{   // Add element at back of queue
    if((back_idx+1)%capacity == front_idx){
        // resize
        T* temp = _queue;
        _queue = new T[2*capacity];
        int new_back_idx = -1;
        for(int i=(front_idx+1)%capacity; ; i=(i+1)%capacity){
            _queue[++new_back_idx] = temp[i];
            if(i == back_idx)
                break;
        }
        capacity *= 2;
        back_idx = new_back_idx;
        front_idx = capacity - 1;
    }
    back_idx = (back_idx+1)%capacity;
    _queue[back_idx] = element;
    _size++;
}

template<class T>
void queue<T>::pop()
{   // Delete front element from queue
    if(empty())
        throw "Queue is empty. Cannot pop.";

    front_idx = (front_idx+1)%capacity;
    //_queue[front_idx].~T();
    _size--;
}

template<class T>
int queue<T>::size() const
{
    return _size;
}

template<class T>
void queue<T>::print() const
{
    for(int i=(front_idx+1)%capacity; ; i=(i+1)%capacity){
        cout << _queue[i];
        if(i == back_idx)
            break;
    }
}

template<class T1, class T2>
struct pr {
    // Remove constructors just for brace-enclosed initializer
    T1 first;
    T2 second;
};

template<class T1, class T2>
bool operator ==(const pr<T1, T2> &lhs, const pr<T1, T2> &rhs)
{
    return (lhs.first == rhs.first && lhs.second == rhs.second);
}

template<class T1, class T2>
bool operator !=(const pr<T1, T2> &lhs, const pr<T1, T2> &rhs)
{
    return (!(lhs == rhs));
}

template<class T1, class T2>
bool operator <(const pr<T1, T2> &lhs, const pr<T1, T2> &rhs)
{
    return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
}

template<class T1, class T2>
bool operator >(const pr<T1, T2> &lhs, const pr<T1, T2> &rhs)
{
    return (rhs < lhs);
}

template<class T1, class T2>
bool operator <=(const pr<T1, T2> &lhs, const pr<T1, T2> &rhs)
{
    return (!(rhs < lhs));
}

template<class T1, class T2>
bool operator >=(const pr<T1, T2> &lhs, const pr<T1, T2> &rhs)
{
    return (!(lhs < rhs));
}

typedef struct treeNode {
    int data;
    struct treeNode *left;
    struct treeNode *right;
} Node;

void constructTree(Node** head, stringstream &ss)
{
    char c;
    int val;

    ss >> c;
    if((*head)==NULL)
    {
        ss >> c;
        if(c == ')')
            return;

        ss.unget();
        ss >> val;

        (*head) = new Node;
        (*head)->data = val;
        (*head)->left = (*head)->right = NULL;

        if((*head)->left == NULL)
            constructTree( &(*head)->left, ss);
        if((*head)->right == NULL)
            constructTree( &(*head)->right, ss);
    }
    ss >> c;
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

void dfs(Node *root, int idx)
{
    if(root == NULL)
        return;

    root->data = idx;
    dfs(root->left, idx*2);
    dfs(root->right, idx*2+1);
}

string s;
stringstream ss;

int main()
{
    while(cin >> s){
        ss << s;
        Node* root = NULL;
        constructTree(&root, ss);
        int ans = 0;

        dfs(root, 1);

        queue<pr<Node*, int>> q;
        q.push({root, 0});
        int this_level = 0;
        int this_mn_idx = 1;

        while(!q.empty()){
            auto [now, level] = q.front();
            q.pop();

            if(now == NULL)
                continue;

            if(level != this_level){
                this_mn_idx = now->data;
                this_level = level;
            }

            ans = max(ans, now->data - this_mn_idx + 1);

            q.push({now->left, level+1});
            q.push({now->right, level+1});
        }

        cout << ans << '\n';
        freeTree(root);
    }
}
