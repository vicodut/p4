#include <vector>
#include "header.hpp"

class Player
{
public:
    Player() {}
};

class Token
{
private:
    string color;
public:
    const string &getColor() const {
        return color;
    }

    void setColor(const string &color) {
        Token::color = color;
    }
};
class PlayerHuman
{
private:
    string name;
    Token *tkn;
public:
    PlayerHuman() {
        tkn = new Token();
    }

    string getName() {
        return name;
    }

    void setNAme(const string name) {
        this->name = name;
    }

    Token *getTkn() const {
        return tkn;
    }

    void setTkn(Token *tkn) {
        this->tkn = tkn;
    }
};

class Grid {
private:
    int L;
    int h;
    vector<vector <Token *>> grid;

    int getRowId(int column) {
        int i = 0;
        for (i = 0; i < h; ++i) {
            if (grid[i][column] != nullptr)
                return i - 1;
        }
        return i - 1;
    }

    bool checkVertical(int row, Token *token, int column) {
        for (int i = 1; i <= NBR2WIN; ++i) {
            if (grid[row + i][column] != token)
                return false;
        }
        return true;
    }

    bool checkHorizontalByLeft(int row, Token *token, int column) {
        for (int i = 0; i < NBR2WIN; ++i) {
            if (grid[row][column - i] != token)
                return false;
        }
        return true;
    }

    bool checkHorizontalByRight(int row, Token *token, int column) {
        for (int i = 0; i < NBR2WIN; ++i) {
            if (grid[row][column + i] != token)
                return false;
        }
        return true;
    }

    bool checkDiagonalByTopRight(int row, Token *token, int column) {
        cout << row << "  " << column << endl;
        for (int i = 0; i < NBR2WIN; ++i) {
            for (int j = 0; j < NBR2WIN; ++j) {
                if (grid[row + i][column + i] != token)
                    return false;
            }
        }
        return true;
    }

//    bool checkDiagonalByTopRight(int row, Token *token, int column) {
//        int count = 0;
//        int i = 0;
//        while (count != 3) {
//            if (grid[row + i][column + i] == token) {
//                count++;
//            } else {
//                break;
//            }
//        }
//        if (count == 3)
//        {
//            return true;
//        }
//        i = 0;
//        while (count != 3) {
//            if (grid[row + i][column + i] == token) {
//                count++;
//            } else {
//                break;
//            }
//        }
//    }

    bool checkDiagonalByTopLeft(int row, Token *token, int column) {
        for (int i = 0; i < NBR2WIN; ++i) {
            for (int j = 0; j < NBR2WIN; ++j) {
                if (grid[row + i][column - i] != token)
                    return false;
            }
        }
        return true;
    }

public:
    Grid(int L, int h) {
        this->L = L;
        this->h = h;

        vector<Token *> row(L);
        for (int k = 0; k < h; ++k) {
            grid.push_back(row);
        }

        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < L; ++j) {
                grid[i][j] = nullptr;
            }
        }
    }

    void drawGrid () {
        for (int i = 0; i < h + 1; ++i) {
            for (int j = 0; j < L; ++j) {
                if (i != h) {
                    if (grid[i][j])
                    {
                        cout << " " << grid[i][j]->getColor() << " ";
                    } else {
                        cout << " . ";
                    }
                }
                else {
                    cout << j << ": ";
                }
            }
            cout << endl;
        }
    }

    void setToken(PlayerHuman *player, int column)
    {
        grid[this->getRowId(column)][column] = player->getTkn();
    }

    bool testColumnValidity(int column) {
        return (column >= 0 && column <= L - 1 && this->getRowId(column) != -1);
    }

    bool checkToken(int column) {
        int lastRow = this->getRowId(column);
        Token *lastToken = grid[lastRow + 1][column];

        if (lastRow < h - 4 && lastToken == grid[lastRow + 2][column]) {
            if (checkVertical(lastRow, lastToken, column))
                return true;
        }

        if (column >= 3 && grid[lastRow + 1][column - 1] == lastToken) {
            if (checkHorizontalByLeft(lastRow + 1, lastToken, column))
                return true;
        }

        if (column <= L - NBR2WIN && grid[lastRow + 1][column + 1] == lastToken) {
            if (checkHorizontalByRight(lastRow + 1, lastToken, column))
                return true;
        }

        if (column <= L - NBR2WIN && lastRow < h - 4 && grid[lastRow + 2][column + 1] == lastToken) {
            if (checkDiagonalByTopRight(lastRow + 1, lastToken, column))
                return true;
        }

        if (column >= 3 && lastRow < h - 4 && grid[lastRow + 2][column - 1] == lastToken) {
            if (checkDiagonalByTopLeft(lastRow + 1, lastToken, column))
                return true;
        }
        return false;
    }
};

class P4
{
private:
    PlayerHuman *player1;
    PlayerHuman *player2;
    PlayerHuman *current;

    void changePlayer() {
        if (current) {
            if (current == player1) {
                current = player2;
            } else {
                current = player1;
            }
        } else {
            current = new PlayerHuman();
            current = player1;
        }

        cout << "> " <<  current->getName() << endl;
    }

public:
    P4() {
        player1 = new PlayerHuman();
        player2 = new PlayerHuman();

        cout << "Welcome to the game  \u25C9 \u25EF" << endl;

        Token *red = new Token();
        red->setColor("\u25C9");

        Token *yellow = new Token();
        yellow->setColor("\u25EF");

        string name;
        cout << "Name of Player1 : ";
        cin >> name;
        player1->setNAme(name);
        player1->setTkn(red);

        cout << "Name of Player2 : ";
        cin >> name;
        player2->setNAme(name);
        player2->setTkn(yellow);

        cout << "Players : " << player1->getName() << " " << player1->getTkn()->getColor() << endl;
        cout << "    and : " << player2->getName() << " " << player2->getTkn()->getColor() << endl;

        int L, h;
        cout << "Length of the grid : ";
        cin >> L;
        cout << "High of the grid : ";
        cin >> h;

        Grid *grille = new Grid(L, h);
        grille->drawGrid();

        this->changePlayer();

        int column;
        do {
            do {
                cout << current->getTkn()->getColor() << "  " << current->getName() << " column : ";
                cin >> column;
            } while (!grille->testColumnValidity(column));

            grille->setToken(current, column);
            grille->drawGrid();
            if (grille->checkToken(column)) {
                cout << current->getName() << " est le winner" << endl;
                break;
            }

            this->changePlayer();
        } while (column != -1);
    }
};

int main ()
{
  new P4();

  return 0;
}