// which analog pin to connect
#define THERMISTORPIN A5         
// resistance at 25 degrees C
#define THERMISTORNOMINAL 22000      
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25   
// how many samples to take and average, more takes longer
// but is more 'smooth'
#define NUMSAMPLES 5
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 4220
// the value of the 'other' resistor
#define SERIESRESISTOR 10000    
 
int samples[NUMSAMPLES];
 
int tempReader(void) {
  uint8_t i;
  float adc;
 
  // take N samples in a row, with a slight delay
  for (i=0; i< NUMSAMPLES; i++) {
   samples[i] = analogRead(THERMISTORPIN);
  // Serial.print(samples[i]);Serial.println("analog");
   //delay(10);
  }
 
  // average all the samples out
  adc = 0;
  for (i=0; i< NUMSAMPLES; i++) {
     adc += samples[i];
  }
    adc /= NUMSAMPLES;
    //Serial.print("Average analog reading:" ); Serial.println(adc);
   // delay(2000);
 
  // convert the value to resistance
  adc = 1023 / adc - 1;
  //Serial.print("adc b4: "); Serial.println(adc);
  //average = SERIESRESISTOR / average;

  //delay(500);
  float resistor = (SERIESRESISTOR * adc);
  //Serial.print("resistor after: "); Serial.println(resistor);
 
  float steinhart;
  steinhart = resistor / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert to C
  
  int result = (int) truncf(steinhart); 
  //delay(1000);
  Serial.print("resultat:");Serial.println(result);
  return result;
}
