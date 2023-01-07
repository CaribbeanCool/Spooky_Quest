#pragma once
#include "Animation.h"
#include "Entity.h"

class Rock : public Entity {
private:  
    Direction direction;
    int speed = 8;
    int renderX = 1000;
    int renderY = 1000;
    Animation *stillRock;
    string id;
    int moveTimer;
    string entityName;
    ofImage sprite;
    public:
    Rock(string id, string entityName, int ox, int oy);
    ~Rock();
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