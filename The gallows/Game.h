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
        std::cout << "Слово: " << guessedWord << "\n";
        std::cout << "Ошибочные попытки: ";
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
            std::cout << "Поздравляю! Вы угадали слово! Вас не повесят!: " << word << "\n";
        }
        else {
            std::cout << "Вы проиграли, читай понихидну: " << "задуманное слово было: " << word << "\n";
        }

        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Время игры: " << elapsed.count() << " секунд\n";
        std::cout << "Количество попыток: " << attempts << "\n";
        std::cout << "Ошибочные буквы: ";
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
            std::cout << "Введите букву: ";
            std::cin >> guess;

            if (isRepeatedGuess(guess)) {
                std::cout << "Вы уже вводили эту букву. Попробуйте снова.\n";
                continue;
            }

            processGuess(guess);
        }

        end = std::chrono::high_resolution_clock::now();
        displayResults();
    }
};
