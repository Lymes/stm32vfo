# A VFO based on STM32 MCU 

This project is based on stm32f103c8t6 Blue Pill board, st7735 160x128 1.8" TFT display and si5351a.
It was generated by STM32CubeMX for SystemWorkbench (SW4STM32) using HAL drivers, excepting those for SPI.

* st7735 is connected via SPI, LL driver was chosen in order to achieve a full speed at 18MHz SPI bus. No DMA channels were used.
* si5351a is connected via I2C HAL driver with a bugfix from Errata sheet (section 2.14.7).
* st7735 driver has been highly optimised and some C++ GUI classes were written upon it. The GUI supports transparent fonts and gradients as well.  

<img src="/screenshots/screenshot1.JPG" width="300">
<img src="/screenshots/screenshot2.JPG" width="300">
<img src="/screenshots/screenshot3.JPG" width="300">

## WORK IN PROGRESS


## Authors

* **L.Y.Mesentsev** - *Initial work* - [Lymes](https://github.com/Lymes)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.
 