

set (BEA_SOURCES BeaEngine.c)

if (optBUILD_DLL)
  add_library (BeaEngine SHARED ${BEA_SOURCES})
else ()
  add_library (BeaEngine STATIC ${BEA_SOURCES})
endif ()
