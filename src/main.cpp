#include <iostream>
#include "db.hpp"
#include "argxx.hpp"

int main(int argc, char *argv[]) {

    try {
        auto result = argxx::args::check_Args(argc, argv);
        if(!result)
            throw result;
    }catch(...) {
      std::exit(EXIT_FAILURE);
    }

    argxx::args::get_Args(argc, argv);
    return 0;
}
