include(ExternalProject)

# Download RapidJSON
ExternalProject_Add(
    stb
    GIT_REPOSITORY "https://github.com/nothings/stb"
    GIT_TAG c0c982601f40183e74d84a61237e968dca08380e
    TIMEOUT 10
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    UPDATE_COMMAND ""
)

ExternalProject_Get_Property(stb source_dir)
set(STB_INCLUDE_DIR ${source_dir})

