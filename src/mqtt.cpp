/*
 * -------------------------------------------------------------------
 * EmonPixel Emon WiFi Display gateway
 * -------------------------------------------------------------------
 * Adaptation of Chris Howells OpenEVSE ESP Wifi
 * by Trystan Lea, Glyn Hudson, David Hunnisett, OpenEnergyMonitor
 * All adaptation GNU General Public License as below.
 *
 * -------------------------------------------------------------------
 *
 * This file is part of OpenEnergyMonitor.org project.
 * EmonESP is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * EmonESP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with EmonESP; see the file COPYING.  If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "emonesp.h"
#include "mqtt.h"
#include "config.h"
#include "pixel.h"
#include "parser.h"


#include <Arduino.h>
#include <PubSubClient.h>             // MQTT https://github.com/knolleary/pubsubclient PlatformIO lib: 89
#include <WiFiClient.h>


WiFiClient espClient;                 // Create client for MQTT
PubSubClient mqttclient(espClient);   // Create client for MQTT

long lastMqttReconnectAttempt = 0;
int clientTimeout = 0;
int i = 0;
String mqtt_data = "";


// -------------------------------------------------------------------
// MQTT callback
// -------------------------------------------------------------------
void callback(char* topic, byte* payload, unsigned int length) {
        DEBUG.println("Message arrived [");
        DEBUG.println(topic);
        DEBUG.println("] ");
        String command = "";
        stop_animations();
        for (int i= 0; i < length; i++)
        {
                command.concat((char)payload[i]);
        }
        //String command =  String((char *)payload); // DO NOT LIKE THIS
        DEBUG.println(command);

        switch (get_command(command)) {
        case constants::BACKGROUND:
                set_background(get_red(command), get_green(command), get_blue(command));
                break;
        case 3:
                set_pixel(get_count(command), get_red(command), get_green(command), get_blue(command));
                break;
        case 1:
                set_c_target(get_count(command), get_red(command), get_green(command), get_blue(command));
                break;
        case 2:
                set_a_target(get_count(command), get_red(command), get_green(command), get_blue(command));
                break;


        }


}


// -------------------------------------------------------------------
// MQTT Connect
// -------------------------------------------------------------------
boolean mqtt_connect()
{
        set_mqtt_connecting();
        mqttclient.setServer(mqtt_server.c_str(), 1883);
        DEBUG.println("MQTT Connecting...");
        String strID = String(ESP.getChipId());
        if (mqttclient.connect(strID.c_str(), mqtt_user.c_str(), mqtt_pass.c_str())) { // Attempt to connect
                DEBUG.println("MQTT connected");
                set_mqtt_connected();
                mqttclient.publish(mqtt_topic.c_str(), "connected"); // Once connected, publish an announcement..
                mqttclient.subscribe(mqtt_topic.c_str());
                mqttclient.setCallback(callback);
        } else {
                DEBUG.print("MQTT failed: ");
                DEBUG.println(mqttclient.state());
                return(0);
        }
        return (1);
}

// -------------------------------------------------------------------
// Publish to MQTT
// Split up data string into sub topics: e.g
// data = CT1:3935,CT2:325,T1:12.5,T2:16.9,T3:11.2,T4:34.7
// base topic = emon/emonesp
// MQTT Publish: emon/emonesp/CT1 > 3935 etc..
// -------------------------------------------------------------------
void mqtt_publish(String data)
{
        mqtt_data = data;

        // Construct MQTT topic e.g. <base_topic>/CT1 e.g. emonesp/CT1

        // send data via mqtt
        //delay(100);


        //String ram_topic = mqtt_topic + "/" + mqtt_feed_prefix + "freeram";
        //String free_ram = String(ESP.getFreeHeap());
        //mqttclient.publish(ram_topic.c_str(), free_ram.c_str());
}

// -------------------------------------------------------------------
// MQTT state management
//
// Call every time around loop() if connected to the WiFi
// -------------------------------------------------------------------
void mqtt_loop()
{
        if (!mqttclient.connected()) {
                set_mqtt_connecting();
                long now = millis();
                // try and reconnect continuously for first 5s then try again once every 10s
                if ( (now < 50000) || ((now - lastMqttReconnectAttempt)  > 100000) ) {
                        lastMqttReconnectAttempt = now;
                        if (mqtt_connect()) { // Attempt to reconnect
                                lastMqttReconnectAttempt = 0;
                        }
                }
        } else {
                // if MQTT connected
                mqttclient.loop();
                if(!mqtt_data.equals("")){
                  DEBUG.printf("%s = %s\r\n", mqtt_topic.c_str(), mqtt_data.c_str());
                  mqttclient.publish(mqtt_topic.c_str(), mqtt_data.c_str());
                  mqtt_data = ""; // message sent!
              }
        }
}

void mqtt_restart()
{
        if (mqttclient.connected()) {
                mqttclient.disconnect();
        }
}

boolean mqtt_connected()
{
        return mqttclient.connected();
}
