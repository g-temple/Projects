#include <iostream>
#include <string>
#include "Face.cpp"

using namespace std;

class Cube
{
private:
    // Each cube has 6 faces, which each have a unique starting letter
    Face top;
    Face left;
    Face right;
    Face front;
    Face down;
    Face back;

public:

    // Constructor takes 6 strings that initialize the colors in this order
    // top, left, right, front, down, back
    Cube(string t, string l, string r, string f, string d, string b) {

        setTop(t);
        setLeft(l);
        setRight(r);
        setFront(f);
        setDown(d);
        setBack(b);
    }

    // Methods are defined for turning each face, which involes a 90 spin of the turned face, and moving the other rows connected to the face
    void turnTop() {
        // rotate the colors on the spinning face itself
        top.rotate();

        // when the top face spins, rows on the other 4 connected faces also move in the following order
        // front -> left -> back -> right -> front

        // a for loop can be used to make the proper move on this face for each piece
        // moves the top left, top middle, and top right pieces of the front, back, left, and right faces
        for (int i = 0; i < 3; i++) {
            // temp to remember 1 color, then overwrite each color with its
            string temp = front.getSide().arr[0][i];
            front.setSide(0,i,right.getSide().arr[0][i]);
            right.setSide(0,i,back.getSide().arr[0][i]);
            back.setSide(0,i,left.getSide().arr[0][i]);
            left.setSide(0,i,temp);
        }
    }

    // Similar to turnTop method
    void turnDown() {
        // rotate the colors on the spinning face itself
        down.rotate();

        // order of other rotating faces
        // front -> r -> b -> l -> f

        // moves bottom left, bottom middle, and bottom right pieces of the front, back, left, and right faces
        for (int i = 0; i < 3; i++) {
            string temp = front.getSide().arr[2][i];
            front.setSide(2, i, left.getSide().arr[2][i]);
            left.setSide(2, i, back.getSide().arr[2][i]);
            back.setSide(2, i, right.getSide().arr[2][i]);
            right.setSide(2, i, temp);
        }
        
    }
    void turnLeft() {
        left.rotate();
        // t -> f -> d -> b -> t
        // top left corner moves
        string temp = top.getSide().arr[0][0];
        top.setSide(0, 0, back.getSide().arr[2][2]);
        back.setSide(2, 2, down.getSide().arr[2][0]);
        down.setSide(2, 0, front.getSide().arr[0][0]);
        front.setSide(0, 0, temp);

        //middle left edge moves
        temp = top.getSide().arr[1][0];
        top.setSide(1, 0, back.getSide().arr[1][2]);
        back.setSide(1, 2, down.getSide().arr[1][0]);
        down.setSide(1, 0, front.getSide().arr[1][0]);
        front.setSide(1, 0, temp);

        // Bottom left corner moves
        temp = top.getSide().arr[2][0];
        top.setSide(2, 0, back.getSide().arr[0][2]);
        back.setSide(0, 2, down.getSide().arr[0][0]);
        down.setSide(0, 0, front.getSide().arr[2][0]);
        front.setSide(2, 0, temp);
        
    }
    void turnRight() {
        right.rotate();
        // t -> b -> d -> f -> t
        //top right corner moves
        string temp = top.getSide().arr[0][2];
        top.setSide(0, 2, front.getSide().arr[0][2]);
        front.setSide(0, 2, down.getSide().arr[2][2]);
        down.setSide(2, 2, back.getSide().arr[2][0]);
        back.setSide(2, 0, temp);

        //middle right edge moves
        temp = top.getSide().arr[1][2];
        top.setSide(1, 2, front.getSide().arr[1][2]);
        front.setSide(1, 2, down.getSide().arr[1][2]);
        down.setSide(1, 2, back.getSide().arr[1][0]);
        back.setSide(1, 0, temp);

        //bottom right corner moves
        temp = top.getSide().arr[2][2];
        top.setSide(2, 2, front.getSide().arr[2][2]);
        front.setSide(2, 2, down.getSide().arr[0][2]);
        down.setSide(0, 2, back.getSide().arr[0][0]);
        back.setSide(0, 0, temp);

        
    }
    void turnFront() {
        front.rotate();
        // t -> r -> d -> l -> t
        // bottom left corner shuffle
        string temp = top.getSide().arr[2][0];
        top.setSide(2, 0, left.getSide().arr[2][2]);
        left.setSide(2, 2, down.getSide().arr[2][2]);
        down.setSide(2, 2, right.getSide().arr[0][0]);
        right.setSide(0, 0, temp);

        // bottom middle edge shuffle
        temp = top.getSide().arr[2][1];
        top.setSide(2, 1, left.getSide().arr[1][2]);
        left.setSide(1, 2, down.getSide().arr[2][1]);
        down.setSide(2, 1, right.getSide().arr[1][0]);
        right.setSide(1, 0, temp);

        //bottom right corner shuffle
        temp = top.getSide().arr[2][2];
        top.setSide(2, 2, left.getSide().arr[0][2]);
        left.setSide(0, 2, down.getSide().arr[2][0]);
        down.setSide(2, 0, right.getSide().arr[2][0]);
        right.setSide(2, 0, temp);
        
    }
    void turnBack() {
        back.rotate();
        // t -> l -> d -> r -> t
        //top left corner shuffle
        string temp = top.getSide().arr[0][0];
        top.setSide(0, 0, right.getSide().arr[0][2]);
        right.setSide(0, 2, down.getSide().arr[0][2]);
        down.setSide(0, 2, left.getSide().arr[2][0]);
        left.setSide(2, 0, temp);

        //top middle edge shuffle
        temp = top.getSide().arr[0][1];
        top.setSide(0, 1, right.getSide().arr[1][2]);
        right.setSide(1, 2, down.getSide().arr[0][1]);
        down.setSide(0, 1, left.getSide().arr[1][0]);
        left.setSide(1, 0, temp);

        //top right corner shuffle
        temp = top.getSide().arr[0][2];
        top.setSide(0, 2, right.getSide().arr[2][2]);
        right.setSide(2, 2, down.getSide().arr[0][0]);
        down.setSide(0, 0, left.getSide().arr[0][0]);
        left.setSide(0, 0, temp);
    }

    // Getters
    void setTop(string c) {
        top = Face(c);
    }

    void setLeft(string c) {
            left = Face(c);
        }

    void setRight(string c) {
            right = Face(c);
        }

    void setFront(string c) {
            front = Face(c);
        }

    void setDown(string c) {
            down = Face(c);
        }

    void setBack(string c) {
            back = Face(c);
        }

    // Setters
    Face getTop(){
        return top;
    }

    Face getDown(){
        return down;
    }

    Face getLeft(){
        return left;
    }

    Face getRight(){
        return right;
    }

    Face getFront(){
        return front;
    }

    Face getBack(){
        return back;
    }

    // Method to randomly generate an input number of moves on a cube, capped at 100
    void shuffle(int moves){

        // for loop to make a number, and make a move corresponding to each number
        for (int i = 1; i <= min(moves,100); i++) {
            int move = rand() % 6;

            switch(move) {
                case 0:
                turnLeft();
                break;

                case 1:
                turnRight();
                break;
                
                case 2:
                turnBack();
                break;
                
                case 3:
                turnDown();
                break;
                
                case 4:
                turnTop();
                break;
                
                case 5:
                turnFront();
                break;

            }
        }
    }

    // Print methods to show the current state of the cube as 6 faces
    void printState(){
        cout << "Top -----------------\n";
        top.printFace();
        cout << "\n";
        cout << "Left -----------------\n";
        left.printFace();
        cout << "\n";
        cout << "Down -----------------\n";
        down.printFace();
        cout << "\n";
        cout << "Right -----------------\n";
        right.printFace();
        cout << "\n";
        cout << "Front -----------------\n";
        front.printFace();
        cout << "\n";
        cout << "Back -----------------\n";
        back.printFace();
        cout << "\n";

    }

    /* might try to print output as ascii art?
    		|
		/		\
	/				\
 /						\
 \						/
|	\				/     |
|		\		/         |
|		   \ /            |
|			|             |
|			|             |
 \   		|           /
    \       |       /
        \   |   /
           \|/
    */


};



