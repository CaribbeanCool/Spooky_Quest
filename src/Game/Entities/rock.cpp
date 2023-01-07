#include "rock.h"

Rock::Rock(string id, string entityName, int ox, int oy) : Entity(ox, oy, 50, 64, 420, 220, 97, 125, 0, 0) {
    this->id = id;
    this->entityName = entityName;
    moveTimer = 60;
    vector<ofImage> still;
    ofImage sprite;
    ofImage temp;

    sprite.load("images/entities/enemy/Rocks.png");

    int w = 48, h = 48;

    temp.cropFrom(sprite, 96 + w, 16 + h, w - 32, h-33);
    still.push_back(temp);
    stillRock = new Animation(3, still);
}

void Rock::inOverworldUpdate() {
    overworldSprite = stillRock->getCurrentFrame();
}

void Rock::inOverworldDraw() {
    // uncomment these if you want the coordinates of the enemies in the current area
    // ofDrawBitmapString("rX:" + to_string(renderX), 100 + 125 * ((stoi(id) % 10) - 1), 100);
    // ofDrawBitmapString("rY:" + to_string(renderY), 100 + 125 * ((stoi(id) % 10) - 1), 120);
    // ofDrawBitmapString("ow:" + to_string(ox), 100 + 125 * ((stoi(id) % 10) - 1), 140);
    // ofDrawBitmapString("oy:" + to_string(oy), 100 + 125 * ((stoi(id) % 10) - 1), 160);
    overworldSprite.draw(renderX, renderY, ow, oh);
}

void Rock::fightingUpdate() {
}

void Rock::reset() {
}

Rock::~Rock() {
    delete stillRock;
}