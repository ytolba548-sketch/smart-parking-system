# Smart Parking System 🚗🅿️

A smart, automated parking management system built with Arduino Uno. This project aims to monitor parking spaces, control entry/exit gates, and display real-time availability, reducing congestion and saving time for drivers.

## 👥 Team Members

*   **Yahia Mahmoud** - Team Leader
*   **Omar** - Code & Logic Implementation
*   **Raneem** - Circuit Simulation & Tinkercad

## 🌟 Project Overview

The Smart Parking System is designed to automate parking lot management. It utilizes ultrasonic sensors to detect vehicle presence at the entrance and in individual parking slots. The system automatically opens the barrier for incoming vehicles if space is available, updates the available slots count on an LCD display, and provides visual and auditory feedback using LEDs and a buzzer.

## ✨ Features

*   **Automated Entry/Exit:** Servo motor controlled barrier gate.
*   **Real-time Monitoring:** LCD display showing available parking slots.
*   **Space Detection:** Ultrasonic sensors to track vehicle movement and slot occupancy.
*   **Visual Indicators:** Red and Green LEDs indicating availability and system status.
*   **Audio Alerts:** Buzzer for notifications or error states.

## 🏗️ System Architecture & Components

The system is built using the following core components:

*   **Arduino Uno:** The main microcontroller unit processing sensor data and controlling outputs.
*   **2x Ultrasonic Sensors (HC-SR04):** Used for detecting vehicles at the gate and in parking spaces.
*   **16x2 LCD Display:** Shows the welcome message and real-time count of available slots.
*   **Micro Servo Motor (SG90):** Acts as the entry/exit barrier gate.
*   **LEDs (Red & Green):** Provide quick visual status (e.g., Green = space available / gate open, Red = lot full / gate closed).
*   **Buzzer:** Emits sound for specific events (like gate opening or full capacity warning).

## 🚀 Simulation

You can view and interact with our circuit simulation on Tinkercad:

*   **Tinkercad Link:** [Insert Tinkercad Link Here]

## 📂 Project Structure

*   `code/`: Contains the Arduino sketch (`smart_parking.ino`).
*   `simulation/`: Contains simulation assets and links (`link.txt`).
*   `docs/`: Project documentation and presentation notes (`presentation_notes.md`).

---
*Developed for the Hackathon.*
