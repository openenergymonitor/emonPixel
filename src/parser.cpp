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
 #include <parser.h>
 #include <emonesp.h>

#define RED_INDEX = 3;
#define GREEN_INDEX = 4;
#define BLUE_INDEX = 5;
#define NUMBER_INDEX = 6;


String get_string_between_nth_slash(uint8_t slash_start, String to_parse)
{
        uint8_t start=to_parse.indexOf("/");
        uint8_t i=1;
        while( i < slash_start && start != -1)
        {
                //not found the start yet so look at the next /
                start = to_parse.indexOf("/", start + 1);
                i++;
        }

        if (start == -1) {
                return "";
        }
        //find the last / if this is -1 then look use to the end of the string
        uint8_t end_slash_index = to_parse.indexOf("/", start + 1);

        String possible_number = "";
        if(end_slash_index == -1) {
                possible_number = to_parse.substring(start+1);
        }
        else{
                possible_number = to_parse.substring(start+1,end_slash_index);
        }

        return possible_number;
}
uint8_t get_number_between_nth_slash(uint8_t slash_start, String to_parse)
{
        //barf if there is nothing in the string it must have at least a / and something else
        if(to_parse.length() < 2) {
                return constants::ERROR;
        }


        String might_be_number = get_string_between_nth_slash(slash_start,to_parse);
        //barf if the rest is
        if(might_be_number.length() == 0) {
                return constants::ERROR;
        }
        might_be_number.trim();
        uint8_t result = (uint8_t)might_be_number.toInt();
        if(result > 0) {
                return result;
        }
        else if (result == 0 && might_be_number.charAt(0) == 0) {
                return 0;
        }
        else{
                return constants::ERROR;
        }


}
uint8_t get_red(String command)
{
        //first / will be end of command and start of red string
        return get_number_between_nth_slash(1,command);
}

uint8_t get_green(String command)
{

        return get_number_between_nth_slash(2,command);

}

uint8_t get_blue(String command)
{
        return get_number_between_nth_slash(3,command);

}
uint8_t get_count(String command)
{
        return get_number_between_nth_slash(4,command);

}
int get_command(String command)
{
        uint8_t start=command.indexOf("/");
        if (start < 2) {
                return constants::ERROR;
        }
        String parsed = command.substring(0,start);
        DEBUG.println("parsed command: " + parsed);
        if(parsed.equals("cdial")){
          return constants::CLOCKWISE;
        }
        else if(parsed.equals("adial")){
          return constants::ACLOCKWISE;
        }
        else if(parsed.equals("background")){
          return constants::BACKGROUND;
        }
        else if(parsed.equals("pixel")){
          return constants::PIXEL;
        }
        else {
          return -1;
        }

}
