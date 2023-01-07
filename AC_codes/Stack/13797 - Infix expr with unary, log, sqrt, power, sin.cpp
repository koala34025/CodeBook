#include <iostream>
#include <stack>
#include <string>
#include <cmath>
using namespace std;

class Expression{
public:
    Expression() {}
    void input(){}

    double evaluate(stack<string> postfix)
    {
        string func[10] = {"+", "-", "*", "/", "sin", "cos", "tan", "log", "sqrt", "^"};

        stack<double> ans;
        stack<string> rev_st;

        while(!postfix.empty()){
            rev_st.push(postfix.top());
            postfix.pop();
        }

        while(!rev_st.empty()){
            string now = rev_st.top();
            rev_st.pop();

            if(now == func[0]){
                double num2 = ans.top();
                ans.pop();
                double num1 = ans.top();
                ans.pop();

                ans.push(num1 + num2);
            }
            else if(now == func[1]){
                double num2 = ans.top();
                ans.pop();
                double num1 = ans.top();
                ans.pop();

                ans.push(num1 - num2);
            }
            else if(now == func[2]){
                double num2 = ans.top();
                ans.pop();
                double num1 = ans.top();
                ans.pop();

                ans.push(num1 * num2);
            }
            else if(now == func[3]){
                double num2 = ans.top();
                ans.pop();
                double num1 = ans.top();
                ans.pop();

                ans.push(num1 / num2);
            }
            else if(now == func[4]){
                double num2 = ans.top();
                ans.pop();

                ans.push(sin(num2));
            }
            else if(now == func[5]){
                double num2 = ans.top();
                ans.pop();

                ans.push(cos(num2));
            }
            else if(now == func[6]){
                double num2 = ans.top();
                ans.pop();

                ans.push(tan(num2));
            }
            else if(now == func[7]){
                double num2 = ans.top();
                ans.pop();
                double num1 = ans.top();
                ans.pop();

                ans.push(log(num2)/log(num1));
            }
            else if(now == func[8]){
                double num2 = ans.top();
                ans.pop();

                ans.push(sqrt(num2));
            }
            else if(now == func[9]){
                double num2 = ans.top();
                ans.pop();
                double num1 = ans.top();
                ans.pop();

                ans.push(pow(num1, num2));
            }
            else{ // numeric
                if(now == string(1, 'e')){
                    ans.push(2.718);
                }
                else{
                    ans.push(stod(now));
                }
            }
        }

        return ans.top();
    }

    void eval(){
        stack<string> post = in2post();

        cout << evaluate(post) << '\n';
    }

    int prec(string op_str)
    {
        string func[10] = {"+", "-", "*", "/", "sin", "cos", "tan", "log", "sqrt", "^"};

        for(int i=4; i<=9; i++){
            if(op_str == func[i]){
                return 3;
            }
        }
        for(int i=2; i<=3; i++){
            if(op_str == func[i]){
                return 2;
            }
        }
        for(int i=0; i<=1; i++){
            if(op_str == func[i]){
                return 1;
            }
        }

        return 0;
    }

    stack<string> in2post()
    {
        char c;

        stack<string> st;
        stack<string> postfix;

        while(cin >> c){

            //cout << c << '\n';

            if(c == ' '){
                continue;
            }
            else if(c >= '0' && c <= '9' || c == '.'){ // if c is a digit
                ungetc(c, stdin);
                double num;
                cin >> num;
                string num_str = to_string(num);
                postfix.push(num_str); // postfix push back a num
            }
            else if(c == '(' || c == '{'){
                string c_str = string(1, c);
                st.push(c_str);
            }
            else if(c == ')'){
                string left_parenthesis = "(";
                while(!st.empty() && st.top() != left_parenthesis){
                    postfix.push(st.top());
                    st.pop();
                }
                st.pop();
            }
            else if(c == '}'){
                string left_parenthesis = "{";
                while(!st.empty() && st.top() != left_parenthesis){
                    postfix.push(st.top());
                    st.pop();
                }
                st.pop();
            }
            else if(c == '-'){
                char prev_c = c;
                cin >> c;
                if(c >= '0' && c <= '9' || c == '.'){ // if c is a digit
                    ungetc(c, stdin);
                    ungetc(prev_c, stdin);
                    float num;
                    cin >> num;
                    string num_str = to_string(num);
                    postfix.push(num_str); // postfix push back a num
                }
                else{
                    ungetc(c, stdin);
                    string c_str = to_string(prev_c);
                    while(!st.empty() && prec(c_str) <= prec(st.top())){
                        //if(prec(c_str) == 3 && prec(st.top()) == 3)
                            //break;

                        postfix.push(st.top());
                        st.pop();
                    }
                    st.push(c_str);
                }
            }
            else{
                string c_str;
                if(c == 's'){
                    cin >> c;
                    if(c == 'i'){
                        cin >> c;
                        c_str = string("sin");
                    }
                    else{
                        cin >> c >> c;
                        c_str = string("sqrt");
                    }
                }
                else if(c == 'c'){
                    cin >> c >> c;
                    c_str = string("cos");
                }
                else if(c == 't'){
                    cin >> c >> c;
                    c_str = string("tan");
                }
                else if(c == 'l'){
                    cin >> c >> c >> c;
                    if(c == '_'){
                        c_str = string("log");
                    }
                    else{
                        ungetc(c, stdin);
                        c_str = string("log"); // remember to push e at the same time
                        string e_str = string("e");
                        postfix.push(e_str);
                    }
                }
                else{
                    c_str = string(1, c);
                }

                while(!st.empty() && prec(c_str) <= prec(st.top())){
                    //if(prec(c_str) == 3 && prec(st.top()) == 3)
                        //break;

                    postfix.push(st.top());
                    st.pop();
                }
                st.push(c_str);
            }


            /*stack<string> stk1(st);
            stack<string> stk2(postfix);
            while(!stk1.empty()){
                cout << stk1.top() << ' ';
                stk1.pop();
            }
            cout << '\n';
            while(!stk2.empty()){
                cout << stk2.top() << ' ';
                stk2.pop();
            }
            cout << "\n=======================================\n";*/

        }

        while(!st.empty()){
            postfix.push(st.top());
            st.pop();
        }

        // cout postfix ...
        return postfix;
    }
};



int main(){
    Expression exp1;
    exp1.input();
    exp1.eval();
    return 0;
}
