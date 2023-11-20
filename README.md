# minesweeper for arch

The classic minesweeper game made for Arch Linux using the SFML library.
I'm planning on making this a repo similar to the repos in the AUR, with a PKGBUILD and all that.

### build

It has been only tested to work on Arch Linux so far.

It's built using the **make** utility and made using **cpp** and **SFML**, so before anything you need the `make`, `sfml`, and `gcc` packages. 

Then clone the repo, `cd` into the **sources** folder and build it using `make` and run it using `make run` (or just `cd` into the newly created **bin** folder at the root of the project and run the executable directly).

### how to play

`left mouse click`: reveal field

`right mouse click`: place / remove flag

### todo

- [ ] clean up code
- [ ] make Linux distro agnostic build
- [ ] make Windows build