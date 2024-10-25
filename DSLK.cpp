#include <stdio.h>
#include <stdlib.h>

// Cấu trúc Ngày
typedef struct {
    int ngay, thang, nam;
} Ngay;

// Cấu trúc Sinh viên
typedef struct {
    char maSV[8];
    char hoTen[50];
    int gioiTinh;
    Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];
} SinhVien;

// Cấu trúc Node cho danh sách liên kết
typedef struct Node {
    SinhVien data;
    struct Node* link;
} Node;

// Cấu trúc danh sách sinh viên
typedef struct {
    Node* first;
    Node* last;
} List;

// Hàm khởi tạo danh sách rỗng
void initList(List* list) {
    list->first = NULL;
    list->last = NULL;
}

// Hàm so sánh chuỗi không dùng thư viện
int soSanhChuoi(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

// Hàm để xóa bộ đệm
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Hàm nhập ký tự có khoảng trắng mà không dùng fgets hoặc string.h
void nhapChuoi(char chuoi[], int doDai) {
    int i = 0;
    char c;
    while (i < doDai - 1 && (c = getchar()) != '\n') {
        chuoi[i++] = c;
    }
    chuoi[i] = '\0';  // Kết thúc chuỗi
}

// Hàm nhập thông tin sinh viên
SinhVien nhapSinhVien() {
    SinhVien sv;
    printf("Nhap ma sinh vien: ");
    scanf("%s", sv.maSV);
    clearBuffer();  // Xóa bộ đệm sau khi sử dụng scanf

    printf("Nhap ho ten: ");
    nhapChuoi(sv.hoTen, 50);  // Nhập chuỗi không dùng fgets

    printf("Nhap gioi tinh (0: Nu, 1: Nam): ");
    scanf("%d", &sv.gioiTinh);
    clearBuffer();  // Xóa bộ đệm sau khi sử dụng scanf

    printf("Nhap ngay sinh (dd mm yyyy): ");
    scanf("%d%d%d", &sv.ngaySinh.ngay, &sv.ngaySinh.thang, &sv.ngaySinh.nam);
    clearBuffer();  // Xóa bộ đệm sau khi sử dụng scanf

    printf("Nhap dia chi: ");
    nhapChuoi(sv.diaChi, 100);  // Nhập chuỗi không dùng fgets

    printf("Nhap lop: ");
    scanf("%s", sv.lop);
    clearBuffer();  // Xóa bộ đệm sau khi sử dụng scanf

    printf("Nhap khoa: ");
    scanf("%s", sv.khoa);
    clearBuffer();  // Xóa bộ đệm sau khi sử dụng scanf

    return sv;
}



// Hàm thêm sinh viên vào danh sách theo thứ tự mã SV
void insertStudent(List* list, SinhVien sv) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = sv;
    newNode->link = NULL;

    // Nếu danh sách trống hoặc mã sinh viên nhỏ hơn mã đầu tiên
    if (list->first == NULL || soSanhChuoi(list->first->data.maSV, sv.maSV) > 0) {
        newNode->link = list->first;
        list->first = newNode;
        if (list->last == NULL) {
            list->last = newNode;
        }
    } else {
        Node* temp = list->first;
        while (temp->link != NULL && soSanhChuoi(temp->link->data.maSV, sv.maSV) < 0) {
            temp = temp->link;
        }
        newNode->link = temp->link;
        temp->link = newNode;
        if (newNode->link == NULL) {
            list->last = newNode;
        }
    }
}

// Hàm in danh sách sinh viên
void printList(List* list) {
    Node* temp = list->first;
    while (temp != NULL) {
        printf("MaSV: %s, Ho ten: %s, Ngay sinh: %02d/%02d/%04d\n", 
               temp->data.maSV, temp->data.hoTen, 
               temp->data.ngaySinh.ngay, temp->data.ngaySinh.thang, temp->data.ngaySinh.nam);
        temp = temp->link;
    }
}

// Hàm tìm và in sinh viên có cùng ngày sinh
void printStudentsWithSameBirthday(List* list, Ngay birthday) {
    int found = 0;
    Node* temp = list->first;
    while (temp != NULL) {
        if (temp->data.ngaySinh.ngay == birthday.ngay &&
            temp->data.ngaySinh.thang == birthday.thang &&
            temp->data.ngaySinh.nam == birthday.nam) {
            printf("Sinh vien: %s, Ngay sinh: %02d/%02d/%04d\n", 
                   temp->data.hoTen, 
                   temp->data.ngaySinh.ngay, 
                   temp->data.ngaySinh.thang, 
                   temp->data.ngaySinh.nam);
            found = 1;
        }
        temp = temp->link;
    }
    if (!found) {
        printf("Khong tim thay sinh vien cung ngay sinh.\n");
    }
}

// Hàm xóa sinh viên có cùng ngày sinh
void removeStudentsWithSameBirthday(List* list, Ngay birthday) {
    Node* temp = list->first;
    Node* prev = NULL;

    while (temp != NULL) {
        if (temp->data.ngaySinh.ngay == birthday.ngay &&
            temp->data.ngaySinh.thang == birthday.thang &&
            temp->data.ngaySinh.nam == birthday.nam) {

            if (prev == NULL) {  // Xóa sinh viên đầu danh sách
                list->first = temp->link;
            } else {
                prev->link = temp->link;
            }
            if (temp == list->last) {  // Xóa sinh viên cuối danh sách
                list->last = prev;
            }
            Node* toDelete = temp;
            temp = temp->link;
            free(toDelete);
        } else {
            prev = temp;
            temp = temp->link;
        }
    }
}

int main() {
    List list;
    initList(&list);
    int n;

    // Nhập danh sách sinh viên
    printf("Nhap so luong sinh vien: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        SinhVien sv = nhapSinhVien();
        insertStudent(&list, sv);
    }

    // In danh sách sinh viên sau khi nhập
    printf("\nDanh sach sinh vien da sap xep:\n");
    printList(&list);

    // Nhập ngày sinh cần tìm
    Ngay birthday;
    printf("\nNhap ngay thang nam sinh de tim sinh vien (dd mm yyyy): ");
    scanf("%d%d%d", &birthday.ngay, &birthday.thang, &birthday.nam);

    // In sinh viên có cùng ngày sinh
    printf("\nSinh vien co cung ngay sinh:\n");
    printStudentsWithSameBirthday(&list, birthday);

    // Hỏi người dùng có muốn xóa sinh viên cùng ngày sinh hay không
    char choice;
    printf("\nBan co muon xoa sinh vien cung ngay sinh khong? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        removeStudentsWithSameBirthday(&list, birthday);
        printf("\nDanh sach sinh vien sau khi xoa:\n");
        printList(&list);
    } else {
        printf("\nDanh sach sinh vien khong bi thay doi.\n");
    }

    return 0;
}
