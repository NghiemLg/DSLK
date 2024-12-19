#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Cấu trúc node đơn giản
struct Node {
    char title[50];        // Tên mục
    int level;            // Cấp độ (1: chapter, 2: section, 3: subsection, 4: subsubsection)
    int startPage;        // Trang bắt đầu
    int endPage;         // Trang kết thúc
    struct Node* child;   // Con
    struct Node* sibling; // Anh em
};

// Hàm tạo node mới
struct Node* taoNode(char* title, int level, int startPage, int endPage) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->title, title);
    newNode->level = level;
    newNode->startPage = startPage;
    newNode->endPage = endPage;
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

// Đếm số chương (node có level = 1)
int demSoChuong(struct Node* root) {
    int count = 0;
    struct Node* p = root;
    
    while (p != NULL) {
        if (p->level == 1) {  // Nếu là chapter
            count++;
        }
        // Đệ quy đếm trong cả cây con
        count += demSoChuong(p->child);
        p = p->sibling;
    }
    return count;
}

// Tìm chương dài nhất
struct Node* timChuongDaiNhat(struct Node* root) {
    if (root == NULL) return NULL;
    
    struct Node* maxChapter = NULL;
    int maxLength = 0;
    struct Node* p = root;
    
    while (p != NULL) {
        if (p->level == 1) {  // Nếu là chapter
            int length = p->endPage - p->startPage + 1;
            if (length > maxLength) {
                maxLength = length;
                maxChapter = p;
            }
        }
        // Tìm trong cây con
        struct Node* temp = timChuongDaiNhat(p->child);
        if (temp != NULL && (temp->endPage - temp->startPage + 1) > maxLength) {
            maxLength = temp->endPage - temp->startPage + 1;
            maxChapter = temp;
        }
        p = p->sibling;
    }
    return maxChapter;
}

// Xóa một mục theo tên
struct Node* xoaMuc(struct Node* root, char* title) {
    if (root == NULL) return NULL;
    
    // Nếu node gốc là node cần xóa
    if (strcmp(root->title, title) == 0) {
        struct Node* temp = root->sibling;
        free(root);
        return temp;
    }
    
    struct Node* p = root;
    
    // Tìm trong danh sách anh em
    while (p->sibling != NULL) {
        if (strcmp(p->sibling->title, title) == 0) {
            struct Node* temp = p->sibling;
            p->sibling = temp->sibling;
            free(temp);
            return root;
        }
        p = p->sibling;
    }
    
    // Tìm trong cây con
    root->child = xoaMuc(root->child, title);
    
    return root;
}

// In cây để kiểm tra
void inCay(struct Node* root, int space) {
    if (root == NULL) return;
    
    // Thêm khoảng trắng theo level
    for (int i = 0; i < space; i++) {
        printf("  ");
    }
    
    printf("%s (Trang %d-%d)\n", root->title, root->startPage, root->endPage);
    
    inCay(root->child, space + 1);
    inCay(root->sibling, space);
}

int main() {
    // Tạo cây mẫu
    struct Node* root = taoNode("Sach", 0, 0, 100);
    
    // Thêm các chương
    struct Node* chuong1 = taoNode("Chuong 1", 1, 1, 30);
    struct Node* chuong2 = taoNode("Chuong 2", 1, 31, 45);
    struct Node* chuong3 = taoNode("Chuong 3", 1, 46, 70);
    
    // Thêm các section vào chương 1
    struct Node* section1 = taoNode("Section 1.1", 2, 1, 15);
    struct Node* section2 = taoNode("Section 1.2", 2, 16, 30);
    
    // Tạo liên kết
    root->child = chuong1;
    chuong1->sibling = chuong2;
    chuong2->sibling = chuong3;
    chuong1->child = section1;
    section1->sibling = section2;
    
    // In cây ban đầu
    printf("Cay ban dau:\n");
    inCay(root, 0);
    
    // Đếm số chương
    printf("\nSo chuong: %d\n", demSoChuong(root));
    
    // Tìm chương dài nhất
    struct Node* maxChapter = timChuongDaiNhat(root);
    if (maxChapter != NULL) {
        printf("Chuong dai nhat: %s (%d trang)\n", 
               maxChapter->title, 
               maxChapter->endPage - maxChapter->startPage + 1);
    }
    
    // Xóa một mục
    printf("\nXoa Section 1.1...\n");
    root = xoaMuc(root, "Section 1.1");
    
    printf("\nCay sau khi xoa:\n");
    inCay(root, 0);
    
    return 0;
}
