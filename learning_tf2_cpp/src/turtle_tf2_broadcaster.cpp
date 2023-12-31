#include <memory>
#include <functional>
#include <sstream>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/transform_broadcaster.h"
#include "turtlesim/msg/pose.hpp"

class FramePublisher: public rclcpp::Node {
    public:
        FramePublisher() : Node("turtle_tf2_frame_publisher") {
            turtlename_ = this->declare_parameter<std::string>("turtlename","turtle");
            std::ostringstream stream;
            stream << turtlename_.c_str() << "/pose";
            std::string topic_name = stream.str();
            pose_subscriber_ = this->create_subscription<turtlesim::msg::Pose>(topic_name, 1, std::bind(&FramePublisher::handle_turtle, this, std::placeholders::_1));
            tf_broadcaster_= std::make_unique<tf2_ros::TransformBroadcaster>(*this);
        }
    private:
        std::string turtlename_;
        rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr pose_subscriber_;
        std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;

        void handle_turtle(const std::shared_ptr<turtlesim::msg::Pose> msg) {
            geometry_msgs::msg::TransformStamped t;
            t.header.stamp = this->get_clock()->now();
            t.header.frame_id = "world";
            t.child_frame_id = turtlename_.c_str();

            t.transform.translation.x = msg->x;
            t.transform.translation.y = msg->y;
            t.transform.translation.z = 0.0;

            tf2::Quaternion q;
            q.setRPY(0.0, 0.0, msg->theta);

            t.transform.rotation.x = q.x();
            t.transform.rotation.y = q.y();
            t.transform.rotation.z = q.z();
            t.transform.rotation.w = q.w();

            tf_broadcaster_->sendTransform(t);
        }
};

int main(int argc, char * argv[]){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<FramePublisher>());
    rclcpp::shutdown();
    return 0;
}