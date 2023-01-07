#pragma once

#include "Area.h"
#include "Enemy.h"
#include "OverworldCamera.h"
#include "Player.h"
#include "State.h"
#include "rock.h"
#include "Boss.h"

#include "Friend.h"
#include "Pet.h"

class OverworldState : public State {
private:
    ofImage overworldImage;
    Player *player;
    OverworldCamera *camera;
    Area *area;
    std::vector<Enemy *> enemies;
    Enemy *enemy;
    Rock *rock;
    Friend *friends;
    Pet *pets;
    std::vector<Boss *> bosses;
    Boss *boss;
public:
    OverworldState(Player *player, Area *area);
    Player *getPlayer() { return player; };
    void setEnemy(Enemy *enemy) { this->enemy = enemy; };
    void setBoss(Boss *boss) { this->boss = boss; };
    Enemy *getEnemy() { return enemy; };
    void loadArea(Area *Area);
    Area *getArea() { return area; };
    void update();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);
    void reset();
    Boss *getBoss() { return boss; };
    Rock *getRock() {return rock;};
    Friend *getFriend() {return friends;};
    Pet *getPet() {return pets;};
    int drainCounter = 0;
    int friendCounter = 0;
    int petCounter = 0;
    int petMsg2 = 0;
    bool friendCollide = false;
    bool friendMsg = false;
    bool petCollide = false;
    bool petMsg = false;
    bool petInteract = false;
    bool god = false;
    bool playerSprint = false;
};  