## Communication Protocol

If you want to connect the GUI with the hardware part, just:

```
Serial.println(content);
```

while the `content` is a string in this format:
```
A,B,C,D,E
```

**A** is the alarm state, 0 means NORMAL, 1 means PRE-ALARM, 2 means ALARM.
**B** is the water level in mm, an integer.
**C,D,E** are the states of LED_A, LED_B, LED_C. 1 means ON, 0 means OFF.

For instance:
```
1,1234,1,0,1
```
means the bridge is in PRE-ALARM, the water level is 1234 mm,
LED_A is ON, LED_B is OFF, LED_C is ON.


## How to run the GUI
The `main.exe` file can be directly run on Windows.  

For other OS, you may execute the python source code. You need a Python 3 environment, with the following packages which can be installed by conda:
+ pyqt
+ pyqtchart
+ pyinstaller
+ pyserial

If you want to generate an execable on your OS:
```
pyinstaller main.py -F -w
```