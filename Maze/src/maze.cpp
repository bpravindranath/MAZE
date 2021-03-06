///************************************************************************
//COSC 501                                      Programming Assignment 4
//Barnabas Ravindranath                                 12/6/16
//Program Name:  MAZE
// 
#include <cstdlib>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<iomanip>
using namespace std;
const int SIZE = 20;

void fill_array(ifstream& file, char g[][SIZE], int num);
void print_array(char g[][SIZE], int num);

struct Coordinate {
    int x;
    int y;
};

struct StackFrame {
    Coordinate data;
    StackFrame *link;
};
typedef StackFrame* stackptr;

class Stack {
public:
    Stack();
    void push(Coordinate c);
    void push(int x, int y);
    Coordinate pop();
    bool empty() const;
private:
    stackptr top;

};

int main() {

    int b = 0, c = 0;
    char maze_array[SIZE][SIZE];
    // char maze_array_2[SIZE][SIZE];
    ifstream input;
    Stack Maze;
    Coordinate current;

    input.open("maze.txt");
    if (input.fail()) {
        cout << "Input Filed Failed To Open" << endl;
        exit(1);
    }

    fill_array(input, maze_array, SIZE);
    cout << "Enter the Starting point (Row 1-20) and (Colomn 1-20) Number of Row: ";
    cin >> current.x >> current.y;
    maze_array[--current.x][--current.y] = 'S';

    print_array(maze_array, SIZE);

    bool end;

    Maze.push(current);
    while (!Maze.empty()) {

        current = Maze.pop();
        if (maze_array[current.x][current.y] == 'E') { //current
            //Maze.push(current.x, current.y);
            end = true;
            break;
        }
        maze_array[current.x][current.y] = '+';
        if ((maze_array[current.x - 1][current.y] == '0') || (maze_array[current.x - 1][current.y] == 'E')) { //UP
            Maze.push(current.x - 1, current.y);

        }

        if ((maze_array[current.x + 1][current.y] == '0') || (maze_array[current.x + 1][current.y] == 'E')) {
            Maze.push(current.x + 1, current.y);  
        }

        if ((maze_array[current.x][current.y - 1] == '0') || (maze_array[current.x][current.y - 1] == 'E')) {
            Maze.push(current.x, current.y - 1);
        }

        if ((maze_array[current.x][current.y + 1] == '0') || (maze_array[current.x][current.y + 1] == 'E')) {
            Maze.push(current.x, current.y + 1);
        }
      
        
    }
    //print
    print_array(maze_array, SIZE);
    
    if(end){
        cout << "I am Free!!" << endl;
    }
    else {
        cout << "Help I am Trapped!" << endl;     
    }
    
    
    return 0;
}

//        if (error >= 4) {
//            maze_array[x][y] = (up + down + right + left)/4;  
//        }
//        error = 0;

Stack::Stack() : top(NULL) {

}

void Stack::push(Coordinate c) {
    stackptr temp;
    temp = new StackFrame;
    temp->data = c;
    temp->link = top;
    top = temp;
}

void Stack::push(int x, int y) {
    Coordinate item = {x, y};
    stackptr temp;
    temp = new StackFrame;
    temp->data = item;
    temp->link = top;
    top = temp;
}

Coordinate Stack::pop() {
    if (empty()) {
        cout << "Error: Popping an empty stack!";
        exit(1);
    }
    Coordinate result = top->data;
    stackptr temp;
    temp = top;
    top = top->link;
    delete temp;
    return result;
}

bool Stack::empty() const {
    return (top == NULL);
}

void fill_array(ifstream& file, char g[][SIZE], int num) {

    for (int x = 0; x < SIZE; x++) {
        cout << setw(10);
        for (int y = 0; y < SIZE; y++) {
            file >> g[x][y];
            cout << g[x][y] << "  ";
            if (y == 19) {
                cout << endl;
            }
        }
    }

}

void print_array(char g[][SIZE], int num) {
    for (int x = 0; x < SIZE; x++) {
        cout << setw(10);
        for (int y = 0; y < SIZE; y++) {
            cout << g[x][y] << "  ";
            if (y == 19) {
                cout << endl;
            }
        }
    }
    cout << endl << endl;
}
