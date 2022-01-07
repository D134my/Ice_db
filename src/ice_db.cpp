#include "ice_db.hpp"
#include "argxx.hpp"
#include <experimental/filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::experimental::filesystem;

namespace db {

fs::path ice_db::create_dir(std::string_view dir_Path,
                            std::string_view dir_Name) {
  fs::path d_Path{std::string(dir_Path) + std::string(dir_Name)};

  if (!fs::exists(d_Path)) {
    fs::create_directory(d_Path);
  }

  fs::permissions(d_Path, fs::perms::all);

  // fs::path tmp_Path = fs::temp_directory_path() / ".Icxxx";

  fs::path tmp_Path = getenv("HOME");
  std::ofstream ofs(tmp_Path / ".Icxxx");
  ofs << d_Path.string(); // save path of db directory

  ofs.close();
  return d_Path;
}

fs::path ice_db::create_db(std::string_view db_Name,
                           std::string_view dir_Path) {
  fs::path db_Path;
  fs::path exac_db;

  auto add_Prefix = db_Name.find(".icx");

  if (add_Prefix ==
      std::string::npos) { // if passed db name has not .icx append to it

    exac_db = std::string(db_Name).append(".icx");
    db_Path = std::string(dir_Path) + (std::string(db_Name).append(".icx"));
  } else {
    exac_db = db_Name;
    db_Path = std::string(dir_Path) + db::ice_db::def_Name + '/' +
              std::string(db_Name);
  }

  // create db file
  if (!fs::exists(db_Path)) {
    std::ofstream ofs{db_Path};
    ofs << "ICXXX" << std::endl;
    ofs.close();
  } else {
    return exac_db;
  }
  return exac_db;
}

void ice_db::write_db(std::string_view db_Name,
                      std::vector<std::string> const &names,
                      std::vector<std::string> const &values) noexcept {

  fs::path db_Path = db_Name;
  std::ofstream ofs{db_Path};

  for (std::size_t i{}; i < names.size();
       ++i) { // write data like keys values to db
    ofs << names[i] << ' ';
    ofs << values[i] << std::endl;
  }
  ofs.close();
}

void ice_db::print_db(std::experimental::filesystem::path p,
                      std::span<const std::string> args) noexcept {

  std::ifstream ifs(p);
  std::string return_key{};
  std::string return_value{};

  if (args.front() == "WHOLE") { // print whole db
    if (ifs.is_open()) {
      std::cout << ifs.rdbuf();
      std::exit(EXIT_SUCCESS);
    } else {
      std::cerr << "can't read data " << __LINE__ << std::endl;
      std::exit(EXIT_FAILURE);
    }
  }

  for (auto const &word : args) {
    ifs.clear();
    ifs.seekg(0); // back to first of the file

    while (ifs) {
      ifs >> return_key;
      ifs >> return_value;
      if (return_key == word) {
        if (word == args.back()) {
          std::cout << word << " -> " << return_value << std::endl;
          ifs.close();
          std::exit(EXIT_SUCCESS);
        }
        std::cout << return_key << " -> " << return_value << std::endl;
      } // end of first if
    }   // end of while
  }     // end of for

  ifs.close();
}

void ice_db::append_db(std::experimental::filesystem::path p,
                       std::vector<std::string> const &keys,
                       std::vector<std::string> const &values) noexcept {

  if (keys.size() == values.size()) { // check the size
    std::ofstream ofs;
    ofs.open(p, std::ios::app);
    for (std::size_t i{}; i < keys.size(); ++i) {

      try {
        ofs << keys.at(i) << ' ';
        ofs << values.at(i) << std::endl;
      } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
      }

    } // end of for
    ofs.close();

  } // end of if -> if the size was not the same then
  else {
    std::cerr << "kays and values don't have same size  " << __LINE__ << '\n';
    std::exit(EXIT_FAILURE);
  }
}

void ice_db::remove_db(std::experimental::filesystem::path p,
                       const std::vector<std::string> &word) noexcept {
  std::ifstream ifs;
  std::ofstream ofs;

  if (word.front() == "WHOLE") { // remove whole db
    try {
      fs::remove(p);
      ofs.open(p, std::ios::out);
      ofs << "";
      std::exit(EXIT_SUCCESS);
    } catch (...) {
      std::cerr << "can't remove file !" << __LINE__ << '\n';
      std::exit(EXIT_FAILURE);
    }
  }

  std::string result_Of_Keys{};
  std::string result_Values{};

  for (auto const &key : word) {
    ifs.clear();
    ifs.seekg(0);

    try {
      // create a tmp file to save data to it and rename it to db name

      ifs.open(p, std::ios::in);
      ofs.open(p.string() + ".tmp", std::ios::app);
      while (ifs) {
        ifs >> result_Of_Keys;
        ifs >> result_Values;

        if (result_Of_Keys != key) {
          ofs << result_Of_Keys << ' ';
          ofs << result_Values << std::endl;

          if (result_Of_Keys == word.back()) { // fix last element problem
            ofs << result_Of_Keys << ' ';
            ofs << result_Values << std::endl;
            std::exit(EXIT_SUCCESS);
          }
        } else
          continue;
      }

    } catch (std::exception e) {
      std::cerr << "can't remove words " << __LINE__ << std::endl;
      std::exit(EXIT_SUCCESS);
    }
    ifs.close();
    ofs.close();

    fs::remove(p); // remove previous db and make tmp main db
    fs::rename(p.string() + ".tmp", p);
  }
}

void ice_db::help_db() noexcept {
  // heh you can not read this method

  std::system("clear");
  std::cout << "\n\t\t\t  	ICE DATABASE ^^ \t\n" << std::endl;
  std::cout << "-c   creates a directory for database   -> (dir_path, dir_name)"
            << std::endl;
  std::cout << "-d   creates a database 		-> (dir_name)"
            << std::endl;
  std::cout << "-n   writes data to database  		-> (number of args, "
               "keys, "
               "values)"
            << std::endl;
  std::cout << "-ad  appends to database	        -> (db_name, number "
               "of args, keys, values)"
            << std::endl;

  std::cout << "-gd  gets database data             "
               "    -> (db_name,args...[if no "
               "arg passed prints whole db])"
            << std::endl;
  std::cout
      << "-r   removes data from database         -> (db_name, args...[if no "
         "arg passed removes whole db)"
      << std::endl;

  std::cout << "-h   help menu                          -> (nothing)"
            << std::endl;

  std::endl(std::cout);
  std::cout << "EXAMPLES \n";
  std::cout << "===================================================\n";
  std::cout << "IceDB -c /tmp/ test -d my_DB -n 2 NAME AGE Ice 20 "
            << std::endl;
  std::cout << "===================================================\n";

  std::endl(std::cout);

  std::exit(EXIT_SUCCESS);
}

} // namespace db
