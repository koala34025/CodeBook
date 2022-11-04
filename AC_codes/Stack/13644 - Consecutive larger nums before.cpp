#include <iostream>
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


stack<pr<int, int>> stk;

int main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(0);

    int num;
    while(cin >> num){
        int days = 1;

        while(!stk.empty() && num <= stk.top().first){
            days += stk.top().second;
            stk.pop();
        }
        stk.push({num, days});
        cout << days << ' ';
    }
    cout << '\n';
}
