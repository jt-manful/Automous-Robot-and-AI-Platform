#include "rclcpp/rclcpp.hpp"
#include "detector_pkg/detector_node.hpp"

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<DetectorNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}