#include "BossBattleState.h"

BossBattleState::BossBattleState(Player *player, Area *area) : BattleState(player, area) {
    stage = area->getStage();
    music.load("audio/PBattle.mp3");
    music.setLoop(true);
    music.setVolume(0.15);
    buttonChange.load("audio/ui/beep.mp3");
    buttonChange.setVolume(0.5);
    buttonSelect.load("audio/ui/boop.mp3");
    buttonSelect.setVolume(0.5);
    this->player = player;
    currentButton = 1;
    resultTimer = 0;
    canInteract = true;
    currentPlayerHealth = PLAYER_MAX_HP = player->getHealth();
    button1.load("images/ui/buttons/rock.png");
    button2.load("images/ui/buttons/paper.png");
    button3.load("images/ui/buttons/scissors.png");
    result1.load("images/ui/buttons/rock1.png");
    result2.load("images/ui/buttons/paper1.png");
    result3.load("images/ui/buttons/scissors1.png");
}

void BossBattleState::startBossBattle(Boss *boss) {
    this->boss = boss;
    currentBossHealth = boss->getHealth();
    currentPlayerHealth = player->getHealth();
}

void BossBattleState::update() {
    if (canInteract) {
        if (currentPlayerHealth <= 0) {
            bossLastLife = false;
            setNextState("End");
            setFinished(true);
            player->setHealth(currentPlayerHealth);
            
            return;
        } else if(currentBossHealth<=0 && bossLastLife == false) {
            boss->setHealth(boss->getHealth()* 2);
            bossLastLife = true;
            setNextState("Boss");
            setFinished(true);
            player->setHealth(currentPlayerHealth);
            return;
        } else if(currentBossHealth <=0 && bossLastLife == true) {
            setNextState("Win");
            setFinished(true);
            bossLastLife = false;
            return;
        } else if (getNextState() == "Pause") {
            player->setHealth(currentPlayerHealth);
        }
    }

    player->fightingUpdate();
    boss->fightingUpdate();

    if (choice != Move::none && canInteract) {
        bossChoice = rand() % 3 + 1;
        if ((choice == Move::rock && bossChoice == 2) || (choice == Move::paper && bossChoice == 3) || (choice == Move::scissors && bossChoice == 1)) {
            currentPlayerHealth -= boss->getDmg() * 2.0;
            currentBossHealth -= player->getDmg() / 2.0;
            outcome = Outcome::lose;
        } else if ((choice == Move::rock && bossChoice == 3) || (choice == Move::paper && bossChoice == 1) || (choice == Move::scissors && bossChoice == 2)) {
            currentPlayerHealth -= boss->getDmg() / 2.0;
            currentBossHealth -= player->getDmg() * 2.0;
            outcome = Outcome::win;
        } else {
            currentPlayerHealth -= boss->getDmg();
            currentBossHealth -= player->getDmg();
            outcome = Outcome::draw;
        }
        resultTimer = ofGetFrameRate();
        canInteract = false;
    }
}

void BossBattleState::draw() {
    // render stage
    stage.draw(0, 0, ofGetWidth(), ofGetHeight());

    // render combatant sprites
    player->fightingDraw();
    boss->fightingDraw();

    // render move buttons
    ofSetColor(180, 180, 180);
    if (currentButton == 1)
        ofSetColor(255, 255, 255);
    button1.draw(10 * 4, 84 * 4, 192, 192);

    ofSetColor(180, 180, 180);
    if (currentButton == 2)
        ofSetColor(255, 255, 255);
    button2.draw(56 * 4, 84 * 4, 192, 192);

    ofSetColor(180, 180, 180);
    if (currentButton == 3)
        ofSetColor(255, 255, 255);
    button3.draw(102 * 4, 84 * 4, 192, 192);

    ofSetColor(255, 255, 255);

    drawOutcome();
    drawHealthBar();

    ofSetColor(255, 255, 255);
}

void BossBattleState::drawHealthBar() {
    ofImage healthbar;
    healthbar.load("images/ui/healthbar.png");
    healthbar.draw(64, 64, 192, 192);
    healthbar.draw(384, 64, 192, 192);

    if (bossLastLife == false){ofDrawBitmapString("Boss Phase 1", 28, 100);}
    else if (bossLastLife == true){ofDrawBitmapString("Boss Phase 2", 28, 100);}

    for (int i = 0; i < 3; i++) {
        double playerHealthRatio = (double)currentPlayerHealth / (double)PLAYER_MAX_HP;
        double bossHealthRatio = (double)currentBossHealth / (double)boss->getHealth();
        if (playerHealthRatio < 0)
            playerHealthRatio = 0;
        else if (playerHealthRatio < 0.33)
            ofSetColor(200 - i * 20, 60 - i * 20, 60 - i * 20);
        else if (playerHealthRatio < 0.66)
            ofSetColor(180 - i * 20, 200 - i * 20, 60 - i * 20);
        else if (playerHealthRatio < 0.99 || playerHealthRatio < 2.01)
            ofSetColor(60 - i * 20, 180 - i * 20, 80 - i * 20);
        else
            ofSetColor(ofColor::paleGoldenRod);

        if (playerHealthRatio < 0.99)
            ofDrawRectangle(108, 152 + i * 4, (int)(36 * playerHealthRatio) * 4, 4); // write if statement to check if god mode is on
        else
            ofDrawRectangle(108, 152 + i * 4, (int)(36 * 1.01) * 4, 4);

        if (bossHealthRatio < 0)
            bossHealthRatio = 0;
        else if (bossHealthRatio < 0.33)
            ofSetColor(200 - i * 20, 60 - i * 20, 60 - i * 20);
        else if (bossHealthRatio < 0.66)
            ofSetColor(180 - i * 20, 200 - i * 20, 60 - i * 20);
        else
            ofSetColor(60 - i * 20, 180 - i * 20, 80 - i * 20);

        ofDrawRectangle(428, 152 + i * 4, (int)(36 * bossHealthRatio) * 4, 4);
    }
    ofFill();
}

void BossBattleState::drawOutcome() {
    if (resultTimer > 1) {
        resultTimer--;
        float posY = 60 * 4;
        float pposX = 64 * 4;
        float eposX = 80 * 4;
        float dim = 64;

        switch (outcome) {
            case Outcome::win:
                ofSetColor(100, 255, 100);
                if (choice == Move::rock)
                    result1.draw(pposX, posY, dim, dim);
                if (choice == Move::paper)
                    result2.draw(pposX, posY, dim, dim);
                if (choice == Move::scissors)
                    result3.draw(pposX, posY, dim, dim);
                ofSetColor(255, 100, 100);
                if (bossChoice == 1)
                    result1.draw(eposX, posY, dim, dim);
                if (bossChoice == 2)
                    result2.draw(eposX, posY, dim, dim);
                if (bossChoice == 3)
                    result3.draw(eposX, posY, dim, dim);
                break;
            case Outcome::lose:
                ofSetColor(255, 100, 100);
                if (choice == Move::rock)
                    result1.draw(pposX, posY, dim, dim);
                if (choice == Move::paper)
                    result2.draw(pposX, posY, dim, dim);
                if (choice == Move::scissors)
                    result3.draw(pposX, posY, dim, dim);
                ofSetColor(100, 255, 100);
                if (bossChoice == 1)
                    result1.draw(eposX, posY, dim, dim);
                if (bossChoice == 2)
                    result2.draw(eposX, posY, dim, dim);
                if (bossChoice == 3)
                    result3.draw(eposX, posY, dim, dim);
                break;
            case Outcome::draw:
                ofSetColor(200, 200, 100);
                if (choice == Move::rock)
                    result1.draw(pposX, posY, dim, dim);
                if (choice == Move::paper)
                    result2.draw(pposX, posY, dim, dim);
                if (choice == Move::scissors)
                    result3.draw(pposX, posY, dim, dim);
                if (bossChoice == 1)
                    result1.draw(eposX, posY, dim, dim);
                if (bossChoice == 2)
                    result2.draw(eposX, posY, dim, dim);
                if (bossChoice == 3)
                    result3.draw(eposX, posY, dim, dim);
                break;
        }
        ofSetColor(255, 255, 255);
    }
    if (resultTimer == 1) {
        canInteract = true;
        choice = Move::none;
        resultTimer--;
    }
}

void BossBattleState::keyPressed(int key) {
    if (key == OF_KEY_ESC) {
    setNextState("Pause");
    setFinished(true);
    }
    if (canInteract) {
        if (key == OF_KEY_LEFT || key == 'a') {
            buttonChange.play();
            if (currentButton == 1)
                currentButton = 3;
            else
                currentButton--;
        }
        if (key == OF_KEY_RIGHT || key == 'd') {
            buttonChange.play();
            if (currentButton == 3)
                currentButton = 1;
            else
                currentButton++;
        }
        if (key == OF_KEY_RETURN) {
            buttonSelect.play();
            switch (currentButton) {
                case 2:
                    choice = Move::paper;
                    break;
                case 3:
                    choice = Move::scissors;
                    break;
                default:
                    choice = Move::rock;
                    break;
            }
        }
    }
}

void BossBattleState::reset() {
    setFinished(false);
    setNextState("");
    currentPlayerHealth = player->getHealth();
}