#include <memory>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/set_bool.hpp"

using namespace std::chrono_literals;

class MultiThreadedExample: public rclcpp::Node {
    public:
        MultiThreadedExample() : Node("multithreaded_executor_node"){

            client_cb_group = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
            timer_cb_group = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
            client_ptr_ = this->create_client<std_srvs::srv::SetBool>("/set_bool",rmw_qos_profile_services_default,client_cb_group);
            timer_ptr_ = this->create_wall_timer(1s, std::bind(&MultiThreadedExample::cb, this),timer_cb_group);
        }

    private:
        rclcpp::CallbackGroup::SharedPtr client_cb_group;
        rclcpp::CallbackGroup::SharedPtr timer_cb_group;
        rclcpp::Client<std_srvs::srv::SetBool>::SharedPtr client_ptr_;
        rclcpp::TimerBase::SharedPtr timer_ptr_;

        void cb(){
            auto request = std::make_shared<std_srvs::srv::SetBool_Request>();
            request->data = true;
            auto response_future = client_ptr_->async_send_request(request);
            std::future_status status = response_future.wait_for(10s);
            if (status == std::future_status::ready){
                RCLCPP_INFO(this->get_logger(), "Received Response %s", response_future.get()->message.c_str());
            }
        }
};

int main(int argc, char ** argv){
    rclcpp::init(argc,argv);
    auto node = std::make_shared<MultiThreadedExample>();
    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(node);
    executor.spin();
    rclcpp::shutdown();
    return 0;
}