/*
 * -------------------------------------------------------------------
 * EmonESP Serial to Emoncms gateway
 * -------------------------------------------------------------------
 * Adaptation of Chris Howells OpenEVSE ESP Wifi
 * by Trystan Lea, Glyn Hudson, OpenEnergyMonitor
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
#include "config.h"
#include "wifi.h"
#include "web_server.h"
#include "ota.h"
#include "input.h"
#include "emoncms.h"
#include "mqtt.h"
#include "pixel.h"
#include "parsertest.h"
#include "button.h"

boolean blink = false;
// -------------------------------------------------------------------
// SETUP
// -------------------------------------------------------------------
void setup() {

        delay(1000);

        Serial.begin(9600);
#ifdef DEBUG_SERIAL1
        Serial1.begin(9600);
#endif

        DEBUG.println();
        DEBUG.print("EmonESP ");
        DEBUG.println(ESP.getChipId());
        DEBUG.println("Firmware: "+ currentfirmware);
        pixel_begin();
        pixel_rgb_demo();
        delay(1000);
        pixel_off();

        // Read saved settings from the config
        config_load_settings();
        //DEBUG.println("settings loaded:");

        // Initialise the WiFi
        wifi_setup();
        //DEBUG.println("Wifi loaded:");

        // Bring up the web server
        web_server_setup();

        // Start the OTA update systems
        ota_setup();

        DEBUG.println("Server started");
        //test();
        // Start Pixel
        setup_button();
        delay(100);

        //This magic shoudl set up the button for us



} // end setup

// -------------------------------------------------------------------
// LOOP
// -------------------------------------------------------------------
void loop()
{
        ota_loop();
        web_server_loop();
        wifi_loop();


        yield();


        //DEBUG.println();

        yield();
        if (wifi_mode==WIFI_MODE_STA || wifi_mode==WIFI_MODE_AP_AND_STA)
        {
                if(mqtt_server != 0)
                {
                        mqtt_loop();
                }
                update_c_target();
                update_a_target();
        }
        else
        {
                delay(100);
                if(blink) {
                        set_pixel(10,60,0,0);
                }
                else{
                        set_pixel(10,0,0,0);
                }
        }

} // end loop
