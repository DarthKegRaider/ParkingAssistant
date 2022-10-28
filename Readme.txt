Feel free to use this code.  
I do not claim 100% ownership of any of the written code.  
Most has been borrowed and modified from other great coders.

Wiring up your Arduino, I used a Nano but it will translate to any version.
Whatever pin you use below, change in your code accordingly.


                 '------------'
                 |            | VIN -o-- 5V to NeoPixel and Sonar
                 |            |  
                 |            | 11 --o-- TRIG (sonar)
                 |            | 10 --o-- PING (sonar)
                 |            | 
                 |            | 
                 |            |
                 |  Arduino   |
                 |            |
                 |            |
                 |            |
                 |            | 
                 |            | 3  --o-- DIN on NeoPixel Ring
                 |            | 2  --o-- Button
                 |            | GND -o-- Button, NeoPixel and Sonar
                 '------------'         
 Can be powered using the USB plug, or via the VIN/5V on the Arduino.
