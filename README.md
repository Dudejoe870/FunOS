# FunOS
This is a Hobby 32-bit Operating System, I basically put this up as a backup of the code, but do with the code as you wish.
# Building
You can't yet use Windows to build this, though only simple modification is required to the makefile to make it work.
You will need to build your own i686 cross-compiler (no, using regular GCC is definitely not recommended), on Linux it's quite simple, don't know about Windows though, the guide is [here](https://wiki.osdev.org/GCC_Cross-Compiler) on OSDev.
Other than that all you need to do is run `make` and you're good to go.  To run it use os_image.bin in the build folder as a floppy image in Qemu or similar.  Have fun doing extremely boring things like clearing the screen with the `clear` command!  Yeah, if you can't tell this is in the very early stages (might always be), but really I just wanted to back up the code in the case of an emergency since I did work fairly hard on it.
