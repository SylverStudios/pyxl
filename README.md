# pyxl
A simple project that animates the visibility of characters in a given text file.

## What is it
Point the `pyxl` binary at any text file to view it using the animation engine. Here we've loaded up `text/logo.txt`:

![Screenshot](https://i.imgur.com/CMArJ5M.png)

Then use the animation commands to animate visibility changes over the text file. This is a screenshot taken halfway through the "wave" command:

![Screenshot](https://i.imgur.com/RPjLQQM.png)

You can perform multiple animations simultaneously which will interact with each other in various ways.

### Commands

Press the highlighted key to initiate the animation.

- [r]ipple
- fade [o]ut
- fade [i]n
- [w]ave
- wave, stay [u]p

Press q to [q]uit.

## Setup

### Install ncurses
The `ncurses` headers must be available to build this project.
On Ubuntu, this can be installed with the `libncurses5-dev` package. (`sudo apt install libncurses5-dev`)

### `make`
Run `make` in the top-level directory. This produces compiled `.o` files in `obj/`, as well as the binary executable in `bin/`.

## Run `bin/pyxl`
Run `bin/pyxl path/to/text/file` to load up the given text file in the animation engine.
