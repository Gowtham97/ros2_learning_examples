#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

class MinimalParam : public rclcpp::Node{
    public:
        MinimalParam() : Node("minimal_param_node") {
            auto param_desc = rcl_interfaces::msg::ParameterDescriptor();
            param_desc.description = "This parameter is mine!";
            this->declare_parameter("my_param","world",param_desc);
            timer_ = this->create_wall_timer(1s,std::bind(&MinimalParam::timer_callback, this));
        }
        void timer_callback(){
            std::string param = this->get_parameter("my_param").as_string();
            RCLCPP_INFO(this->get_logger(), "Parameter is %s", param.c_str());
            std::vector<rclcpp::Parameter> all_new_parameters{rclcpp::Parameter("my_param","world")};
            this->set_parameters(all_new_parameters);
        }
    private:
        rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[]){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<MinimalParam>());
    rclcpp::shutdown();
    return 0;
}