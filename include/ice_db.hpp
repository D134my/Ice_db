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
  // a little bit optimization

  ice_db() = default;
  ~ice_db() = default;
  ice_db(ice_db const &) = delete;
  ice_db(ice_db &&) = delete;

  [[maybe_unused]] [[nodiscard(
      "take the path")]] static std::experimental::filesystem::path
  create_dir(std::string_view dir_Path = dir_Info.first,
             std::string_view dir_Name = dir_Info.second);

  [[maybe_unused]] [[nodiscard(
      "take the name!")]] static std::experimental::filesystem::path

  create_db(std::string_view db_Name = "Ice_DB.icx",
            std::string_view dir_Path = dir_Info.first);

  [[maybe_unused]] static void
  write_db(std::string_view db_Name, std::vector<std::string> const &,
           std::vector<std::string> const &) noexcept;

  [[maybe_unused]] static void
  print_db(std::experimental::filesystem::path,
           std::span<const std::string> args) noexcept;

  [[maybe_unused]] static void
  append_db(std::experimental::filesystem::path,
            std::vector<std::string> const &,
            std::vector<std::string> const &) noexcept;

  [[maybe_unused]] static void
  remove_db(std::experimental::filesystem::path,
            std::vector<std::string> const &) noexcept;

  [[maybe_unused]] static void help_db() noexcept;

private:
  const static inline std::string def_Path{"/home/ice/"};
  const static inline std::string sep{"/"};
  const static inline std::string def_Name{sep + "ICE_DB"};

public:
  static const inline auto dir_Info = std::make_pair(def_Path, def_Name);
};

} // namespace db

#endif // ICE_DB_H
