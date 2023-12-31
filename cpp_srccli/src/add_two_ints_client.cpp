// #include <functional>
// #include <memory>
// #include <chrono>

// #include "rclcpp/rclcpp.hpp"
// #include "tutorial_interfaces/srv/add_three_ints.hpp"

// using namespace std::chrono_literals;

// int main(int argc, char **argv)
// {
//     rclcpp::init(argc,argv);
//     if (argc != 4) {
//         RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Usage: Add two ints X Y Z");
//         return 1;
//     }

//     std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_two_ints_client");
//     rclcpp::Client<tutorial_interfaces::srv::AddThreeInts>::SharedPtr client = node->create_client<tutorial_interfaces::srv::AddThreeInts>("add_two_ints");

//     auto request = std::make_shared<tutorial_interfaces::srv::AddThreeInts::Request>();
//     request->a = atoll(argv[1]);
//     request->b = atoll(argv[2]);
//     request->c = atoll(argv[3]);

//     while (!client->wait_for_service(1s)) {
//         if (!rclcpp::ok()){
//             RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"Interrupted while waiting foe service. Exiting");
//             return 0;
//         }
//         RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"Service not available, waiting again...");
//     }

//     auto result = client->async_send_request(request);

//     if (rclcpp::spin_until_future_complete(node, result) == rclcpp::FutureReturnCode::SUCCESS){
//         RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Sum: %ld", result.get()->sum);
//     } else {
//         RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service add_two_ints");
//     }

//     rclcpp::shutdown();
//     return 0;
// }

#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/srv/add_three_ints.hpp"
#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::literals::chrono_literals;

class AddTwoIntsClient : public rclcpp::Node
{
public:
  AddTwoIntsClient() : Node("add_two_ints_client")
  {
    client_ = create_client<tutorial_interfaces::srv::AddThreeInts>("add_two_ints");

    request_ = std::make_shared<tutorial_interfaces::srv::AddThreeInts::Request>();
    request_->a = 5;
    request_->b = 5;

    while (!client_->wait_for_service(1s)) {
      if (!rclcpp::ok()) {
        RCLCPP_ERROR(get_logger(), "Interrupted while waiting for the service. Exiting.");
        return;
      }
      RCLCPP_INFO(get_logger(), "service not available, waiting again...");
    }

    auto future = client_->async_send_request(request_);

    auto status = future.wait_for(1s);
    if (status == std::future_status::ready)
    {
      RCLCPP_INFO(get_logger(), "Sum: %ld", future.get()->sum);
    }
    else {
      RCLCPP_INFO(get_logger(), "Sum: %ld", future.get()->sum);
      RCLCPP_ERROR(get_logger(), "Failed to call service add_two_ints");
    }
  }

private:
  rclcpp::Client<tutorial_interfaces::srv::AddThreeInts>::SharedPtr client_;
  std::shared_ptr<tutorial_interfaces::srv::AddThreeInts::Request> request_;
  int argc_;
  char **argv_;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<AddTwoIntsClient>());
  rclcpp::shutdown();
  return 0;
}
