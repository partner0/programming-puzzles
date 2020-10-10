#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

string int_array_to_string(int int_array[], int size_of_array) {
    string returnstring = "{ ";
    for (int temp = 0; temp < size_of_array; temp++)
    {
        returnstring += to_string(int_array[temp]) + (temp < size_of_array - 1 ? ", " : " }");
    }
    return returnstring;
}

class solver
{
    protected:
    int cnt_lower;
    int cnt_upper;
    int tmp_sum;

    public:
    static const int ARRAY_SIZE = 20;
    int array[ARRAY_SIZE];  //= { -6, 0, -4, 5, -8, -5, -6, 2, -8, -5, 3, 7, 1, 0, -9, 3, 5, 0, 8, -7 };
    //int array[ARRAY_SIZE]  = { 0,0,0,0,0,0,0, 2, -8, -5, 3, 7, 1, 0, -9, 3, 5, 0, 8, 0 };
    int lower_found;
    int upper_found;
    int max_sum_value;

    public: solver()
    {
        srand(time(NULL));

        for (cnt_lower = 0; cnt_lower < ARRAY_SIZE; cnt_lower++)
        {
            array[cnt_lower] = rand() % 21 - 10;
        }

        max_sum_value = array[0];
        lower_found = 0;
        upper_found = 0;
    }

    public: solver(int fed_array[ARRAY_SIZE])
    {
        for (cnt_lower = 0; cnt_lower < ARRAY_SIZE; cnt_lower++)
        {
            array[cnt_lower] = fed_array[cnt_lower];
        }

        max_sum_value = array[0];
        lower_found = 0;
        upper_found = 0;
    }

    public: virtual void solve() = 0;
};

class solver_n2 : public solver
{
    public: void solve()
    {
        for (cnt_lower = 0; cnt_lower < ARRAY_SIZE; cnt_lower++)
        {
            tmp_sum = 0;
            for (cnt_upper = cnt_lower; cnt_upper < ARRAY_SIZE; cnt_upper++)
            {
                tmp_sum += array[cnt_upper];
                if (tmp_sum > max_sum_value)
                {
                    max_sum_value = tmp_sum;
                    lower_found = cnt_lower;
                    upper_found = cnt_upper;
                }
            }
        }
    }
};

class solver_n : public solver
{
    public: solver_n(int fed_array[ARRAY_SIZE])
    {
        for (cnt_lower = 0; cnt_lower < ARRAY_SIZE; cnt_lower++)
        {
            array[cnt_lower] = fed_array[cnt_lower];
        }

        max_sum_value = array[0];
        lower_found = 0;
        upper_found = 0;
    }

    public: void solve()
    {
        int lower = 0;
        int upper = 0;
        int sum = 0;
        int cnt;

        for (cnt = 0; cnt < ARRAY_SIZE; cnt++)
        {
            sum += array[cnt];
            if (sum > max_sum_value)
            {
                max_sum_value = sum;
                lower_found = lower;
                upper_found = cnt;
            }
            if (sum < 0)
            {
                sum = 0;
                lower = cnt + 1;
            }
        }

        /*
        int behind_upper = 0;
        int behind_lower = 0;
        int enclosed_sum = 0;
        int sum_positives = 0;
        int sum_positives_out = 0;
        int sum_negatives = 0;
        int sum_negatives_out = 0;
        
        int original_array[ARRAY_SIZE];
        int index_lower[ARRAY_SIZE];
        int index_upper[ARRAY_SIZE];
        int reduced_size = 0;
        int offset = 0;
        bool isPositive = (array[0] > 0);

        int tmp_lower = 0;
        int tmp_upper = ARRAY_SIZE - 1;

        int sum_from_left[ARRAY_SIZE];
        int sum_from_right[ARRAY_SIZE];
        int max_sum_from_left = array[0];
        int max_sum_from_right = array[ARRAY_SIZE - 1];
        int enclosed_sum_right = 0;

        for (cnt_lower = 0; cnt_lower < ARRAY_SIZE; cnt_lower++)
        {
            enclosed_sum += array[cnt_lower];
            enclosed_sum_right += array[ARRAY_SIZE - cnt_lower - 1];
            sum_from_left[cnt_lower] = enclosed_sum;
            sum_from_right[cnt_lower] = enclosed_sum_right;
            if (enclosed_sum > max_sum_from_left)
            {
                max_sum_from_left = enclosed_sum;
            }
            if (enclosed_sum_right > max_sum_from_right)
            {
                max_sum_from_right = enclosed_sum_right;
            }
        }
    
        lower_found = tmp_lower;
        upper_found = tmp_upper;
        max_sum_value = enclosed_sum;

        while(tmp_lower < tmp_upper)
        {
            if (max_sum_from_left < max_sum_from_right)
            {
                enclosed_sum -= array[tmp_lower];
                max_sum_from_left -= array[tmp_lower];
                tmp_lower++;
            }
            else
            {
                enclosed_sum -= array[tmp_upper];
                max_sum_from_right -= array[tmp_upper];
                tmp_upper--;
            }
            if (enclosed_sum >= max_sum_value)
            {
                lower_found = tmp_lower;
                upper_found = tmp_upper;
                max_sum_value = enclosed_sum;
            }
        }*/

        /*
        // First we reduce the array to a simpler case of alternating signs by grouping adjacent values of the same sign. 
        // It ends up being all odd indexes are positive and even indexes negatives or the other way around
        // index_lower and index_upper retain the original index positions for these groups in the original array
        for (cnt_lower = 0; cnt_lower < ARRAY_SIZE; cnt_lower++)
        {
            original_array[cnt_lower] = array[cnt_lower];
            if (cnt_lower < ARRAY_SIZE && ((isPositive && array[cnt_lower + 1] > 0) || (!isPositive && array[cnt_lower + 1] <= 0)))
            {
                array[reduced_size] += array[cnt_lower + 1];
                offset++;
            }
            else
            {
                index_lower[reduced_size] = (cnt_lower - offset == 0 ? 0 : cnt_lower - offset + 1);
                index_upper[reduced_size] = cnt_lower;
                reduced_size ++;
                offset = 0;
                isPositive = !isPositive;
                array[reduced_size] = array[cnt_lower + 1];
                offset++;
            }
        }
        index_lower[reduced_size] = (cnt_lower - offset == 0 ? 0 : cnt_lower - offset + 1);
        index_upper[reduced_size] = cnt_lower - 1;
        reduced_size++;

        cout << int_array_to_string(original_array, ARRAY_SIZE) + "\n";
        cout << int_array_to_string(index_lower, reduced_size) + "\n";
        cout << int_array_to_string(index_upper, reduced_size) + "\n";
        cout << int_array_to_string(array, reduced_size) + "\n";

        for (cnt_lower = 0; cnt_lower < reduced_size; cnt_lower++)
        {
            enclosed_sum += array[cnt_lower];
            (array[cnt_lower] < 0 ? sum_negatives -= array[cnt_lower] : sum_positives += array[cnt_lower]);
        }

        // Then we go on finding the biggest sub-array in the reduced array
        

        lower_found = 0;
        upper_found = reduced_size;
        max_sum_value = enclosed_sum;

        while(lower_found < upper_found)
        {
            if (array[lower_found] <= 0)
            {
                lower_found++;
                sum_negatives -= -array[lower_found];
                continue;
            }
            if (array[upper_found] <= 0)
            {
                upper_found--;
                sum_negatives -= -array[upper_found];
               continue;
            }
            if (array[lower_found] < array[upper_found])
            {
                if (enclosed_sum - array[lower_found] > array[lower_found])
                {
                    enclosed_sum -= array[lower_found];
                    lower_found++;
                }
                else
                {
                    break;
                }
            }
            else
            {
                if (enclosed_sum - array[upper_found] > array[upper_found])
                {
                    enclosed_sum -= array[upper_found];
                    upper_found--;
                }
                else
                {
                    break;
                }
                
            }
        }
        max_sum_value = enclosed_sum;
        */
    }
};

int main(int argc, char const *argv[])
{
    int arr[20] = { -5, 9, -8, 2, 9, 7, 4, 4, -7, 1, 9, -7, 5, -6, -9, 5, -6, 5, 3, -8 };
    solver_n2 my_solver_n2;
    solver_n my_solver_n(my_solver_n2.array);

    my_solver_n2.solve();
    my_solver_n.solve();

    cout << int_array_to_string(my_solver_n.array, my_solver_n.ARRAY_SIZE) + "\n";
    cout << "Solver N: L: " + to_string(my_solver_n.lower_found) + " / U: " + to_string(my_solver_n.upper_found) + " / S: " + to_string(my_solver_n.max_sum_value) + "\n";
    cout << int_array_to_string(my_solver_n2.array, my_solver_n2.ARRAY_SIZE) + "\n";
    cout << "Solver N2: L: " + to_string(my_solver_n2.lower_found) + " / U: " + to_string(my_solver_n2.upper_found) + " / S: " + to_string(my_solver_n2.max_sum_value) + "\n";
}