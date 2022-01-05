#include "argxx.hpp"
#include "db.hpp"

#include <iostream>
#include <string_view>

namespace argxx {
    bool args::check_Args(int argc , char* argv[]) noexcept(false) {
        try {
            if(argc == 1)
                throw argc;
        }catch(...) {
            no_Args();
            return false;
        }

        return true; //more than one argument
    }


    void args::get_Args(int argc , char **argv) noexcept {

        std::pair<bool, bool> create_Dir__Db {false, false};
        std::pair<std::string_view, std::string_view> dir_Db_Args
            { db::ice_db::dir_Info.first, db::ice_db::dir_Info.second};

        for(std::size_t index{1}; index < argc; ++index) {
            std::string_view arg {argv[index]};

            if(arg == "-c") {
                create_Dir__Db.first = true;
                if(std::string_view argument{argv[index+1]}; argument != " ") { //I'm gonna fix it morrow
                    dir_Db_Args.first= argument; //path
                    if(std::string_view argument2{argv[index+2]}; argument2 != " ")
                        dir_Db_Args.second = argument2;
                }

            }

           /* if(arg == "-d") {
                create_Dir__Db.second = true;
                //if(std::string_view argument{argv[index+1]}; argument != " ") //I'm gonna fix it morrow
            }
           */

        } //end of for loop
        if(dir_Db_Args.first && dir_Db_Args.second)
            db::ice_db::create_Db(dir_Db_Args.first, dir_Db_Args.second);
        else
            db::ice_db::create_Db();
    } //end of get_args


    void args::no_Args() noexcept {
        std::cerr << "No arguments passed !\n";
    }



}//end of namespace argxx
