#include <vector>
#include "header.hpp"

class Token
{
private:
    string color;
public:
    const string &getColor() const
    {
        return color;
    }

    void setColor(const string &color)
    {
        Token::color = color;
    }
};

class Player
{
public :
    bool play = 0;
};

class PlayerHuman : public Player
{
private:
    Token *tkn;
    string name;
    bool play;
public:
    void setPlay()
    {
        play = true;
    }
    PlayerHuman()
    {
        setPlay();
        tkn = new Token();
    }

    const string getName()
    {
        return name;
    }

    void setName(const string & name)
    {
        if(name == "ia")
            this->play = false;
        this->name = name;
    }

    Token *getTkn() const
    {
        return tkn;
    }

    void setTkn(Token *tkn)
    {
        this->tkn = tkn;
    }

    int returnColumn(int max) {
        return rand() % max;
    }

    bool isPlay() const {
        return play;
    }
};

class Grid
{
private:
    int L;
    int h;
    vector<vector <Token *> > grid;

    int getRowId(int column)
    {
        int i = 0;
        for (i = 0; i < h; ++i)
        {
            if (grid[i][column] != NULL)
                return i - 1;
        }
        return i - 1;
    }

    bool checkVertical(int row, Token *token, int column)
    {
        for (int i = 1; i <= NBR2WIN; ++i)
        {
            if (grid[row + i][column] != token)
                return false;
        }
        return true;
    }

    bool checkHorizontal(int row)
    {
        for (int i = 0; i < L - 4; ++i) {
            if (grid[row][i] == grid[row][i + 1] &&
                    grid[row][i + 1] == grid[row][i + 2] &&
                    grid[row][i + 2] == grid[row][i + 3] && grid[row][i] != nullptr)
                return true;
        }
        return false;
    }

    bool checkDiagonalByTopRight() {
        for (int x = 0; x < this->L - 4; x++) {
            for (int y = 0; y < this->h - 4; ++y) {
                if (grid[x][y] == grid[x + 1][y  + 1] &&
                        grid[x + 1][y + 1] == grid[x + 2][y + 2] &&
                        grid[x + 2][y + 2] == grid[x + 3][y + 3] && grid[x][y] != nullptr)
                    return true;
            }
        }
        return false;
    }

    bool checkDiagonalByLeft() {
        for (int x = 0; x < h - 3; x++) {
            for (int y = L - 1; y >= 3; y--) {
                if(grid[x][y] == grid[x + 1][y - 1] &&
                        grid[x + 1][y - 1] == grid[x + 2][y - 2] &&
                        grid[x + 2][y - 2] == grid[x + 3][y - 3] && grid[x][y] != nullptr)
                    return true;
            }
        }
        return false;
    }

public:
    Grid(int L, int h)
    {
        this->L = L;
        this->h = h;

        vector<Token *> row(L);
        for (int k = 0; k < h; ++k)
        {
            grid.push_back(row);
        }

        for (int i = 0; i < h; ++i)
        {
            for (int j = 0; j < L; ++j)
            {
                grid[i][j] = nullptr;
            }
        }
    }

    int getL() const {
        return L;
    }

    int getH() const {
        return h;
    }

    bool testColumnValidity(int column)
    {
        return (column >= 0 && column <= L - 1 && this->getRowId(column) != -1); // ?
    }

    bool checkToken(int column)
    {
        int lastRow = this->getRowId(column);
        Token *lastToken = grid[lastRow + 1][column];

        if (lastRow < h - 4 && lastToken == grid[lastRow + 2][column]) // ?
        {
            if (checkVertical(lastRow, lastToken, column))
                return true;
        }

        if (checkHorizontal(lastRow + 1))
            return true;

        if (checkDiagonalByTopRight())
            return true;

        return checkDiagonalByLeft();
    }

    void setToken(PlayerHuman *player, int column)
    {
        grid[this->getRowId(column)][column] = player->getTkn();
    }

    void drawGrid ()
    {
        for (int i = 0; i < h + 1; ++i)
        {
            for (int j = 0; j < L; ++j)
            {
                if (i != h)
                {
                    if (grid[i][j])
                    {
                        cout << " " << grid[i][j]->getColor() << " ";
                    }
                    else
                    {
                        cout << " . ";
                    }
                }
                else
                {
                    cout << j << ": ";
                }
            }
            cout << endl;
        }
    }

};


class P4
{
private:

    PlayerHuman *player1;
    PlayerHuman *player2;
    PlayerHuman *current;


    void changePlayer()
    {
        if (current)
        {
            if (current == player1)
            {
                current = player2;
            }
            else
            {
                current = player1;
            }
        }
        else
        {
            current = new PlayerHuman();
            current = player1;
        }

        cout << "> " <<  current->getName() << endl;
    }

    void choice()
    {
        int c;
        std::cout << "Que voulez vous faire ? \n 1 : Jouer \n 2 : Lire les règles\n > ";
        while (!( std::cin >> c))
        {
            if ((c=1))
            {

            }
            else if ((c=2))
            {

            }
            else
            {
                system("pause");
            }
        }
    }

public:
    P4() {
        player1 = new PlayerHuman();
        player2 = new PlayerHuman();
        cout << "Welcome to the game " << endl;
        this->choice();

        Token *red = new Token();
        red->setColor("X");

        Token *yellow = new Token();
        yellow->setColor("O");

        string name;

        cout << "Name of Player1 (ia to set ia player) : ";
        cin >> name;

        player1->setName(name);
        player1->setTkn(red);

        cout << "Name of Player2 (ia to set ia player) : ";
        cin >> name;

        player2->setName(name);
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
        do
        {
            do
            {
                cout << current->getTkn()->getColor() << "  " << current->getName() << " column : ";
                if (!current->isPlay())
                {
                    column = current->returnColumn(grille->getL());
                    cout << column << endl;
                }
                else {
                    cin >> column;
                }
            }
            while (!grille->testColumnValidity(column));

            grille->setToken(current, column);
            grille->drawGrid();
            if (grille->checkToken(column))
            {
                cout << current->getName() << " est le winner" << endl;
                break;
            }

            this->changePlayer();
        }
        while (column != -1);
    }
};



int main ()
{
    new P4();

    return 0;
}