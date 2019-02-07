#include "Response.h"

//Setters

void Response::setId(uint8_t id){
    this->id = id;
}

void Response::setValue(uint16_t val){
    this->value = val;
}

//Getters

uint8_t Response::getId(){
    return this->id;
}

uint16_t Response::getValue(){
    return this->value;
}
