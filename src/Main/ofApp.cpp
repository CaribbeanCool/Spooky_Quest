#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetEscapeQuitsApp(false);
    ofSetFrameRate(30);
    ofSetWindowTitle("PA2");
    initAreas();
    // Declaration and Initialization of States
    player = new Player(100, 5);
    titleState = new TitleState();
    overworldState = new OverworldState(player, currentArea);
    battleState = new BattleState(player, currentArea);

    bossBattleState = new BossBattleState(player, currentArea);
    winState = new WinState();
    endGameState = new EndGameState();
    pauseState = new PauseState();

    // Initial State
    currentState = titleState;
}

//--------------------------------------------------------------
void ofApp::initAreas() {
    /**
     * @brief
     * each area is 672 pixels wide and 640 pixels high,
     * with 10 and 8 pixels of space between the player and the edge of the map respectively
     * each in-game pixel is 4 * 1 screen pixel
     */

    vector<Enemy *> enemies3;
    vector<Boss *> bosses3;
    ofPoint entrancePosition3(4 * 110, 4 * 116);
    vector<Rock *> rock3;
    vector<Friend *> friend3;
    vector<Pet *> pet3;
    Rock *area3Rock1 = new Rock("31", "rock3", 4 * 257, 4 * 461);
    Friend *area3Friend1 = new Friend("31", "friend3", 4 * 368, 4 * 422); 
    Pet *area3Pet1 = new Pet("31", "pet3", 4 * 380, 4 * 170);
    Enemy *area3Enemy1 = new Enemy("31", 30, 6, "enemy3", 4 * 476, 4 * 242);
    Boss *area3Boss1 = new Boss("31", 50, 14, "enemy3", 4 * 194, 4 * 221);
    Enemy *area3Enemy2 = new Enemy("32", 30, 6, "enemy3", 4 * 254, 4 * 130);
    Enemy *area3Enemy3 = new Enemy("33", 30, 6, "enemy3", 4 * 542, 4 * 124);
    Enemy *area3Enemy4 = new Enemy("34", 30, 6, "enemy3", 4 * 532, 4 * 368);
    Enemy *area3Enemy5 = new Enemy("35", 30, 6, "enemy3", 4 * 266, 4 * 312);
    Enemy *area3Enemy6 = new Enemy("36", 30, 6, "enemy3", 4 * 194, 4 * 532);
    bosses3.push_back(area3Boss1);
    rock3.push_back(area3Rock1);
    friend3.push_back(area3Friend1);
    pet3.push_back(area3Pet1);
    enemies3.push_back(area3Enemy1);
    enemies3.push_back(area3Enemy2);
    enemies3.push_back(area3Enemy3);
    enemies3.push_back(area3Enemy4);
    enemies3.push_back(area3Enemy5);
    enemies3.push_back(area3Enemy6);
    area3 = new Area("Area 3", NULL, "images/areas/area3.png", "audio/abandonShip.mp3", "images/stages/stage3.png", entrancePosition3, enemies3,rock3,friend3, pet3, bosses3);

    vector<Enemy *> enemies2;
    vector<Boss *> bosses2;
    vector<Rock *> rock2;
    vector<Friend *> friend2;
    vector<Pet *> pet2;
    Rock *area2Rock1 = new Rock("21", "rock2", 4 * 200, 4 * 200);
    Rock *area2Rock2 = new Rock("21", "rock2", 4 * 426, 4 * 374);
    Friend *area2Friend1 = new Friend("21", "friend2", 4 * 472, 4 * 258);
    Pet *area2Pet1 = new Pet("21", "pet2", 4 * 280, 4 * 384);
    ofPoint entrancePosition2(4 * 110, 4 * 116);
    Enemy *area2Enemy1 = new Enemy("21", 30, 6, "enemy2", 4 * 331, 4 * 504);
    Enemy *area2Enemy2 = new Enemy("22", 30, 6, "enemy2", 4 * 254, 4 * 130);
    Enemy *area2Enemy3 = new Enemy("23", 30, 6, "enemy2", 4 * 542, 4 * 124);
    Enemy *area2Enemy4 = new Enemy("24", 30, 6, "enemy2", 4 * 532, 4 * 368);
    Boss *area2Boss1 = new Boss("21", 40, 12, "enemy2", 4 * 362, 4 * 216);
    bosses2.push_back(area2Boss1);
    rock2.push_back(area2Rock1);
    rock2.push_back(area2Rock2);
    friend2.push_back(area2Friend1);
    pet2.push_back(area2Pet1);
    enemies2.push_back(area2Enemy1);
    enemies2.push_back(area2Enemy2);
    enemies2.push_back(area2Enemy3);
    enemies2.push_back(area2Enemy4);
    area2 = new Area("Area 2", area3, "images/areas/area2.png", "audio/area2.wav", "images/stages/stage2.png", entrancePosition2, enemies2,rock2,friend2,pet2, bosses2);

    vector<Enemy *> enemies1;
    vector<Boss *> bosses1;
    vector<Rock *> rock1;
    vector<Friend *> friend1;
    vector<Pet *> pet1;
    ofPoint entrancePosition1(4 * 414, 4 * 566);
    Rock *area1Rock1 = new Rock("11", "rock1", 4 * 372, 4 * 528);
    Rock *area1Rock2 = new Rock("11", "rock1", 4 * 396, 4 * 278);
    Friend *area1Friend1 = new Friend("11", "friend1", 4 * 320, 4 * 486);
    Pet *area1Pet1 = new Pet("11", "pet1", 4 * 324, 4 * 260);
    Enemy *area1Enemy1 = new Enemy("11", 20, 4, "enemy1", 4 * 480, 4 * 432);
    Enemy *area1Enemy2 = new Enemy("12", 20, 4, "enemy1", 4 * 225, 4 * 178);
    Enemy *area1Enemy3 = new Enemy("13", 20, 4, "enemy1", 4 * 420, 4 * 178);
    Boss *area1Boss1 = new Boss("11", 30, 10, "boss1", 4 * 300, 4 * 364);
    bosses1.push_back(area1Boss1);
    rock1.push_back(area1Rock1);
    rock1.push_back(area1Rock2);
    enemies1.push_back(area1Enemy1);
    enemies1.push_back(area1Enemy2);
    enemies1.push_back(area1Enemy3);
    friend1.push_back(area1Friend1);
    pet1.push_back(area1Pet1);
    area1 = new Area("Area 1", area2, "images/areas/area1.png", "audio/grassland.mp3", "images/stages/stage1.png", entrancePosition1, enemies1,rock1, friend1, pet1, bosses1);
    currentArea = area1;
}


//--------------------------------------------------------------
void ofApp::update() {
    currentState->update();
    
    if (currentState->hasFinished()) {
        currentState->toggleMusic();
        
        if (currentState->getNextState() == "Title") {
            endGameState->setWin(false);
            area1->resetEnemies();
            area1->resetBosses();

            area2->resetEnemies();
            area2->resetBosses();

            area3->resetEnemies();
            area3->resetBosses();

            currentArea = area1;
            battleState->reset();
            battleState->setStage(currentArea->getStage());

            bossBattleState->reset();
            bossBattleState->setStage(currentArea->getStage());

            overworldState->loadArea(currentArea);
            overworldState->god = false;
            overworldState->playerSprint = false;
            overworldState->petInteract = false;
            overworldState->petMsg2 = 0;

            player->speed = 8;
            player->setDmg(5);
            currentState = titleState;
        }
        else if(currentState->getNextState() == "Pause") {
            if (currentState == overworldState) {
                pauseState->state = "Overworld";
            } else if (currentState == battleState) {
                pauseState->state = "Battle";
            } else if (currentState == bossBattleState) {
                pauseState->state = "Boss";
            }
            currentState = pauseState;
        }
        else if (currentState->getNextState() == "Overworld") {
            if(currentState == pauseState) {
                pauseState->state = "";
            }
            currentState = overworldState;
        }
        else if (currentState->getNextState() == "Battle") {
            if (pauseState->state != "Battle") {
                battleState->startBattle(overworldState->getEnemy());
            }
            if (currentState == pauseState) {
                pauseState->state = "";
            }
            currentState = battleState;
        }
        else if (currentState->getNextState() == "Boss") {
            if (pauseState->state != "Boss") {
                bossBattleState->startBossBattle(overworldState->getBoss());
            }
            if (currentState == pauseState) {
                pauseState->state = "";
            }
            currentState = bossBattleState;
        }
        else if (currentState->getNextState() == "Win") {
            if (currentState == pauseState) {
                pauseState->state = "";
            }
            if (currentState == bossBattleState && currentState->getNextState() == "Win") {
            overworldState->getBoss()->kill();
            }
            if (currentState == battleState && currentState->getNextState() == "Win") {
                overworldState->getEnemy()->kill();
            }
            if (currentArea->getRemainingEnemies() >= 0 && currentArea->getRemainingBosses() == 0) {
                if (currentArea->getNextArea() == NULL) {
                    endGameState->setWin(true);
                    currentState = endGameState;
                    overworldState->god = false;
                    player->setHealth(100);
                } else {
                    currentArea = currentArea->getNextArea();
                    overworldState->loadArea(currentArea);
                    battleState->setStage(currentArea->getStage());
                    bossBattleState->setStage(currentArea->getStage());
                    currentState = winState;
                }
            } else {
                currentState = winState;
            }
        } 
        else if (currentState->getNextState() == "End") {
            currentState = endGameState;
            player->reset();
        }
        currentState->toggleMusic();
        currentState->reset();
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    currentState->draw();
    if (currentState == overworldState) {
        ofSetColor(ofColor::darkOliveGreen);
        ofDrawRectangle(1, 2, 195, 110);
        ofFill();
        ofSetColor(ofColor::antiqueWhite);
        ofDrawBitmapString("HEALTH: " + to_string(player->getHealth()), 25, 25);
        ofDrawBitmapString("DAMAGE: " + to_string(player->getDmg()), 25, 50);
        ofDrawBitmapString("CURRENT AREA: " + currentArea->getName(), 25, 75);
        ofDrawBitmapString("ENEMIES LEFT: " + to_string(currentArea->getRemainingEnemies()), 25, 100);
        ofSetColor(ofColor::white);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    currentState->keyPressed(key);
    if (key == 'r'){
        currentArea->resetEnemies();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    currentState->keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    currentState->mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    currentState->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    currentState->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    currentState->mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
    currentState->mouseEntered(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
    currentState->mouseExited(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
    currentState->windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
    currentState->gotMessage(msg);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
    currentState->dragEvent(dragInfo);
}