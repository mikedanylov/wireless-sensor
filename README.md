# wireless-sensor
Wireless temperature sensor transmitter and receiver

02.06.15 [Update]
*added two Hardware Adapters for DS18B20 and NRF24L01
*added Record class which represents packet sent by transmitter including sensor ID and data.

13.03.15 [Update] 
Now transmitter uses timer interrupt to send data once in a while. This approach reduces power consumption significantly since now CPU is put to sleep mode after data was send.

[How it looked like on first successfull test!](etc/v1.jpg)
