set (CMAKE_CXX_STANDARD 17)
cmake_minimum_required (VERSION 3.8)

project ("owo-pkg")
add_executable (owo
"src/owo-pkg.cpp"
"src/cli.cpp"
"src/http.cpp"
"src/repo.cpp"
"src/package.cpp"
"src/utils/crypto.cpp"
"src/commands/install.cpp"
"src/commands/remove.cpp"
"src/commands/search.cpp"
"src/commands/update.cpp"
)

# Set vars
set(CMAKE_MODULE_PATH lib)
set(EXTERNAL_LIB_HEADERS lib/curlpp/include lib/clipp/include lib/indicators/include lib/json/include lib/toml11 lib/zlib)
set(OPENSSL_USE_STATIC_LIBS TRUE)

# Compile curlpp
add_subdirectory(lib/curlpp)

# Compile indicators
add_subdirectory(lib/indicators)

# Compile json
add_subdirectory(lib/json)

# Compile toml
add_subdirectory(lib/toml11)

# Compile toml
add_subdirectory(lib/zlib)

find_package(OpenSSL REQUIRED)

# Include libraries
target_include_directories(owo PRIVATE ${EXTERNAL_LIB_HEADERS})

# Link libraries
target_link_libraries(owo PUBLIC curlpp indicators nlohmann_json toml11 OpenSSL::SSL zlib)
