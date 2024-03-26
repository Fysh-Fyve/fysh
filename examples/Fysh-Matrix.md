# Fysh Matrix

This is the fysh

```
------....---
.----.----.--
-..-.----.-.-
---.--------.
-..-.------.-
.----.----.--
------....---
```

Looks like if we wanna use any kind of saturation we gotta send the colour value
of the LED serially or something. Not a fan of that. We'll just use full colours
for the RGB unless it's actually pretty easy to change. So rn we have 7 colours
to choose from (2^3 - 1 (black/off)). Now to figure out what the other pins
do...

## Control Pins

| PIN     | Description    | Fysh-Fyve Pin |
| ------- | -------------- | ------------- |
| +5V     | 5V power input | 5V            |
| GND     | Ground         | GND           |
| OE      | Output enable  | gpio[0]       |
| CLK     | Clock input    | gpio[1]       |
| LAT/STB | Latch pin      | gpio[2]       |

## Colour Pins

| PIN | Description       | Fysh-Fyve Pin |
| --- | ----------------- | ------------- |
| R1  | R higher bit data | gpio[3]       |
| R2  | R lower bit data  | gpio[3]       |
| G1  | G higher bit data | gpio[4]       |
| G2  | G lower bit data  | gpio[4]       |
| B1  | B higher bit data | gpio[5]       |
| B2  | B lower bit data  | gpio[5]       |

## Pixel Pins?? Not sure what these do yet

| PIN | Description      | Fysh-Fyve Pin |
| --- | ---------------- | ------------- |
| A   | A line selection | gpio[6]       |
| B   | B line selection | gpio[7]       |
| C   | C line selection | gpio[8]       |
| D   | D line selection | gpio[9]       |
| E   | E line selection | gpio[10]      |
