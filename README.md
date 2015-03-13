# wireless-sensor
Wireless temperature sensor transmitter and receiver

13.03.15 [Update] 
Now transmitter uses timer interrupt to send data once in a while. This approach reduces power consumption significantly since now CPU is put to sleep mode after data was send.
TODO:
Next step would be to try how much exactly current it consumes in different sleep modes and sleep intervals in order to estimate battery life if final sensor node will work from 2 coin cell batteries.

[How it looked like on first successfull test!](etc/v0.0.1.jpg)
