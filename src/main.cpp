#include<iostream>

#include "read_write.hpp"

using namespace std;

int main () {
  string buffer = "Barco, limao.";
  bool is_normal_mode = false;

  read_buffer(buffer, is_normal_mode);
  cout << buffer << ' ' << is_normal_mode << endl;

  return 0;
}
