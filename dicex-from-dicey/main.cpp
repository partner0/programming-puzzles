#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

class dice
{
    protected: int dice_from_size;
    protected: int dice_to_size;

    public: virtual int throwit() = 0;
};

class utils
{
    public: static int pow(int base, int exponent)
    {
        int cnt;
        int result = 1;

        for (cnt = 0; cnt < exponent; cnt++)
        {
            result = result * base;
        }

        return result;
    }

    public: static int randfrom(int base)
    {
        return rand() % base + 1;
    }
};

class node
{
    public: node* parent;
    private: node** children_array;
    public: node**& children = children_array;
    private: int nb_children;
    public: int value;

    public: node(node* parent, int nb_children, int value)
    {
        int cnt;

        this->parent = parent;
        this->nb_children = nb_children;
        if (nb_children > 0)
        {
            this->children_array = new node*[nb_children];
        }
        else
        {
            this->children_array = 0;
        }
        this->value = value;

        for(cnt = 0; cnt < nb_children; cnt++)
        {
            children_array[cnt] = 0;
        }
    }

    public: node(node* parent, int depth, int nb_children, int value)
    {
        int cnt;

        this->parent = parent;
        this->value = value;

        if (depth == 0)
        {
            this->nb_children = 0;
            this->children_array = 0;
        }
        else
        {
            this->nb_children = nb_children;
            this->children_array = new node*[nb_children];
            for(cnt = 0; cnt < nb_children; cnt++)
            {
                children_array[cnt] = new node(this, depth - 1, nb_children, value);
            }
        }
    }

    public: int get_left_depth()
    {
        int depth = 1;
        node* current_node = this;

        while(current_node->nb_children > 0)
        {
            current_node = current_node->children_array[0];
            depth++;
        }

        return depth;
    }

    vector<node*> get_leaves(node* node_to_parse)
    {
        static node* start_node;
        static vector<node*> leaves;
        int cnt;

        if (start_node == 0)
        {
            start_node = node_to_parse;
        }

        if(node_to_parse->nb_children == 0)
        {
            leaves.push_back(node_to_parse);
            return leaves;
        }

        for (cnt=0; cnt < node_to_parse->nb_children; cnt++)
        {
            if (node_to_parse->children_array[cnt] != 0)
            {
                get_leaves(node_to_parse->children_array[cnt]);
            }
            else
            {
                //leaves.push_back(node_to_parse->children_array[cnt]);
            }
        }

        return leaves;
    }
};

class dice_by_tree : dice
{
    private: node* head;
    private: int tree_depth;

    private: int randfrom()
    {
        return rand() % dice_from_size + 1;
    }

    public: dice_by_tree(int dice_from_size, int dice_to_size)
    {
        int tmp_number = dice_to_size;
        int tree_depth = 0;
        int cnt;
        vector<node*> leaves;

        this->dice_from_size = dice_from_size;
        this->dice_to_size = dice_to_size;

         while (tmp_number > 0)
        {
            tree_depth++;
            tmp_number = tmp_number / dice_from_size;
        } 

        head = new node(0, tree_depth, dice_from_size, 0);

        this->tree_depth = head->get_left_depth();

        leaves = head->get_leaves(head);

        for(cnt = 1; cnt <= utils::pow(dice_from_size, tree_depth); cnt++)
        {
            leaves[cnt - 1]->value = cnt;
        }
    }

    public: int throwit()
    {
        int cnt;
        node* current_node;
        int result;

        do
        {
            current_node = head;
            for(cnt = 0; cnt < tree_depth - 1; cnt++)
            {
                current_node = current_node->children[utils::randfrom(dice_from_size) - 1];
            }
        } while (current_node->value > dice_to_size);

        return current_node->value;
    };
};

class dice_by_base : dice
{
    public:dice_by_base(int dice_from_size, int dice_to_size)
    {
        this->dice_from_size = dice_from_size;
        this->dice_to_size = dice_to_size;
    }

    public:int throwit()
    {
        int tmp_number = dice_to_size;
        int nb_digits_in_base_from = 0;
        int cnt;
        int to_dice_roll = 0;

        while (tmp_number > 0)
        {
            nb_digits_in_base_from++;
            tmp_number = tmp_number / dice_from_size;
        } 
        
        do
        {
            to_dice_roll = 0;
            for(cnt=0; cnt < nb_digits_in_base_from; cnt++)
            {
                to_dice_roll += (utils::randfrom(dice_from_size) - 1) * utils::pow(dice_from_size, cnt);
            }
        }
        while (to_dice_roll +1 > dice_to_size);
        
        return to_dice_roll + 1;
    }
};

class test_node
{
    public: node* head;

    public: test_node()
    {
        vector<node *> leaves;
        
        head = new node(0, 3, 3, 0);
        
        leaves = head->get_leaves(head);
    }
};

class control_dice : dice
{
    public: control_dice(int na, int dice_to_size)
    {
        this->dice_to_size = dice_to_size;
    }

    public: int throwit()
    {
        return utils::randfrom(dice_to_size);
    }
};

int main(int argc, char const *argv[])
{
    int cnt;
    int nb_throws = 10000;
    int total;
    int poundered_total;
    dice_by_tree my_dice(atoi(argv[1]), atoi(argv[2]));
    int results[atoi(argv[2])];
    int totalabove = 0;
    int totalbellow = 0;

    srand (time(NULL));

    if (argc <= 2)
    {
        cout << "argv: [dice from size, dice to size]";
        return 0;
    }

    if (atoi(argv[1]) <= 1)
    {
        cout << "dice from size must be >= 2";
        return 0;
    }

    for(cnt=0; cnt <= atoi(argv[2]); cnt++)
    {
        results[cnt] = 0;
    }

    for(cnt=0; cnt < nb_throws; cnt++)
    {
        results[my_dice.throwit()-1]++;
    }

    total = 0;
    poundered_total = 0;
    for(cnt=0; cnt < atoi(argv[2]); cnt++)
    {
        total += results[cnt];
        poundered_total += results[cnt] * (cnt + 1);
        (results[cnt] > nb_throws/atoi(argv[2]) ? totalabove++ : (results[cnt] < nb_throws/atoi(argv[2]) ? totalbellow++ : 0));
        cout << to_string(cnt + 1) + ":" + to_string(results[cnt]) + (results[cnt] > nb_throws/atoi(argv[2]) ? "+" : (results[cnt] < nb_throws/atoi(argv[2]) ? "-" : "=")) + " | ";
    }

    cout << " TOT: " + to_string(total) + " SAVG: " + to_string(total/atoi(argv[2])) + " PAVG: " + to_string(poundered_total/nb_throws) + " ABV: " + to_string(totalabove) + " BLW: " + to_string(totalbellow) + "\n";

    return 0;
}

