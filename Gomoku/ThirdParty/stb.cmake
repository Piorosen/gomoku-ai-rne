include(ExternalProject)

# Download RapidJSON
ExternalProject_Add(
    stb
    GIT_REPOSITORY "https://github.com/Piorosen/stb"
    GIT_TAG a48d2cfc94489a491689973cfc0daabfc0e7ed91
    TIMEOUT 10
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    UPDATE_COMMAND ""
)

ExternalProject_Get_Property(stb source_dir)
set(STB_INCLUDE_DIR ${source_dir}/include)

