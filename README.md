# Ice_db                       

### Simple command line database for Unix-like systems
### `Ice_db` installation
```
git clone https://github.com/IceIsHere/Ice_db
```
```
cd Ice_db && cmake -Bbuild -H. && cd build && make 
```
```
sudo make install
```
## Usage
```
-c   creates a directory for database   -> (dir_path, dir_name)
-d   creates a database                 -> (dir_name)
-n   writes data to database            -> (number of args, keys, values)
-ad  appends to database                -> (db_name, number of args, keys, values)
-gd  gets database data                 -> (db_name,args...[if no arg passed prints whole db])
-r   removes data from database         -> (db_name, args...[if no arg passed removes whole db)
-h   help menu                          -> (nothing)

EXAMPLES 
===================================================
IceDB -c /tmp/ test -d my_DB -n 2 NAME AGE Ice 20 
===================================================
```

## Demo
![Ice_DB demo](icedb.gif)

 [![forthebadge](https://forthebadge.com/images/badges/made-with-c-plus-plus.svg)](https://forthebadge.com)
