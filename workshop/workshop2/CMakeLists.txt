add_executable(workshop2 main.cpp)

target_include_directories(workshop2 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(workshop2 PUBLIC cxx_std_17)
target_compile_definitions(workshop2 PRIVATE SFML_STATIC)

target_link_libraries(workshop2 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
