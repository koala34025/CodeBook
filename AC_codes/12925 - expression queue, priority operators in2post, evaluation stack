#include <iostream>
#include <string.h>
using namespace std;

template<class T>
class stack
{
public:
    // Constructor
    stack(int stackCapacity = 10);

    // Check if the stack is empty
    bool empty() const;

    // Return the top element
    T& top() const;

    // Insert a new element at top
    void push(const T& element);

    // Delete one element from top
    void pop();

    // Return the number of elements
    int size() const;
private:
    T* _stack;
    int top_idx; // initial value = -1
    int capacity;
};

template<class T>
stack<T>::stack(int stackCapacity)
{
    if(stackCapacity < 1)
        throw "stackCapacity must be > 0.";

    _stack = new T[stackCapacity];
    top_idx = -1;
    capacity = stackCapacity;
}

template<class T>
bool stack<T>::empty() const
{
    return top_idx == -1;
}

template<class T>
T& stack<T>::top() const
{
    if(empty())
        throw "Stack is empty. No top element.";

    return _stack[top_idx];
}

template<class T>
void stack<T>::push(const T& element)
{   // Add element to stack
    if(top_idx == capacity - 1){
        // resize
        T* temp = _stack;
        _stack = new T[2*capacity];
        for(int i=0; i<=top_idx; i++){
            _stack[i] = temp[i];
        }
        //delete [] temp;
        capacity *= 2;
    }
    _stack[++top_idx] = element;
}

template<class T>
void stack<T>::pop()
{   // Delete top element from stack
    if(empty())
        throw "Stack is empty. Cannot pop.";

    //_stack[top--].~T();
    top_idx--;
}

template<class T>
int stack<T>::size() const
{
    return top_idx + 1;
}

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

    // print all elements
    void print() const;

    char* in2post() const;
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

int prec(char c)
{   // Check priority of operators
    if(c == '^')
        return 3;
    if(c == '/' || c == '*')
        return 2;
    if(c == '+' || c == '-')
        return 1;

    return 0;
}

template<class T>
char* queue<T>::in2post() const
{
    char* infix = new char [_size+1];
    int infix_idx = -1;
    for(int i=(front_idx+1)%capacity; ; i=(i+1)%capacity){
        infix[++infix_idx] = _queue[i];
        if(i == back_idx)
            break;
    }
    infix[++infix_idx] = '\0';

    stack<char> st;

    int len = strlen(infix);
    char* postfix = new char[len+1];
    int post_idx = -1;

    for(int i=0; i<len; i++){
        char c = infix[i];

        // operand
        if(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9'){
            postfix[++post_idx] = c;
        }
        // '('
        else if(c == '('){
            st.push(c);
        }
        // ')'
        else if(c == ')'){
            while(!st.empty() && st.top() != '('){
                postfix[++post_idx] = st.top();
                st.pop();
            }
            if(!st.empty())
                st.pop();
        }
        // operator
        else{
            while(!st.empty() && prec(infix[i]) <= prec(st.top())){
                postfix[++post_idx] = st.top();
                st.pop();

            }
            st.push(c);
        }
    }

    while(!st.empty()){
        postfix[++post_idx] = st.top();
        st.pop();
    }

    postfix[++post_idx] = '\0';
    return postfix;
}

bool ok = true;

int eval(char* postfix)
{
    stack<int> st;

    int len = strlen(postfix);
    for(int i=0; i<len; i++){
        char c = postfix[i];
        if(c >= '0' && c <= '9'){
           st.push(c-'0');
        }
        else{
            if(st.empty()){
                ok = false;
                return 0;
            }
            int num2 = st.top();
            st.pop();
            if(st.empty()){
                ok = false;
                return 0;
            }
            int num1 = st.top();
            st.pop();

            switch(c){
            case '+':
                st.push(num2+num1);
                break;
            case '-':
                st.push(num1-num2);
                break;
            case '*':
                st.push(num1*num2);
                break;
            case '/':
                st.push(num1/num2);
                break;
            default:
                ok = false;
                return 0;
            }
        }
    }

    if(st.size() != 1){
        ok = false;
        return 0;
    }

    return st.top();
}

queue<char> que;
char cmd[1003];
char c;
int times;
bool flag = false;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> cmd;
    int len = strlen(cmd);
    for(int i=0; i<len; i++){
        que.push(cmd[i]);
    }

    while(cin >> cmd){
        if(strcmp(cmd, "Dequeue") == 0){
            cin >> times;
            for(int i=0; i<times; i++){
                    que.pop();
            }
        }
        if(strcmp(cmd, "Enqueue") == 0){
            cin >> c;
            que.push(c);
        }
        if(strcmp(cmd, "Print") == 0){
            // print expr
            cout << ((flag == 1) ? "\n" : "");
            flag = 1;

            que.print();
            cout << '\n';

            char* post = que.in2post();
            ok = true;
            int ans = eval(post);

            if(!ok)
                cout << "Invalid";
            else{
                int len = strlen(post);
                for(int i=0; i<len; i++)
                    cout << post[i];

                cout << '\n' << ans;
            }
        }
    }
}
