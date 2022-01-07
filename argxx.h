#ifndef ARGXX_H
#define ARGXX_H

#include <string_view>

namespace argxx {

class args {
public:
  // a little bit optimization

  args() = default;
  ~args() = default;
  args(args const &) = delete;
  args(args &&) = delete;

  static void check_Args(int argc, char **argv) noexcept;
  static void get_Args(int argc, char **argv) noexcept;
};
bool is_Arg_Remained(std::size_t, std::size_t);

} // namespace argxx
#endif // ARGXX_H
