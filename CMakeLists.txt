cmake_minimum_required(VERSION 3.10)
project(personal-edge-ai-transition-plan LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "=== Personal Edge AI Transition Plan ===")

# Phase 入口（始终加入）
add_subdirectory(Phase_01_NativeCppFoundation)

# 可选阶段：目录存在时才加入
foreach(PHASE
    Phase_02_LinuxSystemAndNetworking
    Phase_03_PerformanceAndDataPath
    Phase_04_GeneralAIInference
    Phase_05_DatabaseAndMiddleware
    Phase_06_AdvancedTopics
    edge_core
)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${PHASE}/CMakeLists.txt")
        add_subdirectory(${PHASE})
    else()
        message(STATUS "[Info] ${PHASE} not ready yet, skip.")
    endif()
endforeach()
