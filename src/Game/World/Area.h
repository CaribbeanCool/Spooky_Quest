#pragma once

#include "Enemy.h"
#include "OverworldCamera.h"
#include "Player.h"
#include "rock.h"
#include "Boss.h"
#include "Friend.h"
#include "Pet.h"

class Area {
private:
    string name;
    ofImage areaImage;
    ofSoundPlayer areaMusic;
    ofImage areaStage;
    ofPoint entrancePosition;
    std::vector<Enemy *> enemies;
    Area *nextArea;
     std::vector<Boss *> bosses;
    std::vector<Rock *> rocks;

    std::vector<Friend *> friends;
    std::vector<Pet *> pets;

public:
    Area(string name, Area *nextArea, string areaImagePath, string areaMusicPath, string areaStagePath, ofPoint entrancePosition, vector<Enemy *> enemies, vector<Rock *> rocks, vector <Friend *> friends,vector <Pet *> pets, vector<Boss *> bosses);
    void resetEnemies();
    void resetBosses();
    string getName() { return name; }
    ofImage getImage() { return areaImage; }
    ofSoundPlayer getMusic() { return areaMusic; }
    ofImage getStage() { return areaStage; }
    ofPoint getEntrancePos() { return entrancePosition; }
    vector<Enemy *> getEnemies() { return enemies; }
    int getRemainingEnemies();
    int getRemainingBosses();
    Area *getNextArea() { return nextArea; }
    void setName(string name) { this->name = name; }
    void setEnemies(std::vector<Enemy *> enemies) { this->enemies = enemies; }
    void setBosses(std::vector<Boss *> bosses) {this->bosses = bosses;}
    vector<Boss *> getBosses() { return bosses; }
    vector<Rock *> getRocks() {return rocks;}
    vector<Friend *> getFriends() {return friends;}
    vector<Pet *> getPets() {return pets;}
};