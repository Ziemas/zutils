add_executable(test
    bitfield.cc
    bitutils.cc)
target_link_libraries(test PRIVATE Catch2::Catch2)
target_include_directories(test PRIVATE ../include)
