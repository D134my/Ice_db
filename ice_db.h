#ifndef ICE_DB_H
#define ICE_DB_H

#include <experimental/filesystem>
#include <span>
#include <string>
#include <string_view>
#include <vector>

namespace db {
class ice_db {
public:
  static std::experimental::filesystem::path
  create_dir(std::string_view dir_Path = dir_Info.first,
             std::string_view dir_Name = dir_Info.second);

  static std::experimental::filesystem::path
  create_db(std::string_view db_Name = "Ice_DB.icx",
            std::string_view dir_Path = dir_Info.first);

  static void write_db(std::string_view db_Name,
                       std::vector<std::string> const &,
                       std::vector<std::string> const &);

  static void print_db(std::experimental::filesystem::path,
                       std::span<const std::string> args);

  static void append_db(std::experimental::filesystem::path,
                        std::vector<std::string> const &,
                        std::vector<std::string> const &);

  static void remove_db(std::experimental::filesystem::path,
                        std::vector<std::string> const &);

private:
  const static inline std::string def_Path{"/home/ice/"};
  const static inline std::string sep{"/"};
  const static inline std::string def_Name{sep + "ICE_DB"};

public:
  static const inline auto dir_Info = std::make_pair(def_Path, def_Name);
};
} // namespace db
#endif // ICE_DB_H
