#include <stdint.h> //library to use uint variable
#include <Arduino.h>


//Class represents request

class Request {

  private:
    uint8_t type;
    uint8_t object;
    uint16_t value;
    uint8_t request_id;

  public:
    //Setters

    void setType(uint8_t typ);
    void setObject(uint8_t obj);
    void setValue(uint16_t val);

    //Getters

    uint8_t getType();
    uint8_t getObject();
    uint16_t getValue();
    uint8_t ParseRequest();
};
