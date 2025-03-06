#include <iostream>
#include <vector>
#include <string>
#include <random>
using namespace std;

class Krest{
 private:
 char player='X';
 vector<char> field{' ',' ',' ',' ',' ',' ',' ',' ',' '};
    int countMove=0;
    int cage;

 public:
 void printField(const std::vector<char>& field) {
 cout<<field[0]<<"|"<<field[1]<<"|"<<field[2]<<"\n"<<field[3]<<"|"<<field[4]<<"|"<<field[5]<<"\n"<<field[6]<<"|"<<field[7]<<"|"<<field[8]<<"\n"<<endl;};
 
 bool checkWin(const std::vector<char>& field) {
 const int winCombos[8][3] = {
 {0, 1, 2},  {3, 4, 5},  {6, 7, 8}, 
 {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, 
 {0, 4, 8}, {2, 4, 6} 
 };
 for (int i = 0; i < 8; i++) {
            if (field[winCombos[i][0]] == player &&
                field[winCombos[i][1]] == player &&
                field[winCombos[i][2]] == player) {
                return true;
            }
    }
        return false;
 }
 void play(){
    while(countMove<9){
        cout<<"Ходит "<<player<< ". Выберите клетку 1-9: ";
        while (!(cin >> cage)||cage<1||cage>9||field[cage-1]!=' '){
        cout << "Ошибка попробуйте еще раз \n Выберите клетку 1-9: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
        }
        field.at(cage-1)=player;
        cout<<"1|2|3\n4|5|6\n7|8|9\n\n";
        printField(field);
        checkWin(field);
        if (checkWin(field)) {
                cout << "\nПоздравляем, игрок " << player << " выиграл!\n";
                break;
        }
        countMove++;
        player = (player == 'X') ? 'O' : 'X';
    }
    if(!checkWin(field))cout<<"Ничья";
 }
};

 
int main(){
    setlocale(LC_ALL, "Russian");
    char playAgain;
    do {
        Krest game;
        game.play();
        cout << "\nХотите сыграть ещё раз? (Y/N): ";
        cin >> playAgain;
    } while (playAgain == 'Y' || playAgain == 'y');
    return 0;

 }