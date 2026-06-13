# Autonomous Robotics & AI Platform

A ROS 2 Jazzy-based robotics project focused on learning robotics and AI by incrementally building an autonomous system. The project begins with ROS 2 fundamentals and computer vision, then expands into object detection, tracking, navigation, manipulation, and intelligent task planning.

---

## Project Structure

```text
robot_ws/
├── .devcontainer/
│   └── devcontainer.json
│
├── docker/
│   └── Dockerfile
│
├── src/
│   ├── detector_pkg/
│   ├── tracking_pkg/
│   ├── navigation_pkg/
│   ├── manipulation_pkg/
│   └── robot_bringup/
│
├── docker-compose.yml
└── README.md
```

---

## Prerequisites

### Required

* Docker Desktop
* VS Code
* Dev Containers Extension (recommended)

### Target Environment

* Apple Silicon (M-series Mac)
* ROS 2 Jazzy
* Ubuntu-based Docker container

---

## Build Instructions

### 1. Build the Docker Image

From the project root:

```bash
docker compose build
```

---

### 2. Start the Development Container

```bash
docker compose up -d
```

Verify the container is running:

```bash
docker ps
```

You should see:

```text
ros2_jazzy
```

---

### 3. Enter the Container

```bash
docker exec -it ros2_jazzy bash
```

You are now working inside the ROS 2 environment.

---

### 4. Source ROS 2

```bash
source /opt/ros/jazzy/setup.bash
```

---

### 5. Build the Workspace

From the workspace root:

```bash
cd /robot_ws

colcon build
```

---

### 6. Source the Workspace

After every successful build:

```bash
source install/setup.bash
```

---
## Useful Commands

### Start Container

```bash
docker compose up -d
```

### Stop Container

```bash
docker compose down
```

### Enter Container

```bash
docker exec -it ros2_jazzy bash
```

### View Running Containers

```bash
docker ps
```

### Rebuild Docker Image

```bash
docker compose build --no-cache
```

