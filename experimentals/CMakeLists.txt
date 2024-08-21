file(GLOB_RECURSE LEXER_PATH
    lexer.cpp
  )
  
add_executable(lexer ${LEXER_PATH})
target_link_libraries(lexer
  mini_tablegen
)