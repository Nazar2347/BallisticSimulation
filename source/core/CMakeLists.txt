file (GLOB_RECURSE CORE_HEADERS CONFIGURE_DEPENDS "./include/*.h")
file (GLOB_RECURSE CORE_SOURSES CONFIGURE_DEPENDS "./source/*.cpp")

project(CoreLibrary)

add_library(${PROJECT_NAME} 
	${CORE_HEADERS} 
	${CORE_SOURSES}
)
target_include_directories(${PROJECT_NAME} 
	PUBLIC "./include"
	PRIVATE "./source"
)