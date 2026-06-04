#include "ErrorHandler.h"

/**
 * @brief errorfunctie dat afhankelijk van inkomende errorcode de onboard led knippert en dan 5s wacht
 * @param aantal keren dat de led knippert per 5s. Zie de handleiding voor welk patroon waarvoor staat
 */
void error(int code){
    while(1){
        for(int i = 0; i < code; i++){
            digitalWrite(ONBOARD_LED, HIGH);
            delay(500);
            digitalWrite(ONBOARD_LED, LOW);
            delay(500);
        }
        delay(5000);
    }
}