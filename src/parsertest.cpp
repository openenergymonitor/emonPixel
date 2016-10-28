
#include <parsertest.h>
#include <parser.h>
#include <emonesp.h>

 void test() {
  /* code */
  String max_valid = "cdial/255/253/252/1000";
  String missing_n = "cdial/255/255/255";
  String missing_r = "cdial/foo/255/255/1009";
  String max_valid_anti = "adial/255/255/255/1000";
  String negative = "cdial/255/-25/255/1000";

  DEBUG.println(max_valid);
  DEBUG.println("red val: " + String(get_red(max_valid)));// + " " + get_red(max_valid)==255);
  DEBUG.println("green val: " + String(get_green(max_valid)));// + " " + get_green(max_valid)==253);
  DEBUG.println("blue val: " + String(get_blue(max_valid)));// + " " + get_blue(max_valid)==252);
  DEBUG.println("count :" + String(get_count(max_valid)));//+ " " + get_count(max_valid)==1000);
  DEBUG.println("count when missing :" + String(get_count(missing_n)));//+ " " + get_count(max_valid)==1000);
  DEBUG.println("red should error val: " + String(get_red(missing_r)));// + " " + get_red(max_valid)==255);
  DEBUG.println("green should error as -ve val: " + String(get_green(negative)));// + " " + get_red(max_valid)==255);

  DEBUG.println("command :" + String(get_command(max_valid)));//+ " " + get_count(max_valid)==1000);



}
