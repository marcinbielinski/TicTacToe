#include <iostream>
#include <vector>
#include <algorithm>

using matrix = std::vector<std::vector<char>>;

class Board {
protected:
    void generateBoard() { board.resize(rows, std::vector<char>(columns, init)); }

    void setState(int row, int col, char player) {
        if ((board[row][col] != 'X') && (board[row][col] != 'O')) {
            while (board.size() <= row) board.emplace_back();
            while (board[row].size() <= col) board[row].push_back(char());
            board[row][col] = player;

        } else { std::cout << "This square is already taken. Choose a different one." << std::endl; }
    }

    bool boardIsFull() {
        return std::all_of(board.begin(), board.end(), [](const std::vector<char> &vec) {
            return std::all_of(vec.begin(), vec.end(), [](int elem) { return elem == 'O' || elem == 'X'; });
        });
    }

    void printBoard() {
        for (const auto &row : board) {
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
        checkForWin();
        printBoard();
        changeTurn();
        checkForDraws();
    }

    void changeTurn() {
        if (active_player == Player1) {
            active_player = Player2;
        } else {
            active_player = Player1;
        }
    }

    void checkForWin() {
        if (horizontalWin() || verticalWin() || diagonalWinOneToNine() || diagonalWinThreeToSeven())
        {
            announceWinner();
        }
        else
        {
            state = GameStates::GameOn;
        }
    }
    bool horizontalWin ()
    {
        for (int i = 0; i < rows; ++i)
        {
            if (std::all_of(board[i].begin(), board[i].end(),
                            [this](char x) { return x == active_player;}))
            {
                return true;
            }
        }
        return false;
    }

    bool verticalWin ()
    {
        for (int i = 0; i < rows; ++i)
        {
            if (board[0][i] == active_player && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            {
                return true;
            }
        }
        return false;
    }
//    bool diagonalWinOneToNine ()
//    {
//        if (board[0][0] == active_player && board[0][0] == board[1][1] && board[1][1] == board[2][2])
//        {
//            return true;
//        }
//        return false;
//    }
    bool diagonalWinOneToNine ()
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                if (board[i][j] == active_player && board[i][j] == board[i+1][j+1] && board[i+1][j+1] == board[i+2][j+2])
                {
                    return true;
                }
            }
        }
        return false;
    }

//    bool diagonalWinThreeToSeven ()
//    {
//        if (board[0][2] == active_player && board[0][2] == board[1][1] && board[1][1] == board[2][0])
//        {
//            return true;
//        }
//        return false;
//    }
    bool diagonalWinThreeToSeven ()
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                if (board[i][j+2] == active_player && board[i][j+2] == board[i+1][j+1] && board[i+1][j+1] == board[i+2][j])
                {
                    return true;
                }
            }
        }
        return false;
    }

    void checkForDraws() {
        if (boardIsFull())
        {
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
            if (state == GameStates::Draw)
            {
                break;
            }
            if (state == GameStates::Win)
            {
                break;
            }
        }
    }
};

int main() {
    Runner run;
    return 0;
}
