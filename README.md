# CrimsonNDS

C++ lib for coding on the nintendo ds system

## Dependency

You need to install devkitpro first.

## The project so far

CrimsonNDS are not a independent lib (TODO list).

So actualy the main.cpp contain a "Jetpack joyride" like game.
All other file (except ressource fille like pal.c ect ...) is the lib source.

The lib can manage right now only 16*16 sprite and tiled sheet (TODO list).

## Json

The creatMap.sh script can transforme .json file create by [Tiled](https://www.mapeditor.org/)
to .c and .h

## sharedPal

the sharedPal program transform all image to .c .h for the nds.
A extra pal.c and pal.h will be create for the pallete color

