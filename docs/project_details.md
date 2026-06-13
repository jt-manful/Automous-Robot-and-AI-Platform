# Autonomous Robotics & AI Platform

A ROS 2-based autonomous robotics platform designed to evolve from object detection into a complete intelligent robotic system capable of perception, tracking, mapping, navigation, manipulation, and AI-powered task execution.

## Project Goals

This project is intended as a long-term learning and development platform for:

* ROS 2
* C++
* Computer Vision
* Deep Learning
* Robotics Software Engineering
* Autonomous Navigation
* Manipulation
* Reinforcement Learning
* AI-Assisted Robotics

The development approach is incremental. Every phase should result in a working subsystem that can later be integrated into a larger autonomous architecture.



# Planned Architecture

```text
Perception Layer
├── Camera Node
├── Object Detector
├── Object Tracker
└── Depth Processing

World Model Layer
├── TF2
├── Semantic Mapping
└── Object Database

Navigation Layer
├── SLAM
├── Localization
├── Nav2
└── Path Planning

Manipulation Layer
├── MoveIt
├── Grasp Planning
└── Arm Control

AI Layer
├── Task Planner
├── Behavior Trees
└── Language Interface

Simulation Layer
├── Gazebo
└── Isaac Sim
```



# Development Roadmap

## Phase 1 — ROS 2 Refresher

Objectives:

* Nodes
* Topics
* Publishers
* Subscribers
* Services
* Actions
* Parameters
* Launch Files

Deliverable:

```text
Hello ROS System
```

---

## Phase 2 — Computer Vision Pipeline

Objectives:

* ROS Image Topics
* OpenCV Integration
* Image Processing

Deliverable:

```text
Camera
↓
Image Processing
↓
Display
```

---

## Phase 3 — Object Detection

Objectives:

* Faster R-CNN
* ONNX Runtime
* vision_msgs

Deliverable:

```text
Camera
↓
Object Detection
↓
Detection2DArray
```

---

## Phase 4 — Object Tracking

Objectives:

* DeepSORT
* ByteTrack

Deliverable:

```text
Persistent Object IDs
```

---

## Phase 5 — 3D Localization

Objectives:

* Depth Cameras
* Coordinate Systems
* TF2

Deliverable:

```text
Object Position in World Coordinates
```

---

## Phase 6 — Mapping & Localization

Objectives:

* SLAM
* Occupancy Maps

Deliverable:

```text
Autonomous Localization
```

---

## Phase 7 — Navigation

Objectives:

* Nav2
* Path Planning
* Obstacle Avoidance

Deliverable:

```text
Autonomous Movement
```

---

## Phase 8 — Manipulation

Objectives:

* MoveIt
* Grasp Planning

Deliverable:

```text
Pick and Place
```

---

## Phase 9 — Semantic Mapping

Objectives:

* Scene Understanding
* Object Persistence

Deliverable:

```text
Semantic World Model
```

---

## Phase 10 — AI Planning

Objectives:

* Task Planning
* Natural Language Commands

Deliverable:

```text
"Bring me the red bottle."
```

---

# Repository Structure

```text
robot_ws/
├── .devcontainer/
├── docker/
│   └── Dockerfile
├── src/
│   ├── detector_pkg/
│   ├── tracking_pkg/
│   ├── navigation_pkg/
│   ├── manipulation_pkg/
│   └── robot_bringup/
├── docker-compose.yml
└── README.md
```

---

# Prerequisites

## Hardware

* Apple Silicon Mac (M-series)
* Docker Desktop

## Software

* Docker Desktop
* VS Code
* Dev Containers Extension

---

# Initial Setup

Clone repository:

```bash
git clone <repository-url>
cd robot_ws
```

---

# Build Docker Image

```bash
docker compose build
```

---

# Start Development Environment

```bash
docker compose up -d
```

Verify container is running:

```bash
docker ps
```

Expected:

```text
ros2_jazzy
```

---

# Enter Container

```bash
docker exec -it ros2_jazzy bash
```

You should see:

```bash
root@<container-id>:/robot_ws#
```

---

# Verify ROS Installation

```bash
source /opt/ros/jazzy/setup.bash

ros2 --version
```

---

# Build Workspace

Inside container:

```bash
cd /robot_ws

colcon build
```

Source workspace:

```bash
source install/setup.bash
```

---

# Create First Package

```bash
cd src

ros2 pkg create detector_pkg \
    --build-type ament_cmake \
    --dependencies rclcpp sensor_msgs std_msgs
```

Return to workspace root:

```bash
cd ..
```

Build:

```bash
colcon build
```

---

# ROS Test

Terminal 1:

```bash
source /opt/ros/jazzy/setup.bash

ros2 run demo_nodes_cpp talker
```

Terminal 2:

```bash
source /opt/ros/jazzy/setup.bash

ros2 run demo_nodes_cpp listener
```

Expected:

```text
Messages successfully exchanged.
```

---

# Useful Docker Commands

Start:

```bash
docker compose up -d
```

Stop:

```bash
docker compose down
```

View running containers:

```bash
docker ps
```

Enter container:

```bash
docker exec -it ros2_jazzy bash
```

View logs:

```bash
docker logs ros2_jazzy
```

Rebuild image:

```bash
docker compose build --no-cache
```

---

# Current Milestone

## Sprint 1

ROS 2 Fundamentals

Success Criteria:

* Docker environment operational
* ROS 2 Jazzy running
* Workspace builds successfully
* Custom package created
* Publisher/subscriber example functioning

Once Sprint 1 is complete, development will proceed to the computer vision pipeline and object detection system.
