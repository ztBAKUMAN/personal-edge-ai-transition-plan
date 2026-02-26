file(GLOB SOURCES "src/*.cpp")

add_executable(factory ${SOURCES})

target_include_directories(factory PRIVATE include)