include(ExternalProject)

# Download RapidJSON
ExternalProject_Add(
    freeglut
    GIT_REPOSITORY "https://github.com/dcnieho/FreeGLUT.git"
    GIT_TAG 349a23dcc1264a76deb79962d1c90462ad0c6f50
    TIMEOUT 10
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    UPDATE_COMMAND ""
)

# Prepare RapidJSON (RapidJSON is a header-only library)
ExternalProject_Get_Property(freeglut source_dir)
set(FREEGLUT_INCLUDE_DIR ${source_dir}/freeglut/freeglut/include)