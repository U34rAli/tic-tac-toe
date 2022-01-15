#include <iostream>

const int USER_SIGN = 1;
const int COMPUTER_SIGN = 0;

class GAME
{
public:
    int box_clicked[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
    int winner = -1;
    bool game_over = false;
    bool draw = false;
    bool is_computer_turn = false;
    bool game_in_process = false;
    GAME();
    bool click_box(int position, int sign);
    int take_decision();
    bool row_check(int data_array[3][3], int sign);
    bool column_check(int data_array[3][3], int sign);
    bool diagonal_check(int data_array[3][3], int sign);
    bool draw_check();
    int find_winner(int sign);
    void reset();
};

GAME::GAME(){};

int GAME::take_decision()
{
    while (!game_over)
    {
        int box_number = rand() % 9;
        if (box_clicked[box_number] == -1)
        {
            return box_number;
        }
    }
    return -1;
}

void GAME::reset()
{
    for (int i = 0; i < 9; i++)
    {
        box_clicked[i] = -1;
    }
    winner = -1;
    game_over = false;
}

bool GAME::column_check(int data_array[3][3], int user_sign)
{
    for (int i = 0; i < 3; i++)
    {
        if (data_array[0][i] == user_sign && data_array[1][i] == user_sign && data_array[2][i] == user_sign)
        {
            return true;
        }
    }
    return false;
}

bool GAME::row_check(int data_array[3][3], int user_sign)
{
    for (int i = 0; i < 3; i++)
    {
        if (data_array[i][0] == user_sign && data_array[i][1] == user_sign && data_array[i][2] == user_sign)
        {
            return true;
        }
    }
    return false;
}

bool GAME::diagonal_check(int data_array[3][3], int user_sign)
{
    // digonal check
    if (data_array[0][0] == user_sign && data_array[1][1] == user_sign && data_array[2][2] == user_sign)
    {
        return true;
    }

    if (data_array[0][2] == user_sign && data_array[1][1] == user_sign && data_array[2][0] == user_sign)
    {
        return true;
    }

    return false;
}

int GAME::find_winner(int sign)
{
    int data_array[3][3] = {
        {box_clicked[0], box_clicked[1], box_clicked[2]},
        {box_clicked[3], box_clicked[4], box_clicked[5]},
        {box_clicked[6], box_clicked[7], box_clicked[8]}};

    if (column_check(data_array, sign) || row_check(data_array, sign) || diagonal_check(data_array, sign))
    {
        game_over = true;
        winner = sign;
        return winner;
    }
    else if (draw_check()){
        game_over = true;
        return 2;
    }
    return -1;
}

bool GAME::draw_check()
{
    for (int i = 0; i < 9; i++)
    {
        if (box_clicked[i] == -1)
        {
            return false;
        }
    }
    game_over = true;
    return true;
}

bool GAME::click_box(int position, int sign)
{
    if (box_clicked[position] == -1)
    {
        box_clicked[position] = sign;
        return true;
    }
    return false;
}
