#include <thread>
#include <chrono>
#include "snake.h"


Snake::Snake(int widht, int height){
    gameOver = false;
    maxGridWidth = widht/SNAKE_SIZE;
    maxGridHeight = height/SNAKE_SIZE;
    SnakeUnit head;
    head.x = 0;
    head.y = 0;
    head.direction = Direction::SOUTH;
    snakeBody.push_back(head);
    setDotPosition();
};

Snake::Snake(){
};

void Snake::updateSnake(){

    if(gameOver){
        return;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MILISECONDS));

    int snakeSize = snakeBody.size();
    if (snakeSize > 0){
        cout << "---------Update Snake Postion--------" << endl;
        SnakeUnit head = snakeBody.front();
        SnakeUnit newHead = getNewHead(head);

        Collision collision = collisionCheck(newHead);
        if (collision == Collision::WALL || collision == Collision::ITSELF){
            // gameOver
            gameOver = true;
            return;
        }
        else if (collision == Collision::DOT){
            dotPosition.direction = head.direction;
            cout << "Dot postion: x:" << dotPosition.x << " y:" << dotPosition.y << endl;
            snakeBody.insert(snakeBody.begin(), dotPosition);
            score += scoreIncrement;
            setDotPosition();
            // no need to remove tail in this case.
        }
        else{
            snakeBody.insert(snakeBody.begin(), newHead);

            snakeBody.pop_back(); // remove tail
        }

        SnakeUnit temp = snakeBody.front();
        cout << "Head postion: X:" << temp.x << " Y:" << temp.y << endl;
    }
};



SnakeUnit Snake::getNewHead(SnakeUnit unit){
    SnakeUnit newHead;
    newHead.x = unit.x;
    newHead.y = unit.y;
    newHead.direction = unit.direction;
    if (unit.direction == Direction::NORTH){
        newHead.y -= 1;
    }
    else if (unit.direction == Direction::EAST){
        newHead.x += 1;
    }
    else if (unit.direction == Direction::SOUTH){
        newHead.y += 1;
    }
    else if (unit.direction == Direction::WEST){
        newHead.x -= 1;
    }

    return newHead;
}

void Snake::setDotPosition(){
    int x = rand()%maxGridWidth;
    int y = rand()%maxGridHeight;

    dotPosition.x = x;
    dotPosition.y = y;
}

SnakeUnit Snake::getDotPosition(){
    return dotPosition;
}

SnakeUnit Snake::getViewPointPosition(SnakeUnit unit){
    SnakeUnit viewUnit;
    viewUnit.x = SNAKE_SIZE * unit.x;
    viewUnit.y = SNAKE_SIZE * unit.y;
    return viewUnit;
}   


bool Snake::checkWallCollision(SnakeUnit head){
    if (head.x < 0 || head.x > maxGridWidth){
        // Width colision.
        cout << "=======WARNING: Snake Colided with wall: Width=======" << endl;
        return true;
    }
    else if (head.y < 0 || head.y > maxGridHeight){
        // height colision.
        cout << "=======WARNING: Snake Colided with wall: Height=======" << endl;
        return true;
    }
    return false;
}


bool Snake::checkDotCollision(SnakeUnit head){
    if (head.x == dotPosition.x && head.y == dotPosition.y && head.y){
        cout << "======INFO: Snake Colided Dot=======" << endl;
        return true;
    }
    return false;
}

bool Snake::checkItselfCollision(SnakeUnit head){
    for(int i = 0; i < snakeBody.size(); i++){
        if (head.x == snakeBody.at(i).x && head.y == snakeBody.at(i).y){
            return true;
        }
    }
    return false;
}

Collision Snake::collisionCheck(SnakeUnit head){

    if(checkWallCollision(head)){
        return Collision::WALL;
    }
    else if(checkDotCollision(head)){
        // make dot part of the head.
        return Collision::DOT;
    }
    else if(checkItselfCollision(head)){
        return Collision::ITSELF;
    }

    return Collision::NONE;
}


void Snake::changeHeadDirection(Direction direction){
    SnakeUnit temp = snakeBody.front();
    if((temp.direction == Direction::EAST || temp.direction == Direction::WEST) && (direction == Direction::NORTH || direction == Direction::SOUTH)){
        snakeBody.front().direction = direction;
    }
    else if((temp.direction == Direction::NORTH || temp.direction == Direction::SOUTH) && (direction == Direction::WEST || direction == Direction::EAST)){
        snakeBody.front().direction = direction;
    }
}


void Snake::reset(){

}