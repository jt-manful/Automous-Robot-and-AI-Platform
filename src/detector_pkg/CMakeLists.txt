cmake_minimum_required(VERSION 3.8)
project(detector_pkg)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(/opt/onnxruntime/include)
link_directories(/opt/onnxruntime/lib)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)
find_package(vision_msgs REQUIRED)

add_executable(detector_node
  src/main.cpp
  src/detector_node.cpp
  
)

add_executable(onnx_test src/onnx_test.cpp)

target_link_libraries(onnx_test
    onnxruntime
)
target_compile_features(detector_node PUBLIC cxx_std_17)

ament_target_dependencies(detector_node
  rclcpp
  sensor_msgs
  vision_msgs
  cv_bridge
  OpenCV
)



target_include_directories(detector_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_link_libraries(detector_node
    ${OpenCV_LIBS}
    onnxruntime
)

install(TARGETS detector_node
  onnx_test
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()