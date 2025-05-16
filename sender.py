import serial
import keyboard
import time

# Cambia el puerto COM según tu ESP32 (ej: "COM4" en Windows, "/dev/ttyUSB0" en Linux)
puerto = "COM4"
baudrate = 115200

print(f"[INFO] Conectando a {puerto}...")
ser = serial.Serial(puerto, baudrate)
time.sleep(2)
print("[INFO] Conexión establecida.")

print("[INFO] Presiona ESC para finalizar grabación...")

while True:
    event = keyboard.read_event()
    if event.event_type == keyboard.KEY_DOWN:
        key = event.name
        if key == "esc":
            break
        ser.write((key + "\n").encode())

ser.write(b"__END__\n")
print("[INFO] Teclas enviadas al ESP32.")
ser.close()

