/*
    ~~02-02-2019~~
    ~Paweł Bocian~

Simple Manual :
  HandleRequest();
    First of all we need to identify request, which have 3 variables {type,object,value}
    Guide of markings : type - 0 = set/put
                        type - 1 = get
                        type - 2 = observed
                        type - 3 = metrics
                        object - 0 = buzzer
                        object - 1 = Potentiometer
                        value - depends -> if observe ( 1 - Enable , 0 - Disable)
                                        -> if set <0;20000>
    Cases implemented in code below :
    type = 0 ; object = 0 ; value = xxx  <- Set speaker frequency at xxx
    type = 1 ; object = 0 ; value = any  <- Get speaker frequency
    type = 1 ; object = 1 ; value = any  <- Get Potentiometer Value
    type = 1 ; object = 2 ; value = any  <- Get Radio Connection metrics
    type = 2 ; object = 1 ; value = any  <- Let's observe Potentiometer value


    06-02-2019 UPDATE
    Instead of checking all 3 variables we recived extra variable "request_id" which is most important to identify request.

    SET_SPEAKER_FREQ = 00,
    GET_SPEAKER_FREQ = 10,
    GET_POTENTIOMETER_VAL = 11,
    GET_METRICS = 12,
    OBSERVE_POTENTIOMETER = 21

  HandleResponse();
    Arduino Mini Pro handles response using variable id.
    Markings of id are clearly explained in Enums.h file.
      SPEAKER_FREQ = 00,
      POTENTIOMETER_VALUE = 11,
      METRICS = 12,
      OBSERVED_ITEM = 21,
      EMPTY = 99

 */                                     //include required libraries
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
                                        //include all files
#include "message/Request.h"
#include "message/Response.h"
#include "utils/Attributes.h"
#include "utils/Strings.h"
#include "utils/Enums.h"

using namespace Enums;                  //necessary to use enums


boolean Observe = false;                 //Variable true when MASTER ( Arduino UNO ) wants Observe resource

RF24 radio(7,8);                        // nRF24L01(+) radio attached using Getting Started board

RF24Network network(radio);             // Network uses that radio
uint16_t freq = 0;                      // Variable represents speaker frequency
uint16_t potentiometerTempValue = 0;    // Extra Variable represents Potentiometer Value (necessary to Observe function)
uint16_t potentiometerValue = 0;        // Variable represents Potentiometer Value
uint16_t successfulSending = 0;         // Variable counting number of successful messages sended
uint16_t failedSending = 0;             // Variable counting number of failed messages sended


Request userRequest;                        // Object represents request from MASTER (Arduino UNO )
Response response;                          // Object represents response to MASTER (Arduino Uno )
RF24NetworkHeader mini_header(MINI_NODE);   // Headers to radio communication between Master-Slave
RF24NetworkHeader uno_header(UNO_NODE);

void setup(void)
{
  Serial.begin(115200);                         // Open serial monitor
  SPI.begin();                                  // Allows you to communicate with SPI devices, with the Arduino as the master device
  radio.begin();                                // Radio device begin
  network.begin(CHANNEL,MINI_NODE);             // Open connection at 45-th channel adress : MINI_NODE -> 00
  Serial.println(F("Slave - Arduino Pro Mini active"));
}

void sendResponse(Response res) {                              //Sending response to MASTER (Arduino UNO)
  int allRight = network.write(uno_header,&res,sizeof(res));   //Sending "res" message to MASTER (Arduino UNO)
  if(allRight){
    Serial.print(mini_id);                      // Prints device id
    Serial.println(send_OK);                    // Prints if message was send correctly
    successfulSending++;                        // if send OK count it
  }
  else
  {
    Serial.print(mini_id);                      // Prints device id
    Serial.println(send_FAIL);                  // Prints if message wasn't send correctly
    failedSending++;                            // if send failed count it
  }
}

void HandleRequest(){
  if(network.available()) {                                     // Is there anything ready for us?
    network.read(mini_header,&userRequest,sizeof(userRequest)); //Receiving "request" from Arduino Uno

      switch (userRequest.ParseRequest())        //Identify what Master required
      {

        case SET_SPEAKER_FREQ :
            Serial.println(setting_frequency);
            if(userRequest.getValue()>0){
            freq = userRequest.getValue();
            tone(9,freq);                        //Setting tone at  required frequency
            }
            else
            {
            noTone(9);                           //Disable speaker
            freq = 0;
            }

            response.setId(SPEAKER_FREQ);        //Setting Id to send response correctly
            break;

        case GET_SPEAKER_FREQ :
            Serial.println(sending_frequency);
            response.setId(SPEAKER_FREQ);        //Setting Id to send response correctly
            break;

        case GET_POTENTIOMETER_VAL :
            Serial.println(sending_potentiometer);
            response.setId(POTENTIOMETER_VALUE); //Setting Id to send response correctly
            break;

        case GET_METRICS :
            Serial.println(sending_metrics);
            response.setId(METRICS);             //Setting Id to send response correctly
            break;

        case OBSERVE_POTENTIOMETER :
            if(Observe){
              Serial.println(observe_disabled);
              Observe = false;                  //Enable observe
            break;
            }
            else
            {
              Serial.println(observe_enabled);
              Observe = true;                   //Disable observe
            break;
            }

        default :
            Serial.println(req_error);
            break;
    }
  }
}

void HandleResponse(){                              //Handle response for MASTER ( Arduino UNO )
if(response.getId() != EMPTY){
  switch (response.getId())                         //Identify what Slave returns to Master
  {

    case SPEAKER_FREQ :
        response.setValue(freq);
        sendResponse(response);
        response.setId(EMPTY);                      //Reset id
        break;

    case POTENTIOMETER_VALUE :
        potentiometerValue = analogRead(A0);
        response.setValue(potentiometerValue);
        sendResponse(response);
        response.setId(EMPTY);                      //Reset id
        break;

    case METRICS :
        response.setValue((uint16_t)ceil(((double)failedSending/((double)successfulSending+(double)successfulSending))*100));
        sendResponse(response);
        response.setId(EMPTY);                      //Reset id
        break;

    case OBSERVED_ITEM :
        response.setValue(potentiometerValue);
        sendResponse(response);
        response.setId(EMPTY);                      //Reset id
        break;

    default :
        break;
  }
}
}

void ObserveResource(boolean Observe){
  if(Observe){
    delay(2);                                                   //Delay 2 caused Arduino Mini processor clock ( Stabilize Potentiometer AnalogRead)
      potentiometerTempValue=analogRead(A0);                    //Getting Potentiometer Value
      potentiometerTempValue = map(potentiometerTempValue, 0, 1023, 0, 1023); //Mapping value at range <0;1023>
        if(abs(potentiometerValue-potentiometerTempValue)>5){                 // If value changed, replace value and send new value to Uno
          potentiometerValue = potentiometerTempValue;                        // Setting new value
          response.setId(OBSERVED_ITEM);                                     //Let's send it !
        }
  }
}



void loop(void){

  network.update();             //Updates network regulary
  HandleRequest();
  ObserveResource(Observe);
  HandleResponse();

}
