#ifndef DETECTOR_PKG__DETECTOR_NODE_HPP_
#define DETECTOR_PKG__DETECTOR_NODE_HPP_

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "cv_bridge/cv_bridge.hpp"
#include "opencv2/opencv.hpp"
#include <type_traits>
#include <string>

class DetectorNode : public rclcpp::Node
{
public:
    DetectorNode();

private:
    void image_callback(const sensor_msgs::msg::Image::SharedPtr msg); // subscribe to raw image
    void debug_callback(const cv::Mat &image); // publish detections

    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscriber_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr debug_publisher_;
};

#endif  // DETECTOR_PKG__DETECTOR_NODE_HPP_