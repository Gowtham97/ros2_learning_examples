import rclpy
from rclpy.node import Node
from rcl_interfaces.msg import ParameterDescriptor

class MinimalParameter(Node):
    def __init__(self):
        super().__init__("minimal_parameter_node")
        param_desc = ParameterDescriptor(description="This param is mine")
        self.declare_parameter("my_param","world",param_desc)
        self.timer_ = self.create_timer(1.0, self.timer_callback)

    def timer_callback(self):
        param = self.get_parameter("my_param").get_parameter_value().string_value
        self.get_logger().info("Hello %s" % param)
        new_param = rclpy.parameter.Parameter("my_param",rclpy.Parameter.Type.STRING,"world")
        all_new_params = [new_param]
        self.set_parameters(all_new_params)

def main(args=None):
    rclpy.init(args=args)
    minimal_paramter = MinimalParameter()
    rclpy.spin(minimal_paramter)
    minimal_paramter.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()