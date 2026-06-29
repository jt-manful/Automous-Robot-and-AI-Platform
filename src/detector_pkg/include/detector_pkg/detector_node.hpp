#ifndef DETECTOR_PKG__DETECTOR_NODE_HPP_
#define DETECTOR_PKG__DETECTOR_NODE_HPP_

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "cv_bridge/cv_bridge.hpp"
#include "vision_msgs/msg/detection2_d_array.hpp"
#include "opencv2/opencv.hpp"
#include <type_traits>
#include <string>
#include <vector>



struct Detection {
    int x;
    int y;
    int width;
    int height;
    std::string label;
    float score;
};

class DetectorNode : public rclcpp::Node
{
public:
    DetectorNode();

private:
    void image_callback(
        const sensor_msgs::msg::Image::SharedPtr msg); // subscribe to raw image
    
    cv::Mat ros_to_csv(
        const sensor_msgs::msg::Image::SharedPtr msg);

    std::vector<Detection> run_detections(
        const cv::Mat& image); 

    void draw_boxes(
        cv::Mat& image,
        const std::vector<Detection>& detections);

    void publish_detections(
        std::vector<Detection>& detections);

    void publish_debug(
        const cv::Mat &image);
        
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_subscriber_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr debug_publisher_;
    rclcpp::Publisher<vision_msgs::msg::Detection2DArray>::SharedPtr detection_publisher_;

};


#endif  // DETECTOR_PKG__DETECTOR_NODE_HPP_