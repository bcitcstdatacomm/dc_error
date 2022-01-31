add_compile_definitions(_POSIX_C_SOURCE=200809L _XOPEN_SOURCE=700)

if (APPLE)
    add_definitions(-D_DARWIN_C_SOURCE)
endif ()

set(TEST_HEADER_LIST
        tests.h
        )

set(TEST_SOURCE_LIST
        main.c
        )

include_directories(${CGREEN_PUBLIC_INCLUDE_DIRS} ${PROJECT_BINARY_DIR})
add_executable(libdc_error_test
        ${TEST_SOURCE_LIST} ${TEST_HEADER_LIST} ${SOURCE_LIST} ${HEADER_LIST})

target_compile_features(libdc_error_test PRIVATE c_std_17)
target_compile_options(libdc_error_test PRIVATE -iquote "${libdc_error_SOURCE_DIR}/include/dc_error")
target_compile_options(libdc_error_test PRIVATE -g)
target_compile_options(libdc_error_test PRIVATE -fstack-protector-all -ftrapv)
target_compile_options(libdc_error_test PRIVATE -Wpedantic -Wall -Wextra)
target_compile_options(libdc_error_test PRIVATE -Wdouble-promotion -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wnull-dereference -Winit-self -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wunused-local-typedefs -Wstrict-overflow=5 -Wmissing-noreturn -Walloca -Wfloat-equal -Wdeclaration-after-statement -Wshadow -Wpointer-arith -Wabsolute-value -Wundef -Wexpansion-to-defined -Wunused-macros -Wno-endif-labels -Wbad-function-cast -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion -Wdangling-else -Wdate-time -Wempty-body -Wsign-conversion -Wfloat-conversion -Waggregate-return -Wstrict-prototypes -Wold-style-definition -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Winvalid-pch -Wlong-long -Wvariadic-macros -Wdisabled-optimization -Wstack-protector -Woverlength-strings)

target_include_directories(libdc_error_test PRIVATE ../include/dc_error)
target_include_directories(libdc_error_test PRIVATE /usr/include)
target_include_directories(libdc_error_test PRIVATE /usr/local/include)

find_library(LIBCGREEN cgreen REQUIRED)
target_link_libraries(libdc_error_test PRIVATE ${LIBCGREEN})

add_test(NAME dc_error_test COMMAND libdc_error_test)
