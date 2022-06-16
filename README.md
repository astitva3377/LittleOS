
# LittleOS
A small hobby OS capable made from scratch complete with a bootloader and kernel.
The OS boots from 16 bit real mode to 64 bit protected mode from a floppy disk.

## Requirements and Installation

The project was created and is for Windows systems though it can be ported Linux with minor changes to the `compile.bat` and `run_bochs.bat` files.

These are packages along with the versions I used. The project should work with up to date packages but it is not tested.

### Compilers
`NASM -> 2.15rc9`

`bochs -> 2.6.11`

### Cross compiler
Execute this in the WSL shell
```bash
sudo apt update
sudo apt-get install build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo
export PREFIX="/usr/local/x86_64elfgcc"
export TARGET=x86_64-elf
export PATH="$PREFIX/bin:$PATH"
mkdir /tmp/src
cd /tmp/src
curl -O http://ftp.gnu.org/gnu/binutils/binutils-2.35.1.tar.gz
tar xf binutils-2.35.1.tar.gz
mkdir binutils && cd binutils
../binutils-2.35.1/configure --target=$TARGET --enable-interwork --enable-multilib --disable-nls --disable-werror --prefix=$PREFIX 2>&1 | tee configlog
sudo make all install 2>&1 | tee makelog
cd /tmp/src
curl -O http://ftp.gnu.org/gnu/gcc/gcc-10.2.0/gcc-10.2.0.tar.gz
tar xf gcc-10.2.0.tar.gz
mkdir gcc && cd gcc
../gcc-10.2.0/configure --target=$TARGET --prefix=$PREFIX --disable-nls --disable-libssp --enable-language=c++ --without-headers
sudo make all-gcc
sudo make all-target-libgcc
sudo make install-gcc
sudo make install-target-libgcc
```

Once this is done, add CGCC variable as `/usr/local/x86_64elfgcc/bin` as a system variable (for Windows) or append `PATH="/usr/local/x86_64elfgcc/bin:$PATH"` to .bashrc (for Linux).


```bash
git clone https://github.com/astitva3377/LittleOS.git
cd LittleOS
compile.bat
run_bochs.bat
```

## Resources
• [OSDev Wiki](https://wiki.osdev.org/Expanded_Main_Page)

• [r/osdev](https://www.reddit.com/r/osdev/)

• [Writing a Simple OS from Scratch by Nick Blundell](https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf)
