#include "argxx.hpp"
#include "ice_db.hpp"

int main(int argc, char **argv) {

  argxx::args::check_Args(argc, argv);
  argxx::args::get_Args(argc, argv);

  return 0;
}
