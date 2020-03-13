PROJECT(cgnsdrive)

INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include/
	)
    
SET(SOURCE_FILES
	stdafx.h
    cgddef.h
    stdafx.cpp
	cgdrive.cpp
    cgdrive.def
    cgdmodule.h
    cgdmodule.cpp
    cgdshellview.h
    cgdshellview.cpp
    cgdvirtualfolder.h
    cgdvirtualfolder.cpp
    cgdhook.h
    cgdhook.cpp
    ${CMAKE_SOURCE_DIR}/include/log/logging.h
    ${CMAKE_SOURCE_DIR}/include/log/logging.cpp
)
 
source_group_by_dir(${SOURCE_FILES})

if (MSVC)
    ADD_LIBRARY(cgnsdrive SHARED ${SOURCE_FILES})
endif()