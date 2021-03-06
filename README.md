caddy
=====

Robot control code for the Cal Poly Robotics Club's 2005 entry into the
Roborodentia competition

Authors
-------

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

Documentation
-------------

* Doxygen-generated documenation ([html][doxygen-html], [pdf][doxygen-pdf])
* Taylor Braun-Jones' [senior project][senior-project] report for B.S. Computer Engineering
* Logan Kinde's [master's thesis][masters-thesis] for M.S. Electrical Engineering

[doxygen-html]:   http://nocnokneo.github.io/caddy/
[doxygen-pdf]:    http://nocnokneo.github.io/caddy/caddy.pdf
[senior-project]: http://digitalcommons.calpoly.edu/cpesp/97/
[masters-thesis]: http://poetry.lib.calpoly.edu/record=b1884407~S0

Software Build Requirements
---------------------------

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
--------------------------------

Documenation in HTML and PDF format is generated using the following packages:

* doxygen (>= 1.7.5 for BibTeX support)
* graphviz
* latex
* convert (ImageMagick CLI)
* perl
* gaf >= 1.9 (from gEDA toolset)

To install version 1.9 of gaf on an Ubuntu system run:

```bash
sudo add-apt-repository ppa:mehanik/geda-unstable
sudo apt-get update
sudo apt-get install geda-gaf
```

Documentation Build Instructions
--------------------------------

The first time you generate documenation in the `doc` directory a second clone
of the caddy git repository will be created from the main GitHub-hosted
one. Pushing updates to the special `gh-pages` remote branch publishes them
to: http://nocnokneo.github.com/caddy/

The documentation build, commit, and publish workflow looks like this:

```bash
# Starting from the project base directory
make doc
cd doc/html
git add .
git commit -m "Update doxygen-generated documentation"
git push origin gh-pages
```

LICENSE
-------

Caddy is released under GPLv3 license (see `COPYING`). This is by requirement
because Caddy uses the GPL-licensed AVRlib library.
