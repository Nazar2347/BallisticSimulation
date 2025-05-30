file(GLOB_RECURSE RENDER_HEADERS CONFIGURE_DEPENDS "./include/*.h")
file (GLOB_RECURSE RENDER_SOURSES CONFIGURE_DEPENDS "./source/*.cpp")

project (RenderLibrary)

add_library(${PROJECT_NAME} 
	 ${RENDER_HEADERS} 
	 ${RENDER_SOURSES}
)

target_include_directories (${PROJECT_NAME}
	PUBLIC "./include"
	PRIVATE "./source"
)

include (FetchContent)

FetchContent_Declare(
	raylib
	GIT_REPOSITORY https://github.com/raysan5/raylib.git
	GIT_TAG 5.5
)

FetchContent_Declare(
		raygui
		GIT_REPOSITORY https://github.com/raysan5/raygui.git
		GIT_TAG 4.0
)

FetchContent_MakeAvailable(raylib)
FetchContent_MakeAvailable(raygui)

# Create an INTERFACE target for raygui
add_library(raygui INTERFACE)

# Add include path to interface target
target_include_directories(raygui INTERFACE
    ${raygui_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} PUBLIC raylib)
target_link_libraries(${PROJECT_NAME} PUBLIC raygui)
target_link_libraries(${PROJECT_NAME} PUBLIC CoreLibrary)
