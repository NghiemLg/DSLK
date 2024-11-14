#include <iostream>
#include <string>

struct WordNode {
    std::string word;
    int count;
    WordNode* next;

    WordNode(const std::string& w) : word(w), count(1), next(nullptr) {}
};

class WordLinkedList {
private:
    WordNode* head;

public:
    WordLinkedList() : head(nullptr) {}

    void addWord(const std::string& w) {
        WordNode* current = head;
        WordNode* prev = nullptr;

        while (current != nullptr) {
            if (current->word == w) {
                current->count++;
                return;
            }
            prev = current;
            current = current->next;
        }

        WordNode* newWord = new WordNode(w);
        if (!prev) {
            head = newWord;
        } else {
            prev->next = newWord;
        }
    }

    std::string findMostFrequentWord() {
        int maxCount = 0;
        WordNode* mostFrequent = nullptr;
        WordNode* current = head;

        while (current) {
            if (current->count > maxCount) {
                maxCount = current->count;
                mostFrequent = current;
            }
            current = current->next;
        }
        return mostFrequent ? mostFrequent->word : "";
    }

    void removeRepeatedWords() {
        WordNode* current = head;
        while (current && current->next) {
            // Kiểm tra nếu hai từ giống hệt nhau liên tiếp (từ láy)
            if (current->word == current->next->word) {
                WordNode* temp = current->next;
                current->next = current->next->next;
                delete temp;
            } else {
                current = current->next;
            }
        }
    }

    int countWords() {
        int totalCount = 0;
        WordNode* current = head;
        while (current) {
            totalCount += current->count;
            current = current->next;
        }
        return totalCount;
    }

    void displayWords() {
        WordNode* current = head;
        while (current) {
            std::cout << "Từ: " << current->word << ", Số lần xuất hiện: " << current->count << std::endl;
            current = current->next;
        }
    }

    ~WordLinkedList() {
        WordNode* current = head;
        while (current) {
            WordNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

// Tách câu thành các từ dựa trên khoảng trắng
void splitIntoWords(const std::string& sentence, WordLinkedList& list) {
    std::string::size_type start = 0;
    std::string::size_type end = 0;
    while (end <= sentence.length()) {
        if (end == sentence.length() || sentence[end] == ' ') {
            if (start != end) {
                std::string word = sentence.substr(start, end - start);
                list.addWord(word);
            }
            start = end + 1;
        }
        end++;
    }
}

int main() {
    WordLinkedList sentence;

    // Nhập câu từ người dùng
    std::cout << "Nhập câu tiếng Việt: ";
    std::string input;
    std::getline(std::cin, input);

    // Phân tách câu thành từ và thêm vào danh sách
    splitIntoWords(input, sentence);

    // Hiển thị menu cho người dùng
    int choice;
    do {
        std::cout << "\nChọn một chức năng:\n";
        std::cout << "1. Xác định từ xuất hiện nhiều nhất\n";
        std::cout << "2. Loại bỏ từ láy\n";
        std::cout << "3. Đếm số từ trong câu\n";
        std::cout << "0. Thoát\n";
        std::cout << "Lựa chọn của bạn: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string mostFrequent = sentence.findMostFrequentWord();
                std::cout << "\nTừ xuất hiện nhiều nhất: " << mostFrequent << std::endl;
                break;
            }
            case 2: {
                sentence.removeRepeatedWords();
                std::cout << "\nDanh sách từ sau khi loại bỏ từ láy:\n";
                sentence.displayWords();
                break;
            }
            case 3: {
                int totalWords = sentence.countWords();
                std::cout << "\nTổng số từ trong câu: " << totalWords << std::endl;
                break;
            }
            case 0: {
                std::cout << "Thoát chương trình.\n";
                break;
            }
            default: {
                std::cout << "Lựa chọn không hợp lệ. Vui lòng chọn lại.\n";
                break;
            }
        }
    } while (choice != 0);

    return 0;
}
