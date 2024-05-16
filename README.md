# Raquel-and-the-Johnnies
Major Project for MTRX2700

This project explores the use of microcontrollers and hardware components to design a futuristic game show containing arcase games re-imagined for an audience. 
The chosen game for this project, known as "Lab Bowls" is similar to lawn bowls. 
The aim of the game is to gain as many points as possible during the player's three turns. The player with the highest score wins. 
In order to gain points, players must 'bowl' a golf ball down an alleyway by placing the ball on the ramp, which is adjusted to the players desired angle, and wait for the ball to be released and roll down the ramp and onto the alley.
It is important to note that going further does not necessarily provide more points

## Group Members and Responsibilities
Contributors to the project were Darcy Schofield, Natalie Brown, Axel Purcell, and Raquel Kampel. 

Darcy was responsible for the timer countdown and capacaitive touch sensor. Natalie worked on the PTU and lidar functionality and mechanical design. Axel designed the serial interface reading from lidar functionaility. Raquel was responsible for the servo motor module. 

Natalie was responsible for the meeting minutes. 

Credit is owed to Stewart Worrall's GitHub repo [MTRX2700-2024](https://github.com/stewart-worrall/MTRX2700-2024), which served as a valuable resource and provided a useful framework for this project. Furthermore, the STM32 Reference Manual and the specific datasheet for the STM32F303 were indispensable in completing this task.

## Getting started
 [STM32Cube IDE ](https://github.com/stewart-worrall/MTRX2700-2024) and a pan tilt-unit with LIDAR are essential to run this code, as well as connection to the STM32F303 Microcontroller via micro-USB. The project also involves the use of a mini-servo, a capactivie touch sensor, a piezo buzzer, and some mechanical design materials such as a ball. 

This code can be run by cloning it onto your local machine and importing the project into IDE by selecting:
File > Import > General > Existing project into workspace > Browse, and selecting the desired code to open.

## Modules
There are a number of elements to the project which have been modularised for simplicity and debugging purposes.

The project is modularised into the following parts:
### 1. PTU rotation
The PTU module a key component of the code which controls the rotation of the ramp from which the ball is released. The PTU is continuously rotating by default and is paused when the user presses a button to stop the ramp at the desired release angle. The ramp remains in this position until after the ball is released by the miniservo gate. Afterwards, the ramp is returned to neutral position so the ball distance can be read by the lidar.

### 2. Lidar 
The lidar functionality is to read the distance travelled by the ball which determines the number of points scored by a player. The lidar range is read by the serial module which will return the results to the players.

### 3. Servo motor
The servo motor module controls the opening and closing of the gate which holds the ball before release. It is triggered when the timer is up and the gate raises once, allowing the ball to roll away, and returns to a closed position for the next turn. 

### 4. Piezo/Capacative touch sensor
The capacitive touch sensor is a novelty addition to the game which indicates how close to the highest point-scoring location the ball reaches through the use of a piezo buzzer. Much like a metal detector, the piezo buzzer will output a higher frequency noise as the ball becomes closer to the capacitive toucher sensor. This module is not essential to the basic functionality of the game but is an interesting and fun addition to the project. 

### 5. LED timer countdown
The LED timer countdown serves as both a functional and 'aesthetic' module in the project. Functionally, the end of the timer indicates to the servo module that the gate should be lifted to release the ball, regardless of if the player has selected a ramp angle. Aesthetically, the module provides a visual representation of the depleting time by turning off LEDs in a circular order on the STM32 board as time progresses, with all the lights off when time is up. With a 16 second time limit, one LED turns off every 2 seconds. 

### 6. Serial Interface 
The serial interface recieves data from the lidar module which indicates how far the ball has travelled. Some logic is perfomed within the code to determine the number of points earned by the player's attempt. The results of the turn (distance travelled and points scored) is returned to the user by the serial interface. 

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






