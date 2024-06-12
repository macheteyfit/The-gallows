#include "Hangman.h"
#include <iostream>

void displayWelcomeMessage() {
    std::cout << "Добро пожаловать в игру 'Виселица'!\n";
    std::cout << "Правила просты: отгадайте слово, вводя по одной букве за раз.\n";
    std::cout << "У вас есть 6 попыток сделать неправильный выбор.\n";
    std::cout << "Удачи!\n";
}

int main() {
    setlocale(LC_ALL, "RUS");
    displayWelcomeMessage();

    try {
        Hangman hangman("C:\\The_gallows\\encrypted_words.txt");
        hangman.startGame();
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
