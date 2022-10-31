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
    <img src = "https://user-images.githubusercontent.com/34553466/198073146-00734fee-80fe-4749-86ed-1c23608bd8ce.png" width = 45%>
    <img src = "https://user-images.githubusercontent.com/34553466/198073190-bce97339-9b69-43d1-a48b-790c34924ac2.jpg" width = 45%>
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

</p>

### Link for the showcase video
https://www.youtube.com/shorts/SouPqYfCUUE
</details>