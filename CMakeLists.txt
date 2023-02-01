cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_EXPORT_COMPILE_COMMANDS 1) 

project ("owo-pkg")
add_executable (owo
"src/main.cpp"
"src/owopkg.cpp"
"src/core/crypto.cpp"
"src/core/http.cpp"
"src/core/logging.cpp"
"src/core/database.cpp"
"src/repository/repository.cpp"
"src/repository/repository-manager.cpp"
"src/package/package.cpp"
"src/package/package-manager.cpp"
"src/commands/install.cpp"
"src/commands/remove.cpp"
"src/commands/search.cpp"
"src/commands/update.cpp"
"src/utils/platform.cpp"
)

# Set vars
set(CMAKE_MODULE_PATH lib)
#set(EXTERNAL_LIB_HEADERS include)
#set(OPENSSL_USE_STATIC_LIBS TRUE)

# Find packages
find_package(CURL CONFIG REQUIRED)
find_package(ZLIB REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(unofficial-curlpp CONFIG REQUIRED)
find_package(indicators CONFIG REQUIRED)
find_package(toml11 CONFIG REQUIRED)
find_package(clipp CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(RapidJSON CONFIG REQUIRED)

# Include libraries
target_include_directories(owo PRIVATE) # ${EXTERNAL_LIB_HEADERS})

# Link libraries
target_link_libraries(owo PUBLIC unofficial::curlpp::curlpp indicators::indicators clipp::clipp toml11::toml11 OpenSSL::SSL ZLIB::ZLIB unofficial::sqlite3::sqlite3 rapidjson)
