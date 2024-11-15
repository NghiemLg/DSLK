#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mỗi thanh gỗ
typedef struct ThanhGo {
    char kichThuoc[20];  // Kích thước thanh gỗ
    int tuoiGo;          // Tuổi gỗ
    struct ThanhGo *next; // Con trỏ tới thanh gỗ tiếp theo (stack)
} ThanhGo;

// Mỗi loại gỗ
typedef struct LoaiGo {
    char tenLoai[20];    // Tên loại gỗ
    ThanhGo *top;        // Stack các thanh gỗ trong loại này
    struct LoaiGo *next; // Con trỏ tới loại gỗ tiếp theo
} LoaiGo;

// Hàm tạo loại gỗ mới
LoaiGo* taoLoaiGo(char *tenLoai) {
    LoaiGo *loaiGo = (LoaiGo*) malloc(sizeof(LoaiGo));
    strcpy(loaiGo->tenLoai, tenLoai);
    loaiGo->top = NULL;
    loaiGo->next = NULL;
    return loaiGo;
}

// Thêm thanh gỗ vào loại gỗ
void themThanhGo(LoaiGo *loaiGo, char *kichThuoc, int tuoiGo) {
    ThanhGo *thanhGo = (ThanhGo*) malloc(sizeof(ThanhGo));
    strcpy(thanhGo->kichThuoc, kichThuoc);
    thanhGo->tuoiGo = tuoiGo;
    thanhGo->next = loaiGo->top;
    loaiGo->top = thanhGo;
}

// Tìm loại gỗ trong danh sách
LoaiGo* timLoaiGo(LoaiGo *khoGo, char *tenLoai) {
    LoaiGo *hienTai = khoGo;
    while (hienTai != NULL) {
        if (strcmp(hienTai->tenLoai, tenLoai) == 0) {
            return hienTai;
        }
        hienTai = hienTai->next;
    }
    return NULL;
}

// Thêm loại gỗ mới vào kho
void themLoaiGo(LoaiGo **khoGo, char *tenLoai, char *kichThuoc, int tuoiGo) {
    LoaiGo *loaiGo = timLoaiGo(*khoGo, tenLoai);
    if (loaiGo == NULL) {
        loaiGo = taoLoaiGo(tenLoai);
        loaiGo->next = *khoGo;
        *khoGo = loaiGo;
    }
    themThanhGo(loaiGo, kichThuoc, tuoiGo);
}

// Đếm số thanh gỗ có cùng tuổi trong một loại gỗ
int demSoLuongTheoTuoi(LoaiGo *loaiGo, int tuoiGo) {
    int dem = 0;
    ThanhGo *hienTai = loaiGo->top;
    while (hienTai != NULL) {
        if (hienTai->tuoiGo == tuoiGo) {
            dem++;
        }
        hienTai = hienTai->next;
    }
    return dem;
}

// In thông tin về kho gỗ
void inKhoGo(LoaiGo *khoGo) {
    LoaiGo *hienTai = khoGo;
    while (hienTai != NULL) {
        printf("Loai go: %s\n", hienTai->tenLoai);
        ThanhGo *thanhHienTai = hienTai->top;
        while (thanhHienTai != NULL) {
            printf("- Kich thuoc: %s, Tuoi go: %d\n", thanhHienTai->kichThuoc, thanhHienTai->tuoiGo);
            thanhHienTai = thanhHienTai->next;
        }
        printf("\n");
        hienTai = hienTai->next;
    }
}

// Xóa thanh gỗ theo tiêu chí (tuổi hoặc kích thước)
void xoaThanhGo(LoaiGo *loaiGo, int tuoiGo) {
    ThanhGo *hienTai = loaiGo->top, *truoc = NULL;
    while (hienTai != NULL) {
        if (hienTai->tuoiGo == tuoiGo) {
            if (truoc == NULL) {
                loaiGo->top = hienTai->next;
            } else {
                truoc->next = hienTai->next;
            }
            free(hienTai);
            printf("Đã xóa thanh gỗ tuổi %d\n", tuoiGo);
            return;
        }
        truoc = hienTai;
        hienTai = hienTai->next;
    }
    printf("Không tìm thấy thanh gỗ với tuổi %d.\n", tuoiGo);
}

int main() {
    LoaiGo *khoGo = NULL; // Kho gỗ trống

    // Menu điều khiển
    int luaChon;
    do {
        printf("\n--- Menu Quản Lý Kho Gỗ ---\n");
        printf("1. Thêm thanh gỗ vào kho\n");
        printf("2. In danh sách kho gỗ\n");
        printf("3. Đếm số thanh gỗ theo tuổi\n");
        printf("4. Xóa thanh gỗ theo tuổi\n");
        printf("5. Thoát\n");
        printf("Nhập lựa chọn: ");
        scanf("%d", &luaChon);

        switch (luaChon) {
            case 1: {
                char loaiGo[50], kichThuoc[20];
                int tuoiGo;
                printf("Nhập tên loại gỗ: ");
                scanf("%s", loaiGo);
                printf("Nhập kích thước thanh gỗ: ");
                scanf("%s", kichThuoc);
                printf("Nhập tuổi gỗ: ");
                scanf("%d", &tuoiGo);
                themLoaiGo(&khoGo, loaiGo, kichThuoc, tuoiGo);
                break;
            }
            case 2:
                inKhoGo(khoGo);
                break;
            case 3: {
                char loaiGo[50];
                int tuoiGo;
                printf("Nhập tên loại gỗ: ");
                scanf("%s", loaiGo);
                printf("Nhập tuổi gỗ cần đếm: ");
                scanf("%d", &tuoiGo);
                LoaiGo *loaiGoCanDem = timLoaiGo(khoGo, loaiGo);
                if (loaiGoCanDem != NULL) {
                    int soLuong = demSoLuongTheoTuoi(loaiGoCanDem, tuoiGo);
                    printf("Số thanh gỗ tuổi %d trong loại gỗ '%s': %d\n", tuoiGo, loaiGo, soLuong);
                } else {
                    printf("Không tìm thấy loại gỗ '%s'.\n", loaiGo);
                }
                break;
            }
            case 4: {
                char loaiGo[50];
                int tuoiGo;
                printf("Nhập tên loại gỗ: ");
                scanf("%s", loaiGo);
                printf("Nhập tuổi thanh gỗ cần xóa: ");
                scanf("%d", &tuoiGo);
                LoaiGo *loaiGoCanXoa = timLoaiGo(khoGo, loaiGo);
                if (loaiGoCanXoa != NULL) {
                    xoaThanhGo(loaiGoCanXoa, tuoiGo);
                } else {
                    printf("Không tìm thấy loại gỗ '%s'.\n", loaiGo);
                }
                break;
            }
            case 5:
                printf("Thoát chương trình.\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ, vui lòng thử lại!\n");
        }
    } while (luaChon != 5);

    // Giải phóng bộ nhớ trước khi thoát
    while (khoGo != NULL) {
        LoaiGo *tempLoaiGo = khoGo;
        khoGo = khoGo->next;
        free(tempLoaiGo);
    }

    return 0;
}
