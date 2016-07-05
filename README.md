# pyxl
Interactive animation engine for changing appearance of text files.

## Setup
To build the project, you need ncurses available on your machine.  I think you might be able to
brew install it, but not positive, forgot how I did it.

## How to build
to create the build artifacts (compiled objects and binary executable): `make`
after making, there should be `obj/` and `bin/` directories.
`obj/` contains compiled `.o` files.
`bin/` contains the binary executable.

## How to run
after building: `bin/pyxl path/to/text/file`
