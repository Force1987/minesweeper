#include <iostream>
#include <ctime>
using namespace std;
int main()
{
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));
    short score = 0, bombs, counter, size;
    const short max = 99;
    bool end, debug;
    cout << "\tИгра САПЁР" << endl << endl;
    cout << "Включить debug-режим? 1-да, 0-нет\n";
    cin >> debug;
    do
    {
        char pole[max][max]{};
        bool check[max][max]{};
        counter = 0;
        do
        {
            cout << "Введите размер поля от 5 до 99: ";
            cin >> size;
        } while (size < 5 || size>99);
        for (short i = 0; i < size; i++)
        {
            for (short j = 0; j < size; j++)
            {
                pole[i][j] = '0';
            }
        }
        do
        {
            cout << "Введите количество бомб: ";
            cin >> bombs;
            if (bombs < 1 || bombs>(size * size) - 1) cout << "Некорректный ввод, введите ещё раз\n";
        } while (bombs < 1 || bombs>(size * size) - 1);
        short a, b;
        for (short i = 0; i < bombs; i++)
        {
            a = rand() % size;
            b = rand() % size;
            if (pole[a][b] != 'X')
            {
                pole[a][b] = 'X';
            }
            else i--;
        }
        for (short i = 0; i < size; i++)
        {
            for (short j = 0; j < size; j++)
            {
                if (pole[i][j] != 'X')
                {
                    if (pole[i + 1][j + 1] == 'X' && i + 1 >= 0 && i + 1 < size && j + 1 >= 0 && j + 1 < size)pole[i][j] ++;
                    if (pole[i + 1][j] == 'X' && i + 1 >= 0 && i + 1 < size && j >= 0 && j < size)pole[i][j] ++;
                    if (pole[i + 1][j - 1] == 'X' && i + 1 >= 0 && i + 1 < size && j - 1 >= 0 && j - 1 < size)pole[i][j] ++;
                    if (pole[i][j + 1] == 'X' && i >= 0 && i < size && j + 1 >= 0 && j + 1 < size)pole[i][j] ++;
                    if (pole[i][j - 1] == 'X' && i >= 0 && i < size && j - 1 >= 0 && j - 1 < size)pole[i][j] ++;
                    if (pole[i - 1][j + 1] == 'X' && i - 1 >= 0 && i - 1 < size && j + 1 >= 0 && j + 1 < size)pole[i][j] ++;
                    if (pole[i - 1][j] == 'X' && i - 1 >= 0 && i - 1 < size && j >= 0 && j < size)pole[i][j] ++;
                    if (pole[i - 1][j - 1] == 'X' && i - 1 >= 0 && i - 1 < size && j - 1 >= 0 && j - 1 < size)pole[i][j] ++;
                }
                if (debug == 1)
                {
                    if (pole[i][j] == '0')cout << "- "; else cout << pole[i][j] << " ";
                }
                else
                {
                    if (check[i][j] == 1)
                    {
                        if (pole[i][j] == '0')cout << "- "; else cout << pole[i][j] << " ";
                    }
                    else cout << "* ";
                }
            }
            cout << endl;
        }
        while (counter < (size * size) - bombs)
        {
            do
            {
                cout << "Введите номер строки и номер столбца: ";
                cin >> a >> b;
                system("cls");
                if (a < 1 || a > size || b < 1 || b>size)
                {
                    for (short i = 0; i < size; i++)
                    {
                        for (short j = 0; j < size; j++)
                        {
                            if (check[i][j] == 1)
                            {
                                if (pole[i][j] == '0')cout << "- "; else cout << pole[i][j] << " ";
                            }
                            else cout << "* ";
                        }
                        cout << endl;
                    }
                    cout << "Некорректный ввод, введите ещё раз\n";
                }
                else if (check[a - 1][b - 1] == 1)
                {
                    for (short i = 0; i < size; i++)
                    {
                        for (short j = 0; j < size; j++)
                        {
                            if (check[i][j] == 1)
                            {
                                if (pole[i][j] == '0')cout << "- "; else cout << pole[i][j] << " ";
                            }
                            else cout << "* ";
                        }
                        cout << endl;
                    }
                    cout << "Нет смысла разминировать одну и ту же ячейку, введите ещё раз\n";
                }
            } while (check[a - 1][b - 1] == 1 || (a < 1 || a > size || b < 1 || b>size));
            if (pole[a - 1][b - 1] == 'X')
            {
                for (short i = 0; i < size; i++)
                {
                    for (short j = 0; j < size; j++)
                    {
                        if (pole[i][j] == '0')cout << "- "; else cout << pole[i][j] << " ";
                    }
                    cout << endl;
                }
                cout << "BOOM!!!!!Game over\nУспешных попаданий: " << score << endl;
                score = 0;
                break;
            }
            else
            {
                score++;
                check[a - 1][b - 1] = 1;
                counter++;
                if (pole[a - 1][b - 1] == '0')
                {
                    short ip1[max * max]{}, ip2[max * max]{}, index = 0, indexcounter = 0;
                    ip1[index] = a;
                    ip2[index] = b;
                    for (short x, y; ip1[index] != 0; index++)
                    {
                        x = ip1[index];
                        y = ip2[index];
                        if (pole[x][y] == '0' && x >= 0 && x < size && y >= 0 && y < size && check[x][y] == 0)
                        {
                            indexcounter++;
                            ip1[indexcounter] = x + 1;
                            ip2[indexcounter] = y + 1;
                        }
                        if (check[x][y] == 0 && x >= 0 && x < size && y >= 0 && y < size)
                        {
                            check[x][y] = 1;
                            counter++;
                        }
                        if (pole[x][y - 1] == '0' && x >= 0 && x < size && y - 1 >= 0 && y - 1 < size && check[x][y - 1] == 0)
                        {
                            indexcounter++;
                            ip1[indexcounter] = x + 1;
                            ip2[indexcounter] = y;
                        }
                        if (check[x][y - 1] == 0 && x >= 0 && x < size && y - 1 >= 0 && y - 1 < size)
                        {
                            check[x][y - 1] = 1;
                            counter++;
                        }
                        if (pole[x][y - 2] == '0' && x >= 0 && x < size && y - 2 >= 0 && y - 2 < size && check[x][y - 2] == 0)
                        {
                            indexcounter++;
                            ip1[indexcounter] = x + 1;
                            ip2[indexcounter] = y - 1;
                        }
                        if (check[x][y - 2] == 0 && x >= 0 && x < size && y - 2 >= 0 && y - 2 < size)
                        {
                            check[x][y - 2] = 1;
                            counter++;
                        }
                        if (pole[x - 1][y] == '0' && x - 1 >= 0 && x - 1 < size && y >= 0 && y < size && check[x - 1][y] == 0)
                        {
                            indexcounter++;
                            ip1[indexcounter] = x;
                            ip2[indexcounter] = y + 1;
                        }
                        if (check[x - 1][y] == 0 && x - 1 >= 0 && x - 1 < size && y >= 0 && y < size)
                        {
                            check[x - 1][y] = 1;
                            counter++;
                        }
                        if (pole[x - 1][y - 2] == '0' && x - 1 >= 0 && x - 1 < size && y - 2 >= 0 && y - 2 < size && check[x - 1][y - 2] == 0)
                        {
                            indexcounter++;
                            ip1[indexcounter] = x;
                            ip2[indexcounter] = y - 1;
                        }
                        if (check[x - 1][y - 2] == 0 && x - 1 >= 0 && x - 1 < size && y - 2 >= 0 && y - 2 < size)
                        {
                            check[x - 1][y - 2] = 1;
                            counter++;
                        }
                        if (pole[x - 2][y] == '0' && x - 2 >= 0 && x - 2 < size && y >= 0 && y < size && check[x - 2][y] == 0)
                        {
                            indexcounter++;
                            ip1[indexcounter] = x - 1;
                            ip2[indexcounter] = y + 1;
                        }
                        if (check[x - 2][y] == 0 && x - 2 >= 0 && x - 2 < size && y >= 0 && y < size)
                        {
                            check[x - 2][y] = 1;
                            counter++;
                        }
                        if (pole[x - 2][y - 1] == '0' && x - 2 >= 0 && x - 2 < size && y - 1 >= 0 && y - 1 < size && check[x - 2][y - 1] == 0)
                        {
                            indexcounter++;
                            ip1[indexcounter] = x - 1;
                            ip2[indexcounter] = y;
                        }
                        if (check[x - 2][y - 1] == 0 && x - 2 >= 0 && x - 2 < size && y - 1 >= 0 && y - 1 < size)
                        {
                            check[x - 2][y - 1] = 1;
                            counter++;
                        }
                        if (pole[x - 2][y - 2] == '0' && x - 2 >= 0 && x - 2 < size && y - 2 >= 0 && y - 2 < size && check[x - 2][y - 2] == 0)
                        {
                            indexcounter++;
                            ip1[indexcounter] = x - 1;
                            ip2[indexcounter] = y - 1;
                        }
                        if (check[x - 2][y - 2] == 0 && x - 2 >= 0 && x - 2 < size && y - 2 >= 0 && y - 2 < size)
                        {
                            check[x - 2][y - 2] = 1;
                            counter++;
                        }
                    }
                }
            }
            if (debug == 1)
            {
                cout << "Режим отладки\n";
                for (short i = 0; i < size; i++)
                {
                    for (short j = 0; j < size; j++)
                    {
                        if (pole[i][j] == '0')cout << "- "; else cout << pole[i][j] << " ";
                    }
                    cout << endl;
                }
                cout << endl;
            }
            for (short i = 0; i < size; i++)
            {
                for (short j = 0; j < size; j++)
                {
                    if (check[i][j] == 1)
                    {
                        if (pole[i][j] == '0')cout << "- "; else cout << pole[i][j] << " ";
                    }
                    else cout << "* ";
                }
                cout << endl;
            }
            if (counter == (size * size) - bombs)
            {
                cout << "Congratulations!!!\nУспешных попаданий: " << score << endl;
            }
        }
        cout << "\tНачать сначала?\n1-да\n0-нет\n";
        cin >> end;
        system("cls");
    } while (end == 1);
}
