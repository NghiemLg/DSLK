#include <stdio.h>
#include <stdlib.h>

// Khai bao cau truc cay AVL
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};

// Ham lay chieu cao cua node
int getHeight(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Ham lay gia tri lon hon giua hai so
int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

// Ham tao mot node moi
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1; // Chi so chieu cao mac dinh la 1
    return newNode;
}

// Ham xoay phai
struct Node* rotateRight(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Thuc hien xoay
    x->right = y;
    y->left = T2;

    // Cap nhat chieu cao
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x; // Tra ve node moi la goc
}

// Ham xoay trai
struct Node* rotateLeft(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Thuc hien xoay
    y->left = x;
    x->right = T2;

    // Cap nhat chieu cao
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y; // Tra ve node moi la goc
}

// Ham tinh he so can bang
int getBalance(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// Ham them mot node moi vao cay AVL
struct Node* insert(struct Node* node, int key) {
    if (node == NULL) {
        return createNode(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node; // Khong cho phep them key trung
    }

    // Cap nhat chieu cao
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Kiem tra he so can bang
    int balance = getBalance(node);

    // Left Left
    if (balance > 1 && key < node->left->key) {
        return rotateRight(node);
    }

    // Right Right
    if (balance < -1 && key > node->right->key) {
        return rotateLeft(node);
    }

    // Left Right
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Ham duyet cay theo thu tu truoc
void preOrder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void menu() {
    printf("\nMenu lua chon:\n");
    printf("1. Them phan tu vao cay AVL\n");
    printf("2. In cay AVL (duyet truoc)\n");
    printf("3. Thoat\n");
    printf("Nhap lua chon cua ban: ");
}

int main() {
    struct Node* root = NULL;
    int choice, key;

    while (1) {
        menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhap gia tri can them: ");
                scanf("%d", &key);
                root = insert(root, key);
                printf("Da them %d vao cay AVL.\n", key);
                break;

            case 2:
                printf("Cay AVL (duyet truoc): ");
                preOrder(root);
                printf("\n");
                break;

            case 3:
                printf("Thoat chuong trinh.\n");
                exit(0);

            default:
                printf("Lua chon khong hop le!\n");
        }
    }

    return 0;
}
