add_executable(workshop4 main.cpp)

target_include_directories(workshop4 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(workshop4 PUBLIC cxx_std_17)
target_compile_definitions(workshop4 PRIVATE SFML_STATIC)

target_link_libraries(workshop4 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
