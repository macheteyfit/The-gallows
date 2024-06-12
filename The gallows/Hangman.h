#include "WordHandler.h"
#include "Game.h"

class Hangman {
private:
    WordHandler wordHandler;

public:
    Hangman(const std::string& filename) : wordHandler(filename) {}

    void startGame() {
        std::string word = wordHandler.getRandomWord();
        Game game(word);
        game.play();
    }
};
