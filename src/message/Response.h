#include <stdint.h> //library to use uint variable
#include <Arduino.h>


//Class represents response

class Response {

  private:
    uint8_t id = 99;
    uint16_t value;

  public:
    //Setters

    void setId(uint8_t id);
    void setValue(uint16_t val);

    //Getters
    uint8_t getId();
    uint16_t getValue();

};
