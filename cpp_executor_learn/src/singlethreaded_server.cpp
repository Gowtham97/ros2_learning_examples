#include <memory>
#include <functional>

#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/set_bool.hpp"

class SingleThreadedServer : public rclcpp::Node{
    public:
        SingleThreadedServer() : Node("singlethreaded_server_node"){
            using namespace std::placeholders;
            service_ptr_ = this->create_service<std_srvs::srv::SetBool>("/set_bool",std::bind(& SingleThreadedServer::cb, this, _1, _2));
        }
    private:
        rclcpp::Service<std_srvs::srv::SetBool>::SharedPtr service_ptr_;
        void cb(const std::shared_ptr<std_srvs::srv::SetBool_Request> request, std::shared_ptr<std_srvs::srv::SetBool_Response> response){
            RCLCPP_INFO(this->get_logger(), "Received Request %d", request->data);
            response->message = "Successfully Called";
            response->success = true;
        }  
};

int main(int argc,char ** argv){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<SingleThreadedServer>());
    rclcpp::shutdown();
    return 0;
}