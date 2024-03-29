#include <iostream>
#define random(a,b) a+rand()%(b+1-a);
using namespace std;

int counter;

int chooseSize() {

    int size;
    do {
        cout << "Choose the difficulty level: 1-easy, 2-average or 3-difficult" << endl;
        cin >> size;
    } while (size < 1 || size > 3);
    size *= 8;
    return size;
}

template <typename T>
T** createField(int size) {

    T** buffield1 = new T * [size];
    for (int i = 0; i < size; i++) {
        buffield1[i] = new T[size]{};
    }
    return buffield1;
}

void set_bomb(int** field1) {

    int x1, y1;
    int size = _msize(field1) / sizeof(field1[0]);
    srand(time(NULL));
    int countBomb = size * size * 0.1;
    for (int i = 0, x, y; i < countBomb; i++) {
        x = random(0, size - 1);
        y = random(0, size - 1);
        // Если в ячейке бомба, то проверяем координаты следующей ячейки в строке через цикл for по всем ячейкам строки, пока не найдём пустую.
        // Эта часть будет актуальна для большего процента бомб. Можно использовать вместо декремента в конце итерации.
        /*while (field1[y][x] == 9) {
            for (int i = 0; field1[y][x] == 9 && i < size; i++) {
                if (++x == size) {
                    x = 0;
                }
            }
            if (field1[y][x] == 9) {
                if (++y == size) {
                    y = 0;
                }
            }
        }*/
        if (field1[y][x] != 9) {
            field1[y][x] = 9;
            for (y1 = y - 1; y1 <= y + 1 && y1 < size; y1++) {
                for (x1 = x - 1; x1 <= x + 1 && x1 < size; x1++) {
                    if (y1 < 0) {
                        y1++;
                    }
                    if (x1 < 0) {
                        x1++;
                    }
                    if (field1[y1][x1] != 9) {
                        field1[y1][x1] += 1;
                    }
                }
            }
        }
        else {
            i--;
        }
    }
}

void showField(int** field1, bool** field2) {      //по bool смотреть окрыто или закрыто а по int 

    system("cls");
    int size = _msize(field1) / sizeof(field1[0]);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (field2[i][j]==true) {
                if (field1[i][j] == 9) {
                    cout << 'X'<<' ';
                }
                else {
                    cout << field1[i][j] << ' ';
                }
            }
            else {
                cout << '*'<<' ';
            }
        }
            cout << endl;
    }
}

void openCell(bool** field2, int y1, int x1) {
    *(*(field2 + y1) + x1) = true;
}

void clearance(int** field1, bool** field2, const int x, const int y) {

    int size = _msize(field1) / sizeof(field1[0]);
        for (int y1 = y - 1; y1 <= y + 1 && y1 < size; y1++) {
            for (int x1 = x - 1; x1 <= x + 1 && x1 < size; x1++) {
                if (y1 < 0) {
                    y1++;
                }
                if (x1 < 0) {
                    x1++;
                }
                if (field1[y1][x1] > 0&& field2[y1][x1]== false) {
                    openCell(field2, y1, x1);
                }
                else if (field2[y1][x1] == false &&field1[y1][x1] == 0) {
                    openCell(field2, y1, x1);
                    clearance(field1,field2,x1,y1);
                }
            }
        }
}

void shoot(int** field1, bool** field2) {

    int size = _msize(field1) / sizeof(field1[0]);
        int x, y;
        do {
            cout << "Enter the row index: ";
            cin >> y;
        } while (y >= size);
        do {
            cout << "Enter the column index: ";
            cin >> x;
        } while (x >= size);
        if (field2[y][x] == 1) {
            cout << "It makes no sense to clear the same cell, input again\n";
            system("pause");
        }
        else if (field1[y][x] == 9) {
            int size = _msize(field1) / sizeof(field1[0]);
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    field2[i][j] = true;
                }
            }
            counter = 0;
        }
        else if (field1[y][x] > 0) {
            openCell(field2, y, x);
        }
        else {
            openCell(field2, y, x);
            clearance(field1,field2,x,y);
        }
}

bool checkWin(int size) {

    if (counter == int(size * size * 0.1)) {
        cout << "You WIN!";
        return 0;
    }
    else if (counter == 0) {
        cout << "BOOM!!!!!Game over.\n";
        return 0;
    }
    return 1;
}

int main()
{
    int size = chooseSize();
    counter = size * size;
    int** field1 = createField<int>(size);
    bool** field2 = createField<bool>(size);
    set_bomb(field1);
    showField(field1, field2);
    do {
        shoot(field1, field2);
        showField(field1, field2);
    } while (checkWin(size));
}

