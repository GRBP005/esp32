#include "USB.h"
#include "USBHIDKeyboard.h"

USBHIDKeyboard Keyboard;
String buffer[100];  // Ajusta según cuántas teclas quieras guardar
int index = 0;
bool recordingDone = false;
bool loopActive = false;

void setup() {
  Serial.begin(115200);
  Keyboard.begin();
  Serial.println("Esperando teclas...");
}

void loop() {
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    line.trim();

    if (line == "__END__") {
      recordingDone = true;
      Serial.println("Grabación finalizada.");
    } else if (line == "START") {
      loopActive = true;
      Serial.println("Reproduciendo en bucle...");
    } else if (!recordingDone) {
      if (index < 100) {
        buffer[index++] = line;
        Serial.println("Tecla guardada: " + line);
      }
    }
  }

  if (loopActive && recordingDone) {
    for (int i = 0; i < index; i++) {
      String key = buffer[i];
      Keyboard.print(key);
      delay(200);
    }
  }
}
