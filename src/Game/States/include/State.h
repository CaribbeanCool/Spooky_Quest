#pragma once

#include "ofMain.h"

class State {
protected:
    string nextState;
    ofSoundPlayer music;
    bool finished = false;
    bool SpawnBoss = false;

public:
    State() {}
    virtual void reset() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void keyPressed(int key) {}
    virtual void mousePressed(int x, int y, int button) {}
    virtual void keyReleased(int key) {}
    void mouseMoved(int x, int y) {}
    void mouseDragged(int x, int y, int button) {}
    void mouseReleased(int x, int y, int button) {}
    void mouseEntered(int x, int y) {}
    void mouseExited(int x, int y) {}
    void windowResized(int w, int h) {}
    void gotMessage(ofMessage msg) {}
    void dragEvent(ofDragInfo dragInfo) {}
    bool hasFinished() { return finished; }
    string getNextState() { return nextState; }
    void setFinished(bool finished) { this->finished = finished; }
    void setNextState(string nextState) { this->nextState = nextState; }
    void setSpawnBoss(bool SpawnBoss) {this->SpawnBoss = SpawnBoss;}
    bool isSpawned() {return SpawnBoss; }
    void toggleMusic() {
        // No music to play
        if (!music.isLoaded()) return;
        music.isPlaying() ? music.stop() : music.play();
    }
};