file(GLOB_RECURSE BIN_PATH
    *.cc
  )
  
add_executable(mini_tblgen ${BIN_PATH})
target_link_libraries(mini_tblgen
  mini_tablegen
)