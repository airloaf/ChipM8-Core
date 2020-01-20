#include <ChipM8/Peripherals/Input.h>

Input::Input(){
    for(uint8_t key = 0; key < 16; key++){
        keys[key] = false;
    }
    waiting = false;
}

bool Input::isKeyPressed(uint8_t key){
    return keys[key];
}

void Input::setKeyPressed(uint8_t key, bool pressed){
    keys[key] = pressed;
    // If the input was waiting, set the key
    if(waiting && pressed){
        registers->V[waitedRegister] = key;
        waiting = false;
    }
}

void Input::waitForKeyPress(Registers &registers, uint8_t registerX){
    this->registers = &registers;
    waitedRegister = registerX;
    waiting = true;
}

bool Input::isWaiting(){
    return waiting;
}
