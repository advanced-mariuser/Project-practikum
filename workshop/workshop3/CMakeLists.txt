add_executable(workshop3 main.cpp)

target_include_directories(workshop3 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(workshop3 PUBLIC cxx_std_17)
target_compile_definitions(workshop3 PRIVATE SFML_STATIC)

target_link_libraries(workshop3 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
