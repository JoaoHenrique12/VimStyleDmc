#include<iostream>
#include<unistd.h>

#include "Keyboard.hpp"

using namespace std;

int main () {
  Keyboard k;

  k.read_buffer();
  sleep(5);
  k.write_buffer();

  return 0;
}
