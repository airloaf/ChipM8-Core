#include "Input.h"

bool Input::isKeyPressed(uint8_t key){
    return keys[key];
}

void Input::setKeyPressed(uint8_t key, bool pressed){
    keys[key] = pressed;
}
