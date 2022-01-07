#include "argxx.hpp"
#include "ice_db.hpp"
#include <fstream>
#include <iostream>
#include <vector>

namespace argxx {
void args::check_Args(int argc, char **argv) noexcept {
  try {
    if (argc == 1)
      throw argc;
  } catch (...) {
    std::cerr << "no argument passed !\n";
    db::ice_db::help_db();
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
  //-c save dir path to a file this function gonna read it.
  std::string x_Path = getenv("HOME");
  std::experimental::filesystem::path Tmp_Path = x_Path + "/.Icxxx";

  try {
    std::ifstream ifs(Tmp_Path);
    ifs >> dir;
    return dir;
  } catch (...) {
    std::cerr << "can't read " << Tmp_Path << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

void args::get_Args(int argc, char **argv) noexcept {
  std::string get_Dir_Add{}; // takes name of db

  std::string dir;
  dir = get_Tmp_Dir(dir); // get the address of dir

  auto is_Default_Path = // if -c was not taken path and name use default path
                         // and name
      std::make_pair(db::ice_db::dir_Info.first, db::ice_db::dir_Info.second);

  for (int index{1}; index < argc; ++index) {
    std::string_view current_Arg{argv[index]};

    if (current_Arg == "-h" || current_Arg == "--help") {
      db::ice_db::help_db();
    }

    if (current_Arg == "-c") { //-c means create a database

      bool result = is_Arg_Remained(argc, (index + 1));
      if (result) {
        auto is_Another_Arg = std::string_view(argv[index + 1]).find("-");

        // if there is another argument and it's not a command - means command
        // set the path for creating dir
        if (is_Another_Arg == std::string_view::npos)
          is_Default_Path.first = argv[index + 1];
        is_Default_Path.first += '/';
      }

      result = is_Arg_Remained(argc, (index + 2));
      if (result) {
        auto is_Another_Arg = std::string_view(argv[index + 2]).find("-");
        // if there is another argument and it's not a command - means command
        // set the path for creating dir name
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

      int num_Arg{}; // takes number of arguments
      bool result = is_Arg_Remained(argc, (index + 1));

      if (result) {
        auto is_Another_Arg = std::string_view(argv[index + 1]).find("-");
        if (is_Another_Arg == std::string_view::npos) { // is convertable to int

          try {
            num_Arg = std::stoi(argv[index + 1]);
          } catch (std::exception &e) {
            std::cerr << "bad arg line : " << __LINE__ << '\n';
            std::exit(EXIT_FAILURE);
          } // end of catch

          bool result2 = is_Arg_Remained(argc, (index + num_Arg));
          if (!result2) {
            std::cerr << "no arguments passed \n";
            std::exit(EXIT_FAILURE);
          }

          std::vector<std::string> vec_Name_Arg;  // takes keys
          std::vector<std::string> vec_Value_Arg; // takes values

          for (int i{1}; i <= num_Arg; ++i) {
            vec_Name_Arg.push_back(argv[index + 1 + i]);
          }

          for (int j{1}; j <= num_Arg; ++j) {
            result = is_Arg_Remained(argc, (index + 1 + j));
            if (result) {
              vec_Value_Arg.push_back(argv[index + 1 + num_Arg + j]);
            }
          }
          // dir = address of directory of db + / + name of db + keys + values
          db::ice_db::write_db(dir + '/' + get_Dir_Add, vec_Name_Arg,
                               vec_Value_Arg);
        } // end of npos test
      } else {

        std::cerr << "give me number of arguments you want to pass \n";
        std::exit(EXIT_FAILURE);
      }
    } // end of n check

    if (current_Arg == "-gd") {
      bool result = is_Arg_Remained(argc, (index + 2));
      if (!result) { // if no argument passed print whole db
        auto has_icx = std::string(argv[index]).find(".icx");
        if (has_icx == std::string::npos)
          // if name of db had no .icx at the end you add it and then print it
          db::ice_db::print_db(dir + '/' + get_Dir_Add +
                                   std::string(argv[index + 1]) + ".icx",
                               std::vector<std::string>(1, "WHOLE"));
        else {
          db::ice_db::print_db(dir + '/' + get_Dir_Add +
                                   std::string(argv[index + 1]),
                               std::vector<std::string>(1, "WHOLE"));
        } // if name of db had .icx print it normaly
      }
      // if argument passed !
      std::vector<std::string> args_Shall_Print;
      for (std::size_t i{2}; is_Arg_Remained(argc, (index + i)); ++i) {
        args_Shall_Print.push_back(std::string(argv[index + i]));
      }

      db::ice_db::print_db(dir + '/' + get_Dir_Add +
                               std::string(argv[index + 1]) + ".icx",
                           args_Shall_Print);
    } // end of -gd check

    if (current_Arg == "-ad") {
      bool result = is_Arg_Remained(argc, (index + 1));
      std::string db_name; // get db name which we shall append data to it
      std::vector<std::string> keys;
      std::vector<std::string> values;

      if (result) {
        db_name = argv[index + 1];
      } else {
        std::cerr << "give me database name ! \n";
        std::exit(EXIT_FAILURE);
      }

      result = is_Arg_Remained(argc, (index + 2));
      if (!result) { // user passed db name but didn't pass number of args
        std::cerr << "path, number of args, args...\n";
        std::exit(EXIT_FAILURE);
      }

      int num_Arg{};
      int counter{}; // takes the first index of values
      try {
        num_Arg = std::stoi(argv[index + 2]); // number of args to append
      } catch (std::exception &e) {
        std::cerr << "Bad number ! \n";
        std::exit(EXIT_FAILURE);
      }

      for (int i{1}; i <= num_Arg; ++i) {
        keys.push_back(argv[index + 2 + i]);
        counter = (index + 2 + i);
      }

      for (int i{1}; i <= num_Arg; ++i) {
        values.push_back(argv[counter + i]);
      }

      db::ice_db::append_db(dir + '/' + get_Dir_Add +
                                std::string(argv[index + 1]) + ".icx",
                            keys, values);
    } // end of -ad check

    if (current_Arg == "-r") { // r means remove
      bool result = is_Arg_Remained(argc, (index + 2));
      std::vector<std::string> words_To_Remove;

      if (!result) { // if no argument passed remove whole db
        words_To_Remove.push_back("WHOLE");
        db::ice_db::remove_db(dir + '/' + std::string(argv[index + 1]) + ".icx",
                              words_To_Remove);
      }

      for (int i = index + 2; i <= argc - 1; ++i) {
        words_To_Remove.push_back(argv[i]);
      }
      db::ice_db::remove_db(dir + '/' + std::string(argv[index + 1]) + ".icx",
                            words_To_Remove);
    }

  } // end of for loop
}
} // namespace argxx
