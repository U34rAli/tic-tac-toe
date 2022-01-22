#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <tuple>

#include <context.hpp>
#include <app.hpp>
#include "snake.cpp"


using namespace std;

const int width = 640;
const int height = 480;



class MyApp: public uwe::App {
private:
    uwe::Font font15_;
    int width_;
    int height_;
    Snake snake;
    bool startGame = false;
public:
    MyApp(int width, int height, std::string title);
    ~MyApp();

    void begin() override;
    void update() override;
    void draw() override;

    void game_control();

    void key_pressed(uwe::Scancode scancode, bool repeat) override;

    void mouse_pressed(int x, int y, uwe::Button button) override;
    void mouse_released(int x, int y, uwe::Button button) override;
    void mouse_moved(int x, int y) override;
    void draw_snake();
};

MyApp::MyApp(int width, int height, std::string title)
{
    init(width, height, title);
    snake = Snake(width, height);
}

MyApp::~MyApp() {

}

void MyApp::begin() {
    font15_ = create_font("./assets/fonts/FreeSans.ttf", 30, uwe::Colour::white());
}

void MyApp::update() {
    snake.updateSnake();
}

void MyApp::key_pressed(uwe::Scancode scancode, bool repeat) {

    switch (scancode) {
        case uwe::Scancode::RETURN: {
            startGame = true;
            snake = Snake(width, height);
            break;
        }
        case uwe::Scancode::LEFT: {
            snake.changeHeadDirection(Direction::WEST);
            break;
        }
        case uwe::Scancode::RIGHT: {
            snake.changeHeadDirection(Direction::EAST);
            break;
        }
        case uwe::Scancode::UP: {
            snake.changeHeadDirection(Direction::NORTH);
            break;
        }
        case uwe::Scancode::DOWN: {
            snake.changeHeadDirection(Direction::SOUTH);
            break;
        }
        default: {
            // nothing see here
        }
    }
}

void MyApp::mouse_pressed(int x, int y, uwe::Button button) {

}
    
void MyApp::mouse_released(int x, int y, uwe::Button button) {
}
    
void MyApp::mouse_moved(int x, int y) {
}


void MyApp:: game_control(){
}

void MyApp:: draw_snake(){

    cout << "Snake size: " << snake.snakeBody.size() << endl;
    for(int i = 0; i < snake.snakeBody.size(); i++){
        if(i == 0){
            set_draw_color(uwe::Colour::red());
        }
        else{
            set_draw_color(uwe::Colour::white());
        }

        SnakeUnit actual = snake.snakeBody.at(i);
        SnakeUnit unit = snake.getViewPointPosition(actual);
        draw_rect_fill(unit.x, unit.y, SNAKE_SIZE, SNAKE_SIZE);
        cout << " X: " << actual.x << " Y: " << actual.y << endl;
    }

    set_draw_color(uwe::Colour::green());
    // draw dot  
    SnakeUnit dot = snake.getViewPointPosition(snake.getDotPosition());
    draw_rect_fill(dot.x, dot.y, SNAKE_SIZE, SNAKE_SIZE);

}

void MyApp::draw() {


    clear(uwe::Colour::black());
    set_draw_color(uwe::Colour::white());

    if(!startGame){
        draw_font(font15_, "Press Enter To Play", 100, 150);
    }

    else if(snake.gameOver){
        draw_font(font15_, "Game Over", 100, 100);
        draw_font(font15_, "Press Enter To Play Again", 100, 150);
        std::string score = "Score: " + std::to_string(snake.score);
        draw_font(font15_, score, 100, 200);
    }

    else{
        draw_snake();
    }

}

int main(int argc, char *argv[]) {
    uwe::App* app = new MyApp{width, height, "Snake game"};

    app->run();

    return 0;
}


