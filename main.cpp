#include <iostream>
#include <vector>
#include <algorithm>

using matrix = std::vector<std::vector<char>>;

class Board {
protected:
    matrix board;
    void generateBoard() { board.resize(rows, std::vector<char>(columns, init)); }

    void setState(int row, int col, char val) {
        if ((board[row][col] != 'X') && (board[row][col] != 'O')) {
            while (board.size() <= row) board.emplace_back();
            while (board[row].size() <= col) board[row].push_back(char());
            board[row][col] = val;

        } else { std::cout << "This square is already taken. Choose a different one." << std::endl; }
    }

    bool boardIsFull() {
        std::all_of(board.begin(), board.end(), [](const std::vector<char>& vec) {
            return std::all_of(vec.begin(), vec.end(), [](int elem) { return elem == 'O' || elem == 'X'; });
        });
    }

    void printBoard() {
        std::cout << "Current state of the board: " << std::endl;
        for (const auto &row : board) {
            for (const auto &elem : row) std::cout << elem << ' ';
            std::cout << std::endl;
        }
    }

private:
    int rows = 3;
    int columns = 3;
    char init = '-';
};

class Game : protected Board{
protected:
    void getInput() {
        while (state == GameStates::GameOn) {
            std::cout << "Choose position to play. 1-9" << std::endl;
            std::cin >> input;
            if (!input.empty()) {
                char command = input.c_str()[0];

                if ((command >= '1') && (command <= '9')) {
                    switch (command) {
                        case '1' :
                            setState(0, 0, active_player);
                            continueRoutine();
                            break;
                        case '2' :
                            setState(0, 1, active_player);
                            continueRoutine();
                            break;
                        case '3' :
                            setState(0, 2, active_player);
                            continueRoutine();
                            break;
                        case '4' :
                            setState(1, 0, active_player);
                            continueRoutine();
                            break;
                        case '5' :
                            setState(1, 1, active_player);
                            continueRoutine();
                            break;
                        case '6' :
                            setState(1, 2, active_player);
                            continueRoutine();
                            break;
                        case '7' :
                            setState(2, 0, active_player);
                            continueRoutine();
                            break;
                        case '8' :
                            setState(2, 1, active_player);
                            continueRoutine();
                            break;
                        case '9' :
                            setState(2, 2, active_player);
                            continueRoutine();
                            break;
                        default:
                            std::cout << "You have to put number in range 1-9" << std::endl;
                            return;
                    }
                }
            }
        }
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
        std::cout << active_player << " Wins The Game!" << std::endl;
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
    std::string input;


};
class Runner : public Game {
public:
    Runner() {
        generateBoard();
        state = GameStates::GameOn;
        while (state == GameStates::GameOn) {
            printBoard();
            getInput();
        }
    }
};
int main() {
    Runner run;
    return 0;
}
