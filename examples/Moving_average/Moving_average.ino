/*
  This example demonstrates the use of a running average to smooth
  noisy data.  Load the sketch and then open the Serial monitor.
  As you enter integers into the serial input you will notice 
  the first moving average converges on the new data quicker
  than the second, but neither one jumps directly to the new value.
  
 *      Most sensors in small scale robotics are noisy.  For example as a
 *	mobile robot approaches a wall, an atached ulrasonic sensor should
 *	give readings in cm similar to the list below
 *
 *	11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, ...bump!
 *
 *	but all too often the data will come back like this
 *
 *      11, 10, 6, 8, 7, 3, 5, 4, 1, 2, 1, ..bump!
 *
 *      By filtering the raw data, via a moving average or other more 
 *	specialized filter we can use the noisy data as an input to our
 *	filter and then the processed data will give us a better linear
 *	output.  This linear output still doesn't match the exact distance
 *      to the wall, but it is a much closer approximation than the noisy
 *	data and provides a better set of data for the robot to make 
 *	control decisions from.
 *
 *	Since this filter library is designed to support Arduino applications
 *      I'm limiting it to only work on integer data.  I might add templating
 *      for arbitrary numeric types, but most Arduino users don't know how
 *      to instantiate a templated class, so it might not every get used.
 *
*/

#include <Filter.h>

// Create a moving average filter that averages the last 
// three elements, and starting values are default set to
// zero.
Moving_average ma(3);

// Create a moving average filter that averages the last
// nine data points, and starting values are defaulted to
// 90.  This is a good choice for the default value of a 
// motor command that goes to a servo because the servo's 
// middle position is usually 90.
Moving_average ma2(9, 90);

void setup(){
  Serial.begin(9600);
  Serial.setTimeout(100);  //change default from 1000ms to 100ms so
                           //we timeout quicker in the parseInt function
                           //from read_serial.
}

void loop() {
  static int tmp_val = 0;
  static int filter1 = 0;
  static int filter2 = 90;
  if(Serial.available()) {
    tmp_val = read_serial();
  }
  
  filter1 = ma.filter(tmp_val);
  filter2 = ma2.filter(tmp_val);
  
  Serial.print("tmp_val is: ");
  Serial.print(tmp_val);
  Serial.print("\tma1 is: ");
  Serial.print(filter1);  
  Serial.print("\tma2 is: ");
  Serial.println(filter2);  
  delay(100);
  
}

int read_serial() {
  int incoming = 0;        
  if(Serial.available() > 0) {
    incoming = Serial.parseInt();
  }
  return incoming;
}


