#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "tutorial_interfaces/msg/num.hpp"

using std::placeholders::_1;

class MinimalSubscriber
{
    public:
        MinimalSubscriber(rclcpp::Node::SharedPtr nh): nh_(nh){
        int * intPtr = new int;
        *intPtr = 11;
        delete intPtr;
        intPtr=NULL;
        subscription_ = nh_->create_subscription<tutorial_interfaces::msg::Num>("topic",10,std::bind(&MinimalSubscriber::callback, this, _1));
        }
    private:
        void callback(const tutorial_interfaces::msg::Num & msg) const {
            RCLCPP_INFO(nh_->get_logger(), "I heard : '%ld'",msg.num);
        }
    rclcpp::Node::SharedPtr nh_;
    rclcpp::Subscription<tutorial_interfaces::msg::Num>::SharedPtr subscription_;
};

int main(int argc, char *argv[]){
    rclcpp::init(argc,argv);
    auto node = std::make_shared<rclcpp::Node>("minimal_subscriber");
    MinimalSubscriber ms(node);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
