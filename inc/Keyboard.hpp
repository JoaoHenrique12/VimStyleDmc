#ifndef _KEYBOARD_HPP
#define _KEYBOARD_HPP

#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#include <vector>
#include <iostream>

class Keyboard {
public:
  Keyboard();
  ~Keyboard();

  void read_buffer();
  void write_buffer();

private:
  int file_descriptor;
  struct input_event event;
  std::vector<int> raw_buffer;

  bool is_command_mode;
  int number_attempts;

  void init_file_descriptor();
  void write_key(int key_code, bool is_pressed_key);
};

#endif
