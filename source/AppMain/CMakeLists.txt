project (mainExecutable)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ./)

target_link_libraries(${PROJECT_NAME} PUBLIC RenderLibrary)
target_link_libraries(${PROJECT_NAME} PUBLIC CoreLibrary)