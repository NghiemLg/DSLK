#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Cấu trúc lưu thông tin file
struct File {
  char ten[100];     // Tên file
  int dungLuong;     // Dung lượng file (KB)
  int thoiGian;      // Thời gian lưu (đơn vị: ngày)
};

// Hoán đổi hai file
void hoanDoi(struct File *a, struct File *b) {
  struct File tam = *a;
  *a = *b;
  *b = tam;
}

// Sắp xếp file tăng dần theo dung lượng
void sapXepFile(struct File *dsFile, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (dsFile[j].dungLuong > dsFile[j + 1].dungLuong || 
         (dsFile[j].dungLuong == dsFile[j + 1].dungLuong && dsFile[j].thoiGian > dsFile[j + 1].thoiGian)) {
        hoanDoi(&dsFile[j], &dsFile[j + 1]);
      }
    }
  }
}

// In danh sách file
void inDanhSachFile(struct File *dsFile, int n) {
  if (n == 0) {
    printf("Thư mục hiện tại trống!\n");
    return;
  }
  printf("Danh sách file trong thư mục:\n");
  printf("Tên file\tDung lượng (KB)\tThời gian lưu (ngày)\n");
  for (int i = 0; i < n; i++) {
    printf("%-15s\t%-10d\t%-10d\n", dsFile[i].ten, dsFile[i].dungLuong, dsFile[i].thoiGian);
  }
}

// Xóa file lưu lâu nhất
int xoaFileLuuLauNhat(struct File *dsFile, int *n) {
  if (*n == 0) return 0;

  int maxThoiGian = dsFile[0].thoiGian;
  int i = 0;

  // Tìm file lưu lâu nhất
  for (int j = 1; j < *n; j++) {
    if (dsFile[j].thoiGian > maxThoiGian) {
      maxThoiGian = dsFile[j].thoiGian;
      i = j;
    }
  }

  // Xóa file tìm được
  printf("Xóa file lưu lâu nhất: %s (Dung lượng: %d KB, Thời gian lưu: %d ngày)\n", 
         dsFile[i].ten, dsFile[i].dungLuong, dsFile[i].thoiGian);
  for (int j = i; j < *n - 1; j++) {
    dsFile[j] = dsFile[j + 1];
  }
  (*n)--;
  return 1;
}

// Xóa file dung lượng lớn nhất
int xoaFileDungLuongLonNhat(struct File *dsFile, int *n) {
  if (*n == 0) return 0;

  int maxDungLuong = dsFile[0].dungLuong;
  int i = 0;

  // Tìm file có dung lượng lớn nhất
  for (int j = 1; j < *n; j++) {
    if (dsFile[j].dungLuong > maxDungLuong) {
      maxDungLuong = dsFile[j].dungLuong;
      i = j;
    }
  }

  // Xóa file tìm được
  printf("Xóa file dung lượng lớn nhất: %s (Dung lượng: %d KB, Thời gian lưu: %d ngày)\n", 
         dsFile[i].ten, dsFile[i].dungLuong, dsFile[i].thoiGian);
  for (int j = i; j < *n - 1; j++) {
    dsFile[j] = dsFile[j + 1];
  }
  (*n)--;
  return 1;
}

// Hàm chính
int main() {
  int n;

  // Nhập số lượng file
  printf("Nhập số lượng file trong thư mục: ");
  scanf("%d", &n);

  struct File *dsFile = (struct File *)malloc(n * sizeof(struct File));

  // Nhập thông tin các file
  printf("Nhập thông tin các file:\n");
  for (int i = 0; i < n; i++) {
    printf("File %d:\n", i + 1);
    printf("Tên file: ");
    scanf("%s", dsFile[i].ten);
    printf("Dung lượng (KB): ");
    scanf("%d", &dsFile[i].dungLuong);
    printf("Thời gian lưu (ngày): ");
    scanf("%d", &dsFile[i].thoiGian);
  }

  int luaChon;
  do {
    printf("\n--- Menu ---\n");
    printf("1. Sắp xếp file theo dung lượng\n");
    printf("2. In danh sách file\n");
    printf("3. Xóa file lưu lâu nhất\n");
    printf("4. Xóa file dung lượng lớn nhất\n");
    printf("5. Thoát\n");
    printf("Nhập lựa chọn của bạn: ");
    scanf("%d", &luaChon);

    switch (luaChon) {
      case 1:
        sapXepFile(dsFile, n);
        printf("Danh sách file đã được sắp xếp.\n");
        break;
      case 2:
        inDanhSachFile(dsFile, n);
        break;
      case 3:
        if (!xoaFileLuuLauNhat(dsFile, &n)) {
          printf("Không có file để xóa!\n");
        }
        break;
      case 4:
        if (!xoaFileDungLuongLonNhat(dsFile, &n)) {
          printf("Không có file để xóa!\n");
        }
        break;
      case 5:
        printf("Thoát chương trình.\n");
        break;
      default:
        printf("Lựa chọn không hợp lệ, vui lòng thử lại!\n");
    }
  } while (luaChon != 5);

  free(dsFile);
  return 0;
}
