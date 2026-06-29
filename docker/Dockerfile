FROM ros:jazzy

ENV DEBIAN_FRONTEND=noninteractive
ENV ONNXRUNTIME_DIR=/opt/onnxruntime
ENV LD_LIBRARY_PATH=$ONNXRUNTIME_DIR/lib:$LD_LIBRARY_PATH

RUN apt-get update && apt-get install -y \
    python3-colcon-common-extensions \
    python3-pip \
    python3-rosdep \
    python3-vcstool \
    build-essential \
    git \
    vim \
    nano \
    wget \
    curl \
    gdb \
    cmake \
    libopencv-dev \
    ros-jazzy-cv-bridge \
    ros-jazzy-image-transport \
    ros-jazzy-vision-msgs \
    ros-jazzy-demo-nodes-cpp \
    ros-jazzy-demo-nodes-py \
    ros-jazzy-tf2 \
    ros-jazzy-tf2-ros \
    ros-jazzy-rviz2 \
    ros-jazzy-xacro \
    && rm -rf /var/lib/apt/lists/*


# Install ONNX Runtime (ARM64 version)
RUN wget https://github.com/microsoft/onnxruntime/releases/download/v1.18.0/onnxruntime-linux-aarch64-1.18.0.tgz && \
    tar -xzf onnxruntime-linux-aarch64-1.18.0.tgz && \
    mv onnxruntime-linux-aarch64-1.18.0 /opt/onnxruntime && \
    rm onnxruntime-linux-aarch64-1.18.0.tgz



RUN rosdep init || true

SHELL ["/bin/bash", "-c"]

RUN echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc

WORKDIR /robot_ws