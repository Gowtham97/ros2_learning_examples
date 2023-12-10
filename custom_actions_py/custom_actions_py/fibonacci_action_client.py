import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient

from custom_action_interfaces.action import Fibonacci

class MinimalActionClient(Node):
    def __init__(self):
        super().__init__("fibonacci_action_client")
        self._action_client = ActionClient(self, Fibonacci, "fibonacci")

    def send_goal(self, order):
        goal = Fibonacci.Goal()
        goal.order = order
        self._action_client.wait_for_server()
        self._send_goal_future = self._action_client.send_goal_async(goal,feedback_callback=self.feedback_callback)
        self._send_goal_future.add_done_callback(self.goal_response_callback)

    def goal_response_callback(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().info("Goal Rejected")
            return

        self.get_logger().info("Goal Accepted")
        
        self._get_result_future = goal_handle.get_result_async()
        self._get_result_future.add_done_callback(self.goal_done_callback)

    def goal_done_callback(self, future):
        result = future.result().result
        self.get_logger().info("Result: {0}".format(result.sequence))
        rclpy.shutdown()

    def feedback_callback(self, feedback_msg):
        feedback = feedback_msg.feedback
        self.get_logger().info("Received feedback: {0}".format(feedback.partial_sequence))

def main(args=None):
    rclpy.init(args=args)
    minimal_action_client = MinimalActionClient()
    minimal_action_client.send_goal(10)
    rclpy.spin(minimal_action_client)

if __name__ == "__main__":
    main()