#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <tuple>
#include <chrono>
#include <thread>

#include <context.hpp>
#include <app.hpp>
#include <tictactoe.hpp>

using namespace std;

const int width = 640;
const int height = 480;
const int font_size = 60;
const int USER_SIGN = 1;     // 1 == X;
const int COMPUTER_SIGN = 0; // 0 == 0;
const int MARGIN_X = 20;
const int MARGIN_Y = 40;


class MyApp : public uwe::App
{
private:
    uwe::Font font15_;
    TICTACTOE tictactoe;
    bool press_enter = false;

public:
    MyApp(int width, int height, std::string title);
    ~MyApp();

    void begin() override;
    void update() override;
    void draw() override;
    void draw_board();
    void draw_signs();
    void draw_sign(int position, string sign);

    void key_pressed(uwe::Scancode scancode, bool repeat) override;

    void mouse_pressed(int x, int y, uwe::Button button) override;
    void mouse_released(int x, int y, uwe::Button button) override;
    void mouse_moved(int x, int y) override;
};

MyApp::MyApp(int width, int height, std::string title)
{
    init(width, height, title);
    tictactoe = TICTACTOE(width, height);
}

MyApp::~MyApp()
{
}

void MyApp::begin()
{
#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
    font15_ = create_font("./assets/fonts/FreeSans.ttf", font_size, uwe::Colour::white());
#else
    font15_ = create_font("../assets/fonts/FreeSans.ttf", font_size, uwe::Colour::white());
#endif
}

void MyApp::update(){}

void MyApp::draw_board(){
    // Draw vertical lines
    draw_rect_fill(tictactoe.box_width, 0, tictactoe.line_boldness, height);
    draw_rect_fill(tictactoe.box_width * 2, 0, tictactoe.line_boldness, height);
    // Draw horizontal lines
    draw_rect_fill(0, tictactoe.box_height, width, tictactoe.line_boldness);
    draw_rect_fill(0, tictactoe.box_height * 2, width, tictactoe.line_boldness);
}

void MyApp::draw_signs(){
    int len = sizeof(tictactoe.boxes) / sizeof(tictactoe.boxes[0]);
    for (int i = 0; i < len; i++)
    {
        if (tictactoe.box_clicked[i] == 0)
        {
            draw_sign(i, "0");
        }
        else if (tictactoe.box_clicked[i] == 1)
        {
            draw_sign(i, "X");
        }
    }
}

void MyApp::draw_sign(int position, string sign){
    int *data_xy = tictactoe.get_draw_position(position);
    draw_font(font15_, sign, data_xy[0] - MARGIN_X, data_xy[1] - MARGIN_Y);
}

void MyApp::key_pressed(uwe::Scancode scancode, bool repeat)
{
    switch (scancode)
    {
    case uwe::Scancode::RETURN:
    {
        press_enter = true;
        if (tictactoe.game_over)
        {
            tictactoe.reset();
        }
    }
    default:
    {
        // nothing see here
    }
    }
}

void MyApp::mouse_pressed(int x, int y, uwe::Button button)
{
    printf("Mouse Pressed. X: %d, Y: %d \n", x, y);
    int box_number = tictactoe.get_clicked_box(x, y);
    printf("Box number: %d \n", box_number);

    if (press_enter && tictactoe.un_filled_boxes > 0)
    {
        if (tictactoe.box_clicked[box_number] == -1)
        {
            tictactoe.box_clicked[box_number] = USER_SIGN;
            tictactoe.un_filled_boxes -= 1;
            int winner = tictactoe.find_winner(USER_SIGN);

            if (winner != -1)
            {
                return;
            }
            if (tictactoe.un_filled_boxes <= 0)
            {
                return;
            }

            int computer_decision = tictactoe.take_decision();
            printf("Computer decision: %d \n", computer_decision);
            if (computer_decision != -1)
            {
                tictactoe.box_clicked[computer_decision] = COMPUTER_SIGN;
                tictactoe.un_filled_boxes -= 1;
                int winner = tictactoe.find_winner(COMPUTER_SIGN);
                if (winner != -1)
                {
                    return;
                }
            }
        }
    }
}

void MyApp::mouse_released(int x, int y, uwe::Button button)
{
}

void MyApp::mouse_moved(int x, int y)
{
}

void MyApp::draw()
{
    clear(uwe::Colour::black());
    set_draw_color(uwe::Colour::red());

    if (press_enter == false)
    {
        draw_font(font15_, "Press Enter", 150, 150);
    }
    else if (tictactoe.un_filled_boxes == 0 or tictactoe.winner != -1)
    {
        if (tictactoe.winner == USER_SIGN)
        {
            tictactoe.score += 1;
            draw_font(font15_, "You Won", 180, 20);
        }
        else if (tictactoe.winner == COMPUTER_SIGN)
        {
            draw_font(font15_, "You Lose", 180, 20);
        }
        else
        {
            draw_font(font15_, "Draw", 200, 20);
        }

        draw_font(font15_, "Press Enter", 150, 150);
        tictactoe.games_count += 1;
        tictactoe.game_over = true;
    }
    else
    {
        draw_board();
        draw_signs();
    }
}

int main(int argc, char *argv[])
{
    uwe::App *app = new MyApp{width, height, "Assignment"};
    app->run();

    return 0;
}