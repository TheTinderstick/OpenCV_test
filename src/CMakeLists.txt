file(GLOB Sources "*.cpp")

set(OpenCV_DIR "../../OpenCV/build/")
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( "../include" )

add_executable(OpenCV_test ${Sources})
target_link_libraries( OpenCV_test ${OpenCV_LIBS} )

install(TARGETS OpenCV_test DESTINATION bin)
