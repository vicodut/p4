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
public:
    PlayerHuman() {}

    string getName() {
        return name;
    }

    void setNAme(string name) {
        this->name = name;
    }
};

class P4
{
private:
    PlayerHuman *player1;
    PlayerHuman *player2;
public:
    P4() {
        cout << "Welcome to the game  \u25C9 \u25EF" << endl;
        player1 = new PlayerHuman();
        player2 = new PlayerHuman();

        string name;
        cout << "Name of Player1 : ";
        cin >> name;
        player1->setNAme(name);
        cout << "Name of Player2 : ";
        cin >> name;
        player2->setNAme(name);

        cout << "Players : " << player1->getName() << endl;
        cout << "    and : " << player2->getName() << endl;
    }
};

int main ()
{
  new P4();

  return 0;
}
