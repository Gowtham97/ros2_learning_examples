#include <plugin_learn/plugin_learn.hpp>
#include <std_msgs/msg/string.hpp>

using namespace std::chrono_literals;

namespace publisher_plugins
{
  class StringPublisher : public plugin_learn::Base
  {
    public:
      void initialize(rclcpp::Node::SharedPtr node_) override
      {
        std::cout << "initialize CALLED" << std::endl;
        node_h = node_;
        str_pub = node_h->create_publisher<std_msgs::msg::String>("/hello",10);
        timer = node_h->create_wall_timer(1000ms, std::bind(&StringPublisher::startPublish, this));
      }

      void startPublish() override
      {
        std::cout << "PUBLISHED" << std::endl;
        auto str = std_msgs::msg::String();
        str.data = "hello";
        str_pub->publish(str);
      }

    protected:
      rclcpp::Node::SharedPtr node_h;
      rclcpp::Publisher<std_msgs::msg::String>::SharedPtr str_pub;
      rclcpp::TimerBase::SharedPtr timer;
  };
}

#include <pluginlib/class_list_macros.hpp>

PLUGINLIB_EXPORT_CLASS(publisher_plugins::StringPublisher, plugin_learn::Base)