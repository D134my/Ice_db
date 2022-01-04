include_directories(../include)
aux_source_directory(./ Sources)
add_executable( ice_db_program ${Sources} )
