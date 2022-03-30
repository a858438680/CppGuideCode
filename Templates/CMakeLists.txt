add_executable(
    explicit_instantiation
    ${CMAKE_CURRENT_SOURCE_DIR}/ExplicitInstantiation/main.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/ExplicitInstantiation/int_impl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ExplicitInstantiation/string_impl.cpp)