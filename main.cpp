#include <vector>
#include "header.hpp"

class Player
{
public:
    Player() {}
};

class PlayerHuman
{
private:
    string name;
    string color;
public:
    PlayerHuman() {}

    string getName() {
        return name;
    }

    void setNAme(const string name) {
        this->name = name;
    }

    const string &getColor() const {
        return color;
    }

    void setColor(const string color) {
        this->color = color;
    }
};

class Grid {
private:
    int L = 7;
    int h = 6;
    vector<vector <string>> grid;

    int getRowId(int column) {
        int i = 0;
        for (i = 0; i < h; ++i) {
            if (grid[i][column] != "_  ")
                return i - 1;
        }
        return i - 1;
    }

    bool checkVertical(int row, string token, int column) {
        for (int i = 1; i <= 4; ++i) {
            if (grid[row + i][column] != token)
                return false;
        }
        return true;
    }

public:
    Grid() {
        vector<string> row(L);
        for (int k = 0; k < h; ++k) {
            grid.push_back(row);
        }

        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < L; ++j) {
                grid[i][j] = "_  ";
            }
        }
    }

    void drawGrid () {
        for (int i = 0; i < h + 1; ++i) {
            for (int j = 0; j < L; ++j) {
                if (i != h)
                    cout << grid[i][j];
                else
                    cout << j << ": ";
            }
            cout << endl;
        }
    }

    void setToken(PlayerHuman *player, int column)
    {
        grid[this->getRowId(column)][column] = player->getColor() + "  ";
    }

    bool testColumnValidity(int column) {
        return (column >= 0 && column <= L - 1 && this->getRowId(column) != -1);
    }

    bool checkToken(int column) {
        int lastRow = this->getRowId(column);
        string lastToken = grid[lastRow + 1][column];
        if (lastRow < h - 4 && lastToken == grid[lastRow + 2][column]) {
            return checkVertical(lastRow, lastToken, column);
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

        string name;
        cout << "Name of Player1 : ";
        cin >> name;
        player1->setNAme(name);
        player1->setColor("\u25C9");

        cout << "Name of Player2 : ";
        cin >> name;
        player2->setNAme(name);
        player2->setColor("\u25EF");

        cout << "Players : " << player1->getName() << " " << player1->getColor() << endl;
        cout << "    and : " << player2->getName() << " " << player2->getColor() << endl;

        this->changePlayer();

        Grid *grille = new Grid();
        grille->drawGrid();

        int column;
        do {
            do {
                cout << current->getColor() << "  " << current->getName() << " column : ";
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