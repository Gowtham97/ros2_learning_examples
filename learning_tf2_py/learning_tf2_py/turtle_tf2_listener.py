import math

import rclpy
from rclpy.node import Node

from geometry_msgs.msg import Twist
from tf2_ros.buffer import Buffer
from tf2_ros.transform_listener import TransformListener
from tf2_ros import TransformException

from turtlesim.srv import Spawn

class FrameListener(Node):
    def __init__(self):
        super().__init__("turtle_tf2_frame_listener")
        self.target_frame = self.declare_parameter("target_frame","turtle").get_parameter_value().string_value
        self.cmd_publisher = self.create_publisher(Twist , "turtle2/cmd_vel", 1)

        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer ,self)

        self.timer = self.create_timer(0.1, self.timer_cb)

        self.spawner = self.create_client(Spawn, "spawn")

        self.turtle_spawning_service_ready = False

        self.turtle_spawned = False

    def timer_cb(self):
        from_frame_rel = self.target_frame
        to_frame_rel = "turtle2"

        if self.turtle_spawning_service_ready:
            if self.turtle_spawned:
                try:
                    t = self.tf_buffer.lookup_transform(to_frame_rel, from_frame_rel, rclpy.time.Time())
                except TransformException as ex:
                    self.get_logger().info(f"Could not transform from {to_frame_rel} to {from_frame_rel}: {ex}")
                    return
                msg = Twist()
                scale_rotation_rate = 1.0
                msg.angular.z = scale_rotation_rate * math.atan2(t.transform.translation.y, t.transform.translation.x)
                scale_forward_speed = 0.5
                msg.linear.x = scale_forward_speed * math.sqrt(t.transform.translation.x ** 2 + t.transform.translation.y ** 2)

                self.cmd_publisher.publish(msg)
            else:
                if self.result.done():
                    self.get_logger().info("Turtle Spawned successfully")
                    self.turtle_spawned = True
                else:
                    self.get_logger().info("Turtle Spawn is not finished")
        else:
            if self.spawner.service_is_ready():
                req = Spawn.Request()
                req.name = "turtle2"
                req.x = float(4)
                req.y = float(2)
                req.theta = float(0)

                self.result = self.spawner.call_async(req)
                self.turtle_spawning_service_ready = True
            else:
                self.get_logger().info("Turtle Spawner service is not ready")

def main(args=None):
    rclpy.init(args=args)
    node = FrameListener()
    rclpy.spin(node)
    rclpy.shutdown()