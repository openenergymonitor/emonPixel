/*
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

#include <pixel.h>
#include <NeoPixelBus.h>
#include <emonesp.h>

// ESP Bitbang method using GPIO4

// void pixel_setup(uint16_t PixelCount, uint16_t PixelPin)
// {
// NeoPixelBus<NeoGrbFeature, NeoEsp8266BitBang800KbpsMethod> strip(PixelCount, PixelPin);
// }

NeoPixelBus<NeoGrbFeature, NeoEsp8266BitBang800KbpsMethod> strip(PixelCount, PixelPin);

RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor white(colorSaturation);
RgbColor black(0);

uint8_t c_count = 0;
uint8_t a_count = 0;
uint8_t c_target = 0;
uint8_t a_target = 0;
RgbColor c_colour= black;
RgbColor bgColour = black;


void pixel_begin()
{
        // this resets all the neopixels to an off state
        strip.Begin();
        strip.Show();
}

void set_c_target(uint8_t target , uint8_t red, uint8_t green, uint8_t blue)
{
  c_colour = RgbColor(red,green,blue);
  c_target = target;
  c_count = 0;
}

void update_c_target()
{
  if (c_count == c_target){
    return; //target reached do nothing
  }
  if (c_count == 0){
    //start of a new sequence
    refresh_background();
  } else if (c_count % PixelCount == 0)
  {
    pixel_off();
    delay(FLASH_LOOP_DELAY);
    yield();
    DEBUG.println( String(c_count) + " : "  + String((c_count / PixelCount)));
    for(uint8_t loop_count = 0 ; loop_count < (int)(c_count / PixelCount); loop_count ++){
      set_all_pixels(c_colour);
      delay(FLASH_LOOP_DELAY);
      yield();
      pixel_off();
      delay(FLASH_LOOP_DELAY);
      yield();


    }

  }
  strip.SetPixelColor(c_count % PixelCount,c_colour);
  strip.Show();
  c_count++;
  delay(FLASH_LOOP_DELAY);

}

void random_pixel_setup(){
        for (uint16_t pixel = 0; pixel < PixelCount; pixel++)
        {
                RgbColor color = RgbColor(random(255), random(255), random(255));
                strip.SetPixelColor(pixel, color);
        }
        strip.Show();

}

  void pixel_rgb_demo(){
          for (uint16_t pixel = 0; pixel < PixelCount; pixel++)
          {
                  switch(pixel%4)
                  {
                  case 0:
                          strip.SetPixelColor(pixel,red);
                          break;
                  case 1:
                          strip.SetPixelColor(pixel,green);
                          break;
                  case 2:
                          strip.SetPixelColor(pixel,blue);
                          break;
                  case 3:
                          strip.SetPixelColor(pixel,white);
                          break;
                  }
                  strip.Show();
                  delay(50);
          }

  }

void pixel_off(){
        for (uint16_t pixel = 0; pixel < PixelCount; pixel++)
        {
                strip.SetPixelColor(pixel, black);
        }
        strip.Show();

}
void set_pixel(uint8_t pixel, uint8_t red, uint8_t green, uint8_t blue)
{
  strip.SetPixelColor(pixel, RgbColor(red,green,blue));
  strip.Show();
}
void set_background(uint8_t red, uint8_t green, uint8_t blue)
{
  DEBUG.println("Set backgorund to red: " + String(red) + " Green: " + String(green) + " Blue: " + String(blue) );
  bgColour =  RgbColor(red,green,blue);
  refresh_background();
}

void refresh_background(){
  for (uint16_t pixel = 0; pixel < PixelCount; pixel++)
  {
    strip.SetPixelColor(pixel, bgColour);
  }
  strip.Show();

}
void set_all_pixels(RgbColor theColour){
  for (uint16_t pixel = 0; pixel < PixelCount; pixel++)
  {
    strip.SetPixelColor(pixel,theColour);
  }
  strip.Show();

}
