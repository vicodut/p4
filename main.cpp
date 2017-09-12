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

        cout << "> " << current->getName() << endl;
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
    }
};

int main ()
{
  new P4();

  return 0;
}
