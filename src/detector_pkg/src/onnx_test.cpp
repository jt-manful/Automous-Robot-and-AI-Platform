#include <onnxruntime_cxx_api.h>
#include <iostream>

int main() {
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "test");

    Ort::SessionOptions session_options;
    session_options.SetIntraOpNumThreads(1);

    Ort::Session session(env, "models/yolo11n.onnx", session_options);

    std::cout << "ONNX model loaded successfully!" << std::endl;

    return 0;
}