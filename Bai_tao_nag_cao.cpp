#include <stdio.h>
#include <stdlib.h>

// Cấu trúc node cho một người trong vòng tròn
typedef struct Node {
    int person;           // Số thứ tự người chơi
    struct Node* next;    // Con trỏ đến người tiếp theo trong vòng tròn
} Node;

// Hàm tạo một node mới
Node* createNode(int person) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->person = person;
    newNode->next = NULL;
    return newNode;
}

// Hàm khởi tạo vòng tròn với N người chơi
Node* createCircle(int N) {
    Node* head = createNode(1);
    Node* temp = head;

    for (int i = 2; i <= N; i++) {
        temp->next = createNode(i);
        temp = temp->next;
    }
    temp->next = head;  // Tạo liên kết vòng
    return head;
}

// Hàm thực hiện thuật toán Josephus để tìm người chiến thắng
int josephus(int N, int M) {
    Node* head = createCircle(N);
    Node* prev = NULL;
    Node* current = head;

    // Lặp cho đến khi chỉ còn lại một người
    while (current->next != current) {
        // Di chuyển đến người thứ M
        for (int i = 1; i < M; i++) {
            prev = current;
            current = current->next;
        }
        // Loại bỏ người thứ M
        printf("Nguoi %d bi loai bo\n", current->person);
        prev->next = current->next;
        free(current);  // Giải phóng bộ nhớ cho người bị loại
        current = prev->next;
    }

    int winner = current->person;
    free(current);  // Giải phóng bộ nhớ cho người chiến thắng cuối cùng
    return winner;
}

int main() {
    int N, M;
    printf("Nhap so nguoi choi N: ");
    scanf("%d", &N);
    printf("Nhap so buoc chuyen bong M: ");
    scanf("%d", &M);

    int winner = josephus(N, M);
    printf("Nguoi chien thang la nguoi %d\n", winner);

    return 0;
}
