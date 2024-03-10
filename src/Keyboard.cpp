#include "Keyboard.hpp"

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
   for (int i = 0; i < number_attempts && read(file_descriptor, &event, sizeof(struct input_event)) < 0; i++) {
      std::cout << "Error reading input.\n";
    }

    if (event.type == EV_KEY && event.value == 1) {
      printf("Key pressed: %d\n", event.code);
      raw_buffer.push_back(event.code);
    }
    if (event.type == EV_KEY && event.code == KEY_ENTER) break;
  }
}

void Keyboard::write_key(int keycode, bool is_pressed_key)
{
  event.type = EV_KEY;
  event.code = keycode;
  event.value = is_pressed_key;
  gettimeofday(&event.time, NULL);

  write(file_descriptor, &event, sizeof(struct input_event));

  // Send a synchronization event
  event.type = EV_SYN;
  event.code = SYN_REPORT;
  event.value = 0;
  gettimeofday(&event.time, NULL);
  write(file_descriptor, &event, sizeof(struct input_event));
}

void Keyboard::write_buffer()
{
  for(auto key : raw_buffer) {
    write_key(key, true);
    usleep(100000);
    write_key(key, false);
  }

  write_key(KEY_ENTER, true);
  usleep(100000);
  write_key(KEY_ENTER, false);
}
