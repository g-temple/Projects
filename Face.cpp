#include <string>
#include <iostream>
#pragma once
using namespace std;

// Struct to efficently store an manipulate all the pieces of a face
struct sideStruct {
    string arr[3][3];
};

class Face
{
private:
    
    sideStruct side; // 3x3 2D array to store the string value of each piece on a given face

public:
    Face(){}; // default constructor

    // constructor to initialize every cell of a side to the same value
    Face(string c) {
        for (int i = 0; i < 3; i ++) {
            for (int j = 0; j < 3; j++) {
                side.arr[i][j] = c + to_string(i+j);
            }
        }   
    }

    // method to perform a 90 degree clockwise rotation on any face
    void rotate(){

        // t = top, m = middle, d = down, l = left, m = middle, r = right
        // each piece on a face is indenitifed by row first then column (tmd x lmr)

        // tl is top left, tm is top middle, etc.
        string tl = side.arr[0][0];
        string tm = side.arr[0][1];
        string tr = side.arr[0][2];

        string ml = side.arr[1][0];
        // mm never moves
        string mr = side.arr[1][2];

        string bl = side.arr[2][0];
        string bm = side.arr[2][1];
        string br = side.arr[2][2];

        side.arr[0][0] = bl;
        side.arr[0][2] = tl;
        side.arr[2][2] = tr;
        side.arr[2][0] = br;

        side.arr[1][2] = tm;
        side.arr[2][1] = mr;
        side.arr[1][0] = bm;
        side.arr[0][1] = ml; 
    }

    // method to print the string contents of the side array
    void printFace(){
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << side.arr[i][j] << " ";
                if (j == 2) {
                    cout << ",";
                }
            }
            cout << "\n";
        }
    }

    // getter
    sideStruct getSide() {
        return side;
    }

    //setter
    void setSide(int r, int c, string color) {
        side.arr[r][c] = color;
    }




};


