#include <rclcpp/rclcpp.hpp>
#include <pluginlib/class_loader.hpp>
#include <std_msgs/msg/string.hpp>

class Publisher
{
    public:
        Publisher(rclcpp::Node::SharedPtr node_);
    private:
        rclcpp::Node::SharedPtr node_h;
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr str_pub;
        rclcpp::TimerBase::SharedPtr timer;
        void publish();
};