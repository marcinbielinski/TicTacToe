#include <iostream>
#include <vector>
#include <algorithm>

using matrix = std::vector<std::vector<char>>;

class Board {
protected:
    matrix board;

    void generateBoard() { board.resize(rows, std::vector<char>(columns, init)); }

    void setState(int row, int col, char player) {
        if ((board[row][col] != 'X') && (board[row][col] != 'O')) {
            while (board.size() <= row) board.emplace_back();
            while (board[row].size() <= col) board[row].push_back(char());
            board[row][col] = player;

        } else { std::cout << "This square is already taken. Choose a different one." << std::endl; }
    }

    bool boardIsFull() {
        std::all_of(board.begin(), board.end(), [](const std::vector<char> &vec) {
            return std::all_of(vec.begin(), vec.end(), [](int elem) { return elem == 'O' || elem == 'X'; });
        });
    }

    void printBoard() {
        for (const auto &row : board) {
            for (const auto &elem : row) std::cout << elem << ' ';
            std::cout << std::endl;
        }
    }

    int rows = 3;
    int columns = 3;
    char init = '-';
};

class Game : protected Board {
protected:

    void makeMove() {
        auto chosenPos = getInput();
        int xRow = (chosenPos / 3);
        int yCol;
        if (chosenPos % 3 == 0)
        {
            xRow = xRow - 1;
            yCol = 2;
        }
        else
        {
            yCol = (chosenPos % 3) - 1;
        }
        setState(xRow, yCol, active_player);
        continueRoutine();
    }

    int getInput() {
        std::cout << "Choose a valid position to play." << std::endl;
        int input;
        while (state == GameStates::GameOn)
        {
            std::cin >> input;

            if ((input >= 1) && (input <= 9))
            {
                break;
            }
            else
            {
                std::cout << "Invalid input!" << std::endl;
            }
        }
        return input;
    }


    void continueRoutine() {
        checkForDraws();
        checkForWin();
        printBoard();
        changeTurn();
    }

    void changeTurn() {
        if (active_player == Player1) {
            active_player = Player2;
        } else {
            active_player = Player1;
        }
    }

    void checkForWin() {
        if ((board[0][0] == Player1) && (board[0][1] == Player1) && (board[0][2] == Player1)) {
            announceWinner();
        } else if ((board[0][0] == Player2) && (board[0][1] == Player2) && (board[0][2] == Player2)) {
            announceWinner();
        }

        if ((board[1][0] == Player1) && (board[1][1] == Player1) && (board[1][2] == Player1)) {
            announceWinner();
        } else if ((board[1][0] == Player2) && (board[1][1] == Player2) && (board[1][2] == Player2)) {
            announceWinner();
        }

        if ((board[2][0] == Player1) && (board[2][1] == Player1) && (board[2][2] == Player1)) {
            announceWinner();
        } else if ((board[2][0] == Player2) && (board[2][1] == Player2) && (board[2][2] == Player2)) {
            announceWinner();
        }

        if ((board[0][0] == Player1) && (board[1][0] == Player1) && (board[2][0] == Player1)) {
            announceWinner();
        } else if ((board[0][0] == Player2) && (board[1][0] == Player2) && (board[2][0] == Player2)) {
            announceWinner();
        }

        if ((board[0][1] == Player1) && (board[1][1] == Player1) && (board[2][1] == Player1)) {
            announceWinner();
        } else if ((board[0][1] == Player2) && (board[1][1] == Player2) && (board[2][1] == Player2)) {
            announceWinner();
        }

        if ((board[0][2] == Player1) && (board[1][2] == Player1) && (board[2][2] == Player1)) {
            announceWinner();
        } else if ((board[0][2] == Player2) && (board[1][2] == Player2) && (board[2][2] == Player2)) {
            announceWinner();
        }

        if ((board[0][0] == Player1) && (board[1][1] == Player1) && (board[2][2] == Player1)) {
            announceWinner();
        } else if ((board[0][0] == Player2) && (board[1][1] == Player2) && (board[2][2] == Player2)) {
            announceWinner();
        }

        if ((board[2][0] == Player1) && (board[1][1] == Player1) && (board[0][2] == Player1)) {
            announceWinner();
        } else if ((board[2][0] == Player2) && (board[1][1] == Player2) && (board[0][2] == Player2)) {
            announceWinner();
        }
    }

    void checkForDraws() {
        if (boardIsFull()) {
            announceDraw();
        }
    }

    void announceWinner() {
        std::cout << "Player: " << active_player << " Wins The Game!" << std::endl;
        state = GameStates::Win;
    }

    void announceDraw() {
        std::cout << "The Game was a draw!" << std::endl;
        state = GameStates::Draw;
    }

    enum Players : char {
        Player1 = 'O', Player2 = 'X'
    };

    enum class GameStates {
        Win, Draw, GameOn
    };

    GameStates state = GameStates::GameOn;
    char active_player{Player1};
};

class Runner : public Game {
public:
    Runner() {
        generateBoard();
        printBoard();
        state = GameStates::GameOn;
        while (state == GameStates::GameOn) {
            makeMove();
        }
    }
};

int main() {
    Runner run;
    return 0;
}
