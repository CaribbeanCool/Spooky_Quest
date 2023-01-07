#include "PauseState.h"

PauseState::PauseState() {
    screen.load("images/ui/pause.png");
}

void PauseState::update() {
}

void PauseState::draw() {
    screen.draw(0, 0, ofGetWidth(), ofGetHeight());
}

void PauseState::keyPressed(int key) {
    if(key == OF_KEY_ESC){
        setNextState(state);
        setFinished(true);
    }
}
void PauseState::reset() {
    setFinished(false);
    setNextState("");
}