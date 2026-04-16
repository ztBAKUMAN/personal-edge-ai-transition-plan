file(GLOB SOURCES "src/*.cpp")

add_executable(threadpool ${SOURCES})

target_include_directories(threadpool PRIVATE include)