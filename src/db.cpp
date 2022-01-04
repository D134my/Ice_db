#include "db.hpp"
#include "argxx.hpp"
namespace db {

    void create_Db(std::string_view dir_Path, std::string_view dir_Name) {
        const fs::path path {dir_Path};
        try {
            if(fs::exists(path))
                throw std::string_view("dir exists !\n");
        }catch(std::string_view msg) {
            std::cerr << msg << std::endl;
            std::exit(EXIT_FAILURE);
        }

        fs::create_directory(path/dir_Name);
    }// end of create_db

}
