file(GLOB SRC_LIST "*.cpp")
file(GLOB HEADERS "*.h")

add_library(devcore ${SRC_LIST} ${HEADERS})
target_include_directories(devcore PUBLIC ${BOOST_INCLUDE_DIR})

target_link_libraries(devcore PRIVATE Boost::Filesystem Boost::Thread)
add_dependencies(devcore Boost::Thread)
