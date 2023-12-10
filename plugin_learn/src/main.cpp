#include "plugin_learn/publisher.hpp"

int main(int argc, char * argv[]){
    std::cout << "HELLO" << std::endl;
    rclcpp::init(argc,argv);
    auto node_options = rclcpp::NodeOptions();
    node_options.use_intra_process_comms(true);
    auto node_h = std::make_shared<rclcpp::Node>("publisher_node","",node_options);
    auto node = std::make_shared<Publisher>(node_h);
    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(node_h->get_node_base_interface());
    executor.spin();
    rclcpp::shutdown();
    return 0;
}