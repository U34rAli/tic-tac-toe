#include <iostream>

const int USER_SIGN = 1;
const int COMPUTER_SIGN = 0; // 0 == 0;
typedef struct SDL_Box
{
    int up_right_x, up_right_y;
    int bottom_left_x, bottom_left_y;
    bool new_click = false;
} SDL_Box;

typedef SDL_Box Box;

inline Box make_box(int up_right_x, int up_right_y, int bottom_left_x, int bottom_left_y)
{
    Box box;
    box.up_right_x = up_right_x;
    box.up_right_y = up_right_y;
    box.bottom_left_x = bottom_left_x;
    box.bottom_left_y = bottom_left_y;
    return box;
}

class TICTACTOE
{
public:
    int box_x_y[3][3];
    int box_height;
    int box_width;
    int line_boldness;
    int box_clicked[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
    int un_filled_boxes = 9;
    int winner = -1;
    bool game_over = false;
    int score =0;
    int games_count = 0;
    int draw_count = 0;
    bool is_computer_turn = false;
    Box boxes[9];
    TICTACTOE(int width, int height);
    TICTACTOE();
    int get_clicked_box(int x, int y);
    int *get_draw_position(int box_number);
    int take_decision();
    int find_winner(int user_sign);
    void reset();
    void draw_check();
    bool click_box(int position, int sign);
    void update_score();
};

TICTACTOE::TICTACTOE(int width, int height)
{
    box_width = width / 3;
    box_height = height / 3;
    line_boldness = width / 90;

    Box row1_box1 = make_box(box_width, 0, 0, box_height);
    Box row1_box2 = make_box(box_width * 2, 0, box_width, box_height);
    Box row1_box3 = make_box(box_width * 3, 0, box_width * 2, box_height);
    boxes[0] = row1_box1;
    boxes[1] = row1_box2;
    boxes[2] = row1_box3;

    Box row2_box1 = make_box(box_width, box_height, 0, box_height * 2);
    Box row2_box2 = make_box(box_width * 2, box_height, box_width, box_height * 2);
    Box row2_box3 = make_box(box_width * 3, box_height, box_width * 2, box_height * 2);
    boxes[3] = row2_box1;
    boxes[4] = row2_box2;
    boxes[5] = row2_box3;

    Box row3_box1 = make_box(box_width, box_height * 2, 0, box_height * 3);
    Box row3_box2 = make_box(box_width * 2, box_height * 2, box_width, box_height * 3);
    Box row3_box3 = make_box(box_width * 3, box_height * 2, box_width * 2, box_height * 3);
    boxes[6] = row3_box1;
    boxes[7] = row3_box2;
    boxes[8] = row3_box3;
};

TICTACTOE::TICTACTOE(){};

int TICTACTOE::get_clicked_box(int x, int y)
{
    int len = sizeof(boxes) / sizeof(boxes[0]);
    for (int i = 0; i < len; i++)
    {
        if ((x <= boxes[i].up_right_x && x >= boxes[i].bottom_left_x) && (y >= boxes[i].up_right_y && y <= boxes[i].bottom_left_y))
        {
            return i;
        }
    }
    return -1;
}

int TICTACTOE::take_decision()
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

void TICTACTOE::reset()
{
    for (int i = 0; i < 9; i++)
    {
        box_clicked[i] = -1;
    }
    un_filled_boxes = 9;
    winner = -1;
    games_count += 1;
    game_over = false;
}

int TICTACTOE::find_winner(int user_sign)
{
    int data_array[3][3] = {
        {box_clicked[0], box_clicked[1], box_clicked[2]},
        {box_clicked[3], box_clicked[4], box_clicked[5]},
        {box_clicked[6], box_clicked[7], box_clicked[8]}};
    // column check
    for (int i = 0; i < 3; i++)
    {
        if (data_array[0][i] == user_sign && data_array[1][i] == user_sign && data_array[2][i] == user_sign)
        {
            winner = user_sign;
            printf("winner: %d\n", user_sign);
            update_score();
            return user_sign;
        }
    }
    // row check
    for (int i = 0; i < 3; i++)
    {
        if (data_array[i][0] == user_sign && data_array[i][1] == user_sign && data_array[i][2] == user_sign)
        {
            winner = user_sign;
            printf("winner: %d\n", user_sign);
            update_score();
            return user_sign;
        }
    }
    // digonal check
    if (data_array[0][0] == user_sign && data_array[1][1] == user_sign && data_array[2][2] == user_sign)
    {
        winner = user_sign;
        printf("winner: %d\n", user_sign);
        return user_sign;
    }

    if (data_array[0][2] == user_sign && data_array[1][1] == user_sign && data_array[2][0] == user_sign)
    {
        winner = user_sign;
        printf("winner: %d\n", user_sign);
        update_score();
        return user_sign;
    }

    draw_check();
    return -1;
}


void TICTACTOE::update_score()
{
    printf("score: %d\n",score);
    if (winner == USER_SIGN){
        score += 1;
    }
    game_over = true;
}


void TICTACTOE::draw_check()
{
    for(int i = 0; i < 9; i++){
        if (box_clicked[i] == -1){
            return;
        }
    }
    draw_count += 1;
    game_over = true;
}

bool TICTACTOE::click_box(int position, int sign)
{
    if (box_clicked[position] == -1){
        box_clicked[position] = sign;
        return true;
    }
    return false;
}

int *TICTACTOE::get_draw_position(int box_number)
{
    static int r[2];
    r[0] = boxes[box_number].bottom_left_x + (boxes[box_number].up_right_x - boxes[box_number].bottom_left_x) / 2;
    r[1] = boxes[box_number].up_right_y + (boxes[box_number].bottom_left_y - boxes[box_number].up_right_y) / 2;
    return r;
}
