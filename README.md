# AndroidThings-Assignment

As part of an Arduino-based electronics assignment, I designed and built an interactive locking mechanism to support a real-world escape room. The goal was to provide a hands-on way to unlock a magnetic lock using RFID tags, acting like puzzle keys that, when placed correctly, trigger the lock to open.

This project was created to support an expansion location of a local escape room chain. The system is designed to detect multiple RFID key placements. When all correct keys are placed, a magnetic lock is released, activating a physical game element (e.g., dropping a box, opening a compartment, or revealing a clue).

---

## Schematics Plan – Electronics and Connectivity

![Image](https://github.com/user-attachments/assets/5a9d21e6-c40d-4c33-af3c-b6d14603bffe)

Each RFID sensor is connected to the Arduino through a shared SPI interface with unique slave select pins. The magnetic lock is controlled via a relay module, which is triggered by the Arduino.

---

## Pre-requisites – Hardware Components

To build this project, you'll need the following components:

- 1x [Arduino Uno](https://www.robofun.ro/platforme-de-dezvoltare/arduino-uno-r3.html) 
- 4x [RC522 RFID readers](https://www.optimusdigital.ro/ro/wireless-rfid/67-modul-cititor-rfid-mfrc522.html)
- 1x [12V Electromagnetic Lock](https://www.emag.ro/incuietoare-electromagnetica-mini-12-v-2830/pd/DG55YCYBM/)
- 1x Relay Module (for the lock)
- 1x 12V Power Adapter
- Breadboard and jumper wires
- [RFID key tags/cards](https://www.itgstore.ro/card-rfid-tk4100-overlay-125khz-cr80-alb-p-TK4100-OL-22432)
- [Fritzing](https://fritzing.org) (for schematics)

---

## Setup and Build Plan



The setup for this project involved several stages to ensure everything worked seamlessly for an escape room environment.

First, we wired four RC522 RFID readers to the Arduino Uno using the SPI communication protocol. Each RFID module shares the same SPI bus (MISO, MOSI, SCK), but has a unique Slave Select (SS) pin to allow the Arduino to differentiate between them. The wiring was done on a breadboard for easy prototyping and testing.

Once the hardware was connected, we developed Arduino code to continuously read the RFID tags scanned by each module. The code compares the scanned tag IDs against a list of predefined “correct” tags. Only when all required tags are present does the system trigger the next action.

To control the electromagnetic lock, we added a relay module. The Arduino sends a HIGH signal to the relay when the correct RFID tags are detected, which then allows 12V power to flow to the magnetic lock. This releases the lock and activates a physical mechanism (e.g., a drawer dropping, compartment opening, or puzzle piece being revealed).

A 12V external power adapter is used to supply sufficient current to the maglock, ensuring it stays reliably engaged until it's intentionally triggered.

The entire prototype was tested on a breadboard, and functionality was confirmed with the right combination of RFID tags. All components work together to create a simple, reliable, and fun escape room interaction.

---

## Demo Video 🎥

https://github.com/user-attachments/assets/9f660308-482a-440b-ba12-34e50ae86625

--- 

## Coding 💻

For this project, we used the **Arduino IDE** to program the logic that controls the escape room puzzle. The goal was to read four RFID tags, compare them with a predefined sequence, and unlock a magnetic lock once all tags are correct.

The system uses four **MFRC522** RFID readers connected via SPI to an **Arduino Uno**, and a **relay module** that toggles a **12V electromagnetic lock**.

Below are a few key code snippets and explanations to show how the system was implemented.

### Checking for RFID Tags and Matching

Inside the `loop()`, each RFID reader checks for a new card. If a card is detected, its UID is read and converted into a string. That string is then compared to a predefined list of correct tag IDs.

This check helps determine whether the puzzle has been solved.

![Image](https://github.com/user-attachments/assets/6187ae3f-6af0-4d77-b462-3dad13b2d124)


### Initializing Multiple RFID Readers

In the `setup()` function, all RFID readers are initialized using SPI, the relay pin for the maglock is configured, and debug logs are printed via serial to confirm the system is ready.


![Image](https://github.com/user-attachments/assets/0c37240e-3343-48e2-ab64-4ae6c0e0c1cd)

