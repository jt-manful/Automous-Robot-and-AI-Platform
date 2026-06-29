from ultralytics import YOLO

model = YOLO("/path/to/yolo11n.pt")
model.eval()
model.export(format='onnx', simplify=True)