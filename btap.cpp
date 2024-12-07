#include <iostream>
#include <string>
#include <stack>
#include <cctype>

using namespace std;

// Cấu trúc node của cây biểu thức
struct Node {
    string data;
    Node* left;
    Node* right;
    Node(string val) : data(val), left(nullptr), right(nullptr) {}
};

struct ExpressionTree {
    Node* root;

    ExpressionTree() : root(nullptr) {}

    // Kiểm tra cây có rỗng không
    bool isEmpty() {
        return root == nullptr;
    }

    // Hàm khởi tạo cây từ một biểu thức
    void buildTree(const string& expr) {
        stack<Node*> nodes;

        for (char c : expr) {
            if (isalnum(c)) {  // Hỗ trợ cả chữ cái và số
                nodes.push(new Node(string(1, c)));
            } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
                // Nếu là toán tử, lấy 2 node con từ stack và tạo node mới
                Node* right = nodes.top(); nodes.pop();
                Node* left = nodes.top(); nodes.pop();
                Node* newNode = new Node(string(1, c));
                newNode->left = left;
                newNode->right = right;
                nodes.push(newNode);
            }
        }

        // Sau khi duyệt hết biểu thức, phần tử duy nhất trong stack là root của cây
        if (!nodes.empty())
            root = nodes.top();
    }

    // In biểu thức theo dạng Trung tố (Infix)
    void infixTraversal(Node* node) {
        if (node) {
            if (node->left) cout << "(";
            infixTraversal(node->left);
            cout << node->data;
            infixTraversal(node->right);
            if (node->right) cout << ")";
        }
    }

    // In biểu thức theo dạng Tiền tố (Prefix)
    void prefixTraversal(Node* node) {
        if (node) {
            cout << node->data;
            prefixTraversal(node->left);
            prefixTraversal(node->right);
        }
    }

    // In biểu thức theo dạng Hậu tố (Postfix)
    void postfixTraversal(Node* node) {
        if (node) {
            postfixTraversal(node->left);
            postfixTraversal(node->right);
            cout << node->data;
        }
    }

    // Hàm in các biểu thức theo ba dạng
    void printAllTraversals() {
        cout << "Infix (Trung tố): ";
        infixTraversal(root);
        cout << endl;

        cout << "Prefix (Tiền tố): ";
        prefixTraversal(root);
        cout << endl;

        cout << "Postfix (Hậu tố): ";
        postfixTraversal(root);
        cout << endl;
    }
};

int main() {
    ExpressionTree exprTree;

    string expr = "a5*bc6^*d/-hf-e12/^*+";

    exprTree.buildTree(expr);

    exprTree.printAllTraversals();

    return 0;
}
