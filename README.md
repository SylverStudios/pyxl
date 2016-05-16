# LogoAnimation
Let's make the logo animate in the terminal

## Setup
To build the project, you need ncurses available on your machine.  I think you might be able to
brew install it, but not positive, forgot how I did it.

## How to build
to create the build artifacts (compiled objects and binary executable): `make`
after making, there should be `obj/` and `bin/` directories.
`obj/` contains compiled `.o` files.
`bin/` contains the binary executable.

## How to run
after building: `bin/sylver path/to/text/file`
