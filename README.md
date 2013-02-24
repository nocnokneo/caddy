caddy
=====

Robot control code for the Cal Poly Robotics Club's 2005 entry into the
Roborodentia competition

Authors
=======

* Taylor Braun-Jones
* Logan Kinde
* Patrick McCarty
* Michael Shelley
* Scott Barlow

This software is written for the Atmel Atmega32 processor using the free
gcc-avr C compiler. It has been tested on the ERE EMBMega32 developement board
from ERE (http://ere.co.th) but should run on any Atmega32 processor, although
it will be useless without the right peripherals connected to the proper pins
on the Atmega chip.

TODO: Some high-level information about what our program does and how
to configure, compile, load, and run on the chip.

Software Build Requirements
===========================

* make (only tested with GNU make)
* avr-gcc
* avr-binutils
* avr-libc
* AVRlib (bundled in `thirdparty/` directory)

To program the ATmega32 chip, you will need a ISP programming cable and
programming software such as avrdude or MEGA32ISP. We used MEGA32ISP and the
following fuse bit configuration:

    BOOTRST = Address $0000
    BOOTSZ(1...0) Select Boot Size = 256      Words (11)   [3F00H - 3FFFH]
    EESAVE = checked
    CKOPT = checked
    SPIEN = checked, but greyed out
    JTAGEN = unchecked
    OCDEN = unchecked
    CKSEL(0...3) Select Clock = External Crystal/Ceramic Resonator (1111)
    SUT(5...4) Select start-up time = Reserved (11)
    BODEN Brown-out Detector enable = unchecked
    BODLEVEL Brown-out level = 4.0 V

Documentation Build Requirements
================================

Documenation in HTML and PDF format is generated using the following packages:

* doxygen (>= 1.7.5 for BibTeX support)
* graphviz
* latex
* ImageMagick (`convert` command)
* perl

Documentation Build Instructions
================================

In your local caddy git repository, create a second clone of the caddy git
repository from the main GitHub-hosted one and switch to the special
`gh-pages` "orphan" branch:

```bash
cd <YOUR_CADDY_CHECKOUT>/doc
rm -rf html
git clone git@github.com:nocnokneo/caddy.git html
cd html
git checkout gh-pages
git config http.postBuffer 100000000   # required when pushing to http:// URL
```

Build, commit, and publish (push to origin/gh-pages) the documenation

```bash
make -C ..
git add .
git commit -m "Update doxygen-generted documenation"
git push origin gh-pages
```

LICENSE
=======

Caddy is released under GPLv3 license (see `COPYING`). This is by requirement
because Caddy uses the GPL-licensed AVRlib library.
