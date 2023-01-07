#include "Friend.h"

Friend::Friend(string id, string entityName, int ox, int oy) : Entity(ox, oy, 50, 64, 420, 220, 97, 125, 0, 0) {
    this->id = id;
    this->entityName = entityName;
    moveTimer = 60;
    vector<ofImage> downFrames;
    vector<ofImage> upFrames;
    vector<ofImage> leftFrames;
    vector<ofImage> rightFrames;
    ofImage sprite;
    ofImage temp;

    sprite.load("images/entities/friend.png");

    int w = 48, h = 48;
    int x = 72, y = 94;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            temp.cropFrom(sprite,  218 + x * i, 6 + y * j, w + 8, h + 12);
            if (j == 0)
                downFrames.push_back(temp);
            else if (j == 1)
                leftFrames.push_back(temp);
            else if (j == 2)
                rightFrames.push_back(temp);
            else
                upFrames.push_back(temp);
        }
    }
    walkDown = new Animation(3, downFrames);
    walkUp = new Animation(3, upFrames);
    walkLeft = new Animation(3, leftFrames);
    walkRight = new Animation(3, rightFrames);

    direction = Direction::right;
}

void Friend::inOverworldUpdate() {
    if (moveTimer == 60) {
        walking = true;
        switch (direction) {
        case Direction::left:
            direction = Direction::up;
            break;
        case Direction::right:
            direction = Direction::upLeft;
            break;
        case Direction::up:
            direction = Direction::right;
            break;
        case Direction::down:
            direction = Direction::left;
            break;
        case Direction::downLeft:
            direction = Direction::right;
            break;
        case Direction::upLeft:
            direction = Direction::downLeft;
            break;
        }
    }
    if (moveTimer == 0) {
        walking = false;
    }
    moveTimer--;
    if (moveTimer == 0)
        moveTimer = 60;

    if (walking) {
        switch (direction) {
        case Direction::left:
            this->ox -= speed;
            walkLeft->update();
            overworldSprite = walkLeft->getCurrentFrame();
            break;
        case Direction::right:
            this->ox += 2 * speed;
            walkRight->update();
            overworldSprite = walkRight->getCurrentFrame();
            break;
        case Direction::up:
            this->oy -= speed;
            walkUp->update();
            overworldSprite = walkUp->getCurrentFrame();
            break;
        case Direction::down:
            this->oy += speed;
            walkDown->update();
            overworldSprite = walkDown->getCurrentFrame();
            break;
        case Direction::downLeft:
            this->ox -= speed;
            this->oy -= speed;
            walkLeft->update();
            overworldSprite = walkDown->getCurrentFrame();
            overworldSprite = walkLeft->getCurrentFrame();
            break;
        case Direction::upLeft:
            this->ox -= speed;
            this->oy += speed;
            walkUp->update();
            walkLeft->update();
            overworldSprite = walkUp->getCurrentFrame();
            overworldSprite = walkLeft->getCurrentFrame();
            break;
        }
    } else {
        switch (direction) {
        case Direction::left:
            overworldSprite = walkLeft->getCurrentFrame();
            break;
        case Direction::right:
            overworldSprite = walkRight->getCurrentFrame();
            break;
        case Direction::up:
            overworldSprite = walkUp->getCurrentFrame();
            break;
        case Direction::down:
            overworldSprite = walkDown->getCurrentFrame();
            break;
        case Direction::downLeft:
            overworldSprite = walkDown->getCurrentFrame();
            overworldSprite = walkLeft->getCurrentFrame();
            break;
        case Direction::upLeft:
            overworldSprite = walkUp->getCurrentFrame();
            overworldSprite = walkLeft->getCurrentFrame();
            break;
        }
    }
}

void Friend::inOverworldDraw() {
    // uncomment these if you want the coordinates of the enemies in the current area
    // ofDrawBitmapString("rX:" + to_string(renderX), 100 + 125 * ((stoi(id) % 10) - 1), 100);
    // ofDrawBitmapString("rY:" + to_string(renderY), 100 + 125 * ((stoi(id) % 10) - 1), 120);
    // ofDrawBitmapString("ow:" + to_string(ox), 100 + 125 * ((stoi(id) % 10) - 1), 140);
    // ofDrawBitmapString("oy:" + to_string(oy), 100 + 125 * ((stoi(id) % 10) - 1), 160);
    overworldSprite.draw(renderX, renderY, ow, oh);
}

void Friend::fightingUpdate() {
}

void Friend::reset() {
}

Friend::~Friend() {
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
}