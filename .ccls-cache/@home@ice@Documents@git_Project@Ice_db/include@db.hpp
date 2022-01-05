#ifndef __Ice_DB__
#define __Ice_DB__

#include <iostream>
#include <string>
#include <string_view>
#include <experimental/filesystem>
#include <fstream>
#include <map>

namespace fs = std::experimental::filesystem;
namespace db {

    class ice_db {
        public:
           static bool is_Empty_Dir() noexcept;
           static void create_Db(std::string_view dir_Path = dir_Info.first, std::string_view dir_Name = dir_Info.second) noexcept;
           static std::string_view default_db() noexcept;

        private:
#ifdef __WIN32__
            const std::string_view def_Path {"C:\"};
            const std::string_view sep {"\\"};
#else
             static inline const  std::string def_Path {"~/"};
              static inline const  std::string sep {"/"};
#endif
              static inline const std::string_view dir_Name {def_Path+sep+"ice_DB"};
        public:

                static const inline std::pair<std::string_view, std::string_view> dir_Info
                      = { def_Path, dir_Name };

           };
    }
#endif
