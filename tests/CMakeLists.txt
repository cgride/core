function(cgride_core_add_test name source)
  add_executable(${name}
    ${source}
  )

  target_link_libraries(${name}
    PRIVATE
      cgride::core
  )

  target_compile_features(${name}
    PRIVATE
      cxx_std_23
  )

  set_target_properties(${name}
    PROPERTIES
      CXX_EXTENSIONS OFF
  )

  add_test(
    NAME ${name}
    COMMAND ${name}
  )
endfunction()

cgride_core_add_test(cgride_core_result_test result_test.cpp)
cgride_core_add_test(cgride_core_error_test error_test.cpp)
cgride_core_add_test(cgride_core_command_test command_test.cpp)
cgride_core_add_test(cgride_core_path_test path_test.cpp)
cgride_core_add_test(cgride_core_hash_test hash_test.cpp)
