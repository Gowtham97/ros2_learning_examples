import rclpy
from rclpy.node import Node

from example_interfaces.srv import AddTwoInts


class Server(Node):
    def __init__(self):
        super().__init__("add_two_ints_server")
        self.server_ = self.create_service(AddTwoInts, "add_two_ints", self.callback)

    def callback(self, request, response):
        response.sum = request.a + request.b
        self.get_logger().info("Incoming Request\na: %d b: %d" % (request.a,request.b))
        return response

def main(args=None):
    rclpy.init(args=args)
    server = Server()
    rclpy.spin(server)
    server.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()