import serial
import time

# Replace 'COM5' with the port your Arduino/ESP is on
arduino = serial.Serial(port='COM5', baudrate=9600, timeout=.1)

def send_coords(x, y, duration_ms):
    data = f"{x},{y},{duration_ms}\n"
    arduino.write(data.encode())
    print(f"Sent: {data.strip()}")

time.sleep(2)  # Wait for connection

# 🧪 Test example (replace with actual YOLO output)
send_coords(85, 100, 400)
