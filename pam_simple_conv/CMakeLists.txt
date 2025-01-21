cmake_minimum_required(VERSION 3.14)

include(FindPkgConfig)
set(CMAKE_FIND_FRAMEWORK LAST)

#-----------------------------------------------------------------------
project(pam_simple_conv)
set(TARGET_EXE ${PROJECT_NAME})
message("Cmake pro: " ${TARGET_EXE})

find_library(PAM_LIBRARIES NAMES pam)
find_library(PAM_MISC_LIBRARIES NAMES pam_misc)


set (HPP_INCLUDES_DIR ../)
set (CPP_SOURCES ${TARGET_EXE}.c

)

#сначала add_executable
add_executable(${TARGET_EXE} ${CPP_SOURCES}) # Исполняемый файл

#затем опции
target_compile_options(${TARGET_EXE} PRIVATE
            ${PAM_LIB_CFLAGS}
)

target_include_directories(${TARGET_EXE} PRIVATE ${HPP_INCLUDES_DIR})

target_link_libraries(${TARGET_EXE} 
${PAM_LIBRARIES}
${PAM_MISC_LIBRARIES}
pthread
)
#-----------------------------------------------------------------------

