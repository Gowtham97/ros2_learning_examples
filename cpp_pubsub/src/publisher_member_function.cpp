#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "tutorial_interfaces/msg/num.hpp"

using namespace std::chrono_literals;


class MinimalPublisher : public rclcpp::Node {
    public:
        MinimalPublisher() : Node("minimal_publisher"), count_(0)
        {
            timer_ = this->create_wall_timer(500ms, std::bind(&MinimalPublisher::TimerCallback, this));
            publisher_ = this->create_publisher<tutorial_interfaces::msg::Num>("topic",10);
        }
    private:
        void TimerCallback(){
            auto message = tutorial_interfaces::msg::Num();
            message.num = count_++;
            RCLCPP_INFO(this->get_logger(),"Publishing '%ld'", message.num);
            publisher_->publish(message);
        }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char *argv[]){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<MinimalPublisher>());
    rclcpp::shutdown();
    return 0;
}