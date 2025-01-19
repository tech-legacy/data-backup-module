#############################################################################
## MIT License
## 
## Author	: xiaofeng.zhu
## Support	: zxffffffff@outlook.com, 1337328542@qq.com
## 
#############################################################################

project(data-backup)
message("[${PROJECT_NAME}] -------- start")

message(STATUS "[${PROJECT_NAME}] PROJECT_SOURCE_DIR : ${PROJECT_SOURCE_DIR}")

# 引入 boost (大部分 header-only 的库不需要 link)
find_package(Boost REQUIRED)
message(STATUS "[${PROJECT_NAME}] Boost_VERSION_STRING : ${Boost_VERSION_STRING}")
message(STATUS "[${PROJECT_NAME}] Boost_INCLUDE_DIRS : ${Boost_INCLUDE_DIRS}")
message(STATUS "[${PROJECT_NAME}] Boost_LIBRARY_DIRS : ${Boost_LIBRARY_DIRS}")

# 引入 nlohmann-json
find_package(nlohmann_json CONFIG REQUIRED)

# 引入 tinyxml
find_package(tinyxml2 CONFIG REQUIRED)

# 引入 fmt
find_package(fmt CONFIG REQUIRED)

# Public 头文件
file(GLOB_RECURSE include_headers
    common/cpp_version.h
    common/cpp_def.h
    common/common.h
    common/platform.h
    common/hardware.h
    common/chrono.h
    common/log.h
    common/benchmark.h
    common/interface/threadpool_interface.h
    common/interface/threadtimer_interface.h
    common/impl/progschj-ThreadPool.h
    common/impl/stl_threadpool_impl.h # use "progschj-ThreadPool.h"
    common/impl/stl_threadtimer_impl.h
    define.h
    DataBackup.h
)

add_library(${PROJECT_NAME} SHARED
    DataBackup.cpp
    ${include_headers}
)

# dynamic 导出宏
target_compile_definitions(${PROJECT_NAME}
    PRIVATE DATA_BACKUP_LIB_EXPORT
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC nlohmann_json::nlohmann_json
    PUBLIC tinyxml2::tinyxml2
    PUBLIC fmt::fmt-header-only
    # PUBLIC simple-cryptography
)

if(APPLE)
    # hardware 依赖系统库
    target_link_libraries(${PROJECT_NAME}
        PUBLIC "-framework CoreFoundation"
        PUBLIC "-framework IOKit"
    )
endif()

target_include_directories(${PROJECT_NAME}
    PUBLIC ${Boost_INCLUDE_DIRS}
    PUBLIC ${PROJECT_SOURCE_DIR}
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    PUBLIC_HEADER "${include_headers}"
)

install(TARGETS ${PROJECT_NAME}
    PUBLIC_HEADER DESTINATION include
    RUNTIME DESTINATION bin # .dll
    LIBRARY DESTINATION bin # .dylib .so
    ARCHIVE DESTINATION lib # .lib .a
)

message("[${PROJECT_NAME}] -------- done")
