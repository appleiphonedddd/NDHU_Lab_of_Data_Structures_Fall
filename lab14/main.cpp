#include <iostream>
#include <stack>

using namespace std;

/**
 * @brief Node of a  tree
 */
struct node
{
    char data;    // data of the node
    node *left;   // pointer to the left child
    node *right;  // pointer to the right child
};

/**
 * @brief Creates a new node
 * @param data Data of the node
 * @return Pointer to the new node
 */
node *create_node(char data)
{
    node *new_node = new node();   // allocate memory for the new node
    new_node->data = data;         // set the data of the new node
    new_node->left = nullptr;      // set the left child of the new node to null
    new_node->right = nullptr;     // set the right child of the new node to null
    return new_node;
}

/**
 * @brief Constructs a  tree from a postfix expression
 */
node *construct_tree(char postfix[])
{
    stack<node *> s;                          // Stack s is used to temporarily store node pointers
    int i = 0;
    while (postfix[i] != '\0')
    {
        char ch = postfix[i];

        /**
         * If ch is the operand (letter), create a new node, the data is ch, and push it onto the stack s
         */
        if (ch >= 'A' && ch <= 'Z')
        {
            node *new_node = create_node(ch);
            s.push(new_node);
        }
        /**
         * If ch is the operator (+, -, *, /), create a new node, 
         * the data is ch, and pop two nodes from the stack s
         */
        else
        {
            node *new_node = create_node(ch);
            new_node->right = s.top();
            s.pop();
            new_node->left = s.top();
            s.pop();
            s.push(new_node);
        }
        i++;
    }
    /**
     * The top of the stack s is the root of the binary tree
     */
    return s.top();
}

class ExpressionTree
{
    public:

        void inorder(node *root) 
        { 
            if (root != NULL) 
            { 
                inorder(root->left); 
                cout << root->data << " "; 
                inorder(root->right); 
            } 
        }

        void postorder(node *root) 
        { 
            if (root != NULL) 
            { 
                postorder(root->left); 
                postorder(root->right); 
                cout << root->data << " "; 
            } 
        }

        void preorder(node *root) 
        { 
            if (root != NULL) 
            { 
                cout << root->data << " "; 
                preorder(root->left); 
                preorder(root->right); 
            } 
        }

        double evaluate(node *root)
        {
            if (root == nullptr)
                return 0;
            /**
             * If the left and right children of the root are empty (leaf nodes), 
             * return the data value of the root node minus '0', which is the corresponding number
             */
            if (root->left == nullptr && root->right == nullptr)
                return root->data - '0';

            /**
             * Recursively call evaluate, calculate the left subtree and return l_val and the right subtree return r_val
             */
            double l_val = evaluate(root->left);
            double r_val = evaluate(root->right);

            /**
             * If the data of the root node is an operator, 
             * perform the corresponding operation on l_val and r_val and return the result
             */
            if (root->data == '+')
                return l_val + r_val;

            /**
             * If the data of the root node is an operator,
             */
            if (root->data == '-')
                return l_val - r_val;

            /**
             * If the data of the root node is an operator,
             */
            if (root->data == '*')
                return l_val * r_val;

            return l_val / r_val;
        }
};