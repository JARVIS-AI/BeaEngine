cmake_minimum_required (VERSION 2.6)
project                (BeaEngine)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

option (optHAS_OPTIMIZED "Turn Optimizations ON"    OFF)
option (optHAS_SYMBOLS   "Build with debug Symbols" ON)
option (optBUILD_64BIT   "Build 64 bits executable" OFF)
option (optBUILD_DLL     "Build Shared Objects"     OFF)
option (optBUILD_STDCALL "Build using stdcall"      OFF)


if (optHAS_OPTIMIZED)
  if (optHAS_SYMBOLS)
    set (CMAKE_BUILD_TYPE relwithdebinfo)
  else (optHAS_SYMBOLS)
    set (CMAKE_BUILD_TYPE release)
  endif (optHAS_SYMBOLS)
else (optHAS_OPTIMIZED)
  if (optHAS_SYMBOLS)
    set (CMAKE_BUILD_TYPE Debug)
  else (optHAS_SYMBOLS)
    set (CMAKE_BUILD_TYPE Debug)
  endif (optHAS_SYMBOLS)
endif (optHAS_OPTIMIZED)

# determine BEA_COMPILER
if (NOT BEA_COMPILER)
  if (${CMAKE_SYSTEM_NAME} STREQUAL Linux)
    set (BEA_COMPILER gnu)
  endif ()
  if (${CMAKE_SYSTEM_NAME} STREQUAL FreeBSD)
    set (BEA_COMPILER gnu)
  endif ()
  if (${CMAKE_SYSTEM_NAME} STREQUAL SunOS)
    set (BEA_COMPILER suncc)
  endif ()
  if (${CMAKE_SYSTEM_NAME} STREQUAL Windows)
    if (MINGW OR MSYS)
      set (BEA_COMPILER mingw)
    else ()
      if (CYGWIN)
	set (BEA_COMPILER gnu)
      else ()
	set (BEA_COMPILER msvc)
      endif ()
    endif ()
  endif ()
endif ()

# =========================================
# gcc configuration
# =========================================
if (BEA_COMPILER STREQUAL gnu)
  set (CMAKE_C_COMPILER   gcc)
  set (CMAKE_CXX_COMPILER g++)
  set (BEA_WARNINGS -Wall -W -Wextra -Wconversion -Wno-long-long)
  set (BEA_FLAGS    -pedantic -ansi -pipe)
  if (optHAS_SYMBOLS)
    list (APPEND BEA_FLAGS -g)
  endif ()
  if (optHAS_OPTIMIZED)
    list (APPEND BEA_FLAGS -fomit-frame-pointer -O2)
  endif ()
  if (optBUILD_64BIT)
    list (APPEND BEA_FLAGS -m64)
  endif ()
endif ()
# =========================================
# SunStudio configuration
# =========================================
if (BEA_COMPILER STREQUAL suncc)
  set (CMAKE_C_COMPILER   cc)
  set (CMAKE_CXX_COMPILER CC)
endif ()
# =========================================
# Visual Studio configuration
# =========================================
if (BEA_COMPILER STREQUAL msvc)
  set (CMAKE_C_COMPILER   cl)
  set (CMAKE_CXX_COMPILER cl)
endif ()
# =========================================
# Intel Compiler configuration
# =========================================
if (BEA_COMPILER STREQUAL intel)
  set (CMAKE_C_COMPILER   icc)
  set (CMAKE_CXX_COMPILER icpc)
  set (BEA_WARNINGS -Wall -Wcheck -Wp64)
  set (BEA_FLAGS    -ansi -pipe)
  if (optHAS_SYMBOLS)
    list (APPEND BEA_FLAGS -g)
  endif ()
  if (optHAS_OPTIMIZED)
    list (APPEND BEA_FLAGS -fomit-frame-pointer -O2)
  endif ()
  if (optBUILD_64BIT)
    list (APPEND BEA_FLAGS -m64)
  endif ()
endif ()


# ============================================
# construct compiler flags
# ============================================
set (myC_FLAGS "")
set (myCXX_FLAGS "")

foreach (flag ${BEA_FLAGS})
  set (myC_FLAGS "${myC_FLAGS} ${flag}")
endforeach ()

foreach (flag ${BEA_WARNINGS})
  set (myC_FLAGS "${myC_FLAGS} ${flag}")
endforeach ()

foreach (flag ${BEA_FLAGS})
  set (myCXX_FLAGS "${myCXX_FLAGS} ${flag}")
endforeach ()

foreach (flag ${BEA_WARNINGS})
  set (myCXX_FLAGS "${myCXX_FLAGS} ${flag}")
endforeach ()

# ================================================
# pass compiler flags to cmake
# ================================================

if (${CMAKE_BUILD_TYPE} STREQUAL RelWithDebInfo)
  set (CMAKE_C_FLAGS_RELWITHDEBINFO   ${myC_FLAGS})
  set (CMAKE_CXX_FLAGS_RELWITHDEBINFO ${myCXX_FLAGS})
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL Release)
  set (CMAKE_C_FLAGS_RELEASE   ${myC_FLAGS})
  set (CMAKE_CXX_FLAGS_RELEASE ${myCXX_FLAGS})
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL DebugFull)
  set (CMAKE_C_FLAGS_DEBUGFULL   ${myC_FLAGS})
  set (CMAKE_CXX_FLAGS_DEBUGFULL ${myCXX_FLAGS})
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
  set (CMAKE_C_FLAGS_DEBUG   ${myC_FLAGS})
  set (CMAKE_CXX_FLAGS_DEBUG ${myCXX_FLAGS})
endif ()



add_definitions     (${BEA_DEFINITIONS})
include_directories (${BEA_SRC_ROOT} ${BEA_INCLUDE_PATH})
link_directories    (${BEA_LIBS_PATH})

# ======================================
# set output dirs
# ======================================

set (myQualification "${CMAKE_SYSTEM_NAME}.${BEA_COMPILER}.${CMAKE_BUILD_TYPE}")
set (myLIB_OUTPUT "${CMAKE_SOURCE_DIR}/lib/${myQualification}" )
set (myBIN_OUTPUT "${CMAKE_SOURCE_DIR}/bin/${myQualification}")
set (myOBJ_OUTPUT obj)

if (optBUILD_64BIT)
  set (myLIB_OUTPUT "${myLIB_OUTPUT}.64" )
  set (myBIN_OUTPUT "${myBIN_OUTPUT}.64")
  set (myOBJ_OUTPUT "${myOBJ_OUTPUT}.64")
endif ()

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${myLIB_OUTPUT})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${myLIB_OUTPUT})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${myBIN_OUTPUT})


set (BEA_SOURCES BeaEngine.c)

if (optBUILD_DLL)
  add_library (BeaEngine SHARED ${BEA_SOURCES})
else ()
  add_library (BeaEngine STATIC ${BEA_SOURCES})
endif ()

