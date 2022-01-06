#include "ice_db.h"
#include "argxx.h"
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

  std::cout << "create dir : " << d_Path << std::endl;

  fs::path tmp_Path = fs::temp_directory_path() / ".Icxxx";
  std::ofstream ofs(tmp_Path);
  ofs << d_Path.string();

  ofs.close();
  return d_Path;
}

fs::path ice_db::create_db(std::string_view db_Name,
                           std::string_view dir_Path) {
  fs::path db_Path;
  fs::path exac_db;
  auto add_Prefix = db_Name.find(".icx");

  if (add_Prefix == std::string::npos) {

    exac_db = std::string(db_Name).append(".icx");
    db_Path = std::string(dir_Path) + (std::string(db_Name).append(".icx"));
  } else {
    exac_db = db_Name;
    db_Path = std::string(dir_Path) + db::ice_db::def_Name + '/' +
              std::string(db_Name);
  }

  std::cout << "create db " << db_Path << std::endl;
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
                      std::vector<std::string> const &values) {

  fs::path db_Path = db_Name;
  std::ofstream ofs{db_Path};

  std::cout << "write db " << db_Path << std::endl;
  for (std::size_t i{}; i < names.size(); ++i) {
    ofs << names[i] << ' ';
    ofs << values[i] << std::endl;
  }
  ofs.close();
}

void ice_db::print_db(std::experimental::filesystem::path p,
                      std::span<const std::string> args) {

  std::ifstream ifs(p);
  std::string return_key{};
  std::string return_value{};

  if (args.front() == "NULL") { // print whole db
    if (ifs.is_open()) {
      std::cout << ifs.rdbuf();
      std::exit(EXIT_SUCCESS);
    }
  }

  for (auto const &word : args) {
    ifs.clear();
    ifs.seekg(0);

    while (ifs) {
      ifs >> return_key;
      ifs >> return_value;
      if (return_key == word) {
        ifs >> return_value;
        if (word == args.back()) {
          std::cout << word << " -> " << return_value << std::endl;
          ifs.close();
          std::exit(EXIT_SUCCESS);
        }
        std::cout << return_key << " -> " << return_value << std::endl;
      }
    }
  }
  ifs.close();
}

void ice_db::append_db(std::experimental::filesystem::path p,
                       std::vector<std::string> const &keys,
                       std::vector<std::string> const &values) {
  if (keys.size() == values.size()) {
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
    }
    ofs.close();

  } else {
    std::cerr << "kays and values don't have same size  \n";
    std::exit(EXIT_FAILURE);
  }
}

void ice_db::remove_db(std::experimental::filesystem::path p,
                       const std::vector<std::string> &word) {
  std::ifstream ifs;
  std::ofstream ofs;

  if (word.front() == "WHOLE") {
    try {
      fs::remove(p);
      ofs.open(p, std::ios::out);
      ofs << "";
      std::exit(EXIT_SUCCESS);
    } catch (...) {
      std::cerr << "can't remove file !\n";
      std::exit(EXIT_FAILURE);
    }
  }

  std::string result_Of_Keys{};
  std::string result_Values;

  for (auto const &key : word) {
    ifs.clear();
    ifs.seekg(0);
    try {
      ifs.open(p, std::ios::in);
      ofs.open(p.string() + ".tmp", std::ios::app);
      while (ifs) {
        ifs >> result_Of_Keys;
        ifs >> result_Values;
        if (result_Of_Keys != key) {
          ofs << result_Of_Keys << ' ';
          ofs << result_Values << std::endl;
          if (result_Of_Keys == word.back()) {
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

    fs::remove(p);
    fs::rename(p.string() + ".tmp", p);
  }
}
} // namespace db
