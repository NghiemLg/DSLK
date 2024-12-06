#include <stdio.h>
#include <stdlib.h>

// Định nghĩa cấu trúc cho một node trong cây biểu thức
typedef struct Node {
    char data; // Toán tử hoặc toán hạng
    struct Node* left;
    struct Node* right;
} Node;

// Hàm tạo một node mới
Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Hàm xây dựng cây biểu thức mẫu
Node* buildExpressionTree() {
    // Biểu thức mẫu: (a + b) * c
    Node* root = createNode('*');
    root->left = createNode('+');
    root->right = createNode('c');
    
    root->left->left = createNode('a');
    root->left->right = createNode('b');
    
    return root;
}

// Duyệt cây theo thứ tự NLR (Preorder)
void preorderTraversal(Node* root) {
    if (root == NULL) return;
    printf("%c ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// Duyệt cây theo thứ tự LNR (Inorder)
void inorderTraversal(Node* root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    printf("%c ", root->data);
    inorderTraversal(root->right);
}

// Duyệt cây theo thứ tự LRN (Postorder)
void postorderTraversal(Node* root) {
    if (root == NULL) return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%c ", root->data);
}

// Hàm chính
int main() {
    Node* root = buildExpressionTree();
    
    printf("Duyệt NLR (Preorder): ");
    preorderTraversal(root);
    printf("\n");
    
    printf("Duyệt LNR (Inorder): ");
    inorderTraversal(root);
    printf("\n");
    
    printf("Duyệt LRN (Postorder): ");
    postorderTraversal(root);
    printf("\n");
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

// Định nghĩa cấu trúc cho một node trong cây biểu thức
typedef struct Node {
    char data; // Toán tử hoặc toán hạng
    struct Node* left;
    struct Node* right;
} Node;

// Hàm tạo một node mới
Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Hàm xây dựng cây biểu thức mẫu
Node* buildExpressionTree() {
    // Biểu thức mẫu: (a + b) * c
    Node* root = createNode('*');
    root->left = createNode('+');
    root->right = createNode('c');
    
    root->left->left = createNode('a');
    root->left->right = createNode('b');
    
    return root;
}

// Duyệt cây theo thứ tự NLR (Preorder)
void preorderTraversal(Node* root) {
    if (root == NULL) return;
    printf("%c ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// Duyệt cây theo thứ tự LNR (Inorder)
void inorderTraversal(Node* root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    printf("%c ", root->data);
    inorderTraversal(root->right);
}

// Duyệt cây theo thứ tự LRN (Postorder)
void postorderTraversal(Node* root) {
    if (root == NULL) return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%c ", root->data);
}

// Hàm chính
int main() {
    Node* root = buildExpressionTree();
    
    printf("Duyệt NLR (Preorder): ");
    preorderTraversal(root);
    printf("\n");
    
    printf("Duyệt LNR (Inorder): ");
    inorderTraversal(root);
    printf("\n");
    
    printf("Duyệt LRN (Postorder): ");
    postorderTraversal(root);
    printf("\n");
    
    return 0;
}
