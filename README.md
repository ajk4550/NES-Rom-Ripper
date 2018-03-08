# NES-Rom-Ripper
Arduino Project for ripping NES masked roms. This project was for a very specific project I was working on and now that I've completed it I will likely not be updating this code base. Feel free to use it though!

## Installation

I ran this project on an Arduino Nano but I am sure you could get it to work on any arduino. The target masked rom was the CHR rom and the PRG Rom from the NES game ExciteBike.

## Usage

To use, upload this software to your arduino and follow the wiring guide I've provided. Please note: NES Masked Roms have a lot of variance to them. Please do not this to be a "working ready" solution. Hopefully this will get you started. Some areas that may differ include the rom pinouts, the amount of data you need to receive, whether the chip is 28 pins or 32 pins, etc.

## Circuit Wiring
This project used an Arduino Nano and 2 74HC595 Shift Registers. My target masked roms were 2 28-pin EEPROM chips, 16KB and 8KB. The two chips can be swapped out, I first dumped the PGM and then the CHR chip.
![alt text](https://raw.githubusercontent.com/ajk4550/NES-Rom-Ripper/master/REF-Circuit.png)
![alt text](https://raw.githubusercontent.com/ajk4550/NES-Rom-Ripper/master/REF-FRITZING.png)

## Pinout
I had the hardest time finding a pinout for the NES EEPROM that I felt 100% confident with. I used the following and made some tweaks

![alt text](https://raw.githubusercontent.com/ajk4550/NES-Rom-Ripper/master/REF-Pinout.png)

Image Credit: https://wiki.nesdev.com/w/index.php/Mask_ROM_pinout

On my EEPROM:

Pin 1: Address 15 -> VCC (+5V)

Pin 2:  A12 -> Shift Register 2

Pin 3:  A7 -> Shift Register 1

Pin 4:  A6 -> Shift Register 1

Pin 5:  A5 -> Shift Register 1

Pin 6:  A4 -> Shift Register 1

Pin 7:  A3 -> Shift Register 1

Pin 8:  A2 -> Shift Register 1

Pin 9:  A1 -> Shift Register 1

Pin 10: A0 -> Shift Register 1

Pin 11: D0 (First data line) -> Arduino Pin D5

Pin 12: D1 (Second data line) -> Arduino Pin D6

Pin 13: D2 (Third data line) -> Arduino Pin D7

Pin 14: GND

Pin 15: D3 (Fourth data line) -> Arduino Pin D8

Pin 16: D4 (Fifth data line) -> Arduino Pin D9

Pin 17: D5 (Sixth data line) -> Arduino Pin D10

Pin 18: D6 (Seveth data line) -> Arduino Pin D11

Pin 19: D7 (Eigth data line) -> Arduino Pin D12

Pin 20: Chip Enable -> GND

Pin 21: A10 -> Shift Register 2

Pin 22: Output Enable -> GND

Pins 23: A11 -> Shift Register 2

Pin 24: A9 -> Shift Register 2

Pin 25: A8 -> Shift Register 2

Pin 26: A13 -> Shift Register 2 (Even though the pinout above says NC)

Pin 27: A14 -> GND

Pin 28: VCC (+5V)

## Combining the two chips into a ROM file

If you use this method, you will end up with a PGM ROM and a CHR ROM. Just copy the arduino serial output into a file for both chips. You will also need a header file. If you have a know working rom from the internet this is the first 16 Bytes or you should be able to research how to get it. Header is only needed for use in emulators.


```bash
$ ls
eb-chr		eb-header	eb-pgm		head_bin	head_dump
$ cat eb-pgm > pgm_dump
$ xxd -p -r pgm_dump > pgm_bin
$ cat eb-chr > chr_dump
$ xxd -p -r chr_dump > chr_bin
$ 
$ ls
chr_bin		eb-chr		eb-pgm		head_dump	pgm_dump
chr_dump	eb-header	head_bin	pgm_bin
$ cat head_bin pgm_bin chr_bin > ExciteBike.nes
```


In this case, ExciteBike.nes is the working ROM file!


## Credits

Aaron Kaye: Owner of this project

I would also like to thank:

Ben Eater - Ben's video on arduino EEPROM was the driving force behind this project. It would have been very difficult without that resource:
https://www.youtube.com/watch?v=K88pgWhEb1M

NES Cart DB - This helped me gather more information about the NES rom I was working with. 
http://bootgod.dyndns.org:7777/profile.php?id=18
