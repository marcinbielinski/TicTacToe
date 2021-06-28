#include <iostream>
#include <vector>
#include <algorithm>

using matrix = std::vector<std::vector<char>>;

class Board {
protected:
    void generateBoard() { board.resize(rows, std::vector<char>(columns, init)); }

    void setState(int row, int col, char player) {
        if ((board[row][col] != 'X') && (board[row][col] != 'O'))
        {
            while (board.size() <= row) board.emplace_back();
            while (board[row].size() <= col) board[row].push_back(char());
            board[row][col] = player;
            printBoard();

        } else { std::cout << "This square is already taken. Choose a different one." << std::endl; }
    }

    bool boardIsFull()
    {
        return std::all_of(board.begin(), board.end(), [](const std::vector<char> &vec) {
            return std::all_of(vec.begin(), vec.end(), [](int elem) { return elem == 'O' || elem == 'X'; });
        });
    }

    void printBoard()
    {
        for (const auto &row : board)
        {
            for (const auto &elem : row) std::cout << elem << ' ';
            std::cout << std::endl;
        }
    }

    matrix board;
    int rows = 3;
    int columns = 3;
    char init = '-';
};

class Game : protected Board {
protected:
    void makeMove() {
        auto chosenPos = getInput();
        int x = (chosenPos - 1) / rows;
        int y = (chosenPos - 1) % columns;

        setState(x, y, active_player);
        checkForWin();
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

    void continueRoutine()
    {
        changeTurn();
        checkForDraws();
    }

    void changeTurn() {
        if (active_player == Player1)
        {
            active_player = Player2;
        }
        else
        {
            active_player = Player1;
        }
    }

    void checkForWin() {
        if (horizontalWin() || verticalWin() || diagonalWin())
        {
            announceWinner();
        }
        else
        {
            continueRoutine();
            state = GameStates::GameOn;
        }
    }

    bool horizontalWin()
    {
        for (int i = 0; i < rows; ++i)
        {
            if (std::all_of(board[i].begin(), board[i].end(),
                            [this](char x) { return x == active_player; }))
            {
                return true;
            }
        }
        return false;
    }

    bool verticalWin()
    {
        for (int col = 0; col < columns; ++col)
        {
            for (int row = 0; row < rows; ++row)
            {
                if (board[row][col] != active_player)
                {
                    break;
                }
                if (row == rows-1)
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool diagonalWin()
    {
        for (int i = 0; i < rows; ++i)
        {
            if (board[i][i] != active_player )
            {
                break;
            }
            if (i == rows - 1)
            {
                return true;
            }
        }
        for (int i = 0; i < rows; ++i)
        {
            if (board[rows - 1 - i][0 + i] != active_player)
            {
                break;
            }
            if (i == rows - 1)
            {
                return true;
            }
        }
        return false;
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

    static void greetings() {
        std::cout << "Hello! Welcome to my game of Tic-Tac-Toe. Player '0' goes first. Have fun." << std::endl;
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
        greetings();
        generateBoard();
        printBoard();
        while (state == GameStates::GameOn)
        {
            makeMove();
        }
    }
};

int main() {
    Runner run;
    return 0;
}
