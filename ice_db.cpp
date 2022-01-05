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

void ice_db::print_db(std::experimental::filesystem::path p, int count) {
  std::cout << "counter " << count << std::endl;
  try {
    std::ifstream ifs(p);

    if (ifs.is_open())
      std::cout << ifs.rdbuf();
    else
      throw ifs;
  }

  catch (std::exception e) {
    std::cerr << e.what() << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

} // namespace db
