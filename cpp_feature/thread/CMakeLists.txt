BUILD_MAIN_MACRO(thread1)
find_package(Threads REQUIRED )
target_link_libraries(thread1 Threads::Threads)