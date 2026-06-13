#include "detector_pkg/detector_node.hpp"


// reate package
// ✓ Subscribe to Image topic
// ✓ Convert Image → cv::Mat
// ✓ Draw rectangle on image
// ✓ Publish debug image
// ✓ Launch file
// ✓ YAML config

DetectorNode::DetectorNode() : Node("detector_node"){
    //subscribes to raw can image
    subscriber_ = this->create_subscription<sensor_msgs::msg::Image>(
        "/camera/image_raw", //topic
        10,
        std::bind(&DetectorNode::image_callback,
                  this,
                  std::placeholders::_1)
    );

    RCLCPP_INFO(this->get_logger(),
        "node started - listening on /camera/image_raw");



   // publisher
   debug_publisher_ = this->create_publisher<sensor_msgs::msg::Image>(
    "/detector/debug_image", // which topic
    10
   );

    RCLCPP_INFO(this->get_logger(),
        "pulishing to debug on - /detector/debug_image");



}

void DetectorNode::image_callback(const sensor_msgs::msg::Image::SharedPtr msg){
    // log incoming image a look at basic features
    RCLCPP_INFO(this->get_logger(),
        "Image Received | %u x %u | encoding: %s",
        msg->height,
        msg->width,
        msg->encoding.c_str()


    );
    
    // convert from ros image to somethign useable by open cv
    cv_bridge::CvImagePtr cv_ptr;
    try{
        cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
    }
    catch (cv_bridge::Exception& e){
        RCLCPP_ERROR(
            this->get_logger(),
            "cv_bridge exception: %s", e.what());
    }
    cv::Mat image = cv_ptr->image;
    cv::rectangle(image,
              cv::Point(50,50),
              cv::Point(200,200),
              cv::Scalar(0,255,0),
              2);
    // cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
    debug_callback(image);
    


}


void DetectorNode::debug_callback(const cv::Mat & image){
    // convert image back and send it 
   sensor_msgs::msg::Image::SharedPtr msg =
        cv_bridge::CvImage(
            std_msgs::msg::Header(),
            "bgr8",
            image
        ).toImageMsg();

        cv::imwrite("/tmp/latest_frame.jpg", image);

        debug_publisher_->publish(*msg);
        RCLCPP_INFO(this->get_logger(),
        "image published and saved to  - /tmp/latest_frame.jpg");

}

docker cp 176263c466b7:/tmp/latest_frame.jpg ./latest_frame.jpg