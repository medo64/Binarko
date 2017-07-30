### Binarko ###

* Size: 107.8 x 57.8 mm
* Area: 9.7 sqin


#### Parts ####

|  # | Part name                        | RefDes  | DigiKey                    |
|---:|----------------------------------|---------|----------------------------|
|  4 | C 100nF /16V X7R (0603)          | C1-c4   | 311-1088-1-ND              |
|  2 | C 10uF /16V X5R (0805)           | C5 C6   | 1276-6455-1-ND             |
|  8 | DS LED (5mm)                     | DS1-DS8 | 160-1853-ND                |
|  1 | DS 3d 7-seg CC 14.2mm (DIP-28)   | DS9     | 754-1658-5-ND              |
|  2 | J JST S3B-XH-A (3w)              | J1-J2   | 455-2250-ND                |
| 22 | R 300R 0.1W (0603)               | R1-R22  | 311-300HRCT-ND             |
| 10 | R 1K 0.1W (0603)                 | R23 R32 | 311-1.00KHRCT-ND           |
|  3 | R 1K5 0.1W (0603)                | R33-R35 | 311-1.50KHRCT-ND           |
| 10 | S Tactile SPST-NO (6x6mm)        | S1-S10  | 450-1647-ND                |
|  1 | U PIC16F15386-I/PT (TQFP-48)     | U1      | PIC16F15386-I/PT-ND        |
|  1 | U TPS2115A (TSSOP-8)             | U2      | 296-16940-1-ND             |
|  1 | H Enclosure Hammond 1591BBK      |         | HM115-ND                   |
|  1 | BT 3xAA                          |         | BC3AAW-ND                  |
|  2 | P MC 1,5/ 4-ST-3,81              |         | ED2876-ND                  |



#### Jumpers ####

Jumpers on this board are of SMD variety. To connect them, simply solder between
the pads.


##### F-BAT #####

When this jumper is connected battery will power the device directly without
going through TPS2115A power switcher. This is to be used only if power switcher
is not mounted. DO NOT connect this jumper if external power is present. DO NOT
connect this jumper is F-EXT is connected.


##### F-EXT #####

When this jumper is connected the device will use external power without going
through TPS2115A power switcher. This is to be used only if power switcher is
not mounted. DO NOT connect this jumper if battery power is present. DO NOT
connect this jumper is F-BAT is connected.


##### UNFUSED #####

When this jumper is connected, power switcher will not limit output current.
This is useful if more devices have to be daisy chained and their combined
consumption would go over 500 mA. Not recommended for AA batteries as it will
drain them really quickly.
