# STM32 Bare-Metal — Self-Learning Project

Bare-metal (register-level, no HAL) firmware for the **STM32F411RE** Cortex-M4
microcontroller, written while teaching myself ARM embedded development from the
official STMicroelectronics reference manual and datasheet.

The goal here is to understand what HAL libraries abstract away: clock gating,
GPIO configuration, and the memory-mapped peripheral registers — by reading the
reference manual and writing directly to the registers.

## Learning approach

I'm deliberately doing this the old way — no AI assistants writing or explaining
the firmware. The whole point is to actually understand what's going on under
the hood: I work from the STMicroelectronics reference manual and datasheet,
look up the registers and bit fields myself, and write the code by hand.

The only thing I used AI for is the setup of this repository (gitignore,
README, license, and pushing it to GitHub). The firmware itself is mine.

## Hardware

- **MCU:** STM32F411RET6 (ARM Cortex-M4F, 100 MHz)
- **Board:** ST Nucleo-64 (NUCLEO-F411RE)
- **On-board LED:** LD2 on port **PA5**

## What it does

`0_test` — bare-metal LED blink. No HAL, no CubeMX-generated peripheral code.
The program:

1. Enables the GPIOA clock via `RCC->AHB1ENR` (clock gating on the AHB1 bus).
2. Configures PA5 as a push-pull output via `GPIOA->MODER`.
3. Toggles the LED by XOR-ing `GPIOA->ODR` in the main loop.

This exercises the core concepts of memory-mapped I/O: looking up register
addresses and bit fields in the reference manual and manipulating them with
bitwise operations.

## Repository layout

```
0_test/
  Src/main.c          # bare-metal application (RCC + GPIO register access)
  Src/syscalls.c      # newlib syscall stubs
  Src/sysmem.c        # _sbrk heap implementation
  Startup/            # Cortex-M4 startup assembly (vector table, reset handler)
  STM32F411RETX_*.ld  # linker scripts (FLASH / RAM)
  .project .cproject  # STM32CubeIDE project files
chip_headers/CMSIS/   # ARM CMSIS + ST device headers (third-party, see Licensing)
```

## Toolchain

- STM32CubeIDE (GNU Arm Embedded `arm-none-eabi-gcc`)
- CMSIS device headers for register definitions
- ST-LINK for flashing/debugging over the Nucleo's on-board programmer

### Build

Open the `0_test` folder as a project in STM32CubeIDE and build, or build from
the generated makefiles:

```sh
cd 0_test/Debug
make
```

## Reference documentation

These STMicroelectronics documents are not redistributed in this repo
(copyright ST). Originals:

- [RM0383 — STM32F411xC/E reference manual](https://www.st.com/resource/en/reference_manual/rm0383-stm32f411xce-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
- [STM32F411xC/E datasheet](https://www.st.com/en/microcontrollers-microprocessors/stm32f411ce.html)
- [UM1724 — STM32 Nucleo-64 boards user manual](https://www.st.com/resource/en/user_manual/um1724-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf)

## Licensing

My own source code in this repository is released under the [MIT License](LICENSE).

The files under `chip_headers/CMSIS/` are third-party headers from ARM (CMSIS,
Apache-2.0) and STMicroelectronics (device headers), each retaining its original
license and copyright as stated in the file headers.
