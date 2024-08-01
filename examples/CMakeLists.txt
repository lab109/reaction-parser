
add_executable(o2_reaction_test)


target_sources(o2_reaction_test PRIVATE o2_reaction_example.cpp)

set_target_properties(
    o2_reaction_test
    PROPERTIES CXX_STANDARD 20
               CXX_STANDARD_REQUIRED on
               CXX_EXTENSIONS off
)


target_link_libraries(o2_reaction_test PRIVATE lab109::reaction_parser)