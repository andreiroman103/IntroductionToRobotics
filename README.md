# Introduction To Robotics (2022 - 2023)
Homeworks and projects for the "Introduction To Robotics" course, taken in the 3rd year at the Faculty of Mathematics and Computer Science. The homeworks and projects will consist of code, image files and documentation. This is my first contact with robotics and Arduino and I want to make the most of it.

<details>
<summary> Homework 1 </summary>

# Homework 1

### Task
Using a separate potentiometer in controlling each of the colors of the RGB led (Red, Green and Blue). The control must be done with digital electronics (aka the value of the potentiometer must be read with Arduino, and a mapped value must be written to each of the pins connected to the led).

### Solution
I used 3 variables corresponding to the Red, Green and Blue colors to store the value read from each of the potentiometers (redAnalogValue, greenAnalogValue, blueAnalogValue). Then I mapped those values to the intensity value for each color of the LED using the map() function and stored the mapped values in 3 variables: redValue, greenValue, blueValue. In the end, I passed the mapped values to the pins that the LED is connected to using the analogWrite() function.

### Components used
- 1x RGB LED
- 3x Potentiometers
- 3x Resistors (330 Ω)
- Wires

### Picture and scheme of the setup

<p float = "left">
    <img src = "https://user-images.githubusercontent.com/34553466/198073146-00734fee-80fe-4749-86ed-1c23608bd8ce.png" height = "450" width = 45%>
    <img src = "https://user-images.githubusercontent.com/34553466/198073190-bce97339-9b69-43d1-a48b-790c34924ac2.jpg" height = "450" width = 45%>
</p>

### Link for the showcase video
https://www.youtube.com/shorts/Luyyr2wGY1Y
</details>

<details>
<summary> Homework 2 </summary>

# Homework 2

### Task
Building the traffic lights for a crosswalk. There will be 2 LEDs used to represent the traffic lights for pedestrians (red and green) and 3 LEDs used to represent the traffic lights for cars (red, yellow and green). The system will have 4 possible states: 
- State 1 (default, reinstated after state 4 ends): green light for cars,
red light for people, no sounds. Duration: indefinite, changed by
pressing the button.
- State 2 (initiated by counting down 8 seconds after a button press):
the light should be yellow for cars, red for people and no sounds.
Duration: 3 seconds.
- State 3 (initiated after state 2 ends): red for cars, green for people
and a beeping sound from the buzzer at a constant interval. Duration:
8 seconds.
- State 4 (initiated after state 3 ends): red for cars, blinking green
for people and a beeping sound from the buzzer, at a constant interval,
faster than the beeping in state 3. This state should last 4
seconds.

Pressing the button in any state other than state 1 should
NOT yield any actions!

### Solution
The system is controlled by a variable called systemState. I created a function for each of the 4 possible states and called the corresponding function depending on the systemState value in the loop() function. In the defaultState function, I used debounce to make sure that the button press was registered correctly and also checked that the systemState is equal to 1 (the system is in the default state) to make sure that the button press is only registered in this state (if the button is pressed during other state nothing happens). The other states functions control the lights for the cars and pedestrians and the sounds according to the task and change the systemState value in order to create the states flow. 

### Components used
- 5x LEDs
- 1x Button
- 1x Buzer
- 5x Resistors (330 Ω)
- 1x Resistor (100 Ω)
- Wires

### Picture and scheme of the setup

<p float = "left">
    <img src = "https://user-images.githubusercontent.com/34553466/199082018-d951aea6-38a5-41c4-96a0-5a7b6fae90a4.png" height = "450" width = 45%>
    <img src = "https://user-images.githubusercontent.com/34553466/199079548-0e334c71-ed21-42fd-96d3-067945a28d2d.jpg" height = "450" width = 45%>
</p>

### Link for the showcase video
https://www.youtube.com/shorts/SouPqYfCUUE
</details>

<details>
<summary> Homework 3 </summary>

# Homework 3
    
### Task
"Drawing" on the 7-segment display using the joystick to control the position of the segment. The system has the following states:
 - State 1 (default, but also initiated after a button press in State 2): Current position blinking. Can use the joystick to move from one position to neighbors. Short pressing the button toggles state 2. Long pressing the button in state 1 resets the entire display by turning all the segments OFF and moving the current position to the decimal point.
- State 2 (initiated after a button press in State 1): The current segment stops blinking, adopting the state of the segment before selection (ON or OFF). Toggling the X (or Y) axis should change the segment state from ON to OFF or from OFF to ON. Clicking the joystick should save the segment state and exit back to state 1.
Long pressing the button to reset should only be available in State 1.

Possible moves:
| Current segment |  UP | DOWN | LEFT | RIGHT |
|:---------------:|:---:|:----:|:----:|:-----:|
|        a        | N/A |   g  |   f  |   b   |
|        b        |  a  |   g  |   f  |  N/A  |
|        c        |  g  |   d  |   e  |   dp  |
|        d        |  g  |  N/A |   e  |   c   |
|        e        |  g  |   d  |  N/A |   c   |
|        f        |  a  |   g  |  N/A |   b   |
|        g        |  a  |   d  |  N/A |  N/A  |
|        dp       | N/A |  N/A |   c  |  N/A  |
    
### Solution
The systemState variable is used to toggle between the 2 states, each having its own function. In the state1() function, I made the current segment blink and read the X and Y values of the joystick in order to change the segments according to the possible movements. I used the possibleMovements matrix to store the possible moves each segment can have (the matrix is 8x4, each row represents a segment and each column a direction). This matrix is used in the changeSegment() function, which takes the direction parameter and sets the next segment (for example if the current segment is a and the direction is right, the next segment will be b).
In the state2() function the state of the current segment is set to its last state (stored in the segmentsStates vector) and the X value of the joystick is read in order to change the state of the current segment. If the system is in state 1 and the button is pressed for long, the system will be reset, but if the button is pressed shortly, the system will go in the second state. If the system is in the second state and the button is pressed shortly, the system will go back to state 1.
    
### Components used
- 1x 7-segment display
- 1x joystick
- 2x Resistors (1000 Ω)
- Wires
    
### Picture and scheme of the setup
<p float = "left">
    <img src = "https://user-images.githubusercontent.com/34553466/200983636-ce241dc1-1184-4629-a9ad-1f0bb487c07b.png" height = "450" width = 45%>
    <img src = "https://user-images.githubusercontent.com/34553466/200983963-f25ed159-6b43-40ef-8db8-c0017f0b523a.jpg" height = "450" width = 45%>
</p>
    
### Link for the showcase video
https://www.youtube.com/watch?v=EEjVxh2KkmE 
</details>

<details>
<summary> Homework 4 </summary>

# Homework 4
    
### Task
"Drawing" HEX numbers on the 4 digit 7-segment display using the joystick to control the digit and the written number. The system has the following states:
- First state: you can use a joystick axis to cycle through the 4 digits; using the other axis does nothing. A blinking decimal point shows the current digit position. When pressing the button, you lock in on
the selected digit and enter the second state.
- Second state: in this state, the decimal point stays always on, no longer blinking and you can no longer use the axis to cycle through the 4 digits. Instead, using the other axis, you can increment on decrement the number on the current digit IN HEX (aka from 0 to F, as in the lab). Pressing the button again returns you to the previous state. Also, keep in mind that when changing the number, you must increment it for each joystick movement - it should not
work continuosly increment if you keep the joystick in one position (aka with joyMoved).
- Reset: toggled by long pressing the button only in the first state. When resetting, all the digits go back to 0 and the current position is set to the first (rightmost) digit, in the first state.

### Solution
The systemState variable controls the state changes. In the state1() function, I made the dp of the current digit blink and used the Y axis to change between the 4 digits of the display. The state2() function uses the X axis of the joystick to change the number displayed on the selected digit. The reset() function changes the current digit to the first digit and sets all the digits back to 0. The writeReg() function is the one shifting the bits in the shift register and it is used inside the writeNumber() function to display the number on the digit. 

### Components used
- 1x 4 digit 7-segment display
- 1x joystick
- 1x 74hc595 shift register
- 4x Resistors (1000 Ω)
- Wires

### Picture and scheme of the setup
<p float = "left">
    <img src = "https://user-images.githubusercontent.com/34553466/202419119-ea78cd9d-711f-44f3-98de-36200037d054.png" height = "450" width = 45%>
    <img src = "https://user-images.githubusercontent.com/34553466/202419169-2f116d22-e8c5-4804-8550-b90321e0651d.jpg" height = "450" width = 45%>
</p>

### Link for the showcase video
https://www.youtube.com/watch?v=yw67836DK_4
</details>

<details>
<summary> Matrix Project </summary>
https://github.com/andreiroman103/MatrixProject-REMEMBER-Robotics
</details>

<details>
<summary> Line Follower Project </summary>
https://github.com/andreiroman103/LineFollower-Robotics
</details>
