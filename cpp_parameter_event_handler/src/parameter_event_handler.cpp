#include <memory>

#include "rclcpp/rclcpp.hpp"

using namespace std;

class ParameterEventHandler: public rclcpp::Node {
    public:
        ParameterEventHandler() : Node("parameter_event_handler") {
            this->declare_parameter("an_int_parameter", 0);

            param_subscriber = std::make_shared<rclcpp::ParameterEventHandler>(this);

            auto cb = [this] (const rclcpp::Parameter & p) -> void {
                RCLCPP_INFO(this->get_logger(), "Received Parameter update for \"%s\" of type \"%s\" : \"%ld\"",
                p.get_name().c_str(),
                p.get_type_name().c_str(),
                p.as_int());
            };

            auto cb2 = [this] (const rclcpp::Parameter& p) -> void {
                RCLCPP_INFO(this->get_logger(), "Received Parameter Update for '%s' of tpye '%s' : '%0.2lf'",
                p.get_name().c_str(),
                p.get_type_name().c_str(),
                p.as_double());
            };

            auto remote_node_name = string("parameter_blackboard");
            auto remote_param_name = string("a_double_param");

            callback_handle = param_subscriber->add_parameter_callback("an_int_parameter", cb);
            remote_callback_handle = param_subscriber->add_parameter_callback(remote_param_name, cb2, remote_node_name);
        }
    private:
        std::shared_ptr<rclcpp::ParameterEventHandler> param_subscriber;
        std::shared_ptr<rclcpp::ParameterCallbackHandle> callback_handle;
        std::shared_ptr<rclcpp::ParameterCallbackHandle> remote_callback_handle;
};

int main(int argc, char ** argv){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<ParameterEventHandler>());
    rclcpp::shutdown();

    return 0;
}