/*
    ~~06-02-2019~~
    ~Paweł Bocian~

Simple Manual :
  handleRequest() function is using variable request_id created while entering request.
    a ∈ {0,2} - type of request, 0-Set/Put , 1-Get , 2- Observe
    b ∈ {0,2} - object , 0-Speaker , 1-Potentiometer , 2-Metrics
    c ∈ <0,65534> - value : In case :
                            type = 0 <- Frequency of speaker ( 0-20000)

    request_id = 00 <- SET_SPEAKER_FREQ
    request_id = 10 <- GET_SPEAKER_FREQ
    request_id = 11 <- GET_POTENTIOMETER_VAL
    request_id = 12 <- GET_METRICS
    request_id = 21 <- OBSERVE_POTENTIOMETER

  handleResponse();
  Master identify response from Slave using variable response.id comaped to responseCode
    In case :
    ID = 00 <- SPEAKER_FREQ
    ID = 11 <- POTENTIOMETER_VALUE
    ID = 21 <- OBSERVED_ITEM .
    ID = 12 <- METRICS
    ID = 99 <- EMPTY  // impossible to recive

  Dictionary :
  Arduino UNO - Master
  Mini_Pro - Slave
*/
                                              // Include required libraries
#include <Arduino.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
                                              // Include all files
#include "message/Request.h"
#include "message/Response.h"
#include "utils/Attributes.h"
#include "utils/Strings.h"
#include "utils/Enums.h"

using namespace Enums;                        // Necessary to use enums

RF24 radio(7,8);                              // Radio attached at board pin 7 and 8
RF24Network network(radio);                   // Network uses that radio

Request userRequest;                          // Object represents request to SLAVE ( Arduino PRO MINI )
Response response;                            // Object represents response to MASTER (Arduino Uno)
RF24NetworkHeader uno_header(UNO_NODE);       // Headers to radio communication between Master-Slave
RF24NetworkHeader mini_header(MINI_NODE);

void setup()
 {
  Serial.begin(115200);                       // Open serial monitor
  SPI.begin();                                // Allows you to communicate with SPI devices, with the Arduino as the master device.
  radio.begin();                              // Radio device begin
  network.begin(CHANNEL,UNO_NODE);            // Open connection at 45-th channel adress : UNO_NODE -> 01
  Serial.println(F("Master - Arduino Uno active"));
}

void sendRequest(Request req) {                                 //Sending request to SLAVE ( Arduino MINI PRO )
  int allRight = network.write(mini_header,&req,sizeof(req));   //Sending "req" message to SLAVE ( Arduino MINI PRO )
  if(allRight){
    Serial.print(uno_id);                     // Prints device id
    Serial.println(send_OK);                  // Prints if message was send correctly
  }
  else
  {
    Serial.print(uno_id);                     // Prints device id
    Serial.println(send_FAIL);                // Prints if message wasn't send correctly
  }
}

void handleRequest(){
if(Serial.available()){
  Serial.print(enterType);
    while(Serial.available()==0 ){}             // Wait for type value
    userRequest.setType(Serial.parseInt());
    Serial.println(userRequest.getType());
  Serial.print(enterObject);
    while(Serial.available()==0 ){}             // Wait fot object value
    userRequest.setObject(Serial.parseInt());
    Serial.println(userRequest.getObject());
  Serial.print(enterValue);
    while(Serial.available()==0 ){}             // Wait for value value
    userRequest.setValue(Serial.parseInt());
    Serial.println(userRequest.getValue());

    switch (userRequest.ParseRequest())         // Identify what User required
    {

      case SET_SPEAKER_FREQ :
        if(userRequest.getValue()>MAX_FREQ || userRequest.getValue()<MIN_FREQ)
          Serial.println(freq_not_allowed);
        else
          Serial.println(set_frequency);
          sendRequest(userRequest);             // Send appropriate request
          break;

      case GET_SPEAKER_FREQ :
          Serial.println(get_frequency);
          sendRequest(userRequest);             // Send appropriate request
          break;

      case GET_POTENTIOMETER_VAL :
          Serial.println(get_potentiometer);
          sendRequest(userRequest);             // Send appropriate request
          break;

      case GET_METRICS :
          Serial.println(get_metrics);
          sendRequest(userRequest);             // Send appropriate request
          break;

      case OBSERVE_POTENTIOMETER :
          Serial.println(observe);
          sendRequest(userRequest);             // Send appropriate request
          break;

      default :
          Serial.println(req_error);
          break;
    }
  }
}

void handleResponse(){                                     // Handle response from SLAVE ( Arduino MINI PRO )
    if(network.available()){
    network.read(uno_header,&response,sizeof(response));   // Receiving "response" from SLAVE

    switch (response.getId())                              // Identify what Slave returns to Master
    {

      case SPEAKER_FREQ :
          Serial.print(frequency);
          Serial.println(response.getValue());              // Get appropriate value
          break;

      case POTENTIOMETER_VALUE :
          Serial.print(potentiometer);
          Serial.println(response.getValue());              // Get appropriate value
          break;

      case METRICS :
          Serial.print(metrics);
          Serial.print(response.getValue());                // Get appropriate value
          Serial.println(percent);
          break;

      case OBSERVED_ITEM :
          Serial.print(observed);
          Serial.println(response.getValue());              // Get appropriate value
          break;

      default :
          Serial.println(res_error);
          break;

    }
  }
}

void loop() {
  network.update();
  handleRequest();
  handleResponse();
}
