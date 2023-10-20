#include <iostream>
#include <cstdlib>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <windows.h>
using namespace std;
bool valid_point(int x, int y, int rows, int cols)
{
    return (x >= 0 && x < rows) && (y >= 0 && y < cols);
}
int score(int c, int n, int i, int l) {
    return c + (n / i) + l;
}
int main()
{
    system("color 1f");
    int EnteredNumber;
    bool Only123 = 0;
    do {
        cout << "== Main Menu ==\n";
        cout << "1)New Game\n";
        cout << "2)History Of Scores\n";
        cout << "3)Exit\n";
        cin >> EnteredNumber;
        if (EnteredNumber != 1 && EnteredNumber != 2 && EnteredNumber != 3) {
            system("cls");
            cout << "Sorry,You only have these three options:(\n"; Sleep(2300);  system("cls");
        }
        else Only123 = 1;
    } while (!Only123);
    if (EnteredNumber == 1) {
        system("color 9f");
        srand(time(0));
        int n = 0;
        system("cls");

        cout << "Enter Game Size:\n";
        cin >> n;
        n = abs(n);
        while (n > 19 || n < 5 || n % 2 == 0) {
            cout << "Invalid Size.Please Enter An Odd Number Between 5 and 19 For The Game Size\n";
            cin >> n; system("cls");
        }
        int rows = n;
        int cols = n / 2;

        //these are all the integers needed to set the players score.
        int c{};//number of exact shots to the aim.
        int i{ 1 };//missed shots
        //

        char player[20][20];
        char pc_player[20][20];
        //we've given the maximum possible size of rows and columns,so that all the others are covered.this way we wouldn't need to define a pointer.
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
            {
                player[i][j] = '#';
                pc_player[i][j] = '#';
            }
        //Now,all the lines except for the middle one are sharps(#).
        int player_points = n, pc_points = n;
        int x, y;
        int player_ships_placed = 0;
        while (player_ships_placed != n)
        {
            cout << "Enter Point To set Ship:\n";
            cin >> x >> y; system("cls");
            if (player[x][y] == '#' && valid_point(x, y, rows, cols))//the coordinate validation statement
            {
                player[x][y] = '*';
                player_ships_placed++;
            }
            else {
                cout << "Invalid Place, Try Again.\n";
            }
        }
        bool checker1[20][10];//this will be used later on as a coordinatechecker.
        bool checker2[20][10];
        for (int i{}; i < rows; i++)
            for (int j{}; j < cols; j++) {
                checker1[i][j] = 1;
                checker2[i][j] = 1;
            }
        //
        int pc_ships_placed = 0;
        while (pc_ships_placed != n)
        {
            int random_row = (rand() % (rows + 1));
            int random_col = (rand() % (cols + 1));

            if (pc_player[random_row][random_col] == '#')
            {
                pc_player[random_row][random_col] = '*';
                pc_ships_placed++;
            }
        }//with this loop we place the enemys ships in an unshown coordinate.

        while (pc_ships_placed != 0 && player_ships_placed != 0)//the game starts here and ends when a side looses all its ships.
        {
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                    cout << player[i][j] << " ";

                cout << "| ";
                for (int j = 0; j < cols; j++)
                {
                    if (pc_player[i][j] == '*')//this is stated so that the random enemy ships aren't shown.
                        cout << "# ";
                    else
                        cout << pc_player[i][j] << " ";
                }

                cout << "\n";
            }



            cout << "Enter Point To Fire:\n";
            bool loopBreaker = 1;//With this boolean we determine whether the entered coordinate is valid or not and if not promp the player to enter yet another coordinate.
            while (loopBreaker) {

                cin >> x >> y;

                if (checker1[x][y] && valid_point(x, y, rows, cols)) {
                    checker1[x][y] = 0;
                    if (pc_player[x][y] == '#')
                    {
                        pc_player[x][y] = '0';
                        i++;//counting the missed shots
                    }
                    else if (pc_player[x][y] == '*')
                    {
                        pc_player[x][y] = '1';
                        c++;//counting the number of exact shots to the aim.
                        pc_ships_placed--;
                    }
                    loopBreaker = 0;

                    cout << endl;
                    cout << "You Fired The Enemey...";
                    Sleep(1000);
                    system("cls");
                }


                else
                    cout << "Invalid Coordinate, Try Again." << endl;
            }

            if (pc_ships_placed == 0)//we don't want it to continue playing when all the enenmy ships where shot. 
                break;
            cout << "Now Pc Fireing To You:\n";
            bool loopBreaker2 = 1;
            while (loopBreaker2) {

                int x = rand() % rows;
                int y = rand() % cols;

                if (checker2[x][y] == 1) {
                    checker2[x][y] = 0;
                    loopBreaker2 = 0;
                    cout << x << ' ' << y;

                    if (player[x][y] == '#')
                    {
                        player[x][y] = '0';
                    }
                    else if (player[x][y] == '*')
                    {
                        player[x][y] = '1';
                        player_ships_placed--;
                    }
                }
            }
            system("cls");

            cout << "You'r Remaining Ships: " << player_ships_placed << "\n"; Sleep(800); system("cls");
            cout << "PC's Remaining Ships: " << pc_ships_placed << "\n"; Sleep(800); system("cls");

            cout << "Your Score: " << score(c, n, i, player_ships_placed) << endl; Sleep(20);

        }
        Sleep(2000);
        if (player_ships_placed == 0) {
            cout << "\n PC Wins The Game"; Sleep(1000); system("cls");
        }
        else if (pc_ships_placed == 0) {
            cout << "\n You Win The Game"; Sleep(1000); system("cls");
        }
    }
    if (EnteredNumber == 3) {
        cout << "Ok, We Wait For You To Come Back.\n";
        cout << "     Have a Nice Day:)";
        Sleep(10000);
        return 0;
    }
}
