# Raquel-and-the-Johnnies
Major Project for MTRX2700

This project explores the use of microcontrollers and hardware components to design a futuristic game show containing arcase games re-imagined for an audience. 
The chosen game for this project, known as "**GAME NAME**" is spinoff of lawn bowls. 
The aim of the game is to gain as many points as possible during the player's three turns. The player with the highest score wins. 
In order to gain points, players must 'bowl' a ping pong ball down an alleyway by placing the ball on the ramp, which is adjusted to the players desired angle, and wait for the ball to be released and roll down the ramp and onto the alley.
It is important to note that going further does not necessarily provide more points

## Group Members and Responsibilities
Contributors to the project were Darcy Schofield, Natalie Brown, Axel Purcell, and Raquel Kampel. 

Darcy was responsible for the timer countdown and capacaitive touch sensor. Natalie worked on the PTU functionality and mechanical design. Axel designed the serial interface and lidar functionaility. Raquel was tasked with the servo motor module. 

Natalie was responsible for the meeting minutes. 

Credit is owed to Stewart Worrall's GitHub repo [MTRX2700-2024](https://github.com/stewart-worrall/MTRX2700-2024), which served as a valuable resource and provided a useful framework for this project. Furthermore, the STM32 Reference Manual and the specific datasheet for the STM32F303 were indispensable in completing this task.

## Prerequisites
STM32Cube IDE must be installed to run this code, as well as connection to the STM32F303 Microcontroller via micro-USB. IDE can be downloaded  [here](https://github.com/stewart-worrall/MTRX2700-2024). 

This code can be run by cloning it onto your local machine and importing the project into IDE by selecting:
File > Import > General > Existing project into workspace > Browse, and selecting the desired code to open.

## Modules
There are a number of elements to the project which have been modularised for simplicity and debugging purposes.

The project is modularised into the following parts:
### 1. PTU rotation
- ramp angle control

### 2. Lidar 
- reading ball distance and returning result to serial

### 3. Servo motor
- opens gate when time is up
- ball is released 

### 4. Piezo/Capacative touch sensor
- cosmetic addition
- indicates closeness to target 

### 5. LED timer countdown
- 16s time to choose angle and set ball
- makes servo gate open
- if you dont put the ball up in time 0 points.

### 6. Serial Interface 
- recieve lidar data and output points/distance to user interface

### 7. Integration
- integrate all modules to create a cohesive game 

## Testing
**PTU Rotation**
- test functionality; press button and observe that the ptu stops
  
**Lidar**
- put ball at a known distance away from the lidar and ensure that it reads the correct distance

**Servo Motor**
- run code and observe that it does desired behaviour 

**Piezo/Capacative Touch**
- run code and observe that it does desired behaviour 

**LED Timer Countdown**
- run code and observe that it does desired behaviour 

**Serial interface**
- input sample distances and observe output

**Integration**
- play the game





