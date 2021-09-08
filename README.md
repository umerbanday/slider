# Slider
**Note for VSCode**<br/>
If remote dev branch doesnt show up in vscode, use:
```
git fetch --all
```
After deleting a remote branch, remove it from vscode by:
```
git fetch --prune
```
Local branches can then be deleted in vscode by:
```
Ctrl + Shift + P
```
Then, go to **Git:Delete Branch** and select the branch to delete.

**Arduino Slider Control**


_Pins used:_  <br />
StepPin : GPIO 9  <br />
DirPIn  : GPIO 8   <br />
Joystick : Analog 14,15  <br />
LCD : GPIO 2, 3, 4, 5, 6, 7  <br />
Encoder : CLK-GPIO 12, DT-GPIO 11, SW-GPIO 10<br />
Open Pins : GPIO 0,1,13

**Features Implemented**

- [x] Stepper Driver
- [x] LCD Interfacing
- [x] Joystick Interfacing
- [x] Joystick Control
- [x] Encoder Interfacing
- [ ] Encoder Control
- [ ] Menu Design
- [ ] Automatic Operation 



**Arduino Built-in Functions**<br />

Setup function which runs initially :<br />
```
void setup(){
    //setup code
}

```
Loop function which runs continuosly :<br />
```

void loop(){
    //loop code
}

```

**Basic Information**<br />
_Arduino Pinout:_<br />

![alt text](https://github.com/umerbanday/slider/blob/main/images/High-Res-Arduino-UNO-Pinout.jpg?raw=true) <br />

_A4988 Pinout:_<br /><br />
![alt text](https://github.com/umerbanday/slider/blob/main/images/A4988%20Diagram.png?raw=true)<br /><br />

_16x2 LCD Pinout:_<br /><br />
![alt text](https://github.com/umerbanday/slider/blob/main/images/interfacing-LCD-to-arduino.png?raw=true)<br /><br />


