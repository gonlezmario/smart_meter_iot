float ADCMeasurements() {
  float voltage_1[100];
  float voltage_2[100];
  float voltage_3[100];
  float current_1[100];
  float current_2[100];
  float current_3[100];
  unsigned int old_time = 0;
  unsigned int new_time = 0;
  
  //voltage_value = (ADC_VALUE * 325.27 ) / (4095) to scale voltages from ADC value to the actual one
  new_time = micros();
  old_time = micros();
  while (new_time - old_time <= 20000) { // Measuring each 1/50 s = 20000 us
    for (int i = 0; i <= 100; i++) {
      voltage_1[i] = (analogRead(4) * 565.69) / 4095; //ADC Read for V1
      voltage_2[i] = (analogRead(5) * 565.69) / 4095; //ADC Read for V2
      voltage_3[i] = (analogRead(6) * 565.69) / 4095; //ADC Read for V3
      //current_value = (ADC_VALUE * 70) / (4095) to scale currents from ADC value to the actual one
      current_1[i] = (analogRead(11) * 70) / 4095; //ADC Read for I1
      current_2[i] = (analogRead(12) * 70) / 4095; //ADC Read for I2
      current_3[i] = (analogRead(13) * 70) / 4095; //ADC Read for I3
      new_time = micros();
    }
    return measurements[6] = {
      voltage_1,
      voltage_2,
      voltage_3,
      current_1,
      current_2,
      current_3,
    }; //Arrays containing all measurements and time
  }
