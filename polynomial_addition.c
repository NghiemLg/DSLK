#include <stdio.h>
#include <stdlib.h>

// Cấu trúc node cho mỗi hạng tử của đa thức
typedef struct Node {
    int coeff;  // Hệ số
    int exp;    // Bậc
    struct Node* next;
} Node;

// Hàm tạo node mới cho đa thức
Node* createNode(int coeff, int exp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

// Hàm thêm node vào cuối đa thức
void appendNode(Node** poly, int coeff, int exp) {
    Node* newNode = createNode(coeff, exp);
    if (*poly == NULL) {
        *poly = newNode;
    } else {
        Node* temp = *poly;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Hàm cộng hai đa thức
Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;
    Node *p1 = poly1, *p2 = poly2;

    while (p1 != NULL && p2 != NULL) {
        if (p1->exp == p2->exp) {
            appendNode(&result, p1->coeff + p2->coeff, p1->exp);
            p1 = p1->next;
            p2 = p2->next;
        } else if (p1->exp > p2->exp) {
            appendNode(&result, p1->coeff, p1->exp);
            p1 = p1->next;
        } else {
            appendNode(&result, p2->coeff, p2->exp);
            p2 = p2->next;
        }
    }

    // Thêm các phần tử còn lại của poly1 hoặc poly2
    while (p1 != NULL) {
        appendNode(&result, p1->coeff, p1->exp);
        p1 = p1->next;
    }
    while (p2 != NULL) {
        appendNode(&result, p2->coeff, p2->exp);
        p2 = p2->next;
    }

    return result;
}

// Hàm in đa thức
void printPolynomial(Node* poly) {
    while (poly != NULL) {
        printf("%dx^%d", poly->coeff, poly->exp);
        if (poly->next != NULL) {
            printf(" + ");
        }
        poly = poly->next;
    }
    printf("\n");
}

// Hàm giải phóng bộ nhớ của đa thức
void freePolynomial(Node* poly) {
    Node* temp;
    while (poly != NULL) {
        temp = poly;
        poly = poly->next;
        free(temp);
    }
}

int main() {
    Node* poly1 = NULL;
    Node* poly2 = NULL;

    // Nhập các hạng tử của đa thức poly1
    appendNode(&poly1, 5, 2);  // 5x^2
    appendNode(&poly1, 4, 1);  // 4x^1
    appendNode(&poly1, 2, 0);  // 2

    // Nhập các hạng tử của đa thức poly2
    appendNode(&poly2, 3, 2);  // 3x^2
    appendNode(&poly2, 2, 1);  // 2x^1
    appendNode(&poly2, 1, 0);  // 1

    // Cộng hai đa thức
    Node* result = addPolynomials(poly1, poly2);

    // In kết quả
    printf("Poly1: ");
    printPolynomial(poly1);
    printf("Poly2: ");
    printPolynomial(poly2);
    printf("Result: ");
    printPolynomial(result);

    // Giải phóng bộ nhớ
    freePolynomial(poly1);
    freePolynomial(poly2);
    freePolynomial(result);

    return 0;
}
