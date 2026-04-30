cmake_minimum_required(VERSION 3.16)

project(hms VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(apphms
    src/main.cpp
    sfml/app.cpp
    #src/admin.cpp
    #src/doctor.cpp
    #src/patient.cpp
    #src/person.cpp
    #src/char_array_functions.cpp
    #src/apppointment.cpp
    #src/bill.cpp
    #src/file_handler.cpp
    #src/parser.cpp
    #src/prescription.cpp
    #src/validator.cpp
    #src/hospital_exception.cpp
    #src/invalid_input_exception.cpp
    #src/insufficent_funds_exception.cpp
    #src/file_not_found_exception.cpp
    #src/slot_unavailable_exception.cpp

)

target_include_directories(apphms PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/sfml
)

target_link_libraries(apphms PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

set_target_properties(apphms PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS apphms
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
