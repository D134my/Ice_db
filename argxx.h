#ifndef ARGXX_H
#define ARGXX_H

#include <string_view>

namespace argxx {

class args {
public:
  static void check_Args(int argc, char **argv);
  static void get_Args(int argc, char **argv);
};
bool is_Arg_Remained(std::size_t, std::size_t);
} // namespace argxx
#endif // ARGXX_H
