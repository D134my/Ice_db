#include "argxx.h"
#include "ice_db.h"
#include <cstring>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
namespace argxx {
void args::check_Args(int argc, char **argv) {
  try {
    if (argc == 1)
      throw argc;
  } catch (...) {
    std::cerr << "no argument passed !\n";
    std::exit(EXIT_FAILURE);
  }
}

bool is_Arg_Remained(std::size_t argc, std::size_t arg) {
  if (arg < argc)
    return true;
  else
    return false;
}

std::string get_Tmp_Dir(std::string &dir) {
  std::experimental::filesystem::path Tmp_Path =
      std::experimental::filesystem::temp_directory_path() / ".Icxxx";

  std::ifstream ifs(Tmp_Path);
  ifs >> dir;
  std::cout << "dir is" << dir << std::endl;
  return dir;
}

void args::get_Args(int argc, char **argv) {
  std::string get_Dir_Add;

  std::string dir;
  dir = get_Tmp_Dir(dir);

  auto is_Default_Path =
      std::make_pair(db::ice_db::dir_Info.first, db::ice_db::dir_Info.second);

  for (std::size_t index{1}; index < argc; ++index) {
    std::string_view current_Arg{argv[index]};

    if (current_Arg == "-c") { //-c means create a database

      bool result = is_Arg_Remained(argc, (index + 1));
      if (result) {

        auto is_Another_Arg = std::string_view(argv[index + 1]).find("-");

        if (is_Another_Arg == std::string_view::npos)
          is_Default_Path.first = argv[index + 1];
        is_Default_Path.first += '/';
      }

      result = is_Arg_Remained(argc, (index + 2));
      if (result) {
        auto is_Another_Arg = std::string_view(argv[index + 2]).find("-");
        if (is_Another_Arg == std::string_view::npos)
          is_Default_Path.second = argv[index + 2];
      }

      dir =
          db::ice_db::create_dir(is_Default_Path.first, is_Default_Path.second);
    }

    if (current_Arg == "-d") { //-d means database
      bool result = is_Arg_Remained(argc, (index + 1));
      if (result) {
        auto is_Another_Arg = std::string_view(argv[index + 1]).find("-");
        if (is_Another_Arg == std::string_view::npos)
          get_Dir_Add = db::ice_db::create_db(argv[index + 1], dir + '/');
        else {
          std::cerr << "wrong argument! \n";
          std::exit(EXIT_FAILURE);
        }
      } else
        get_Dir_Add = db::ice_db::create_db(); // default name
    }

    if (current_Arg == "-n") {
      int num_Arg;
      bool result = is_Arg_Remained(argc, (index + 1));
      if (result) {
        auto is_Another_Arg = std::string_view(argv[index + 1]).find("-");
        if (is_Another_Arg == std::string_view::npos) { // is convertable to int

          try {
            num_Arg = std::stoi(argv[index + 1]);
          } catch (...) {
            std::cerr << "bad arg";
            std::exit(EXIT_FAILURE);
          } // end of catch

          bool result2 = is_Arg_Remained(argc, (index + num_Arg));
          if (result2) {
            std::cout << "yes ";
          } else {
            std::cerr << "no arguments passed";
            std::exit(EXIT_FAILURE);
          }

          std::vector<std::string> vec_Name_Arg;
          std::vector<std::string> vec_Value_Arg;
          for (std::size_t i{1}; i <= num_Arg; ++i) {
            vec_Name_Arg.push_back(argv[index + 1 + i]);
          }

          for (std::size_t j{1}; j <= num_Arg; ++j) {
            result = is_Arg_Remained(argc, (index + 1 + j));
            if (result) {
              vec_Value_Arg.push_back(argv[index + 1 + num_Arg + j]);
            }
          }

          db::ice_db::write_db(dir + '/' + get_Dir_Add, vec_Name_Arg,
                               vec_Value_Arg);
        } // end of npos test
      }
    } // end of n check

    if (current_Arg == "-gd") {
      bool result = is_Arg_Remained(argc, (index + 1));
      if (result) {
        auto has_icx = std::string(argv[index]).find(".icx");
        if (has_icx == std::string::npos)
          db::ice_db::print_db(dir + '/' + get_Dir_Add +
                                   std::string(argv[index + 1]) + ".icx",
                               (argc - (index)));
        else
          db::ice_db::print_db(dir + '/' + get_Dir_Add +
                                   std::string(argv[index + 1]),
                               (argc - index));
      }
    }

  } // end of for loop
}
} // namespace argxx
