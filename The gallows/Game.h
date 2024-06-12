#include <string>
#include <vector>
#include <chrono>
#include <iostream>
#include <algorithm>

class Game {
private:
    std::string word;
    std::string guessedWord;
    std::vector<char> incorrectGuesses;
    int attempts;
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

    void displayCurrentState() {
        std::cout << "�����: " << guessedWord << "\n";
        std::cout << "��������� �������: ";
        for (char c : incorrectGuesses) {
            std::cout << c << " ";
        }
        std::cout << "\n";
    }

    bool isRepeatedGuess(char guess) {
        return std::find(guessedWord.begin(), guessedWord.end(), guess) != guessedWord.end() ||
            std::find(incorrectGuesses.begin(), incorrectGuesses.end(), guess) != incorrectGuesses.end();
    }

    void processGuess(char guess) {
        bool correctGuess = false;
        for (size_t i = 0; i < word.size(); ++i) {
            if (word[i] == guess) {
                guessedWord[i] = guess;
                correctGuess = true;
            }
        }

        if (!correctGuess) {
            incorrectGuesses.push_back(guess);
        }

        attempts++;
    }

    void displayResults() {
        if (guessedWord == word) {
            std::cout << "����������! �� ������� �����! ��� �� �������!: " << word << "\n";
        }
        else {
            std::cout << "�� ���������, ����� ���������: " << "���������� ����� ����: " << word << "\n";
        }

        std::chrono::duration<double> elapsed = end - start;
        std::cout << "����� ����: " << elapsed.count() << " ������\n";
        std::cout << "���������� �������: " << attempts << "\n";
        std::cout << "��������� �����: ";
        for (char c : incorrectGuesses) {
            std::cout << c << " ";
        }
        std::cout << "\n";
    }

public:
    Game(const std::string& word) : word(word), guessedWord(word.size(), '_'), attempts(0) {
        start = std::chrono::high_resolution_clock::now();
    }

    void play() {
        while (guessedWord != word && incorrectGuesses.size() < 6) {
            displayCurrentState();

            char guess;
            std::cout << "������� �����: ";
            std::cin >> guess;

            if (isRepeatedGuess(guess)) {
                std::cout << "�� ��� ������� ��� �����. ���������� �����.\n";
                continue;
            }

            processGuess(guess);
        }

        end = std::chrono::high_resolution_clock::now();
        displayResults();
    }
};
