cmake_minimum_required(VERSION 3.8)
project(gtest_learn)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

add_executable(gtest_learn src/some_node.cpp)
ament_target_dependencies(gtest_learn rclcpp example_interfaces)
install(TARGETS
  gtest_learn
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  # find_package(ament_lint_auto REQUIRED)
  find_package(ament_cmake_gtest REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  # set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  # set(ament_cmake_cpplint_FOUND TRUE)
  # ament_lint_auto_find_test_dependencies()

  ament_add_gtest(${PROJECT_NAME}_test test/first_test.cpp)
  target_include_directories(${PROJECT_NAME}_test PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  )
endif()

ament_package()
