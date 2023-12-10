#ifndef PLUGIN_LEARN_BASE_HPP
#define PLUGIN_LEARN_BASE_HPP

#include <rclcpp/rclcpp.hpp>

namespace plugin_learn
{
  class Base
  {
    public:
      virtual void initialize(rclcpp::Node::SharedPtr node_) = 0;
      virtual ~Base(){}
      virtual void startPublish() = 0;

    protected:
      Base(){}
  };
}  // namespace polygon_learn

#endif  // POLYGON_LEARN_REGULAR_POLYGON_HPP