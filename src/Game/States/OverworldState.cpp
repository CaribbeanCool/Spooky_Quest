#include "OverworldState.h"

OverworldState::OverworldState(Player *player, Area *area) {
    this->player = player;
    camera = new OverworldCamera(player);
    loadArea(area);
}

void OverworldState::loadArea(Area *area) {
    this->area = area;
    overworldImage = area->getImage();
    music = area->getMusic();
    music.setVolume(0.15);
    music.setLoop(true);
    player->setOX(area->getEntrancePos().x);
    player->setOY(area->getEntrancePos().y);
}

void OverworldState::update() {
    player->inOverworldUpdate();
    for (unsigned int i = 0; i < area->getEnemies().size(); i++) {
        if (!area->getEnemies().at(i)->isDead()) {
            area->getEnemies().at(i)->inOverworldUpdate();
            if (player->collides(area->getEnemies().at(i))) {
                setEnemy(area->getEnemies().at(i));
                setNextState("Battle");
                setFinished(true);
                break;
            }
        }
    }

    if (area->getRemainingEnemies() == 0 || isSpawned() == true) {
        for (unsigned int i = 0; i < area->getBosses().size(); i++) {
            if (!area->getBosses().at(i)->isDead()) {
                area->getBosses().at(i)->inOverworldUpdate();
                if (player->collides(area->getBosses().at(i))) {
                    setBoss(area->getBosses().at(i));
                    setNextState("Boss");
                    setSpawnBoss(false);
                    setFinished(true);
                    break;
                }
            }
        }
    }

    else if (area->getRemainingEnemies() > 0 && isSpawned() == true) {
        for (unsigned int i = 0; i < area->getBosses().size(); i++) {
            if (!area->getBosses().at(i)->isDead()) {
                area->getBosses().at(i)->inOverworldUpdate();
                if (player->collides(area->getBosses().at(i))) {
                    setBoss(area->getBosses().at(i));
                    setNextState("Boss");
                    setFinished(true);
                    setSpawnBoss(false);
                    break;
                }
            }
        }
}

    for (unsigned int i = 0; i < area->getRocks().size(); i++) {
            area->getRocks().at(i)->inOverworldUpdate();
            if (player->collides(area->getRocks().at(i))){
                if(player->direction == Direction::left){
                    player->setOX(player->getOX()+player->speed);
                }
                else if(player->direction == Direction::right){
                    player->setOX(player->getOX()-player->speed);
                }
                else if(player->direction == Direction::up){
                    player->setOY(player->getOY()+player->speed);
                }
                else if(player->direction == Direction::down){
                    player->setOY(player->getOY()-player->speed);
                }
                break;
            }
        
    }

    for (unsigned int i = 0; i < area->getFriends().size(); i++) {
        area->getFriends().at(i)->inOverworldUpdate();
        if (player->collides(area->getFriends().at(i))) {
            friendCollide = true;
            break;
        }
        else {
            friendCollide = false;
        }
    }
        for (unsigned int i = 0; i < area->getPets().size(); i++) {
        area->getPets().at(i)->inOverworldUpdate();
        if (player->collides(area->getPets().at(i))) {
            if (player->getHealth() < 200 && petMsg == true){
            player->setHealth(player->getHealth() + 1);
            }
            petCollide = true;
            break;
        }
        else {
            petCollide = false;
        }
    }

    if (player->getHealth() <= 0) {
        setNextState("End");
        setFinished(true);
        player->setHealth(player->getHealth());
        setSpawnBoss(false);
        god = false;
        playerSprint = false;
        return;
    } else if (getNextState() == "End" && player->getHealth() > 0) {
        setNextState("End");
        setFinished(true);
        setSpawnBoss(false);
        god = false;
        playerSprint = false;
        return;
    }
    camera->update();
    if (drainCounter < 30*3) {
        drainCounter++;
    } else {
        drainCounter = 0;
    }

    if (area->getName() == "Area 2" && drainCounter == 30*3){
        player->setHealth(player->getHealth()-1);
    }

    if (friendCounter == 30*3 && friendMsg == true) {
        friendMsg = false;
        friendCounter = 0;
    }
        if (petCounter == 30*3 && petMsg == true) {
        petMsg = false;
        petCounter = 0;
    }
}

void OverworldState::draw() {
    overworldImage.drawSubsection(0, 0, camera->getDimensionX(), camera->getDimensionY(), camera->getLeftCornerX(), camera->getTopCornerY());
    player->inOverworldDraw();
    for (unsigned int i=0; i<area->getRocks().size();i++){
        int playerDistanceX = area->getRocks().at(i)->getOX() - camera->getPlayerX();
        int playerDistanceY = area->getRocks().at(i)->getOY() - camera->getPlayerY();
        area->getRocks().at(i)->setRenderX(camera->getDimensionX() / 2 + playerDistanceX);
        area->getRocks().at(i)->setRenderY(camera->getDimensionY() / 2 + playerDistanceY);
        area->getRocks().at(i)->inOverworldDraw();
    }
    for (unsigned int i = 0; i < area->getEnemies().size(); i++) {
        if (!area->getEnemies().at(i)->isDead()) {
            int playerDistanceX = area->getEnemies().at(i)->getOX() - camera->getPlayerX();
            int playerDistanceY = area->getEnemies().at(i)->getOY() - camera->getPlayerY();
            area->getEnemies().at(i)->setRenderX(camera->getDimensionX() / 2 + playerDistanceX);
            area->getEnemies().at(i)->setRenderY(camera->getDimensionY() / 2 + playerDistanceY);
            area->getEnemies().at(i)->inOverworldDraw();
        }
    }
    if (isSpawned() == true || area->getRemainingEnemies() == 0){
    for (unsigned int i = 0; i < area->getBosses().size(); i++) {
        if (!area->getBosses().at(i)->isDead()){
        int playerDistanceX = area->getBosses().at(i)->getOX() - camera->getPlayerX();
        int playerDistanceY = area->getBosses().at(i)->getOY() - camera->getPlayerY();
        area->getBosses().at(i)->setRenderX(camera->getDimensionX() / 2 + playerDistanceX);
        area->getBosses().at(i)->setRenderY(camera->getDimensionY() / 2 + playerDistanceY);
        area->getBosses().at(i)->inOverworldDraw();
        }
    }
}
    for (unsigned int i = 0; i < area->getFriends().size(); i++) {
        int playerDistanceX = area->getFriends().at(i)->getOX() - camera->getPlayerX();
        int playerDistanceY = area->getFriends().at(i)->getOY() - camera->getPlayerY();
        area->getFriends().at(i)->setRenderX(camera->getDimensionX() / 2 + playerDistanceX);
        area->getFriends().at(i)->setRenderY(camera->getDimensionY() / 2 + playerDistanceY);
        area->getFriends().at(i)->inOverworldDraw();
    }

    for (unsigned int i = 0; i < area->getPets().size(); i++) {
        int playerDistanceX = area->getPets().at(i)->getOX() - camera->getPlayerX();
        int playerDistanceY = area->getPets().at(i)->getOY() - camera->getPlayerY();
        area->getPets().at(i)->setRenderX(camera->getDimensionX() / 2 + playerDistanceX);
        area->getPets().at(i)->setRenderY(camera->getDimensionY() / 2 + playerDistanceY);
        area->getPets().at(i)->inOverworldDraw();
    }

    if (friendMsg == true) {
        ofDrawBitmapString("Have you seen my dog, Scooby?\nHe might have something for you.", 275, 210);
        friendCounter++;
    }
    if (friendCollide == true && friendMsg == false) {
        ofDrawBitmapString("Press [e] to Interact", 275, 210);
    }
    if (petMsg == true) {
        ofDrawBitmapString("WOOF WOOF!", 275, 195);
        if(petMsg2==1){ ofDrawBitmapString("+5 Damage", 275, 210);}
        petCounter++;
    }
    if (petCollide == true && petMsg == false) {
        ofDrawBitmapString("Press [e] to Interact", 275, 210);
    }
}

void OverworldState::keyPressed(int key) {
    player->keyPressed(key);
    if (key == OF_KEY_ESC) {
        setNextState("Pause");
        setFinished(true);
    }
    if (key == 'h'){
        if(god == false){
            player->setHealth(100);
        }
        else if(god == true){
            player->setHealth(9999);
        }
    }
    if (key == 'g') {
        if (god == false){
        god = true;
        player->setHealth(9999);
        }
    else if (god == true) {
        god = false;
        player->setHealth(100);
        }
    }

    if (key == 'e' && friendCollide == true) {
        friendMsg = true;
    }
    if (key == 'e' && petCollide == true) {
        petMsg = true;
        petMsg2++;
        if (petInteract == false) {
            player->setDmg(player->getDmg() + 5);
            petInteract = true;           
            }
    }    
    if (key == 'b') {
        setSpawnBoss(true);
    }
    if (key == OF_KEY_LEFT_SHIFT) {
        if (playerSprint == false) {
            playerSprint = true;
            player->speed = 12;
        }
        else if (playerSprint == true) {
            playerSprint = false;
            player->speed = 8;
        }
    }
}

void OverworldState::keyReleased(int key) {
    player->keyReleased(key);
}

void OverworldState::reset() {
    player->keyReleased('w');
    player->keyReleased('a');
    player->keyReleased('s');
    player->keyReleased('d');
    setFinished(false);
    setNextState("");
}