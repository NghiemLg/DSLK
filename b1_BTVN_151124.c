#include <stdio.h>
#include <stdlib.h>

// Cấu trúc của 1 node
struct Node {
  int giaTri;          // Dữ liệu của node
  struct Node *tiepTheo; // Con trỏ tới node kế tiếp
};

// Thêm node mới vào cuối danh sách
void themCuoi(struct Node **dau, int so) {
  struct Node *nutMoi = (struct Node *)malloc(sizeof(struct Node));
  nutMoi->giaTri = so;
  nutMoi->tiepTheo = NULL;
  if (*dau == NULL) {
    *dau = nutMoi;
  } else {
    struct Node *tam = *dau;
    while (tam->tiepTheo) tam = tam->tiepTheo;
    tam->tiepTheo = nutMoi;
  }
}

// In danh sách
void inDanhSach(struct Node *dau) {
  struct Node *tam = dau;
  while (tam) {
    printf("%d -> ", tam->giaTri);
    tam = tam->tiepTheo;
  }
  printf("NULL\n");
}

// Xóa phần tử ở đầu danh sách
void xoaDau(struct Node **dau) {
  if (*dau) {
    struct Node *tam = *dau;
    *dau = (*dau)->tiepTheo;
    free(tam);
  }
}

// Xóa phần tử ở cuối danh sách
void xoaCuoi(struct Node **dau) {
  if (*dau) {
    if ((*dau)->tiepTheo == NULL) {
      free(*dau);
      *dau = NULL;
    } else {
      struct Node *tam = *dau;
      while (tam->tiepTheo->tiepTheo) tam = tam->tiepTheo;
      free(tam->tiepTheo);
      tam->tiepTheo = NULL;
    }
  }
}

// Xóa phần tử sau một node cho trước
void xoaSau(struct Node *node) {
  if (node && node->tiepTheo) {
    struct Node *tam = node->tiepTheo;
    node->tiepTheo = tam->tiepTheo;
    free(tam);
  }
}

// Hàm chính
int main() {
  struct Node *dauDanhSach = NULL;
  int n;

  // Nhập số lượng phần tử
  printf("Nhập số lượng phần tử trong mảng: ");
  scanf("%d", &n);

  // Nhập các giá trị cho danh sách
  printf("Nhập các giá trị: ");
  for (int i = 0; i < n; i++) {
    int giaTri;
    scanf("%d", &giaTri);
    themCuoi(&dauDanhSach, giaTri);
  }

  // Hiển thị danh sách ban đầu
  printf("Danh sách ban đầu: ");
  inDanhSach(dauDanhSach);

  // Thực hiện các thao tác
  int luaChon;
  do {
    printf("\n--- Menu ---\n");
    printf("1. Xóa đầu\n");
    printf("2. Xóa cuối\n");
    printf("3. Xóa sau một node cụ thể\n");
    printf("4. In danh sách\n");
    printf("5. Thoát\n");
    printf("Nhập lựa chọn của bạn: ");
    scanf("%d", &luaChon);

    switch (luaChon) {
      case 1:
        xoaDau(&dauDanhSach);
        printf("Danh sách sau khi xóa đầu: ");
        inDanhSach(dauDanhSach);
        break;
      case 2:
        xoaCuoi(&dauDanhSach);
        printf("Danh sách sau khi xóa cuối: ");
        inDanhSach(dauDanhSach);
        break;
      case 3: {
        int giaTri;
        printf("Nhập giá trị node trước node cần xóa: ");
        scanf("%d", &giaTri);
        struct Node *tam = dauDanhSach;
        while (tam && tam->giaTri != giaTri) {
          tam = tam->tiepTheo;
        }
        if (tam) {
          xoaSau(tam);
          printf("Danh sách sau khi xóa sau node %d: ", giaTri);
          inDanhSach(dauDanhSach);
        } else {
          printf("Không tìm thấy node có giá trị %d!\n", giaTri);
        }
        break;
      }
      case 4:
        printf("Danh sách hiện tại: ");
        inDanhSach(dauDanhSach);
        break;
      case 5:
        printf("Thoát chương trình.\n");
        break;
      default:
        printf("Lựa chọn không hợp lệ. Vui lòng thử lại.\n");
    }
  } while (luaChon != 5);

  return 0;
}

