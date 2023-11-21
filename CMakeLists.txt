cmake_minimum_required(VERSION 3.26)
project(CPP3_SmartCalc_v2_0_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(CPP3_SmartCalc_v2_0_1
        src/view/consoleView.cc
        src/view/consoleView.h
        src/controller/controller.cc
        src/controller/controller.h
        src/model/model.cc
        src/model/model.h
        src/main.cc
        src/model/s21_SmartCalc.h
        src/model/s21_SmartCalc.cc
)
