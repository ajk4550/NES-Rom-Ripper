/*******************************************************************************
 * Name:                NES Rom Ripper
 * 
 * Author:              Aaron Kaye
 * 
 * Date:                2/8/18
 * 
 * Version:             0.1
 * 
 * Description:         This program will read the contents of a masked ROM (EEPROM) of an
 *                      NES game. I used it for reading both the PGM and CHR contents. You
 *                      Will still need to manually combine them with the NES header if you
 *                      plan on using this in an emulator.
 *                      
 * Usage:               This was installed on an Arduino Nano in my case but should work on any
 * 
 * Disclaimer:          Each NES Rom is a little different so this isn't a one-size-fits-all
 *                      program. Some things that can possible differ are the pinouts, the
 *                      number of pins used (mine was 28 pins), the size of the rom files,
 *                      etc. Hopefully this will be a starting point for someone who is trying
 *                      to do the same.
 *                      
 * Copywrite Disclaimer: I am in no way trying to steal games or break any copywrites.
 *                       This was all done out of interest and for education. I was trying
 *                       to combine my interest for video games, electric circuits, and 
 *                       computer science. I take no responsibility for how this software
 *                       is used.
 * 
 *******************************************************************************/
#define SHIFT_DATA 2
#define SHIFT_CLK 3
#define SHIFT_LATCH 4
#define EEPROM_D0 5
#define EEPROM_D7 12

// Helper function that Sets the address on the EEPROM that you are trying to 
// get data from the EEPROM
// Params
// int address in decimal form i.e 8192
// bool outputEnable - Not used in my version but might be needed for writing
// In my version pin 13 isn't even wired in
void setAddress(int address, bool outputEnable) {
  if(outputEnable) {
    digitalWrite(13, HIGH);    
  } else {
    digitalWrite(13, LOW);
  }

  // Outputting the address to the two shift registers
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (address >> 8));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, address);
  digitalWrite(SHIFT_LATCH, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
}

// Function for reading the EEPROM data at a given address
// int address - the address you are trying to read from in decimal form
byte readEEPROM(int address) {
  // Setting the address pins on the EEPROM and waiting
  setAddress(address, true);
  delay(50);
  // Building a byte of data based on the 8 data pins from the EEPROM
  byte data = 0;
  for (int pin = EEPROM_D7; pin >= EEPROM_D0; pin -= 1) {
    data = (data << 1) + digitalRead(pin);
  }
  return data;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  pinMode(SHIFT_DATA, OUTPUT);
  pinMode(SHIFT_CLK, OUTPUT);
  pinMode(SHIFT_LATCH, OUTPUT);
  pinMode(13, OUTPUT);

  for (int pin = EEPROM_D7; pin >= EEPROM_D0; pin -= 1) {
    pinMode(pin, INPUT);
    digitalWrite(pin, HIGH);
  }

  // Looping through the data on the EEPROM. 8192 is the end of your data and will likely 
  // change 8192 was used when I was reading the 8 KB CHR rom on an NES game. If you aren't 
  // reading enough data increase that number. Loop increments by 16
  for (int base = 0; base <= 8192; base += 16) {
    byte data[16];
    for (int offset = 0; offset <= 15; offset += 1) {
      data[offset] = readEEPROM(base + offset);
    }

    char buf[80];
    // Build a formatted HEX string
    sprintf(buf, "%02x%02x %02x%02x %02x%02x %02x%02x %02x%02x %02x%02x %02x%02x %02x%02x",
                data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7],
                data[8], data[9], data[10], data[11], data[12], data[13], data[14], data[15]);
    // Logging the results
    Serial.println(buf);
  }
}

void loop() {
//  // put your main code here, to run repeatedly:
//    This is code that I used for debugging. I was comparing to a NES Rom I already had so 
//    I knew what the expected address was. This repeatedly gets the data at a given address
//    which is defined by the variable start. It will log the output to the Serial monitor.
//    char buf[80];
//    int start = 8192;
//    sprintf(buf, "%02x%02x %02x%02x %02x%02x %02x%02x", readEEPROM(start), readEEPROM(start+1), readEEPROM(start+2), readEEPROM(start+3), readEEPROM(start+4), readEEPROM(start+5), readEEPROM(start+6), readEEPROM(start+7));
//    //sprintf(buf, "%02x", readEEPROM(start));
//    Serial.println(buf);
//    delay(1000);

}
