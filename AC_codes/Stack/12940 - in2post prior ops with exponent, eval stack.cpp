#include <iostream>
#include <math.h>
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

bool flag = false;

int prec(char c)
{
    if(c == '^'){
        return 3;
    }
    else if(c == '*' || c == '/'){
        return 2;
    }
    else if(c == '+' || c == '-'){
        return 1;
    }

    return 0;
}

char* in2post(char* infix)
{
    stack<char> st;
    char* postfix = new char[1003];
    int postfix_index = -1;

    int len = strlen(infix);
    for(int i=0; i<len; i++){
        char c = infix[i];

        if(c >= '0' && c <= '9'){
            postfix[++postfix_index] = c;
        }
        else if(c == '('){
            st.push(c);
        }
        else if(c == ')'){
            while(!st.empty() && st.top() != '('){
                postfix[++postfix_index] = st.top();
                st.pop();
            }
            st.pop();
        }
        else{
            while(!st.empty() && prec(c) <= prec(st.top())){
                if(prec(c) == 3 && prec(st.top()) == 3)
                    break;

                postfix[++postfix_index] = st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    while(!st.empty()){
        postfix[++postfix_index] = st.top();
        st.pop();
    }
    postfix[++postfix_index] = '\0';

    return postfix;
}

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
            int num2 = st.top();
            st.pop();
            int num1 = st.top();
            st.pop();

            switch(c){
            case '^':
                st.push((int)pow(num1, num2));
                break;
            case '*':
                st.push(num1 * num2);
                break;
            case '/':
                st.push(num1 / num2);
                break;
            case '+':
                st.push(num1 + num2);
                break;
            case '-':
                st.push(num1 - num2);
                break;
            }
        }
    }

    return st.top();
}

int main()
{
    char* infix = new char[1003];

    while(cin >> infix){
        cout << (flag == 1 ? "\n": "");
        flag = 1;

        cout << infix << '\n';

        char* postfix = in2post(infix);
        cout << postfix << '\n';

        cout << eval(postfix);
    }
}
