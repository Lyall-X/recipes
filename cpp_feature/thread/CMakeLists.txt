BUILD_ALL_MAIN_MACRO()
find_package(Threads REQUIRED )
target_link_libraries(thread1 Threads::Threads)