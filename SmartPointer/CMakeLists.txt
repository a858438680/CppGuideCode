add_executable(simple_unique_ptr ${CMAKE_CURRENT_SOURCE_DIR}/simple_unique_ptr.cpp)
add_executable(unique_ptr1 ${CMAKE_CURRENT_SOURCE_DIR}/unique_ptr1.cpp)
add_executable(unique_ptr2 ${CMAKE_CURRENT_SOURCE_DIR}/unique_ptr2.cpp)
add_executable(unique_ptr_cycle ${CMAKE_CURRENT_SOURCE_DIR}/unique_ptr_cycle.cpp)
add_executable(simple_shared_ptr ${CMAKE_CURRENT_SOURCE_DIR}/simple_shared_ptr.cpp)
add_executable(shared_ptr1 ${CMAKE_CURRENT_SOURCE_DIR}/shared_ptr1.cpp)
add_executable(shared_ptr_cycle ${CMAKE_CURRENT_SOURCE_DIR}/shared_ptr_cycle.cpp)

set(link_thread_list
    shared_ptr1
)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    foreach(target ${link_thread_list})
        target_link_libraries(${target} PRIVATE pthread)
    endforeach()
endif()