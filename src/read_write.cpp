#include "read_write.hpp"

Keyboard::Keyboard()
{
  file_descriptor = -1;
  is_command_mode = false;

  number_attempts = 5;

  init_file_descriptor();
}
Keyboard::~Keyboard(){
  if(file_descriptor != -1)
    close(file_descriptor);
}

bool Keyboard::get_is_command_mode(){
  return is_command_mode;
}

void Keyboard::init_file_descriptor()
{
  for (int i = 0; i < number_attempts && file_descriptor == -1; i++) {
    file_descriptor = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDWR );
    std::cout << "Try Open File Descriptor. " << i + 1 << '\n';
  }
}

void Keyboard::read_buffer()
{
  raw_buffer.clear();
  while (true) {
   for (int i = 0; i < number_attempts && read(file_descriptor, &event, sizeof(struct input_event); i++) < 0) {
      std::cout << "Error reading input.\n";
    }

    if (event.type == EV_KEY && event.value == 1) {
      printf("Key pressed: %d\n", event.code);
      raw_buffer.push_back(event.code);
    }
    if (event.type == EV_KEY && event.code == KEY_ENTER) break;
  }
}
