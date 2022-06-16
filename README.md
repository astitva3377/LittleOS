
# LittleOS
A small hobby OS capable made from scratch complete with a bootloader and kernel.
The OS boots from 16 bit real mode to 64 bit protected mode.

## Requirements
These are packages along with the versions I used. The project should work with up to date packages but it is not tested.

`NASM -> 2.15rc9`

`bochs -> 2.6.11`

## Installation
This assumes you have a WSL system set up with cross compiler as in OSDev wiki.
```cmd
git clone https://github.com/astitva3377/LittleOS.git
cd LittleOS
compile.bat
run_bochs.bat
```
