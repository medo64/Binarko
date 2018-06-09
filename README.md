### Binarko ###

Binary teaching board.


#### Usage ####

| Button          | Duration   | Description                                      |
|:---------------:|:----------:|--------------------------------------------------|
| <1> to <8>      | Short      | Toggles binary digit.                            |
| <Add>           | Short      | Increases binary number by one.                  |
| <Display>       | Short      | Shows or hides display.                          |
| <Display>       | Long       | Toggles between decimal and hexadecimal display. |
| <Display>       | Extra      | Puts device to sleep.                            |
| <Display>       | Extra + 2s | Full reset.                                      |


#### Diagnostic mode ####

To enter diagnostic mode, keep both Display and Plus buttons pressed during
reset.

| Mode |                                                                          |
|:----:|--------------------------------------------------------------------------|
|    1 | Measures power-supply voltage.                                           |
|    2 | Displays power-supply voltage in percents                                |
|    4 | Test UART receive and timer.                                             |
|    8 | Test UART transmit.                                                      |
|   16 |                                                                          |
|   32 | Shows all segments for third digit.                                      |
|   64 | Shows all segments for second digit.                                     |
|  128 | Shows all segments for first digit.                                      |


#### Design ####

While case has a space for holes, I decided to go without them as screws make it
just too bulky. And anyhow, PCB fit is tight enough to keep board from falling
out.


---

* Josip Medved, [www.medo64.com](https://www.medo64.com/) *
