import rclpy
from rclpy.node import Node

from std_srvs.srv import SetBool

class Server(Node):
    def __init__(self):
        super().__init__("singlethreaded_server")
        server = self.create_service(SetBool,"/set_bool", self.cb)

    def cb(self, request, response):
        self.get_logger().info("Received Request %s" % str(request.data))
        response.message = "Successful"
        response.success = True
        return response

def main(args=None):
    rclpy.init(args=args)
    node = Server()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()