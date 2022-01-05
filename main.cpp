#include "argxx.h"
#include "ice_db.h"

int main(int argc, char **argv) {

  argxx::args::check_Args(argc, argv);
  argxx::args::get_Args(argc, argv);
}
