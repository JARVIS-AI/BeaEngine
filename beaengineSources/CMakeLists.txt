set (BEA_SOURCES BeaEngine.c)

if (optBUILD_DLL)
  add_library (${BEA_TARGET} SHARED BeaEngine.c)
else ()
  add_library (${BEA_TARGET} STATIC BeaEngine.c)
endif ()
