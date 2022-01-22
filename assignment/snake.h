#include <iostream>
#include <vector>


using namespace std;

const int SNAKE_SIZE = 20;
const int SLEEP_MILISECONDS = 250;


// Direction for each snake unit
enum Direction 
{   
    NORTH,
    EAST,
    SOUTH,
    WEST,
    CENTER,
};


// Collision enum
enum Collision 
{   
    WALL,
    ITSELF,
    DOT,
    NONE,
};


struct SnakeUnit
{
    int x = 0; // x position in grid
    int y = 0; // y position in grid
    Direction direction = EAST; // 0: North, 1: East, 3: South, 4: West
};


class Snake{
    public:
        vector<SnakeUnit> snakeBody;
        int scoreIncrement = 1; // Score increment per dot.
        int score = 0;
        bool gameOver = true; //
        int maxGridWidth = 0; //
        int maxGridHeight = 0; //
        Snake(int width, int height);
        Snake();
        bool start();
        void updateSnake();
        int getTotalScore();
        SnakeUnit getDotPosition();
        SnakeUnit getViewPointPosition(SnakeUnit unit);
        void changeHeadDirection(Direction direction);
        bool end();
        void reset();
    private:
        Collision collisionCheck(SnakeUnit head);
        bool checkWallCollision(SnakeUnit head);
        bool checkItselfCollision(SnakeUnit head);
        bool checkDotCollision(SnakeUnit head);
        void moveSnakeTrunk();
        void setDotPosition();
        SnakeUnit getNewHead(SnakeUnit unit);
        SnakeUnit dotPosition;
};