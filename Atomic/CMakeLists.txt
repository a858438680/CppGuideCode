add_executable(non_atomic ${CMAKE_CURRENT_SOURCE_DIR}/non_atomic.cpp)
add_executable(atomic ${CMAKE_CURRENT_SOURCE_DIR}/atomic.cpp)
add_executable(non_sync ${CMAKE_CURRENT_SOURCE_DIR}/non_sync.cpp)
add_executable(sync ${CMAKE_CURRENT_SOURCE_DIR}/sync.cpp)
add_executable(cas_spin_lock ${CMAKE_CURRENT_SOURCE_DIR}/cas_spin_lock.cpp)
add_executable(ticket_spin_lock ${CMAKE_CURRENT_SOURCE_DIR}/ticket_spin_lock.cpp)
add_executable(msc_spin_lock ${CMAKE_CURRENT_SOURCE_DIR}/msc_spin_lock.cpp)

set(link_thread_list
    non_atomic
    atomic
    non_sync
    sync
    cas_spin_lock
    ticket_spin_lock
    msc_spin_lock
)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    foreach(target ${link_thread_list})
        target_link_libraries(${target} PRIVATE pthread)
    endforeach()
endif()