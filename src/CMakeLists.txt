file(GLOB Sources "*.cpp")

add_executable(OpenCV_test ${Sources})

install(TARGETS OpenCV_test DESTINATION bin)
