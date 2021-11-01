set (CMAKE_CXX_STANDARD 17)
cmake_minimum_required (VERSION 3.8)

project ("owo-pkg")
add_executable (owo "src/owo-pkg.h" "src/owo-pkg.cpp" "src/cli.h" "src/cli.cpp" "src/http.h" "src/http.cpp" "src/commands/install.h" "src/commands/install.cpp" "src/commands/remove.h" "src/commands/remove.cpp" "src/commands/update.h" "src/commands/update.cpp")

# Set vars
set(CMAKE_MODULE_PATH lib)
set(EXTERNAL_LIB_HEADERS lib/curlpp/include lib/indicators/include lib/json/include)

# Compile curlpp
add_subdirectory(lib/curlpp)

# Compile indicators
add_subdirectory(lib/indicators)

# Compile json
add_subdirectory(lib/json)

# Include libraries
target_include_directories(owo PRIVATE ${EXTERNAL_LIB_HEADERS})

# Link libraries
target_link_libraries(owo PUBLIC curlpp indicators nlohmann_json)
