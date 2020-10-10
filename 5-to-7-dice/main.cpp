#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

class dice
{
    private: int dice_size;

    public:dice(int size)
    {
        dice_size = size;
    }

    private: int rand5()
    {
        return rand() % 5 + 1;
    }

    public:int throwit()
    {
        int cnt;
        int result = 0;
        int iterations = (dice_size - 1) / 5 + 1;

        if (iterations > 1)
        {
            dice proba_dice(iterations);
            do
            {
               result = rand5() + (proba_dice.throwit() - 1) * 5;
            }
            while (result > dice_size);
        }
        else
        {
            do
            {
               result = rand5();
            }
            while (result > dice_size);
        }
        
        return result;
    }

};

int main(int argc, char const *argv[])
{
    // argv[1] is dice size

    int cnt;
    int nb_throws = 10000;
    int total;
    dice my_dice(atoi(argv[1]));
    int results[atoi(argv[1])];
    int totalabove = 0;
    int totalbellow = 0;

    srand (time(NULL));

    if (argc <= 1)
    {
        cout << "Please specify the dice size, thank you!";
        return 0;
    }

    for(cnt=0; cnt <= atoi(argv[1]); cnt++)
    {
        results[cnt] = 0;
    }

    for(cnt=0; cnt < nb_throws; cnt++)
    {
        results[my_dice.throwit()-1]++;
    }

    total = 0;
    for(cnt=0; cnt <= atoi(argv[1]); cnt++)
    {
        total += results[cnt];
        (results[cnt] > nb_throws/atoi(argv[1]) ? totalabove++ : (results[cnt] < nb_throws/atoi(argv[1]) ? totalbellow++ : 0));
        cout << to_string(cnt + 1) + ":" + to_string(results[cnt]) + (results[cnt] > nb_throws/atoi(argv[1]) ? "+" : (results[cnt] < nb_throws/atoi(argv[1]) ? "-" : "=")) + " | ";
    }

    cout << " TOT: " + to_string(total) + " AVG: " + to_string(total/atoi(argv[1])) + " ABV: " + to_string(totalabove) + " BLW: " + to_string(totalbellow) + "\n";

    return 0;
}
