#include <iostream>
#include <cstdlib>
using namespace std;
bool valid_point(int x, int y, int rows, int cols)
{
    return (x >= 0 && x < rows) && (y >= 0 && y < cols);
}
int main()
{
    srand(time(0));

    int n = 0;
    cout << "Enter Game Size: ";
    cin >> n;
    int rows = n;
    int cols = n / 2;
    char* player[rows][cols];

    char pc_player[rows][cols];
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            player[i][j] = '#';
            pc_player[i][j] = '#';
        }


    int player_points = n, pc_points = n;

    int x = 0, y = 0;
    int player_ships_placed = 0;
    while (player_ships_placed != n)
    {
        cout << "Enter Point To set Ship: ";
        cin >> x >> y;
        if (player[x][y] == '#' && valid_point(x, y, rows, cols))
        {
            player[x][y] = '*';
            player_ships_placed++;
        }
        else
            cout << "Invalid Place, Try Again.\n";
    }
    int pc_ships_placed = 0;
    int min = 0;
    while (pc_ships_placed != n)
    {
        int rnd_row = (rand() % (rows - min + 1)) + min;
        int rnd_col = (rand() % (cols - min + 1)) + min;

        if (pc_player[rnd_row][rnd_col] == '#')
        {
            pc_player[rnd_row][rnd_col] = '*';
            pc_ships_placed++;
        }
    }
    while (player_points != 0 || pc_points != 0)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
                cout << player[i][j] << " ";

            cout << "| ";
            for (int j = 0; j < cols; j++)
            {
                if (pc_player[i][j] == '*')
                    cout << "# ";
                else
                    cout << pc_player[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "Enter Point To Fire:\n";
        cin >> x >> y;
        if (valid_point(x, y, rows, cols))
        {
            if (pc_player[x][y] == '#')
            {
                pc_player[x][y] = '0';
            }
            else if (pc_player[x][y] == '*')
            {
                pc_player[x][y] = '1';
                pc_ships_placed--;
            }
        }
        cout << "Pc Fireing To You:\n";

        x = (rand() % (rows - min + 1)) + min;
        y = (rand() % (cols - min + 1)) + min;
        cout << x << " " << y;
        if (player[x][y] == '#')
        {
            player[x][y] = '0';
        }
        else if (player[x][y] == '*')
        {
            player[x][y] = '1';
            player_ships_placed--;
        }

        cout << "\nYou'r Remaining Ships: " << player_ships_placed << "\n";
        cout << "PC's Remaining Ships: " << pc_ships_placed << "\n";
    }

    if (player_points == 0)
        cout << "\n PC Win The Game";
    else
        cout << "\n You Win The Game";
}
