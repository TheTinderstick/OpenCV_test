file(GLOB Sources "*.cpp")

set(OpenCV_DIR "$ENV{HOME}/projects/OpenCV/build/")
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( "../include" )

set(GSL_INCLUDE_DIR "$ENV{HOME}/projects/GSL/include")
include_directories( ${GSL_INCLUDE_DIR} )

set(POTRACE_BASE_DIR "/mnt/RaspiYocto/potrace/install")
set(POTRACE_LIB "${POTRACE_BASE_DIR}/lib/libpotrace.a")
set(POTRACE_INC "${POTRACE_BASE_DIR}/include")
include_directories( ${POTRACE_INC} )

add_executable(OpenCV_test ${Sources})
target_link_libraries( OpenCV_test ${OpenCV_LIBS} ${POTRACE_LIB})

install(TARGETS OpenCV_test DESTINATION bin)