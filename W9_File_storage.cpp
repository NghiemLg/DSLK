#include <iostream>

struct FileNode {
    char fileName[50]; // Tên file tối đa 50 ký tự
    double fileSize;    // Kích thước file tính bằng MB
    char creationTime[20]; // Thời gian tạo (dạng chuỗi "YYYY-MM-DD HH:MM")

    FileNode* next; // Con trỏ tới node tiếp theo

    FileNode(const char* name, double size, const char* time) : fileSize(size), next(nullptr) {
        // Sao chép chuỗi tên file
        int i = 0;
        while (name[i] != '\0' && i < 49) {
            fileName[i] = name[i];
            i++;
        }
        fileName[i] = '\0';

        // Sao chép chuỗi thời gian tạo
        i = 0;
        while (time[i] != '\0' && i < 19) {
            creationTime[i] = time[i];
            i++;
        }
        creationTime[i] = '\0';
    }
};

class FileLinkedList {
private:
    FileNode* head;

public:
    FileLinkedList() : head(nullptr) {}

    // Hàm so sánh hai chuỗi thời gian
    bool compareTime(const char* time1, const char* time2) {
        for (int i = 0; i < 19; ++i) {
            if (time1[i] < time2[i]) return true;
            if (time1[i] > time2[i]) return false;
        }
        return false;
    }

    // Hàm thêm file vào danh sách theo thứ tự thời gian
    void addFile(const char* name, double size, const char* time) {
        FileNode* newFile = new FileNode(name, size, time);

        if (!head || compareTime(time, head->creationTime)) {
            newFile->next = head;
            head = newFile;
        } else {
            FileNode* current = head;
            while (current->next && !compareTime(time, current->next->creationTime)) {
                current = current->next;
            }
            newFile->next = current->next;
            current->next = newFile;
        }
    }

    // Hàm tính tổng kích thước file trong thư mục
    double calculateTotalSize() {
        double totalSize = 0;
        FileNode* current = head;
        while (current) {
            totalSize += current->fileSize;
            current = current->next;
        }
        return totalSize;
    }

    // Hàm xóa file có kích thước nhỏ nhất
    void removeSmallestFile() {
        if (!head) return;

        FileNode* minFile = head;
        FileNode* minPrev = nullptr;
        FileNode* current = head;
        FileNode* prev = nullptr;

        while (current) {
            if (current->fileSize < minFile->fileSize) {
                minFile = current;
                minPrev = prev;
            }
            prev = current;
            current = current->next;
        }

        if (minPrev) {
            minPrev->next = minFile->next;
        } else {
            head = head->next;
        }
        delete minFile;
    }

    // Hàm sao lưu vào USB, loại bỏ các file nhỏ nhất nếu cần
    void backupToUSB(double usbSize) {
        while (calculateTotalSize() > usbSize) {
            removeSmallestFile();
        }
    }

    // Hàm hiển thị danh sách các file
    void displayFiles() {
        FileNode* current = head;
        while (current) {
            std::cout << "File: " << current->fileName
                      << ", Size: " << current->fileSize << " MB"
                      << ", Creation Time: " << current->creationTime << std::endl;
            current = current->next;
        }
    }
};


int main() {
    FileLinkedList folder;

    // Thêm các file vào danh sách
    folder.addFile("File1.txt", 500, "2024-11-10 10:00");
    folder.addFile("File2.txt", 1000, "2024-11-12 12:30");
    folder.addFile("File3.txt", 200, "2024-11-11 15:45");

    std::cout << "Danh sách các file trong thư mục:\n";
    folder.displayFiles();

    // Tính tổng kích thước file trong thư mục
    std::cout << "\nTổng kích thước file trong thư mục: " << folder.calculateTotalSize() << " MB\n";

    // Sao lưu các file vào USB 32GB
    folder.backupToUSB(32 * 1024); // 32 GB = 32768 MB

    std::cout << "\nDanh sách các file sau khi sao lưu vào USB:\n";
    folder.displayFiles();

    return 0;
}
