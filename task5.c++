#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cstdlib>
using namespace std;

struct TreeNode {
    string value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(string val) : value(val), left(nullptr), right(nullptr) {}
};

bool isOperator(const string& c) {
    return c == "+" || c == "-" || c == "*" || c == "/";
}

int evaluate(int a, int b, string op) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") return a / b;  
    return 0;
}

void printTree(TreeNode* root, int level = 0) {
    if (root != nullptr) {
        printTree(root->right, level + 1);
        cout << string(4 * level, ' ') << root->value << "\n";
        printTree(root->left, level + 1);
    }
}

int evalTree(TreeNode* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return stoi(root->value);
    int leftVal = evalTree(root->left);
    int rightVal = evalTree(root->right);
    return evaluate(leftVal, rightVal, root->value);
}

TreeNode* constructTree(const string& expression) {
    stack<TreeNode*> st;
    string token;
    size_t i = 0;
    while (i < expression.length()) {
        if (expression[i] == ' ') {
            i++;
            continue;
        }
        
        if (expression[i] == '(' || isOperator(string(1, expression[i]))) {
            st.push(new TreeNode(string(1, expression[i])));
            i++;
        } else if (isdigit(expression[i]) || (expression[i] == '-' && i + 1 < expression.length() && isdigit(expression[i + 1]))) {
            token = "";
            if (expression[i] == '-') {
                token += '-';
                i++;
            }
            while (i < expression.length() && isdigit(expression[i])) {
                token += expression[i++];
            }
            st.push(new TreeNode(token));
        } else if (expression[i] == ')') {
            TreeNode* right = st.top(); st.pop();
            TreeNode* op = st.top(); st.pop();
            TreeNode* left = st.top(); st.pop();
            op->left = left;
            op->right = right;
            st.pop(); 
            st.push(op);
            i++;
        }
    }
    return st.top();
}

int main() {
    string expression = "(3 + (2-5) * 6) / (8-3))";
    TreeNode* root = constructTree(expression);
    cout << "Binary Expression Tree (Visualized sideways):\n";
    printTree(root);
    cout << "Value at root: " << evalTree(root) << endl;
    return 0;
}
