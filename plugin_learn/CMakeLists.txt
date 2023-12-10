cmake_minimum_required(VERSION 3.8)
project(plugin_learn)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)
find_package(pluginlib REQUIRED)
find_package(std_msgs REQUIRED)

install(
  DIRECTORY include/
  DESTINATION include
)


add_library(publisher SHARED src/publisher.cpp)
target_include_directories(publisher PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(publisher PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(publisher
  rclcpp
  pluginlib
  std_msgs
  rclcpp_lifecycle)

install(TARGETS publisher
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

add_executable(publisher_node
  src/main.cpp
)

target_link_libraries(publisher_node publisher)

install(TARGETS publisher_node
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

ament_export_include_directories(
  include
)
ament_export_libraries(
  publisher
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
