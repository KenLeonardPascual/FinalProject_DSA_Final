# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\FinalProject_DSA_Final_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\FinalProject_DSA_Final_autogen.dir\\ParseCache.txt"
  "FinalProject_DSA_Final_autogen"
  )
endif()
