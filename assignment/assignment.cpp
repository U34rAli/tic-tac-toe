#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <tuple>

#include <context.hpp>
#include <app.hpp>
#include "bridge.hpp"

using namespace std;

const int width = 640;
const int height = 480;
const int font_size = 50;

const int MARGIN = 50; //Margin between windows and game.
const int FONT_MARGIN_X = 20;
const int FONT_MARGIN_Y = 40;

class MyApp : public uwe::App
{
private:
    uwe::Font font15_;
    uwe::Font text_font;
    Bridge game_bridge;

public:
    MyApp(int width, int height, std::string title);
    ~MyApp();

    bool is_computer_turn = false;
    void begin() override;
    void update() override;
    void draw() override;
    void draw_signs();
    void clear_screen();
    void draw_board();
    void draw_sign(int position, string sign);
    void key_pressed(uwe::Scancode scancode, bool repeat) override;
    void mouse_pressed(int x, int y, uwe::Button button) override;
    void mouse_released(int x, int y, uwe::Button button) override;
    void mouse_moved(int x, int y) override;
};

MyApp::MyApp(int width, int height, std::string title)
{
    init(width, height, title);
    game_bridge = Bridge(width-MARGIN*2, height-MARGIN*2, MARGIN);
}

MyApp::~MyApp()
{
}

void MyApp::begin()
{
    font15_ = create_font("./assets/fonts/FreeSans.ttf", font_size, uwe::Colour::white());
    text_font = create_font("./assets/fonts/FreeSans.ttf", 25, uwe::Colour::white());
}

void MyApp::update(){}

void MyApp::draw_board(){
    for(int i = 0; i < 4; i++){
        int x = game_bridge.lines[i].top_right_x;
        int y = game_bridge.lines[i].top_right_y;
        int width = game_bridge.lines[i].bottom_left_x;
        int height = game_bridge.lines[i].bottom_left_y;
        draw_rect_fill(x,y,width,height);
    }

}

void MyApp::draw_sign(int position, string sign){
    int *data_xy = game_bridge.get_draw_position(position);
    draw_font(font15_, sign, data_xy[0] - FONT_MARGIN_X, data_xy[1] - FONT_MARGIN_Y);
}

void MyApp::draw_signs(){
    for (int i = 0; i < 9; i++)
    {
        if (game_bridge.get_box_sign(i) == 0)
        {
            draw_sign(i, "0");
        }
        else if (game_bridge.get_box_sign(i) == 1)
        {
            draw_sign(i, "X");
        }
    }
}

void MyApp::key_pressed(uwe::Scancode scancode, bool repeat)
{
    switch (scancode)
    {
    case uwe::Scancode::RETURN:
    {
        game_bridge.reset();
    }
    default:
    {
        // nothing see here
    }
    }
}

void MyApp::mouse_pressed(int x, int y, uwe::Button button)
{
    int box_number = game_bridge.get_clicked_box(x, y);
    bool status = game_bridge.user_clicked_box(box_number, USER_SIGN);
    printf("Box clicked: %d, Status: %d\n", box_number, status);
}


void MyApp::mouse_released(int x, int y, uwe::Button button)
{
}

void MyApp::mouse_moved(int x, int y)
{
}

void MyApp::clear_screen(){
    clear(uwe::Colour::black());
    set_draw_color(uwe::Colour::green());
}

void MyApp::draw()
{
    clear_screen();
    draw_board();
    draw_signs();

    std::string score = "You: " + std::to_string(game_bridge.user_score);
    std::string computer = "Computer: " + std::to_string(game_bridge.computer_score);
    std::string draw = "Draw: " + std::to_string(game_bridge.draw_score);
    draw_font(text_font, score, 50, 440);
    draw_font(text_font, computer, 150, 440);
    draw_font(text_font, draw, width-150, 440);
    draw_font(text_font, "Press Enter to Play.", width/3, 1);
}

int main(int argc, char *argv[])
{
    uwe::App *app = new MyApp{width, height, "Assignment: TIC TAC TOE"};
    app->run();

    return 0;
}