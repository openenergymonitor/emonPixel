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

#include "button.h"
#include "mqtt.h"
#include "emonesp.h"
void handleButton (){
  //detachInterrupt(BUTTON_PIN);
  DEBUG.println("button pressed");
  mqtt_publish("Pressed");
  reset_button();
}
void setup_button (){
        //

        pinMode(BUTTON_PIN, OUTPUT);
        digitalWrite(BUTTON_PIN,LOW);
        pinMode(BUTTON_PIN, OUTPUT);
        attachInterrupt(BUTTON_PIN, handleButton, RISING);
}
void reset_button (){
        //

        //pinMode(BUTTON_PIN, OUTPUT);
        digitalWrite(BUTTON_PIN,LOW);
        //pinMode(BUTTON_PIN, INPUT);
}
int button_down (){
  int result =  digitalRead(BUTTON_PIN);
  if(BUTTON_HACK)
  {
    //reset the button if its in funny mode
    setup_button();
  }
  return result == 0;
}
