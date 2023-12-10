#include <memory>
#include <functional>
#include <string>

#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

class UDPPUB : public rclcpp::Node {
    public:
        UDPPUB() : Node("udp_publisher"){
            timer_ = this->create_wall_timer(1000ms, std::bind(UDPPUB::TimerCallback, this));
        }
    private:
        rclcpp::TimerBase::SharedPtr timer_;
        void TimerCallback(){
            RCLCPP_INFO(this->get_logger(),"Called");
        }
};

int main(int argc, char* argv[]){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<UDPPUB>());
    rclcpp::shutdown();
}