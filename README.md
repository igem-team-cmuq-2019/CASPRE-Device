# For more detail please visit [the official iGEM-CMUQ 2019 Hardware Page](https://2019.igem.org/Team:CMUQ/Hardware)


_Introduction_

With the recent developments of the Cas12a enzyme, our biology team was able to use its matching and breaking abilities to snap matching gene sequences to that of a specific genetic disease, such as: sickle cell anemia, cystic fibrosis, etc. With the aid of an identifier molecule that has a fluorescent tag, we can map these identifiers throughout the genetic sequence, such that when the Cas12a enzyme snaps on matching gene sequences, the identifier&#39;s fluorescent tag gets released. To be able to detect the level of fluorescent tags released, we have to excite the tags with 535 nm of light, and at full emission should emit back at 555 nm.

Keeping the quantities of identifiers controlled, we can analyze multiple test trials to probabilistically plot a threshold value for which we can deterministically say whether a patient&#39;s genes carry a certain genetic disease.

The interface works as such:

- --A specifically shaped slot is made for the microtube - with patient DNA sequence, target DNA sequence, and Cas12a enzyme - to fit in.
- --The slot is fitted with a custom light detection sensor, and an LED that emits light at 530nm.
- --The device is operated by an Arduino based PCB, equipped with a Bluetooth module, LCD screen, and a Lithium Polymer battery for portability.
- --The motherboard controls the entire program sequence and follows this control flow:

Individual Parts:

TSL252: This is a specific ambient light sensor that responds to light by changes of output voltage. With a supply of 5V (VCC), the fluorescence of the micro tube creates a range of output voltage from the sensor of 2.2V to 2.8V. This is read via an Analog pin on the Arduino board and mapped to a PWM value.

HC-05: This is a fairly popular Bluetooth module that allows serial communication through RX and TX terminals. This is connected to the Arduino for live relay of fluorescence data to a computer for analysts to compile with other data per analysis. The HC-05 was programmed with AT commands into &#39;Slave&#39; mode to automatically connect to anything that connects to it, and takes in specifically encrypted commands so as to protect the device from ill-intentioned attackers.

Arduino Pro Mini: The specific model we chose is a 5V @ 16MHz, for direct communication with the amplified LiPo charger that outputs at 5V exactly. Although the HC-05 communicates at 3.3V, we had to integrate a voltage divider to protect the HC05 from surges and ensure a stable line of communication. Otherwise the Pro Mini provides a great low profile and a variety of analog and digital pins, with I2C and Serial communication for our LCD and Bluetooth modules.

128x32 OLED LCD: A low profile display for live measurements and instructions of the device, regardless of the Bluetooth connection. It was great for our project, because it communicates with an I2C interface and has supply voltage options for 3.3 and 5V.

Micro Tube: A micro test tube provided better results than a cuvette given its smaller form factor. With the cuvette, we had to dilute the solution to actually fill the cuvette enough for the sensor and LED. A micro tube allows the same material with little to none fluorescence resistance and no dilution of the substance.

535nm LED: On the color spectrum, 535nm of light is about a light green color and is exactly what we need to excite the fluorescent tags that have been broken off by the Cas12a to determine how much of the target gene was matched to the disease.

Testing:

        With the samples prepared by the biology lab team, we tested the fluorescence values the device received on different types of samples, which had been tested with a lab fluorimeter to for expected results for each sample. The team operated in a dark room for no outside exposure to light to disturb the TSL252 and light sensitive solutions.

_Data Collection_

| **Solution (IV)** | **Concentration Volume (CV)** | **Trial 1 (ru)** | **Trial 2 (ru)** | **Trial 3 (ru)** | **Trial 4 (ru)** | **Average (ru)** |
| --- | --- | --- | --- | --- | --- | --- |
| DNase Alert | 50μL + 1mL | 248.67 | 248.00 | 247.00 | 247.33 | 247.75 |
| Mix | 32μL + 1mL | 320.33 | 321.00 | 322.00 | 321.67 | 321.25 |
| Nuclease Free Water | 1mL | 398.67 | 394.67 | 401.67 | 400.67 | 398.92 |
| Control G | 82μL + 1mL | 442.00 | 443.33 | 445.67 | 442.67 | 443.42 |
| G | 82μL + 1mL | 286.67 | 288.00 | 280.00 | 280.67 | 283.84 |
| Control WIldtype | 82μL + 1mL | 359.00 | 361.00 | 360.67 | 361.67 | 360.59 |
| Wildtype | 82μL + 1mL | 259.33 | 289.00 | 289.33 | 289.00 | 281.67 |

Seven different samples were tested with the device. All expected fluorescence levels were based off of lab fluorimeter machine.

- --Wildtype and G were expected to fluoresce past a threshold because they were designed to bind to the target DNA sequence.
- --DNase Alert was a tester sample to relate values from the fluorimeter and CASPRE device. It was expected to produce the greatest fluorescence.
- --Mix was a sample designed as a biological test to see if the Cas12a enzyme was snapping off incorrectly matched sequences, thus expecting unexpectedly higher fluorescence levels if failed.
- --Nuclease Free Water, Control G, and Control Wildtype were three samples that were designed for no DNA matching, so the Cas12a shouldn&#39;t have snapped as much and thus should have lower fluorescence levels.

_Data Analysis_

Quite successfully, the device&#39;s light-to-voltage sensor (TSL252) revealed data trends in its values that matched our expectations. The sensor returned extremely large inverted values that ranged from 247 to 446. The fluorimeter returns values in RFU (Relative Fluorescence Unit) which is on a 0 – 5 scale, as it&#39;s analogous to the its sensors voltage levels. Since we&#39;re making use of the PWM pins on the Arduino that operates in 10 bits, our sensor was relaying values on an unsigned range of 0 – (210 – 1), which is 0 – 1023. Since the sensor already operates on a 5V logic level, we just had to normalize the values to an inverted range, done as so:

RFU = 1024/raw

This trend was confirmed with control tests of Nuclease Free Water, and DNase Alert.

So, the device yielded these values in RFU for our tested samples, allowing us to determine a relative threshold value that the fluorescence levels must break to assert a positive test result.

| **Solution (IV)** | **Average (ru)** | **Fluorescence (RFU)** |
| --- | --- | --- |
| DNase Alert | 247.75 | 4.133198789 |
| Mix | 321.25 | 3.187548638 |
| Nuclease Free Water | 398.92 | 2.566930713 |
| Control G | 443.42 | 2.30933601 |
| G | 283.84 | 3.607729843 |
| Control WIldtype | 360.59 | 2.839829721 |
| Wildtype | 281.67 | 3.635524471 |

 
The results now similarly match with the values obtained from the fluorimeter, and confirm our expectations. For now it seems that a tentative threshold value can be placed at 3.45 RFU, but more tests are needed to confirm that trend and the reliability of the DNA modelling.

After reprogramming the device with a calibration procedure to floor a baseline fluorescence value, and a malleable threshold value (changeable by Bluetooth PC program which receives more real time RFU data for compilation) the device is ready!
