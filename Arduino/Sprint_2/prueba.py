import paho.mqtt.client as mqtt
import serial
import time

# Configuració AWS IoT
BROKER_ENDPOINT = "a2lg3qizupe1nw-ats.iot.us-east-1.amazonaws.com"  # Endpoint AWS
PORT = 8883
TOPIC = "esp32/readings"
CLIENT_ID = "esp32_targeta"

# Certificats AWS
CA_PATH = "C:\\Users\\Marcos Pérez Salomón\\Documents\\Arduino\\segundo_segundo\\AmazonRootCA1.pem"
CERT_PATH = "C:\\Users\\Marcos Pérez Salomón\\Documents\\Arduino\\segundo_segundo\\device-certificate.pem.crt"
KEY_PATH = "C:\\Users\\Marcos Pérez Salomón\\Documents\\Arduino\\segundo_segundo\\private.pem.key"

# Configuració del port sèrie (Arduino)
SERIAL_PORT = "COM3"  # Canvia-ho segons el port del sistema
BAUD_RATE = 115200

# Connexió MQTT
def on_connect(client, userdata, flags, rc):
    print("Connected with result code", rc)

client = mqtt.Client(client_id=CLIENT_ID)
client.on_connect = on_connect
client.tls_set(ca_certs=CA_PATH, certfile=CERT_PATH, keyfile=KEY_PATH)
client.connect(BROKER_ENDPOINT, PORT, keepalive=60)

# Connecta amb l'arduino
arduino = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
time.sleep(2)  # Esperar inicialització

# Bucle principal
client.loop_start()
try:
    while True:
        if arduino.in_waiting > 0:
            data = arduino.readline().decode().strip()
            if data:
                print("Sending data:", data)
                client.publish(TOPIC, data)
except KeyboardInterrupt:
    print("Disconnecting...")
    client.loop_stop()
    client.disconnect()
    arduino.close()
