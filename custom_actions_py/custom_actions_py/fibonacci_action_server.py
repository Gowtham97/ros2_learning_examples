import rclpy
import time
from rclpy.node import Node
from rclpy.action import ActionServer

from custom_action_interfaces.action import Fibonacci

class MinimalActionServer(Node):
    def __init__(self,):
        super().__init__("fibonacci_action_server")
        self._action_server = ActionServer(self, Fibonacci, "fibonacci", self.execute_callback)

    def execute_callback(self, goal_handler):
        self.get_logger().info("Executing Goal")

        feedback = Fibonacci.Feedback()
        feedback.partial_sequence = [0,1]
        for i in range(1, goal_handler.request.order):
            feedback.partial_sequence.append(feedback.partial_sequence[i] + feedback.partial_sequence[i-1])
            goal_handler.publish_feedback(feedback)
            time.sleep(1)
        goal_handler.succeed()
        result = Fibonacci.Result()
        result.sequence = feedback.partial_sequence
        return result

def main(args=None):
    rclpy.init(args=args)
    minimal_action_sever = MinimalActionServer()
    rclpy.spin(minimal_action_sever)
    minimal_action_sever.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()