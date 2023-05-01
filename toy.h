#ifndef TOY_H
#define TOY_H
#include "command.h"
#include <array>
#include <cstring>
#include <fstream>
#include <list>
#include <string>

enum ToyState { FETCH, INCREMENT, EXECUTE, POST_EXECUTE };

class Toy {
  ToyState state;

  //  TimeMachine time_machine; TODO
  std::array<uint16_t, 256> memory_; // mem 0xFF -> IO
  std::array<uint16_t, 16> registers_;

  uint8_t pc_;
  Command ir_;

  void fetch();
  void increment();
  void execute();
  void post_execute();

public:
  Toy();

  void hard_reset();

  std::array<uint16_t, 16> get_registers();
  std::array<uint16_t, 256> get_memory();
  Command get_command();
  uint8_t get_pc();
  ToyState get_state();

  void exec() {
    switch (state) {
    case FETCH:
      fetch();
      break;
    case INCREMENT:
      increment();
      break;
    case EXECUTE:
      execute();
      break;
    case POST_EXECUTE:
      post_execute();
      break;
    default:
      break;
    }
  }

  uint16_t io_read() { return memory_[256]; }
  void io_write(uint16_t data) { memory_[256] == data; }

  bool save_memory_dump(const std::string &path);
  bool load_memory_dump(const std::string &path);

  // bool save_raw_memory_dump(const std::string &path) {} TODO
  // bool load_raw_memory_dump(const std::string &path) {} TODO
};

#endif // TOY_H
