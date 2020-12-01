#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <tuple>

#include <context.hpp>
#include <app.hpp>

using namespace std;

const int width = 640;
const int height = 480; 

class MyApp: public uwe::App {
private:
public:
    MyApp(int width, int height, std::string title);
    ~MyApp();

    void begin() override;
    void update() override;
    void draw() override;

    void key_pressed(uwe::Scancode scancode, bool repeat) override;

    void mouse_pressed(int x, int y, uwe::Button button) override;
    void mouse_released(int x, int y, uwe::Button button) override;
    void mouse_moved(int x, int y) override;
};

MyApp::MyApp(int width, int height, std::string title) {
    init(width, height, title);
}

MyApp::~MyApp() {

}

void MyApp::begin() {
    
}

void MyApp::update() {

}

void MyApp::key_pressed(uwe::Scancode scancode, bool repeat) {
    switch (scancode) {
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

void MyApp::draw() {
    clear(uwe::Colour::black());
}

int main(int argc, char *argv[]) {
    uwe::App* app = new MyApp{width, height, "Assignment"};

    app->run();

    return 0;
}