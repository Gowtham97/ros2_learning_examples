#include <rclcpp/rclcpp.hpp>
#include "example_interfaces/srv/add_two_ints.hpp"

class SomeNode: public rclcpp::Node{
    public:
        SomeNode() : Node("some_node"){
            using namespace std::placeholders;
            server_ = this->create_service<example_interfaces::srv::AddTwoInts>("/add_two_ints", std::bind(&SomeNode::add_cb,this, _1,_2));
        }
    private:
        rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr server_;
        double add(double num1, double num2){
            return num1+num2;
        }

        bool add_cb(const example_interfaces::srv::AddTwoInts::Request::SharedPtr req, example_interfaces::srv::AddTwoInts::Response::SharedPtr res){
            res->sum = add(req->a,req->b);
            return true;
        }
};

int main(int argc, char * argv[]){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<SomeNode>());
    rclcpp::shutdown();
}