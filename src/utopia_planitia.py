#!/usr/bin/env python

import pygtk
pygtk.require('2.0')

import os.path
import gtk

from gwp.models import Game
from plugins.utopia_planitia.ui import UP

game = Game(os.path.expanduser('~/VP/ARGF4/'), 7)

up = UP()
up.show_all()

#shell = Shell()
#shell.show_all()
gtk.main()
