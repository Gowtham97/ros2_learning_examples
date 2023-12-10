import rclpy
from rclpy.executors import MultiThreadedExecutor
from rclpy.callback_groups import MutuallyExclusiveCallbackGroup,ReentrantCallbackGroup
from rclpy.node import Node

from std_srvs.srv import SetBool


class Client(Node):
    def __init__(self):
        super().__init__("multithreaded_client")
        client_cb_group = MutuallyExclusiveCallbackGroup()
        timer_cb_group = MutuallyExclusiveCallbackGroup()
        self.client = self.create_client(SetBool, "/set_bool", callback_group=client_cb_group)
        self.timer = self.create_timer(1, self.cb, callback_group=timer_cb_group)

    def cb(self):
        request = SetBool.Request()
        request.data = True
        self.get_logger().info("Sending Request")
        response = self.client.call(request)
        self.get_logger().info("Received Response %s" % response.message)

def main(args=None):
    rclpy.init(args=args)
    node = Client()
    executor = MultiThreadedExecutor()
    executor.add_node(node)
    executor.spin()
    node.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()