# DEV Log

---
# Log Entry 2
**Date:** 2026-06-19.

**Package worked on:** `detector_pkg` 

## Summary
Today's task was to finsih phase 3 transition from image processing to object detection 

Turning the DectionNode from 
DetectorNode
 ├── subscribes: raw image
 ├── processes: OpenCV (for now)
 └── publishes: debug image
```
to

```
DetectorNode
 ├── subscribes: camera/image_raw
├── converts: ROS → OpenCV
├── runs: ML model (ONNX Runtime)
├── outputs:
│    ├── /detections (vision_msgs/Detection2DArray)
│    └── /debug_image (optional visualization)
```

We are switching to vision_msgs which are standardized set of ROS 2 message types designed for computer vision and object recognition pipelines. Its main feature  2D and 3D object detection using bounding boxes and spatial poses. it also has object classification metadata such as class IDs and confidence scores. 

I intially planned to create a custom msg but after a little conversation with my big brother I learnt about vision_msg and it honeslty simplifies my work.

Now for the real task I followed a tutorial by this guy:
https://medium.com/@taffealexander/object-detection-with-yolo-and-onnx-runtime-in-c-c8bfb964520b



# Log Entry 1
**Date:** 2026-06-13.

**Package worked on:** `detector_pkg` 

## Summary

Set up the initial pipeline for image-processing. 
Detector node subscribes to a camera image topic, runs it through OpenCV, draws a debug bounding box, and republishes/saves the result. T
 
the current pipeline implemented to help re-learn ros basics.
![bounding box on image](image.png)
 
```
DetectorNode
 ├── subscribes: raw image
 ├── processes: OpenCV (for now)
 └── publishes: debug image
```
that pipeline will then be altered to the real detection model 
```
DetectorNode
 ├── subscribes: raw image
 ├── runs: Faster R-CNN
 └── publishes: detections
```

may need to switch over to ubuntu due to lack of visualization capabilities.

The goal for the next time I look at this project is to finish up on the detection  and move on to tracking

The goal for the rest of the month is to finsih up on the perception layer
```
Perception Layer 
├── Camera Node
├── Object Detector
├── Object Tracker
└── Depth Processing
```

## Commands Used Today
 
Build the package:
```bash
colcon build --cmake-args -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
```
 
Source the workspace:
```bash
source install/setup.bash
```
 
Run synthetic camera publisher (remapped to expected topic):
```bash
ros2 run image_tools cam2image --ros-args -p burger_mode:=true -r image:=/camera/image_raw
```
 
Run the detector node:
```bash
ros2 run detector_pkg detector_node
```
 
Check topics and message rate:
```bash
ros2 topic list
ros2 topic hz /detector/debug_image
```
 
Copy saved debug frame out of the container (run on Mac host, not inside container):
```bash
docker ps
docker cp <container_id>:/tmp/latest_frame.jpg ./latest_frame.jpg
```




