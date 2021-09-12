include(ExternalProject)

# Download RapidJSON
ExternalProject_Add(
    spdlog
    GIT_REPOSITORY "https://github.com/gabime/spdlog"
    GIT_TAG eb3220622e73a4889eee355ffa37972b3cac3df5
    TIMEOUT 10
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    UPDATE_COMMAND ""
)

ExternalProject_Get_Property(spdlog source_dir)
set(SPDLOG_INCLUDE_DIR ${source_dir}/include)

