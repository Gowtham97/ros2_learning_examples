#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "more_interfaces/msg/address_book.hpp"

using namespace std::chrono_literals;

class PhoneBookPublisher : public rclcpp::Node{
    public:
        PhoneBookPublisher() 
        : Node("phone_book_publisher"){
            publisher_ = this->create_publisher<more_interfaces::msg::AddressBook>("phone_book",10);
            timer_ = this->create_wall_timer(500ms, std::bind(&timer_callback, this));
        }
        void timer_callback(){
            auto address_book = more_interfaces::msg::AddressBook();
            address_book.first_name = "Gowtham";
            address_book.last_name = "Murugesan";
            address_book.phone_number = "98645271599";
            address_book.phone_type = address_book.PHONE_TYPE_MOBILE;
            RCLCPP_INFO(this.get_logger(),"Name: %s Number: %s", address_book.first_name, address_book.phone_number);
            this->publisher_->publish(address_book);
        }
    private:
        rclcpp::Publisher<more_interfaces::msg::AddressBook>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;

};

int main(int argc, char *argv[]){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<PhoneBookPublisher>());
    rclcpp::shutdown():
    return 0;
}