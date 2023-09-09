# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/pi_logic__autogen.dir/AutogenUsed.txt"
  "CMakeFiles/pi_logic__autogen.dir/ParseCache.txt"
  "pi_logic__autogen"
  )
endif()
