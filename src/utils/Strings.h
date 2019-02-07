#ifndef STRINGS_H
#define STRINGS_H

//Enter request notofications
const char enterType[] = "\033[1;37m[ARDUINO UNO]-\033[0mEnter type of request : ";
const char enterObject[] = "\033[1;37m[ARDUINO UNO]-\033[0mEnter Object id : ";
const char enterValue[]  = "\033[1;37m[ARDUINO UNO]-\033[0mEnter value if required (if not put 0) : ";

//Devices id
const char uno_id[] = "\033[1;37m[ARDUINO UNO]-\033[0m"; // Master
const char mini_id[] = "\033[1;36m[ARDUINO PRO]-\033[0m"; // Slave

//Radio commuication notification
const char send_OK[] = "\033[1;32mSending successful\033[0m";
const char send_FAIL[] = "\033[1;31mSending failed\033[0m";

//Request notifications
const char freq_not_allowed[] = "\033[1;37m[ARDUINO UNO]-\033[0mSetting frequency is not allowed. Range 0-200000 [Hz]";
const char set_frequency[] = "\033[1;37m[ARDUINO UNO]-\033[0mSet speaker frequency";
const char get_frequency[] = "\033[1;37m[ARDUINO UNO]-\033[0mGet speaker frequency";
const char get_potentiometer[] = "\033[1;37m[ARDUINO UNO]-\033[0mGet value of potentiometer";
const char observe[] = "\033[1;37m[ARDUINO UNO]-\033[0mObserve potentiometer";
const char get_metrics[] = "\033[1;37m[ARDUINO UNO]-\033[0mGet radio connection methrics";
const char req_error[] = "\033[1;37m[ARDUINO UNO]-\033[0mCannot identify request";

//Response notifications
const char frequency[] = "\033[1;36m[ARDUINO PRO]-\033[0mFrequency of speaker : ";
const char potentiometer[] = "\033[1;36m[ARDUINO PRO]-\033[0mValue of potentiometer : ";
const char metrics[] = "\033[1;36m[ARDUINO PRO]-\033[0mMessages lost ";
const char observed[] = "\033[1;36m[ARDUINO PRO]-\033[0mValue of observed item : ";
const char res_error[] = "\033[1;36m[ARDUINO PRO]-\033[0mCannot identify response";

//Slave - Arduino Pro Mini notifications
const char setting_frequency[] = "\033[1;36m[ARDUINO PRO]-\033[0mSetting speaker frequency";
const char sending_frequency[] = "\033[1;36m[ARDUINO PRO]-\033[0mSending speaker frequency";
const char sending_potentiometer[] = "\033[1;36m[ARDUINO PRO]-\033[0mSending value of potentiometer";
const char sending_metrics[] = "\033[1;36m[ARDUINO PRO]-\033[0mSending metrics ";
const char observe_enabled[] = "\033[1;36m[ARDUINO PRO]-\033[0mObserve Potentiometer enabled";
const char observe_disabled[] = "\033[1;36m[ARDUINO PRO]-\033[0mObserve Potentiometer disabled";


const char percent[] = "%" ;
#endif //SRINGS_H
