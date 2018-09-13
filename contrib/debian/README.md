
Debian
====================
This directory contains files used to package aximd/axim-qt
for Debian-based Linux systems. If you compile aximd/axim-qt yourself, there are some useful files here.

## axim: URI support ##


axim-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install axim-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your aximqt binary to `/usr/bin`
and the `../../share/pixmaps/axim128.png` to `/usr/share/pixmaps`

axim-qt.protocol (KDE)

