cmake_minimum_required(VERSION 3.8)
project(publisher_plugins)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_ros REQUIRED)
find_package(rclcpp REQUIRED)
find_package(pluginlib REQUIRED)
find_package(plugin_learn REQUIRED)

pluginlib_export_plugin_description_file(plugin_learn plugins.xml)

add_library(publisher_plugins src/publisher_plugins.cpp)
add_library(publisher_plugins::publisher_plugins ALIAS publisher_plugins)
target_compile_features(publisher_plugins PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
target_include_directories(publisher_plugins PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_target_dependencies(
  publisher_plugins
  std_msgs
  pluginlib
  rclcpp
  plugin_learn
)

# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(publisher_plugins PRIVATE "POLYGON_PLUGINS_BUILDING_LIBRARY")

install(
  DIRECTORY include/
  DESTINATION include
)

install(
  TARGETS publisher_plugins
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

ament_export_include_directories(
  include
)
ament_export_libraries(
  publisher_plugins
)

ament_export_targets(
  export_${PROJECT_NAME}
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
