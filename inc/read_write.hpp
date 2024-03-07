#ifndef _READ_WRITE_HPP
#define _READ_WRITE_HPP

#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#include <vector>
#include <iostream>

class Keyboard {
public:
  Keyboard();
  ~Keyboard();
  bool get_is_command_mode();

  void read_buffer();
  void write_buffer();

private:
  int file_descriptor;
  struct input_event event;
  std::vector<int> raw_buffer;

  bool is_command_mode;
  int number_attempts;

  void init_file_descriptor();
};

#endif // !_READ_WRITE_HPP
