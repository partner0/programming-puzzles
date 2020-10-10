#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    srand (time(NULL));

    int door_money;
    int door_chosen;
    int door_switched;
    int cnt_no_switch_wins = 0;
    int cnt_switch_wins = 0;
    int cnt_nb_tries = 1000;
    int cnt;

    for (cnt = 0; cnt < cnt_nb_tries; cnt++)
    {
        door_money = rand() % 3;
        door_chosen = rand() % 3;
        if (door_chosen == 0)
        {
            if (door_money == 0)
                door_switched = rand() % 2 + 1;

            if (door_money == 1)
                door_switched = 1;

            if (door_money == 2)
                door_switched = 2;
        }
        if (door_chosen == 1)
        {
            if (door_money == 0)
                door_switched = 0;

            if (door_money == 1)
                door_switched = rand() % 2 * 2;

            if (door_money == 2)
                door_switched = 2;
        }
        if (door_chosen == 2)
        {
            if (door_money == 0)
                door_switched = 0;

            if (door_money == 1)
                door_switched = 1;

            if (door_money == 2)
                door_switched = rand() % 2;
        }
        if (door_chosen == door_money)
            cnt_no_switch_wins++;
        if (door_switched == door_money)
            cnt_switch_wins++;
    }

    cout << "Switch: " + to_string(cnt_switch_wins) + " No switch: " + to_string(cnt_no_switch_wins) + "\n";

    return 0;
}