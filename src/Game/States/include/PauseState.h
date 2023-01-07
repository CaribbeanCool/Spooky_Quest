#pragma once

#include "Enemy.h"
#include "Player.h"
#include "State.h"
#include "Boss.h"

class PauseState : public State {
private:
    Player *player;
    Enemy *enemy;
    ofImage screen;
public:
    PauseState();
    void update();
    void draw();
    void keyPressed(int key);
    void reset();
    string state;
};