import rclpy
from rclpy.node import Node
from geometry_msgs.msg import TransformStamped

from tf2_ros.static_transform_broadcaster import StaticTransformBroadcaster

import math
import sys
import numpy as np

def quaternion_from_euler(ai, aj, ak):
    ai /= 2.0
    aj /= 2.0
    ak /= 2.0

    ci = math.cos(ai)
    si = math.sin(ai)
    cj = math.cos(aj)
    sj = math.sin(aj)
    ck = math.cos(ak)
    sk = math.sin(ak)
    
    cc = ci*ck
    cs = ci*sk
    sc = si*ck
    ss = si*sk

    q = np.empty((4, ))
    q[0] = cj*sc - sj*cs
    q[1] = cj*ss + sj*cc
    q[2] = cj*cs - sj*sc
    q[2] = cj*cc + sj*ss

    return q

class StaticFramePublisher(Node):
    def __init__(self, transforamtion):
        super().__init__("static_turtle_tf2_broadcaster")
        self.tf_static_broadcaster = StaticTransformBroadcaster(self)
        self.make_transforms(transformation=transforamtion)

    def make_transforms(self, transformation):
        t = TransformStamped()
        t.header.stamp = self.get_clock().now().to_msg()
        t.header.frame_id = "world"
        t.child_frame_id = transformation[0]

        t.transform.translation.x = float(transformation[1])
        t.transform.translation.y = float(transformation[2])
        t.transform.translation.z = float(transformation[3])

        quat = quaternion_from_euler(float(transformation[4]),float(transformation[5]),float(transformation[6]))
        t.transform.rotation.x = quat[0]
        t.transform.rotation.y = quat[1]
        t.transform.rotation.z = quat[2]
        t.transform.rotation.w = quat[3]

        self.tf_static_broadcaster.sendTransform(t)

def main():
    logger = rclpy.logging.get_logger("logger")
    if len(sys.argv) != 8:
        logger.info("Invalid number of parameters, usage \n",
                    "$ ros2 run learning_tf2_py static_turtle_tf2_broadcaster",
                    "child_frame_name x y z roll pitch yaw")
        sys.exit(1)
    
    if sys.argv[1] == "world":
        logger.info("Your static turtle name cannot be 'World'")
        sys.exit(2)

    rclpy.init()
    static_frame_publisher = StaticFramePublisher(sys.argv[1:])
    try:
        rclpy.spin(static_frame_publisher)
    except KeyboardInterrupt:
        pass
    static_frame_publisher.destroy_node()
    rclpy.shutdown()