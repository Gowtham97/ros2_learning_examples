#include "plugin_learn/publisher.hpp"
#include "plugin_learn/plugin_learn.hpp"

Publisher::Publisher(rclcpp::Node::SharedPtr node_): node_h(node_){
    pluginlib::ClassLoader<plugin_learn::Base> publisher_loader("plugin_learn", "plugin_learn::Base");
    std::cout << "CONSTRUCTOR" << std::endl;
    str_pub = node_h->create_publisher<std_msgs::msg::String>("/test",10);
    using namespace std::chrono_literals;
    timer = node_h->create_wall_timer(1000ms, std::bind(&Publisher::publish, this));
    try
    {
        printf("Plugin Loaded Successfully");
        std::shared_ptr<plugin_learn::Base> string_publisher = publisher_loader.createSharedInstance("publisher_plugins::StringPublisher");
        string_publisher->initialize(node_h);

    }
    catch(pluginlib::PluginlibException& ex)
    {
        std::cout << "The plugin failed to load for some reason." << std::endl;
        printf("The plugin failed to load for some reason. Error: %s\n", ex.what());
    }
    
}

void Publisher::publish(){
    auto str = std_msgs::msg::String();
    str.data = "hello";
    str_pub->publish(str);
}