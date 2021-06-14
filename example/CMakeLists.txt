file(GLOB files ${CMAKE_CURRENT_LIST_DIR}/matrix/*.cpp CONFIGURE_DEPEND)

foreach(file ${files})
    message(STATUS ${file})
    get_filename_component(source ${file} NAME_WE)
    add_executable(${source} ${file})
    target_include_directories(${source}
            BEFORE
            INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_link_libraries(${source} PRIVATE la_include_directories)
endforeach()