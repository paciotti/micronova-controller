#include "Arduino.h"
#include <AsyncTCP.h>
#include <WiFi.h>
#include "config.h"

#include "common.h"
#include "micronova_stove.h"
#include "console.h"
#include "wifi.h"
#include "tcp_server.h"

MicronovaStove stove = MicronovaStove(
    STOVE_PIN_RX,
    STOVE_PIN_TX,
    STOVE_PIN_EN_RX
);
Preferences settings;





void setup() {
    
    // if this is not set, the server will crash it all
    WiFi.mode(WIFI_STA);
    
    // we begin stove and serial console before wifi
    stove.init();
    init_console();
    
    settings.begin(PREFERENCES_NAMESPACE, false); 
    
    // init server
    AsyncServer* server = new AsyncServer(TCP_SERVER_PORT); 
    server->onClient(&tcp_handle_new_cient, server);
    server->begin();

    // wifi is at the end, so it is no-blocking
    wifi_connect();    

}


void loop() {
    // its all async :)
}
