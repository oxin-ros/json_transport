set(JSON_HEADER_PATH ${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}/nlohmann/json.hpp)

if(NOT EXISTS ${JSON_HEADER_PATH})

    # Download the JSON library
    set(NLOHMANN_JSON_VERSION "v3.11.2")
    message(STATUS "Download https://github.com/nlohmann/json/releases/download/${NLOHMANN_JSON_VERSION}/json.hpp")
    file(DOWNLOAD
        https://github.com/nlohmann/json/releases/download/${NLOHMANN_JSON_VERSION}/json.hpp
        ${JSON_HEADER_PATH}
        EXPECTED_HASH SHA256=665fa14b8af3837966949e8eb0052d583e2ac105d3438baba9951785512cf921
    )
endif()