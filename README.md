Filter
======

Basic filters implemented as an Arduino library.  

Includes easily configured moving average with an example for low pass filter 
applicable to noisy servo commands reeived via a wireless serial connection
for a remote control robot or noisy distance data received by a Ping))) sonsor
or other ultrasonic (sonar) rangefinder.

Most sensors in small scale robotics are noisy.  For example as a
mobile robot approaches a wall, an atached ulrasonic sensor should
give readings in cm similar to the list below

11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, ...bump!

but all too often the data will come back like this

11, 10, 6, 8, 7, 3, 5, 4, 1, 2, 1, ..bump!

By filtering the raw data, via a moving average or other more 
specialized filter we can use the noisy data as an input to q
filter and then the processed data will give a better linear
output.  This linear output still doesn't match the exact distance
to the wall, but it is a much closer approximation than the noisy
data and provides a better set of data for the robot to make 
control decisions from.
