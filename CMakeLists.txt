cmake_minimum_required(VERSION 3.24)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled src/main.cpp src/Workflow/workflow_functions.cpp src/Workflow/workflow_functions.h tests/workflow_functions_test.cpp tests/workflow_functions_test.cpp.h src/Workflow/Workflow.cpp src/Workflow/Workflow.h)
