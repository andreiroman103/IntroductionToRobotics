# Introduction To Robotics (2021 - 2022)
Homeworks and projects for the "Introduction To Robotics" course, taken in the 3rd year at the Faculty of Mathematics and Computer Science. The homeworks and projects will consist of code, image files and documentation. This is my first contact with robotics and Arduino and I want to make the most of it.

# Homework 1
### Task
Use a separate potentiometer in controlling each of the colors of the RGB led (Red, Green and Blue). The control must be done with digital electronics (aka you must read the value of the potentiometer with Arduino, and write a mapped value to each of the pins connected to the led.

### Solution
I used 3 variables corresponding to the Red, Green and Blue colors to store the value read from each of the potentiometers (redAnalogValue, greenAnalogValue, blueAnalogValue). Then I mapped those values to the intensity value for each color of the LED using the map() function and stored the mapped values in 3 variables: redValue, greenValue, blueValue. In the end, I passed the mapped values to the pins that the LED is connected to using the analogWrite() function.

### Components used
- 1x RGB LED
- 3x Potentiometers
- 3x Resistors (330 Ω)
- Wires

### Picture and scheme of the setup

![RGB Led with 3 potentiometers scheme](https://user-images.githubusercontent.com/34553466/198073146-00734fee-80fe-4749-86ed-1c23608bd8ce.png)
![Setup](https://user-images.githubusercontent.com/34553466/198073190-bce97339-9b69-43d1-a48b-790c34924ac2.jpg)

### Link for the showcase video
https://www.youtube.com/shorts/Luyyr2wGY1Y
