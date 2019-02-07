#include "Request.h"

//Setters

void Request::setType(uint8_t typ){
    this->type = typ;
}

void Request::setObject(uint8_t obj){
    this->object = obj;
}

void Request::setValue(uint16_t val){
    this->value = val;
}

//Getters

uint8_t Request::getType(){
    return this->type;
}

uint8_t Request::getObject(){
    return this->object;
}

uint16_t Request::getValue(){
    return this->value;
}

uint8_t Request::ParseRequest(){
    this->request_id = 0;

    this->request_id =  this->request_id + this->object * 1;
    this->request_id =  this->request_id + this->type * 10;

    return this->request_id;
}
