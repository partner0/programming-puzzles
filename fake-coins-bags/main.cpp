#include <iostream>
#include <stdlib.h>
#include <string>
#include <stddef.h>

using namespace std;

const int NUMBER_OF_BAGS = 100;
const int REAL_WEIGHT = 31;
const int NUMBER_OF_PRIMES_BELLOW_REAL_WEIGHT = 11;

struct solution
{
    int weight;
    int bag;
    int multiplicity;
};

class utils
{
    public: static string int_array_to_string(int int_array[], int size_of_array) 
    {
        int cnt;

        string array_string = "{ ";
        for (cnt = 0; cnt < size_of_array; cnt++)
        {
            array_string += to_string(cnt) + ":" + to_string(int_array[cnt]) + (cnt < size_of_array - 1 ? ", " : " }");
        }
        return array_string;
    }
};

class primes
{
    private: int primes_list[NUMBER_OF_BAGS + NUMBER_OF_PRIMES_BELLOW_REAL_WEIGHT];
    
    public: primes()
    {
        int cnt;
        int index = 1;
        int tmp_number = 3;
        
        primes_list[0] = 2;

        while(index < NUMBER_OF_BAGS + NUMBER_OF_PRIMES_BELLOW_REAL_WEIGHT)
        {
            for (cnt = 0; cnt < index; cnt++)
            {
                if (tmp_number % primes_list[cnt] == 0)
                {
                    break;
                }
            }
            if (cnt == index)
            {
                primes_list[index] = tmp_number;
                index++;
            }
            tmp_number++;
        }
    }

    public: void get_primes_list(int* mem_ptr)
    {
        int cnt;

        for (cnt = 0; cnt < NUMBER_OF_BAGS + NUMBER_OF_PRIMES_BELLOW_REAL_WEIGHT; cnt++)
        {
            mem_ptr[cnt] = primes_list[cnt];
        }

        return;
    }
};

class solver_n2_logn
{
    public: static solution solve(int total_weight)
    {
        int cnt;
        int cnt_inner;
        int tmp_fake_weight;
        int tmp_weight;
        primes obj_primes;
        int primes_list[NUMBER_OF_BAGS + NUMBER_OF_PRIMES_BELLOW_REAL_WEIGHT];
        solution solution;

        obj_primes.get_primes_list(primes_list);
        solution.bag = 0;
        solution.weight = 0;
        solution.multiplicity = 0;

        for (cnt = 0; cnt < NUMBER_OF_BAGS; cnt++)
        {
            for (tmp_fake_weight = 1; tmp_fake_weight < REAL_WEIGHT; tmp_fake_weight++)
            {
                if ((total_weight - primes_list[cnt + NUMBER_OF_PRIMES_BELLOW_REAL_WEIGHT] * tmp_fake_weight) % REAL_WEIGHT == 0)
                {
                    tmp_weight = 0;
                    for (cnt_inner = 0; cnt_inner < NUMBER_OF_BAGS; cnt_inner++)
                    {
                        tmp_weight += primes_list[cnt_inner + NUMBER_OF_PRIMES_BELLOW_REAL_WEIGHT] * (cnt_inner == cnt ? 0 : REAL_WEIGHT);
                    }
                    if (tmp_weight + primes_list[cnt + NUMBER_OF_PRIMES_BELLOW_REAL_WEIGHT] * tmp_fake_weight == total_weight)
                    {
                        solution.bag = cnt;
                        solution.weight = tmp_fake_weight;
                        solution.multiplicity++;
                    }
                }
            }
        }
        return solution;
    }
};

class solver_n
{
    public: static solution solve(int total_weight)
    {
        int cnt;
        int total_weight_no_fake = 0;
        primes obj_primes;
        int primes_list[NUMBER_OF_BAGS + NUMBER_OF_PRIMES_BELLOW_REAL_WEIGHT];
        solution solution;

        obj_primes.get_primes_list(primes_list);
        solution.bag = 0;
        solution.weight = 0;
        solution.multiplicity = 0;

        for (cnt = 0; cnt < NUMBER_OF_BAGS; cnt++)
        {
            total_weight_no_fake += primes_list[cnt + NUMBER_OF_PRIMES_BELLOW_REAL_WEIGHT] * REAL_WEIGHT;
        }

        for (cnt = 0; cnt < NUMBER_OF_BAGS; cnt++)
        {
            if ((total_weight_no_fake - total_weight) % primes_list[cnt + NUMBER_OF_PRIMES_BELLOW_REAL_WEIGHT] == 0)
            {
                //if (solution.multiplicity > 0) cout << "Previous sol: Fake weight found: " + to_string(solution.weight) + " Fake bag found: " + to_string(solution.bag) + " Number of solutions: " + to_string(solution.multiplicity) + "\n";
                solution.bag = cnt;
                solution.weight = REAL_WEIGHT - (total_weight_no_fake - total_weight) / primes_list[cnt + NUMBER_OF_PRIMES_BELLOW_REAL_WEIGHT];
                solution.multiplicity++;
            }
        }
        return solution;
    }
};

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    int cnt;
    int total_weight = 0;
    int fake_bag = rand() % NUMBER_OF_BAGS + 1;
    int fake_weight = rand() % (REAL_WEIGHT - 1) + 1;
    int primes_list[NUMBER_OF_BAGS + NUMBER_OF_PRIMES_BELLOW_REAL_WEIGHT];
    primes obj_primes;
    solution solution;

    obj_primes.get_primes_list(primes_list);

    cout << utils::int_array_to_string(primes_list, NUMBER_OF_BAGS + NUMBER_OF_PRIMES_BELLOW_REAL_WEIGHT);

    // La pesee consiste en 37 pieces du premier sac, 41 du 2eme, 43 du 3eme, ...
    for (cnt = 0; cnt < NUMBER_OF_BAGS; cnt++)
    {
        total_weight += primes_list[cnt + NUMBER_OF_PRIMES_BELLOW_REAL_WEIGHT] * (cnt == fake_bag ? fake_weight : REAL_WEIGHT);
    }

    cout << "Total Weight: " + to_string(total_weight) + "\n";

    // Ici, l'isolation de la class solver interdit tout access aux variables locales, notament le poid et le numero du sac.
    // Unique parametre: la pesee
    /*solution = solver_n2_logn::solve(total_weight);

    cout << "Fake weight found: " + to_string(solution.weight) + " Fake bag found: " + to_string(solution.bag) + " Number of solutions: " + to_string(solution.multiplicity) + "\n";
    cout << "Fake weight was: " + to_string(fake_weight) + " Fake bag was: " + to_string(fake_bag) + "\n";*/

    solution = solver_n::solve(total_weight);

    cout << "Fake weight found: " + to_string(solution.weight) + " Fake bag found: " + to_string(solution.bag) + " Number of solutions: " + to_string(solution.multiplicity) + "\n";
    cout << "Fake weight was: " + to_string(fake_weight) + " Fake bag was: " + to_string(fake_bag) + "\n";
}
