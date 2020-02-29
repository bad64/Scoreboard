[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

 Hotkeyed scoreboard for streamers, with a nice green background for chroma keying in OBS or XSplit.
Windows only, might port it to Linux some other day.

**COMPILING**
You will need to edit the Makefile to set up the path to your SDL libraries. Other than that, just run `make`.

**HOW TO USE**

First, place a font of your choice in the executable folder, and rename it "font.ttf". I use [Big Noodle Titling](https://www.dafont.com/bignoodletitling.font), but it should take any TrueType font.

If launching from the command line, you can put a prefix in quotes (example: scoreboard.exe "Today's scores:").

F1 increases wins, F2 increases losses, F3 increases draws. Holding ALT and pressing a key decreases its corresponding value.
