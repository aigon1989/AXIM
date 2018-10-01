
Debian
====================
This directory contains files used to package staterad/statera-qt
for Debian-based Linux systems. If you compile staterad/statera-qt yourself, there are some useful files here.

## statera: URI support ##


statera-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install statera-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your stateraqt binary to `/usr/bin`
and the `../../share/pixmaps/statera128.png` to `/usr/share/pixmaps`

statera-qt.protocol (KDE)

