#ifndef __argxx__
#define __argxx__

namespace argxx {
    class args {
        public :

           static  bool check_Args(int argc, char* argv[])noexcept(false);
           static  void get_Args(int argc, char* argv[])   noexcept;
           static  void no_Args()    noexcept;
        private:

    };
}


#endif
