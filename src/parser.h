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
 #ifndef Included_Parser_H
 #define Included_Parser_H

 #include <Arduino.h>

 namespace constants
{
        const uint8_t BACKGROUND = 0;
        const uint8_t CLOCKWISE = 1;
        const uint8_t ACLOCKWISE = 2;
        const uint8_t PIXEL = 3;
        const uint8_t ERROR = 0;

}



extern uint8_t get_red(String command);
extern uint8_t get_green(String command);
extern uint8_t get_blue(String command);
extern uint8_t get_count(String command);
extern int get_command(String command);
#endif
