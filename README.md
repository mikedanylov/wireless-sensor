## Wireless Temperature Sensor

Wireless temperature sensor transmitter and receiver

####Hardware configuration
######Transmitter:
* Analog temperature sensor TMP36GZ (Analog Devices) 
* 8 bit microcontroller ATmega328p (Atmel)
* Wireless transceiver NRF24L01+ (Nordic Semiconductiors)
* Step-up voltage regulator 3.3V
* Other misc components
######Receiver:
* 8 bit microcontroller ATmega328p (Atmel)
* Wireless transceiver NRF24L01+ (Nordic Semiconductiors)
* USB-TTL converter
* Other misc components

![Transmitter Hardware](/etc/transmitterHW.JPG)
Configuration of transmitter and receiver is pretty much the same but the latter doesn't have sensor and voltage reg but has USB-TTL converter instead.

####Brief description of operation
######Transmitter:
1. Power on or reset initializes timer interrupt and sensor id is assigned to transmitter
2. Most of the time the uC stays in sleep mode and wireless transceiver is powered down
3. Every ~2 min a timer interrupt occurs
4. uC lights up and LED indicating that it woke up from sleep mode
5. NRF24 chip is initialized 
6. Samples (~100) are read from ADC where analog temperature sensor is connected
7. Average is calculated concatenated with sensor id and passed to NRF24 module
8. Transceiver sends the data over pipe to receiver
9. LED is turned off indicating that transmission is completed
10. NRF24 is powered down and atmega328p goes to sleep mode again
######Receiver:
1. Receiver is pulling the data from a pipe all the time
2. Once the data is available it sends it straight to USART
Then it is a task of host machine to read the serial port and interpret the data accodingly. 