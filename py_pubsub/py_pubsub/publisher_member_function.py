import rclpy
from rclpy.node import Node

from std_msgs.msg import String

class MinimalPublisher(Node):
    def __init__(self):
        super().__init__("minimal_publisher")
        self.publisher_ =  self.create_publisher(String, "topic", 10)
        time_period = 0.5
        self.timer = self.create_timer(time_period, self.timer_callback)
        self.count = 0

    def timer_callback(self):
        message = String()
        message.data = "Hello World '%d' " % self.count
        self.publisher_.publish(message)
        self.get_logger().info("Published '%s'" % message.data)
        self.count += 1

def main(args=None):
    rclpy.init(args=args)
    minimal_publisher = MinimalPublisher()
    rclpy.spin(minimal_publisher)
    minimal_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()