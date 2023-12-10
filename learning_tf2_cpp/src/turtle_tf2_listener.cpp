#include <memory>
#include <functional>
#include <sstream>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_listener.h"
#include "tf2/exceptions.h"
#include "geometry_msgs/msg/twist.hpp"

#include "turtlesim/srv/spawn.hpp"

class FrameListener : public rclcpp::Node {
    public:
        FrameListener() : Node("turtle_tf2_frame_listener") {
            target_frame_ = this->declare_parameter<std::string>("target_frame", "turtle");
            using namespace std::chrono_literals;
            timer_ = this->create_wall_timer(1s, std::bind(&FrameListener::timer_cb, this));
            cmd_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle2/cmd_vel", 1);
            tf2_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
            tf2_listerner_ = std::make_shared<tf2_ros::TransformListener>(*tf2_buffer_);
            spawn_srv_ = this->create_client<turtlesim::srv::Spawn>("/spawn");
        }

    private:
        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_publisher_;
        rclcpp::Client<turtlesim::srv::Spawn>::SharedPtr spawn_srv_;
        std::unique_ptr<tf2_ros::Buffer> tf2_buffer_;
        std::shared_ptr<tf2_ros::TransformListener> tf2_listerner_;
        std::string target_frame_;
        bool turtle_spawn_service_ready = false;
        bool turtle_spwaned = false;

        void timer_cb(){

            std::string fromFrameRel = target_frame_.c_str();
            std::string toFrameRel = "turtle2";

            if (turtle_spawn_service_ready == true) {
                if (turtle_spwaned == true){
                    geometry_msgs::msg::TransformStamped t;
                    try {
                        t = tf2_buffer_->lookupTransform(toFrameRel, fromFrameRel, tf2::TimePointZero);
                    }catch(const tf2::TransformException & ex){
                        RCLCPP_INFO(this->get_logger(),"Could not tranform %s to %s:  %s",
                        toFrameRel.c_str(), fromFrameRel.c_str(), ex.what());
                        return;
                    }

                    geometry_msgs::msg::Twist msg;
                    static const double scaleRotationRate = 1.0;
                    msg.angular.z = scaleRotationRate * atan2(t.transform.translation.y, t.transform.translation.x);
                    static const double scaleForwardSpeed = 0.5;
                    msg.linear.x = scaleForwardSpeed * sqrt(pow(t.transform.translation.x, 2)+ pow(t.transform.translation.y, 2));

                    cmd_publisher_->publish(msg);
                }
            }
            else {
                if (spawn_srv_->service_is_ready()){
                    auto req = std::make_shared<turtlesim::srv::Spawn::Request>();
                    req->name = "turtle2";
                    req->x = 4.0;
                    req->y = 2.0;
                    req->theta = 0.0;

                    using ServiceResponseFuture = rclcpp::Client<turtlesim::srv::Spawn>::SharedFuture;

                    auto response_reveived_callback = [this] (ServiceResponseFuture future) {
                        auto result = future.get();
                        if (strcmp(result->name.c_str(), "turtle2") == 0){
                            turtle_spawn_service_ready = true;
                            turtle_spwaned = true;
                            RCLCPP_INFO(this->get_logger(), "Turtle Spawned Successfully");
                        }
                        else{
                            RCLCPP_INFO(this->get_logger(), "Service callback result mismatch");
                        }
                    };

                    auto result = spawn_srv_->async_send_request(req,response_reveived_callback);
                }
                else{
                    RCLCPP_INFO(this->get_logger(), "Service Not Ready");
                }
            }
        }
};

int main(int argc, char * argv[]){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<FrameListener>());
    rclcpp::shutdown();
    return 0;
}