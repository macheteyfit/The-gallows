#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

class WordHandler {
private:
    std::vector<std::string> words;

    void loadWords(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("�� ������� ������� ����: " + filename);
        }
        std::string line;
        while (std::getline(file, line)) {
            words.push_back(decryptWord(line));
        }
        if (words.empty()) {
            throw std::runtime_error("���� ���� ��� �� �������� ���������� ������: " + filename);
        }
    }

    std::string decryptWord(const std::string& encryptedWord) {
        std::string decryptedWord = encryptedWord;
        for (char& c : decryptedWord) {
            if ((c >= '�' && c <= '�') || (c >= '�' && c <= '�')) {
                c = (c - '�' + 3) % 32 + '�';
            }
        }
        return decryptedWord;
    }

public:
    WordHandler(const std::string& filename) {
        loadWords(filename);
    }

    std::string getRandomWord() {
        srand(static_cast<unsigned int>(time(nullptr)));
        return words[rand() % words.size()];
    }
};
