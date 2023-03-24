#include <iostream>
#include <string>
#include "Cube.cpp"
#include "Face.cpp"

using namespace std;

int main() {

    // top left right front down back
    Cube rubix = Cube("white", "blue", "green", "red", "yellow", "orange");
    char move;

    // infinite while loop to move the cube
    while (true) {
        rubix.printState();
        cout << "Please input a move. t, l, r, d, f, b, or s to shuffle";
        cin >> move;
        makeMove(move, rubix);
        
    }

}

// helper method to interpret and execute moves on a cube
static void makeMove(int choice, Cube cu) {
    // switch function to interpret each move
    switch(choice) {
            case 't':
            cu.turnTop();
            break;

            case 'l':
            cu.turnLeft();
            break;

            case 'r':
            cu.turnRight();
            break;

            case 'd':
            cu.turnDown();
            break;

            case 'f':
            cu.turnFront();
            break;

            case 'b':
            cu.turnBack();
            break;

            case 's':
            int x = 0;
            cout << "How many moves would you like to shuffle? Enter a positive whole number below 100.";
            cin >> x;
            cu.shuffle(x);
            
        }
}