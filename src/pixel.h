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

#ifndef _EMONESP_PIXEL_H
#define _EMONESP_PIXEL_H

#include <Arduino.h>
#include <NeoPixelBus.h>

#define PIXEL //enable pixel

#define PixelCount      16
#define PixelPin        4
#define colorSaturation 128
#define FLASH_LOOP_DELAY 100

extern void pixel_begin();
extern void pixel_rgb_demo();
extern void random_pixel_setup();
extern void set_pixel(uint8_t pixel, uint8_t red, uint8_t green, uint8_t blue);
extern void set_background(uint8_t red, uint8_t green, uint8_t blue);
extern void pixel_off();
extern void set_c_target(uint8_t target , uint8_t red, uint8_t green, uint8_t blue);
extern void set_a_target(uint8_t target , uint8_t red, uint8_t green, uint8_t blue);

void update_c_target();
void update_a_target();

void set_c_target_state();



void refresh_background();
void set_all_pixels(RgbColor theColour);






#endif // _EMONESP_PIXEL_H
