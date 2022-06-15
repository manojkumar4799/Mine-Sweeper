#include <iostream>
#include <time.h>
using namespace std;

class MineSweeper {
public:
    int openedCells;
private:
    int** array;
    int size;
    int** mineArray;


public:
    MineSweeper(int size) {
        openedCells = (size * size) - size;
        this->size = size;
        array = new int* [size] {0};
        mineArray = new int* [size] {0};

        for (int i = 0; i < size; i++) {
            array[i] = new int[size] {0};
            mineArray[i] = new int[size] {0};
        }
    }

    void FirstMove() {

        int x, y;
        cout << endl << "enter first x value: ";
        cin >> x;
        cout << endl << "enter first y value: ";
        cin >> y;

        if (x >= size || x < 0 || y >= size || y < 0) {
            cout << endl << "Invalid input";
            FirstMove();
            return;
        }

        srand(time(0));
        int tempX, tempY;
        for (int count = 0; count < size; count++) {

            tempX = rand() % size;
            tempY = rand() % size;
            if ((mineArray[tempX][tempY] == 9) || (tempX == x && tempY == y)) {
                count--;
                continue;
            }
            mineArray[tempX][tempY] = 9;

        }
        array[x][y] = CheckForAdjacentMines(x, y);
        openedCells++;
        OpenEmptyAdjacentCell(x, y);
        PrintArray();
        cout << endl << "adjacent mines at index (" << x << " , " << y << ") are " << array[x][y] << endl;
    }

    int MakeMove(int x, int y) {

        if (mineArray[x][y] == 1) {
            cout << endl << "index (" << x << "," << y << ") already opened!";
            return 0;
        }
        if (mineArray[x][y] == 9) {
            cout << endl << "You have opened a mine! GAMEOVER";
            return -1;
        }
        array[x][y] = CheckForAdjacentMines(x, y);
        openedCells++;
        OpenEmptyAdjacentCell(x, y);
        cout << endl << "adjacent mines at index (" << x << " , " << y << ") are " << array[x][y] << endl;
        PrintArray();
        return array[x][y];
    }


    int CheckForAdjacentMines(int x, int y) {

        int temp = 0;
        if ((x + 1 < size && y >= 0 && y < size) && mineArray[x + 1][y] == 9) {
            temp++;
        }

        if ((x - 1 >= 0 && y >= 0 && y < size) && mineArray[x - 1][y] == 9) {
            temp++;
        }

        if ((y + 1 < size && x >= 0 && x < size) && mineArray[x][y + 1] == 9) {
            temp++;
        }

        if ((y - 1 >= 0 && x >= 0 && x < size) && mineArray[x][y - 1] == 9) {
            temp++;
        }

        if ((x + 1 < size && y + 1 < size) && (mineArray[x + 1][y + 1] == 9)) {
            temp++;
        }

        if ((x + 1 < size && y - 1 >= 0) && (mineArray[x + 1][y - 1] == 9)) {
            temp++;
        }

        if ((x - 1 >= 0 && y - 1 >= 0) && (mineArray[x - 1][y - 1] == 9)) {
            temp++;
        }

        if ((x - 1 >= 0 && y + 1 < size) && (mineArray[x - 1][y + 1] == 9)) {
            temp++;
        }

        return temp;
    }


    void OpenEmptyAdjacentCell(int x, int y) {

        if (mineArray[x][y] != 0) {
            return;
        }
        array[x][y] = CheckForAdjacentMines(x, y);
        mineArray[x][y]++;
        openedCells++;
        if (array[x][y] >= 1) {
            return;;
        }

        if ((x + 1 < size && y >= 0 && y < size)) {
            OpenEmptyAdjacentCell(x + 1, y);
        }

        if ((x - 1 >= 0 && y >= 0 && y < size)) {
            OpenEmptyAdjacentCell(x - 1, y);
        }

        if ((y + 1 < size && x >= 0 && x < size)) {
            OpenEmptyAdjacentCell(x, y + 1);
        }

        if ((y - 1 >= 0 && x >= 0 && x < size)) {
            OpenEmptyAdjacentCell(x, y - 1);
        }

        if ((x + 1 < size && y + 1 < size)) {
            OpenEmptyAdjacentCell(x + 1, y + 1);
        }

        if ((x + 1 < size && y - 1 >= 0)) {
            OpenEmptyAdjacentCell(x + 1, y - 1);
        }

        if ((x - 1 >= 0 && y - 1 >= 0)) {
            OpenEmptyAdjacentCell(x - 1, y - 1);

        }

        if ((x - 1 >= 0 && y + 1 < size)) {
            OpenEmptyAdjacentCell(x - 1, y + 1);
        }
    }



    void PrintArray() {

        for (int i = 0; i < size; i++) {

            for (int j = 0; j < size; j++) {

                if (mineArray[i][j] == 0 || mineArray[i][j] == 9) {
                    cout << " -" << " ";
                }
                else
                    cout << " " << array[i][j] << " ";
            }
            cout << endl << endl;

        }
    }

    void PrintMineArray() {

        for (int i = 0; i < size; i++) {

            for (int j = 0; j < size; j++) {
                if (mineArray[i][j] == 9) {
                    cout << "(*)" << " ";
                }
                else
                    cout << " " << mineArray[i][j] << "  ";
            }
            cout << endl << endl;

        }
    }
};
int main()
{
    int size;
    cout << "enter board size: ";
    cin >> size;
    MineSweeper MS(size);
    MS.FirstMove();
    MS.PrintMineArray();
    cout << endl << "************" << endl;
    int x, y;
    for (int i = 0; i < 100 && MS.openedCells != (size * size) - size; i++) {
        cout << endl << "x value: ";
        cin >> x;
        cout << endl << " y value: ";
        cin >> y;
        cout << endl;
        if (MS.MakeMove(x, y) == -1)
        {
            return 0;
        }
    }

    cout << endl << "You won!";

}

