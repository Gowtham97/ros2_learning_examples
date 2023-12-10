#include <gazebo/gazebo.hh>
#include <gazebo_ros/node.hpp>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

using namespace std::chrono_literals;

namespace gazebo
{
  class WorldPluginTutorial : public SensorPlugin
  {
    public: WorldPluginTutorial() : SensorPlugin()
            {
              printf("Hello World!\n");
              std::cout << "Hi Gazebo World" << std::endl;
              gzmsg << "HI GAZEBO MSG" << std::endl;
            }

    public: void Load(sensors::SensorPtr _sensor, sdf::ElementPtr _sdf)
            {
              printf("LOAD : Hello World!\n");
              std::cout << "LOAD : Hi Gazebo World" << std::endl;
              this->ros_node_ = gazebo_ros::Node::Get(_sdf);
              pub_ = this->ros_node_->create_publisher<std_msgs::msg::String>("/hello_world",10);
              timer_ = this->ros_node_->create_wall_timer(1s, std::bind(&WorldPluginTutorial::publish, this));
            }
    private:
        private: gazebo_ros::Node::SharedPtr ros_node_{nullptr};
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
        rclcpp::TimerBase::SharedPtr timer_;

        void publish(){
          auto str = std_msgs::msg::String();
          str.data = "Hello World!";
          pub_->publish(str);
        }
  };
  GZ_REGISTER_SENSOR_PLUGIN(WorldPluginTutorial)
}