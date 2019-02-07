// enums.h
#ifndef ENUMS_H
#define ENUMS_H

#include <Arduino.h>

namespace Enums {

  //requestCode is conection of type and object variable. It's done to identify what master send to slave.
  enum requestCode{

      SET_SPEAKER_FREQ = 00,
      GET_SPEAKER_FREQ = 10,
      GET_POTENTIOMETER_VAL = 11,
      GET_METRICS = 12,
      OBSERVE_POTENTIOMETER = 21

  };

  //responseCode is conection of type and object variable. It's done to identify what slave send to master.
  enum responseCode{

      SPEAKER_FREQ = 00,
      POTENTIOMETER_VALUE = 11,
      METRICS = 12,
      OBSERVED_ITEM = 21,
      EMPTY = 99

  };
}

#endif //ENUMS_H
