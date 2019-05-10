# FunOS
This is a Hobby 32-bit Operating System, I basically put this up as a backup of the code, but do with the code as you wish.

## Building
You can't yet use Windows to build this, though only simple modification is required to the makefile to make it work.

You will need to build your own i686 cross-compiler (no, using regular GCC is definitely not recommended), on Linux it's quite simple, don't know about Windows though, the guide is [here](https://wiki.osdev.org/GCC_Cross-Compiler) on OSDev.

Other than that all you need to do is run `make` and you're good to go.  

## Running
To run it using [Qemu](https://www.qemu.org/) just type `make run-qemu`.

## State of the Project
Currently few things are working.  You can boot into it and type in the terminal, get an "Unknown command" message, or type `clear` and clear the screen of all text, but currently, that's it.  

Under the hood there is more than that going on though, and while this is definitely not your run of the mill "Everything uses the BIOS and it's in Real Mode, and is only really a shell" Hobby Operating System made by a beginner, i'm still learning a whole lot about Operating System development, I wouldn't even say I have enough experience in programming to actually make a serious Kernel, this is mostly just for fun and learning purposes.

## Contributing
If you want you can open a PR, i'm always happy to accept positive change, especially if I learn something from it, but this is first and foremost a personal project, so I don't expect this to turn into a contributor-driven project.