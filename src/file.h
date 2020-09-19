#ifndef FILE_H
#define FILE_H
#include <string>

#include "file_format.h"

FileFormat get_file_format(std::string filename);

std::string get_file_extension(std::string filename);

std::string get_filename(std::string filename, const bool& extension = true);
#endif