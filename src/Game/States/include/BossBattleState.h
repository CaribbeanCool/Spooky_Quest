#pragma once

#include "BattleState.h"
#include "Player.h"
#include "Area.h"
#include "Boss.h"

class BossBattleState : public BattleState {
    private: 
        ofImage stage;
        Player *player;
        Boss *boss;
        Move choice = Move::none;
        Outcome outcome = Outcome::draw;
        int bossChoice = 0;
        ofSoundPlayer buttonChange;
        ofSoundPlayer buttonSelect;
        ofImage button1;
        ofImage button2;
        ofImage button3;
        ofImage result1;
        ofImage result2;
        ofImage result3;
        int currentButton;
        int currentPlayerHealth;
        int currentBossHealth;
        int resultTimer;
        bool canInteract;
        int PLAYER_MAX_HP;
    public:
        BossBattleState(Player *player, Area *area);
        void update();
        void draw();
        void startBossBattle(Boss *boss);
        void drawHealthBar();
        void drawOutcome();
        void setBoss(Boss *boss) {this->boss = boss;};
        Boss* getBoss() {return boss;};
        void setStage(ofImage stage) {this-> stage = stage;};
        void keyPressed(int key);
        void reset();
        int bossLives = 1;
        bool bossLastLife = false;

};