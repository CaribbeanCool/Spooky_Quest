#pragma once

#include "Animation.h"
#include "Entity.h"

class Friend : public Entity {
private:
    Direction direction;
    int speed = 4;
    bool walking = false;
    int renderX = 1000;
    int renderY = 1000;
    Animation *walkUp;
    Animation *walkDown;
    Animation *walkLeft;
    Animation *walkRight;
    string id;
    int moveTimer;
    string entityName;
    ofImage sprite;

public:
    Friend(string id, string entityName, int ox, int oy);
    ~Friend();
    int getOX() { return ox; };
    int getOY() { return oy; };
    void setRenderX(int x) { renderX = x; };
    void setRenderY(int y) { renderY = y; };
    void inOverworldUpdate();
    void fightingUpdate();
    void inOverworldDraw();
    void reset();
    string getId() { return id; };
    ofImage getSprite() { return overworldSprite; };
};