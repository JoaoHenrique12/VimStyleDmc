#ifndef _READ_WRITE_HPP
#define _READ_WRITE_HPP

#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#include <string>

void read_buffer(std::string& buffer, bool& is_normal_mode);

#endif // !_READ_WRITE_HPP
