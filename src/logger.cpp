#pragma once
#include <fstream>
#include <string>

/**
 * This class logs simple messages to a text file. On each initialization
 * it opens the text file and on destruction closes it.
 */
class Logger {
 private:
  std::ofstream log_file;
  std::string log_file_path;

 public:
  Logger(std::string log_file_path) : log_file_path(log_file_path) {
    log_file.open(log_file_path);
  }
  void log(const std::string &message) {
    log_file << message.c_str() << '\n';
    log_file.flush();
  }
};