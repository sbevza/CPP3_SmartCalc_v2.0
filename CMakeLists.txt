cmake_minimum_required(VERSION 3.26)
project(CPP3_SmartCalc_v2_0_1)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(CPP3_SmartCalc_v2_0_1
        src/controller/controller.cc
        src/controller/controller.h
        src/model/model.cc
        src/model/model.h
        src/main.cc
        src/view/deposit.h
        src/view/credit.cc
        src/model/model_credit.cc
        src/tests/check_run_tests.cc
        src/tests/check_s21_SmartCalc.cc
        src/model/model_deposit.cc
        src/view/mainwindow.cc
        src/view/mainwindow.cc
)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

target_link_libraries(CPP3_SmartCalc_v2_0_1 gtest gtest_main Qt6::Core Qt6::Widgets)
