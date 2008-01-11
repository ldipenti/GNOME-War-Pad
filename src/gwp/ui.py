# UI components

import pygtk
pygtk.require('2.0')

import gtk, math, os, ConfigParser

from kiwi.ui.delegates import GladeDelegate, SlaveDelegate, GladeSlaveDelegate
from kiwi.ui.gadgets import quit_if_last

import gwp
from gwp.models import Game, GameConfig
from gwp.widgets import Starchart, PlanetDrawable, ShipDrawable, Line, Rectangle
from gwp.collections import PlanetCollection, ShipCollection, RaceList
from gwp.filereaders import GenFile
from gwp.widgets import pycons
from gwp.utils import PluginManager

class Shell(GladeDelegate):
    def __init__(self):
        super(Shell, self).__init__(gladefile="shell",
                                    delete_handler=self.do_quit)
        self.console = None
        self.starchart = None
        self.pm = PluginManager()
        
        self.__init_starchart()
        self.__init_menu()

        # Planet data UI component
        self.planet_slave = PlanetData()
        self.attach_slave("eventbox_slot_right", self.planet_slave)

    def __init_menu(self):
        m = gtk.Menu()
        layers_menu = gtk.MenuItem('_Layers', True)
        layers_menu.set_submenu(m)

        for l in self.starchart.get_layer_list('shell'):
            item = gtk.CheckMenuItem(l['description'])
            item.set_active(l['enabled'])
            item.connect('toggled', self.__do_toggle_layer, l['name'])
            m.add(item)
        
        self.menubar.append(layers_menu)

        m = gtk.Menu()
        plugin_menu = gtk.MenuItem('_Plugins', True)
        plugin_menu.set_submenu(m)

        for (status, name, plugin) in self.pm.available_plugins():
            item = gtk.CheckMenuItem(name, status)
            # Store the plugin class reference
            #item.set_data('plugin', plugin)
            item.connect('toggled', self.__do_toggle_plugin, plugin)
            m.add(item)

        self.menubar.append(plugin_menu)

    def do_quit(self, *args):
        '''
        Quits GWP
        '''
        print "Bye bye!"
        gtk.main_quit()
        
    def do_show_console(self, action):
        '''
        Sets up a python console with useful live objects within its scope
        to do debugging.
        '''
        if self.console == None:
            self.console = pycons.ConsoleWindow({'__builtins__': __builtins__,
                                                 'starchart': self.starchart,
                                                 'game': Game(),
                                                 'gwp': gwp,
                                                 '__doc__': None},
                                                title = 'GWP Debugging Console')
            self.console.win.connect('delete-event', self.__do_remove_console)
        
    def __do_remove_console(self, w, data):
        self.console = None
        
    def __do_toggle_layer(self, checkmenuitem, layer):
        '''
        Callback to update layer status
        '''
        self.starchart.enable_layer(layer, 'shell', checkmenuitem.active)

    def __do_toggle_plugin(self, checkmenuitem, plugin):
        '''
        Callback to activate/deactivate plugins
        '''
        if checkmenuitem.active:
            self.pm.register(plugin)
        else:
            self.pm.unregister(plugin)

    def __init_starchart(self):
        game = Game()

        # Init starchart
        self.starchart = Starchart()
        self.starchart.add_layer('planets', group='shell',
                                 description='The planets')
        self.starchart.add_layer('ships', group='shell',
                                 description='The ships')
        self.starchart.add_layer('constellations', group='shell',
                                 description='Planet constellations')
        self.starchart.add_layer('selection', group='system',
                                 description='Selection area')

        # Signals
        self.starchart.connect('selected', self._do_starchart_selected)
        self.starchart.connect('selected-area', self._do_starchart_selected_area)
        self.starchart.connect('selecting-area', self._do_starchart_selecting_area)
        
        # Object addition
        self.starchart.add_drawables(game.planets, PlanetDrawable,
                                     layer='planets', group='shell')
        self.starchart.add_drawables(game.ships, ShipDrawable,
                                     layer='ships', group='shell')
        self.starchart.show()

        # Locate starchart in UI
        slave = SlaveDelegate(toplevel=self.starchart)
        self.attach_slave("eventbox_starchart", slave)
        slave.focus_toplevel()

        # Init constellations
        p = game.planets.values()
        while len(p) > 1:
            planet_a = p.pop()
            for planet_b in p:
                distance =  abs(math.hypot(planet_b.x - planet_a.x,
                                           planet_b.y - planet_a.y))
                if distance <= 84:
                    self.starchart.add(Line(planet_a.x, planet_a.y, planet_b.x, planet_b.y,
                                            (0.4, 0.4, 0.4)), layer='constellations', group='shell')

        # Selection area
        self.selection = Rectangle(0, 0, 0, 0,
                                   rgba=(0.1, 0.1, 1, 0.3),
                                   filled=True)
        self.starchart.add(self.selection, layer='selection', group='system')
        return

    def _do_starchart_selected(self, w, x, y):
        print "Selected Point: (%d, %d)" % (x, y)
        # Find the nearest object
        g = Game()
        min_dist = 99999
        ret = None
        objects = g.planets.values()
        for obj in objects:
            distance = abs(math.hypot(obj.x - x, obj.y - y))
            if distance < min_dist:
                min_dist = distance
                ret = obj
        self.starchart.move(ret.x - x, ret.y - y)
        self.planet_slave.proxy.set_model(ret)

    def _do_starchart_selecting_area(self, w, x1, y1, x2, y2):
        print "Selecting Area: (%d, %d) - (%d, %d)" % (x1, y1, x2, y2)
        self.selection.x1 = x1
        self.selection.y1 = y1
        self.selection.x2 = x2
        self.selection.y2 = y2

    def _do_starchart_selected_area(self, w, x1, y1, x2, y2):
        print "Selected Area: (%d, %d) - (%d, %d)" % (x1, y1, x2, y2)
        self.selection.x1 = 0
        self.selection.y1 = 0
        self.selection.x2 = 0
        self.selection.y2 = 0

    pass # End of Shell class

class PlanetData(GladeSlaveDelegate):
    planetwidgets = ["name", "owner", "id", "temperature", "colonists",
                     "happ_colonists", "tax_colonists", "natives",
                     "happ_natives", "tax_natives", "natives_race",
                     "natives_spi", "factories", "mines", "defenses"]
    def __init__(self):
        gd = Game()
        GladeSlaveDelegate.__init__(self, gladefile="planet_data",
                               toplevel_name="planet_data")

        # Widget customizations
        self.get_widget('name').set_bold(True)

        self.proxy = self.add_proxy(model=None, widgets=self.planetwidgets)
    pass

class GameManager(GladeDelegate):
    def __init__(self):
        super(GameManager, self).__init__(gladefile="game-manager",
                                          delete_handler=self.do_quit)
        self.games = []
        self.__init_ui()
        self.__init_config()

    def __init_config(self):
        # Create GWP's user directory if necessary
        self.conf_dir = os.path.expanduser('~/.gwp')
        if not os.path.exists(self.conf_dir):
            os.mkdir(self.conf_dir)
        # Attempt to load game list
        self.conf_file = self.conf_dir + '/config'
        self.config = ConfigParser.SafeConfigParser()
        self.config.read(self.conf_file)

        model = self.iconview.get_model()

        # Load game configurations
        for game in self.config.sections():
            if 'game_' in game:
                gc = GameConfig(game)
                gc.path = self.config.get(game, 'path')
                gc.name = self.config.get(game, 'name')
                gc.player = self.config.get(game, 'player')
                self.games.append(gc)
                # Populate iconview
                model.append((
                    gc.name,
                    gtk.gdk.pixbuf_new_from_file('/usr/local/games/gwp/game_icon.png'), # FIXME: hardcoded path
                    gc,
                    ))

    def __init_ui(self):
        model = gtk.ListStore(str, gtk.gdk.Pixbuf, object)
        self.iconview.set_model(model)
        self.iconview.set_text_column(0)
        self.iconview.set_pixbuf_column(1)
        
    def do_quit(self, *args):
        '''
        Quits GWP
        '''
        self.__save()
        print "Bye bye!"
        gtk.main_quit()

    def do_edit(self, *args):
        try:
            item_nr =  self.iconview.get_selected_items()[0][0]
        except IndexError:
            print "ERROR: Select a game to edit"
            return # If user does not select any game, do nothing
        g = self.iconview.get_model()[item_nr][2]
        game_edit = GameEdit(g)
        game_edit.set_parent(self)
        game_edit.show_all()
        
    def __save(self):
        for game in self.games:
            if game.id != 'game_' + game.name:
                self.config.remove_section(game.id)
                section = 'game_' + game.name
                self.config.add_section(section)
            else:
                section = game.id
                
            self.config.set(section, 'name', game.name)
            self.config.set(section, 'path', game.path)
            self.config.set(section, 'player', game.player)
        configfile = open(self.conf_file, 'w')
        self.config.write(configfile)
        configfile.close()

    def do_delete(self, *args):
        try:
            item_nr =  self.iconview.get_selected_items()[0][0]
        except IndexError:
            print "ERROR: Select a game to delete"
            return # If user does not select any game, do nothing
        model = self.iconview.get_model()
        gc = model[item_nr][2]
        i = model.get_iter(item_nr)
        # Remove game's data
        model.remove(i)
        self.games.remove(gc)
        self.config.remove_section('game_' + gc.name)

    def do_new(self, *args):
        gc = GameConfig()
        self.games.append(gc)
        self.config.add_section(gc.id)
        game_edit = GameEdit(gc)
        game_edit.set_parent(self)
        game_edit.show_all()

    def do_play(self, *args):
        try:
            item_nr =  self.iconview.get_selected_items()[0][0]
        except IndexError:
            print "ERROR: Select a game to play"
            return # If user does not select any game, do nothing
        g = self.iconview.get_model()[item_nr][2]
        self.__save()
        game = Game(g.path, int(g.player))
        shell = Shell()
        self.hide()
        shell.show_all()
        
class GameEdit(GladeDelegate):
    def __init__(self, game_config):
        super(GameEdit, self).__init__(gladefile="game-manager",
                                       toplevel_name="game_edit",
                                       delete_handler=self.do_close)
        self.gc = game_config
        self.__init_ui(self.gc)
        
    def on_game_dir__selection_changed(self, widget):
        races = []
        for race in range(1, 11+1):
            filename = widget.get_current_folder() + '/gen' + str(race) + '.dat'
            try:
                f = GenFile(filename)
            except:
                pass
            else:
                races.append(race)
        try:
            racelist = RaceList(widget.get_current_folder())
        except gwp.filereaders.casefile.NotFoundError:
            racelist = None

        self.game_player.clear()
        for race in races:
            self.game_player.append_item(racelist.get_short(race), str(race))
        if self.gc.player:
            self.game_player.select_item_by_data(self.gc.player)

    def __init_ui(self, gc):
        self.game_name.set_text(gc.name)
        self.game_dir.set_current_folder(gc.path)

    def do_close(self, *args):
        self.hide()
    
    def on_btn_close__clicked(self, *args):
        self.gc.name = self.game_name.get_text()
        self.gc.path = self.game_dir.get_current_folder()
        self.gc.player = self.game_player.get_selected_data()
        self.hide()
