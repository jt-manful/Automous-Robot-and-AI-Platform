#include "rclcpp/rclcpp.hpp"
#include "detector_pkg/detector_node.hpp"
#include <onnxruntime_cxx_api.h>
#include <iostream>


int main(int argc, char * argv[])
{
    // load model
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "Yolo11 Model Logger");

    Ort::SessionOptions session_options;
    session_options.SetIntraOpNumThreads(1);

    Ort::Session session(env, "models/yolo11n.onnx", session_options);

    std::cout << "ONNX model loaded successfully!" << std::endl;
    
    
    // run node
    rclcpp::init(argc, argv);

    auto node = std::make_shared<DetectorNode>();

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}