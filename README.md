# STM32Lvideo

PAL video signal generation with a STM32 using the builtin peripherals

This demonstration project was created for the MB1108 Discovery board from ST Microelectronics. The purpose of the project is to show the use of the builtin peripherals and DMA controller to generate a PAL composite video signal in such a way that timing of the video signal does not need any interrupt processing. After the peripherals have been initialised, the CPU only needs to fill the frame buffer (size 320 * 240 pixels) as desired. The program also requires a standard peripheral library from STM, and a toolchain. ( the non-licensed Atollic TRUE Studio works fine ).

technical design considerations are described on the Wiki page.

This program is a modified version of the program shown in my Youtube video at:
       https://youtu.be/Bg80o8ynzMY (https://youtu.be/Bg80o8ynzMY)

Enhancements:
video in this version is black on white, where the original is white on black
A bigger font was used to improve the readability.
