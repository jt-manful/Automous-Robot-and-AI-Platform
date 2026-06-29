#include "detector_pkg/detector_node.hpp"


DetectorNode::DetectorNode() : Node("detector_node"){
    //subscribes to raw can image
    image_subscriber_ = this->create_subscription<sensor_msgs::msg::Image>(
        "/camera/image_raw", //topic
        10,
        std::bind(&DetectorNode::image_callback,
                  this,
                  std::placeholders::_1)
    );

    RCLCPP_INFO(this->get_logger(),
        "node started - listening on /camera/image_raw");



   // publishers
   debug_publisher_ = this->create_publisher<sensor_msgs::msg::Image>(
    "/debug/image", 
    10
   );

   detection_publisher_ = this->create_publisher<vision_msgs::msg::Detection2DArray>(
    "/detections",
    10
);

   


}


void DetectorNode::image_callback(const sensor_msgs::msg::Image::SharedPtr msg){
    // image to csv
    auto image = ros_to_csv(msg);
    cv::Mat debug_img = image.clone(); // for debug
    // run detection
    auto detections = run_detections(image);
    // publish detections
    publish_detections(detections); 
    // publish debug
    draw_boxes(debug_img, detections);
    publish_debug(debug_img);

}




cv::Mat DetectorNode::ros_to_csv(const sensor_msgs::msg::Image::SharedPtr msg){
    return cv_bridge::toCvCopy(msg, "bgr8")->image;
}


std::vector<Detection> DetectorNode::run_detections(const cv::Mat& image){
    // dummy data to keep the system from breaking
    Detection detection = {50, 50, 150, 150, "object", 0.9};
    return {detection};
}


void DetectorNode::publish_debug(const cv::Mat & image){
        
    sensor_msgs::msg::Image::SharedPtr msg =
        cv_bridge::CvImage(
            std_msgs::msg::Header(),
            "bgr8",
            image
        ).toImageMsg();


        debug_publisher_->publish(
            *msg
        );


        RCLCPP_INFO(
            this->get_logger(),
            "image published and saved to  - /tmp/latest_frame.jpg"
        );

}


void DetectorNode::draw_boxes(cv::Mat &image, const std::vector<Detection>& detections){
    for (const auto& d : detections){
        cv::rectangle(
            image,
            cv::Rect(d.x, d.y, d.width, d.height),
            cv::Scalar(0,255,0),
            2
        );

        cv::putText(
            image,
            d.label,
            cv::Point(d.x, d.y - 5),
            cv::FONT_HERSHEY_SIMPLEX,
            0.5,
            cv::Scalar(0,255,0)
        );
    }
}


void DetectorNode::publish_detections(std::vector<Detection>& detections){

    // construct msg 
    vision_msgs::msg::Detection2DArray msg;
    msg.header.stamp = this->now();
    msg.header.frame_id = "camera";
    
    for (const auto& d : detections){
        vision_msgs::msg::Detection2D det;

        //detectors output boxes in top left corner
        // shift to "center"
        det.bbox.center.position.x =
        d.x + d.width / 2.0;

        det.bbox.center.position.y =
            d.y + d.height / 2.0;

        det.bbox.size_x = d.width;
        det.bbox.size_y = d.height;

        vision_msgs::msg::ObjectHypothesisWithPose hyp;
        hyp.hypothesis.class_id = d.label;
        hyp.hypothesis.score = d.score;

        det.results.push_back(hyp);

        msg.detections.push_back(det);
    }

    // publish
    detection_publisher_ ->publish(msg);

    RCLCPP_INFO(this->get_logger(),
        "pulishing to debug on - /detector/debug_image");

}