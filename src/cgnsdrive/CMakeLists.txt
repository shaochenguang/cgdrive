message("CMAKE_CL_64: " ${CMAKE_CL_64})

if(${CMAKE_CL_64}) 
    if (MSVC)
        PROJECT(cgnsdrive64)
        set(ADDRESS_MODEL 64)
        set(NODE_TARGET x64)
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
        ADD_LIBRARY(cgnsdrive64 SHARED ${SOURCE_FILES})
    endif()
else()
    if (MSVC)
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
        ADD_LIBRARY(cgnsdrive SHARED ${SOURCE_FILES})
    endif()
endif()
