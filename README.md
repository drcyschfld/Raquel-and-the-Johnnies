# Raquel-and-the-Johnnies
Major Project for MTRX2700

This project explores the use of microcontrollers and hardware components to design a futuristic game show containing arcase games re-imagined for an audience. 
The chosen game for this project, known as "Lab Bowls" is similar to lawn bowls. 
The aim of the game is to gain as many points as possible during the player's three turns. The player with the highest score wins. 
In order to gain points, players must 'bowl' a ball down an alleyway by placing the ball on the ramp, which is adjusted to the players desired angle, and wait for the ball to be released and roll down the ramp and onto the alley.
It is important to note that going further does not necessarily provide more points

## Group Members and Responsibilities
Contributors to the project were Darcy Schofield, Natalie Brown, Axel Purcell, and Raquel Kampel. 

Darcy was responsible for the timers and capacaitive touch sensor. Natalie worked on the PTU & lidar functionality. Axel designed the serial interface reading from lidar functionaility. Raquel was responsible for the servo motor module. 

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
The lidar functionality is to read the distance travelled by the ball which determines the number of points scored by a player. The lidar range is read by the serial module which will return the results to the players. The lidar uses PWM to record the distance traveled by the ball. The pulse width is directly related to the distance where 1 milisecond is taken to record 1 meter. 

### 3. Servo motor
The servo motor module controls the opening and closing of the gate which holds the ball before release. It is triggered when the timer is up and the gate raises once, allowing the ball to roll away, and returns to a closed position for the next turn. 

### 4. Piezo/Capacative touch sensor
The capacitive touch sensor is a novelty addition to the game which indicates how close to the highest point-scoring location the ball reaches through the use of a piezo buzzer. Much like a metal detector, the piezo buzzer will output a higher frequency noise as the ball becomes closer to the capacitive toucher sensor. This module is not essential to the basic functionality of the game but is an interesting and fun addition to the project. 

### 5. Timer/LED countdown
The LED timer countdown serves as both a functional and 'aesthetic' module in the project. Functionally, the end of the timer indicates to the servo module that the gate should not be lifted at all, regardless of if the player has selected a ramp angle. Aesthetically, the module provides a visual representation of the depleting time by turning off LEDs in a circular order on the STM32 board as time progresses, with all the lights off when time is up. With a 16 second time limit, one LED turns off every 2 seconds. It calls the general_initialisation function which then calls the enable_clocks and initialise_board function, which are both responsible for general/basic setup for the use of the LEDs and timers. It then turns on all the LEDs by calling the LED_on function. A timer overflow then begins with the timer_overflow pointer which is assigned to the address of the function 'chase_led'. When the timer overflow interrupt (handled by TIM2_IRQHandler()) occurs, chase_led will be executed. The chase_led function is responsible for turning off an LED on each iteration. The timer_set takes a hex value 0x7D0, which is decimal is equivalent to 2000, corresponding to how many milliseconds it takes between each timer overflow trigger, which causes an LED to turn off. Finally, interrupts are enabled, which includes setting the priority and enabling the TIM2 interrupt line. Once all the LEDs have turned off, the chase_led function checks if theyre all off and if they are it calls the timer_set function again, however, now with a hex value of 0x64, which is equivalent to 100 decimal, which is how many milliseconds it takes between light changes now. This is purely aesthetic to indicate the end of a 'turn' in the game.

### 6. Serial Interface 
The serial interface recieves data from the lidar module which indicates how far the ball has travelled. Some logic is perfomed within the code to determine the number of points earned by the player's attempt. The results of the turn (distance travelled and points scored) is returned to the user by the serial interface. 

## Testing
**PTU Rotation**
- test functionality;Ensure that the PTU rotates fully without button integration. Once that is confimed we added the press button and observe that the ptu stops. When 'direction' = 4 is the max value that we can add. Since 2000 is max pulse width, we cannot add values higher than that. 
  
**Lidar**
- put ball at a known distance away from the lidar and ensure that it reads the correct distance.What is the maximum distance the ball can roll and still be detected. 

**Servo Motor**
- run code and observe that it does desired behaviour. Since 2000 is max pulse width for 180 degrees,values higher than 2000 did not run. Minumim values of 180 was also set.
- Adjusting direction to a higher value incraeses speed at which the motor truns, however higher than 4 will cause motor to glitch as tehye were to fast. 

**Piezo/Capacative Touch**
- Testing is completed easily by running the code and observing the nature of it. When watching the code, it can be seen that the lights will individually turn off one at a time at a certain pace, and then the LEDs will flash at another pace. To test, you can select different speeds for these LEDs changes by changing the value given to the timer_set function which is called in main for the countdown, and in digital_io.c inside the chase_led function for the light flashing sequence. Different hex values can be selected such that bigger numbers result in a longer duration time and smaller numbers make it go faster.

**5. Timer/LED countdown**
- run code and observe that it does desired behaviour. 

**Serial interface**
- input sample distances and observe output. tested serial with hard coded values before inetgrating the lidar. anything 100cm or less than 10 = 1000 points

### User Instructions:

### Timer/LED countdown:
**Step 1:**<br />
Open the code (boulesTimer2)
**Step 2:**<br />
Run the code on an STM32f3
**Step 3:**
The timer has now begun, watch the timer go down
**Step 4:**
Release the ball before the timer runs out
**Step 5:**
After 16 seconds has passed, the timer will run out and the LEDs will flash very quickly, indicating the end of your turn
**Step 6:**
If you want to play the timer/game again, press the black 'RESET' button
**Step 7:**
If you would like to reduce the amount of time it takes before the timer runs out and your turn ends (perhaps to make the game more difficult), in the main function, change the hex value given in the timer_set function to a smaller number for less time or a larger number for more time
**Step 8:**
If you would like to change the speed of the flashing LEDs (for aesthetics) locate the chase_led function inside digital_io.c and change the value given in the timer_set function to a smaller number for faster flashes, or a larger number for slower flashes.
