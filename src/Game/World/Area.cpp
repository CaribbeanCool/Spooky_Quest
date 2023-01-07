#include "Area.h"

Area::Area(string name, Area *nextArea, string areaImagePath, string areaMusicPath, string areaStagePath, ofPoint entrancePosition, vector<Enemy *> enemies, vector<Rock *> rocks, vector <Friend *> friends,vector<Pet *> pets, vector<Boss *> bosses) {
    this->name = name;
    this->nextArea = nextArea;
    areaImage.load(areaImagePath);
    areaMusic.load(areaMusicPath);
    areaStage.load(areaStagePath);
    this->entrancePosition = entrancePosition;
    this->enemies = enemies;
    this->rocks = rocks;
    this->friends = friends;
    this->pets = pets;
    this->bosses = bosses;
}

void Area::resetEnemies() {
    for (unsigned int i = 0; i < enemies.size(); i++)
        enemies.at(i)->revive();

}
void Area::resetBosses() {
    for(unsigned int i = 0; i < bosses.size(); i++){
        bosses.at(i)->revive();
    }
}

int Area::getRemainingEnemies() {
    int count = 0;
    for (unsigned int i = 0; i < enemies.size(); i++)
        if (!enemies.at(i)->isDead())
            count++;
    return count;
}
int Area::getRemainingBosses() {
    int count = 0;
    for (unsigned int i = 0; i < bosses.size(); i++)
        if (!bosses.at(i)->isDead())
            count++;
    return count;
}