#include <stdlib.h>
#include <iostream>
#include "game.hpp"

using namespace std;

typedef struct BOX_POINTS
{
    int top_right_x, top_right_y;
    int bottom_left_x, bottom_left_y;
} BOX_POINTS;

typedef BOX_POINTS Box;

inline Box set_box_cordinates(int top_right_x, int top_right_y, int bottom_left_x, int bottom_left_y)
{
    Box box;
    box.top_right_x = top_right_x;
    box.top_right_y = top_right_y;
    box.bottom_left_x = bottom_left_x;
    box.bottom_left_y = bottom_left_y;
    return box;
}


class Bridge
{
public:
    int box_height;
    int box_width;
    int line_boldness;
    int user_score = 0;
    int computer_score = 0;
    int toal_games = 0;
    int draw_score = 0;
    Box boxes[9];
    Box lines[4];
    GAME tictactoe;
    Bridge();
    Bridge(int width, int height, int margin);
    int get_clicked_box(int x, int y);
    int *get_draw_position(int box_number);
    int get_box_sign(int position);
    bool user_clicked_box(int position, int sign);
    void reset();  
private:
    int computer_turn();
    int take_decision();
    void update_score(int winner_sign);
    bool find_and_update_score(int sign);
};

Bridge::Bridge(int width, int height, int margin)
{
    box_width = width / 3;
    box_height = height / 3;
    line_boldness = width / 90;

    Box vline_1 = set_box_cordinates(margin+(box_width*1), margin+(box_height*0), line_boldness, height);
    Box vline_2 = set_box_cordinates(margin+(box_width*2), margin+(box_height*0), line_boldness, height);
    Box hline_1 = set_box_cordinates(margin+(box_width*0), margin+(box_height*1), width, line_boldness);
    Box hline_2 = set_box_cordinates(margin+(box_width*0), margin+(box_height*2), width, line_boldness);
    lines[2] = hline_1;
    lines[3] = hline_2;
    lines[0] = vline_1;
    lines[1] = vline_2;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            Box box = set_box_cordinates(
                margin + (box_width * (1 + j)),
                margin + (box_height * i),
                margin + (box_width * j),
                margin + (box_height * (1 + i))
            );
            int index = (i * 3) + j;
            boxes[index] = box;
        }
    }

    tictactoe = GAME();
};

Bridge::Bridge(){};

int Bridge::get_clicked_box(int x, int y)
{
    int len = sizeof(boxes) / sizeof(boxes[0]);
    for (int i = 0; i < len; i++)
    {
        if ((x <= boxes[i].top_right_x && x >= boxes[i].bottom_left_x) && (y >= boxes[i].top_right_y && y <= boxes[i].bottom_left_y))
        {
            return i;
        }
    }
    return -1;
}

void Bridge::reset()
{
    tictactoe.reset();
}

int *Bridge::get_draw_position(int box_number)
{
    static int r[2];
    r[0] = boxes[box_number].bottom_left_x + (boxes[box_number].top_right_x - boxes[box_number].bottom_left_x) / 2;
    r[1] = boxes[box_number].top_right_y + (boxes[box_number].bottom_left_y - boxes[box_number].top_right_y) / 2;
    return r;
}

int Bridge::computer_turn(){
    int computer_decision = tictactoe.take_decision();
    tictactoe.click_box(computer_decision, COMPUTER_SIGN);
    return computer_decision;
}

int Bridge::get_box_sign(int position){
    return tictactoe.box_clicked[position];
}

bool Bridge::user_clicked_box(int position, int sign){
    if(position >= 0 && position < 9){
        bool is_game_over = find_and_update_score(sign);
        if (is_game_over == false){
            bool status = tictactoe.click_box(position, sign);
            if (status == true){
                bool is_game_over = find_and_update_score(sign);
                if (is_game_over == false){
                    computer_turn();
                    find_and_update_score(COMPUTER_SIGN);
                }
            }
            return status;
        }
    }
    return false;
}

void Bridge::update_score(int winner_sign)
{
    if (winner_sign == USER_SIGN){
        user_score += 1;
    }
    else if (winner_sign == COMPUTER_SIGN){
        computer_score += 1;
    }
    else if (winner_sign == 2){
        draw_score += 1;
    }
}

bool Bridge::find_and_update_score(int sign)
{
    if (tictactoe.game_over){
        return true;
    }
    int winner = tictactoe.find_winner(sign);
    if(winner == USER_SIGN){
        update_score(USER_SIGN);
    }
    else if(winner == COMPUTER_SIGN){
        update_score(COMPUTER_SIGN);
    }
    else if(winner == 2){
        update_score(2);
    }

    if (winner == -1){
        return false;
    }

    return true;
}