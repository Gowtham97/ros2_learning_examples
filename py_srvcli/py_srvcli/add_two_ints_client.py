import rclpy
from rclpy.node import Node

from example_interfaces.srv import AddTwoInts

import sys

class ClientAsync(Node):
    def __init__(self):
        super().__init__("add_two_ints_client")
        self.client_ = self.create_client(AddTwoInts, "add_two_ints")
        while not self.client_.wait_for_service(timeout_sec=1.0):
            self.get_logger().info("Service not avaialble, waiting again..")
        self.request = AddTwoInts.Request()

    def send_request(self, a, b):
        self.request.a = a
        self.request.b = b
        self.future = self.client_.call_async(self.request)
        rclpy.spin_until_future_complete(self, self.future)
        return self.future.result()

def main(args=None):
    rclpy.init(args=args)
    client_async = ClientAsync()
    response = client_async.send_request(int(sys.argv[1]),int(sys.argv[2]))
    client_async.get_logger().info("Result of add two ints: for %d + %d = %d" % (int(sys.argv[1]),int(sys.argv[2]), response.sum))
    client_async.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()