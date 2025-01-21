cmake_minimum_required(VERSION 3.14)


#-----------------------------------------------------------------------
project(basePro)
set(TARGET_EXE ${PROJECT_NAME})
message("Cmake pro: " ${TARGET_EXE})


add_subdirectory(unix_files_info)
add_subdirectory(proc)
# add_subdirectory(pam_simple)
# add_subdirectory(pam_simple2)
add_subdirectory(pam_simple_conv)
add_subdirectory(test_pam_module)
#-----------------------------------------------------------------------

