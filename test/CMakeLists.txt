#file(GLOB_RECURSE TEST_SOURCES "*.cpp")
#file(GLOB_RECURSE TEST_DIRS LIST_DIRECTORIES true "*")
#
#include_directories(${PROJECT_SOURCE_DIR}/src)
#
#foreach (test_dir ${TEST_DIRS})
#    get_filename_component(dir_name ${test_dir} NAME)
#    file(GLOB tests "${test_dir}/*.cpp")
#    if (tests)
#        add_executable(${dir_name}_tests ${tests})
#
#        target_include_directories(${dir_name}_tests PRIVATE
#                ${PROJECT_SOURCE_DIR}/src
#        )
#
#        target_link_libraries(${dir_name}_tests PRIVATE
#                gtest gtest_main YanLib
#        )
#        add_test(NAME ${dir_name}_tests COMMAND ${dir_name}_tests)
#    endif ()
#endforeach ()


file(GLOB_RECURSE TEST_SOURCES "*.cpp")

include_directories(${PROJECT_SOURCE_DIR}/src)

foreach (test_source ${TEST_SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)
    add_executable(${test_name} ${test_source})

    target_include_directories(${test_name} PRIVATE
            ${PROJECT_SOURCE_DIR}/src
    )

    target_link_libraries(${test_name} PRIVATE
            gtest gtest_main YanLib
    )
    add_test(NAME ${test_name}
            COMMAND ${test_name})
endforeach ()