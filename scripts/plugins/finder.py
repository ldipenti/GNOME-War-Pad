import pygtk
import gtk
import re


class Finder(gwp.Plugin):

    name = 'Ship Finder'
    version = '0.2'
    author_name = 'Lucas Di Pentima, Nicolas Cesar'
    author_email = 'lucas@lunix.com.ar'
    desc_short = 'A very simple plugin to search ships by several criteria'
    desc_long = 'Finder is the very first plugin written for GWP. Its main objective is to allow the player to quickly search objects using boolean operators. This plugin can be used as a base to write other plugins by novice GWP contributors, have fun!'
    license = 'GPL'

    # Constructor
    def __init__(self):
        gwp.Plugin.__init__(self)
        self.__create_gui()

    def __multiple_replace(self, dict, text):
        """
        Replace in 'text' all occurences of any key in the given
        dictionary by its corresponding value.  Returns the new string.
        """
        for key,val in dict.items():
            text = re.sub(key,val,text)
        return text

    def __obj_id(self, parm):
        """
        Helper function for __transform_eval
        so we can use reegxp parameters
        """
        return 'obj.get_id() == ' + parm.group(1)

    def __transform_eval(self, str):
        """
        This function does pattern matching, so user typed querys
        can be transformed into real eval'ed code. We know it's
        dangerous, but life also is.
        """
        d = {
            '^([0-9]*)$' : self.__obj_id, # a lonley number is an id
            #r'\b[nN]\b|\bneu\b' : 'obj.get_neutronium()',
            #r'\b[tT]\b|\btri\b' : 'obj.get_tritanium()',
            #r'\b[mM]\b|\bmol\b' : 'obj.get_molybdenum()',
            #r'\b[dD]\b|\bdur\b' : 'obj.get_duranium()',
            r'\b[wW]\b'         : 'obj.calculate_waypoint_distance()',
            r'\bmine\b'         : 'obj.is_mine()',
            r'\bbeams\b' 		: 'obj.get_beams()',
            r'\bbeams_name\b' 		: 'obj.get_beams_name()',
            r'\bbeamspec\b' 		: 'obj.get_beamspec()',
            r'\bbeams_type\b' 		: 'obj.get_beams_type()',
            r'\bbuild_base\b' 		: 'obj.get_build_base()',
            r'\bcol_growth_limit\b' 	: 'obj.get_col_growth_limit()',
            r'\bcolonists\b' 		: 'obj.get_colonists()',
            r'\bcrew\b' 		: 'obj.get_crew()',
            r'\bdamage\b' 		: 'obj.get_damage()',
            r'\bdefense_posts\b' 	: 'obj.get_defense_posts()',
            r'\bdef_sys_battle_mass\b' 	: 'obj.get_def_sys_battle_mass()',
            r'\bdef_sys_beams_nr\b' 	: 'obj.get_def_sys_beams_nr()',
            r'\bdef_sys_beams_type\b' 	: 'obj.get_def_sys_beams_type()',
            r'\bdef_sys_beams_type_str\b': 'obj.get_def_sys_beams_type_str()',
            r'\bdef_sys_fighter_bays\b' : 'obj.get_def_sys_fighter_bays()',
            r'\bdef_sys_fighters_nr\b' 	: 'obj.get_def_sys_fighters_nr()',
            r'\bdens_duranium\b' 	: 'obj.get_dens_duranium()',
            r'\bdens_molybdenum\b' 	: 'obj.get_dens_molybdenum()',
            r'\bdens_neutronium\b' 	: 'obj.get_dens_neutronium()',
            r'\bdens_tritanium\b' 	: 'obj.get_dens_tritanium()',
            r'\bduranium\b' 		: 'obj.get_duranium()',
            r'\bengine_name\b' 		: 'obj.get_engine_name()',
            r'\bengines_type\b' 	: 'obj.get_engines_type()',
            r'\bengspec\b' 		: 'obj.get_engspec()',
            r'\bfactories\b' 		: 'obj.get_factories()',
            r'\bfcode\b' 		: 'obj.get_fcode()',
            r'\bfighter_bays\b' 	: 'obj.get_fighter_bays()',
            r'\bfighters\b' 		: 'obj.get_fighters()',
            r'\bground_duranium\b' 	: 'obj.get_ground_duranium()',
            r'\bground_molybdenum\b' 	: 'obj.get_ground_molybdenum()',
            r'\bground_neutronium\b' 	: 'obj.get_ground_neutronium()',
            r'\bground_tritanium\b' 	: 'obj.get_ground_tritanium()',
            r'\bhappiness_col_change\b' : 'obj.get_happiness_col_change()',
            r'\bhappiness_colonists\b' 	: 'obj.get_happiness_colonists()',
            r'\bhappiness_nat_change\b' : 'obj.get_happiness_nat_change()',
            r'\bhappiness_natives\b' 	: 'obj.get_happiness_natives()',
            r'\bhull_beam_weapons\b' 	: 'obj.get_hull_beam_weapons()',
            r'\bhull_cargo\b' 		: 'obj.get_hull_cargo()',
            r'\bhull_crew\b' 		: 'obj.get_hull_crew()',
            r'\bhull_engines\b' 	: 'obj.get_hull_engines()',
            r'\bhull_fighter_bays\b' 	: 'obj.get_hull_fighter_bays()',
            r'\bhull_fuel_tank\b' 	: 'obj.get_hull_fuel_tank()',
            r'\bhull_name_trunc\b' 	: 'obj.get_hull_name_trunc()',
            r'\bhull_picture\b' 	: 'obj.get_hull_picture()',
            r'\bhullspec\b' 		: 'obj.get_hullspec()',
            r'\bhull_torp_launchers\b' 	: 'obj.get_hull_torp_launchers()',
            r'\bhull_type\b' 		: 'obj.get_hull_type()',
            r'\bintercept_ship_id\b' 	: 'obj.get_intercept_ship_id()',
            r'\bmass_if_unknown\b' 	: 'obj.get_mass_if_unknown()',
            r'\bmegacredits\b' 		: 'obj.get_megacredits()',
            r'\bmined_duranium\b' 	: 'obj.get_mined_duranium()',
            r'\bmined_molybdenum\b' 	: 'obj.get_mined_molybdenum()',
            r'\bmined_neutronium\b' 	: 'obj.get_mined_neutronium()',
            r'\bmined_tritanium\b' 	: 'obj.get_mined_tritanium()',
            r'\bmines\b' 		: 'obj.get_mines()',
            r'\bmining_rate\b' 		: 'obj.get_mining_rate()',
            r'\bmission\b' 		: 'obj.get_mission()',
            r'\bmission_name\b' 	: 'obj.get_mission_name()',
            r'\bmolybdenum\b' 		: 'obj.get_molybdenum()',
            r'\bnat_growth_limit\b' 	: 'obj.get_nat_growth_limit()',
            r'\bnatives\b' 		: 'obj.get_natives()',
            r'\bnatives_race\b' 	: 'obj.get_natives_race()',
            r'\bnatives_race_chars\b' 	: 'obj.get_natives_race_chars()',
            r'\bnatives_spi\b' 		: 'obj.get_natives_spi()',
            r'\bnatives_spi_chars\b' 	: 'obj.get_natives_spi_chars()',
            r'\bneutronium\b' 		: 'obj.get_neutronium()',
            r'\bowner\b' 		: 'obj.get_owner()',
            r'\bowner_name\b' 		: 'obj.get_owner_name()',
            r'\bprimary_enemy\b' 	: 'obj.get_primary_enemy()',
            r'\bprimary_enemy_name\b' 	: 'obj.get_primary_enemy_name()',
            r'\bstarbase\b' 		: 'obj.get_starbase()',
            r'\bsupplies\b' 		: 'obj.get_supplies()',
            r'\btax_collected_colonists\b': 'obj.get_tax_collected_colonists()',
            r'\btax_collected_natives\b': 'obj.get_tax_collected_natives()',
            r'\btax_collected_natives_max\b': 'obj.get_tax_collected_natives_max()',
            r'\btax_colonists\b' 	: 'obj.get_tax_colonists()',
            r'\btax_natives\b' 		: 'obj.get_tax_natives()',
            r'\btax_rate_colonists\b' 	: 'obj.get_tax_rate_colonists()',
            r'\btax_rate_natives\b' 	: 'obj.get_tax_rate_natives()',
            r'\btemperature\b' 		: 'obj.get_temperature()',
            r'\btemperature_f\b' 	: 'obj.get_temperature_f()',
            r'\btemperature_str\b' 	: 'obj.get_temperature_str()',
            r'\btorps\b' 		: 'obj.get_torps()',
            r'\btorps_launchers\b' 	: 'obj.get_torps_launchers()',
            r'\btorps_name\b' 		: 'obj.get_torps_name()',
            r'\btorpspec\b' 		: 'obj.get_torpspec()',
            r'\btorps_type\b' 		: 'obj.get_torps_type()',
            r'\btow_ship_id\b' 		: 'obj.get_tow_ship_id()',
            r'\btransfer_colonists\b' 	: 'obj.get_transfer_colonists()',
            r'\btransfer_duranium\b' 	: 'obj.get_transfer_duranium()',
            r'\btransfer_molybdenum\b' 	: 'obj.get_transfer_molybdenum()',
            r'\btransfer_neutronium\b' 	: 'obj.get_transfer_neutronium()',
            r'\btransfer_ship_id\b' 	: 'obj.get_transfer_ship_id()',
            r'\btransfer_supplies\b' 	: 'obj.get_transfer_supplies()',
            r'\btransfer_tritanium\b' 	: 'obj.get_transfer_tritanium()',
            r'\btritanium\b' 		: 'obj.get_tritanium()',
            r'\bunload_colonists\b' 	: 'obj.get_unload_colonists()',
            r'\bunload_duranium\b' 	: 'obj.get_unload_duranium()',
            r'\bunload_molybdenum\b' 	: 'obj.get_unload_molybdenum()',
            r'\bunload_neutronium\b' 	: 'obj.get_unload_neutronium()',
            r'\bunload_planet_id\b' 	: 'obj.get_unload_planet_id()',
            r'\bunload_supplies\b' 	: 'obj.get_unload_supplies()',
            r'\bunload_tritanium\b' 	: 'obj.get_unload_tritanium()',
            r'\bvisibility\b' 		: 'obj.get_visibility()',
            r'\bwaypoint\b' 		: 'obj.get_waypoint()',
            r'\bx_to_waypoint\b' 	: 'obj.get_x_to_waypoint()',
            r'\by_to_waypoint\b' 	: 'obj.get_y_to_waypoint()'
            }
        return self.__multiple_replace(d, str)

    # This is a callback function. The data arguments are ignored
    # in this example. More on callbacks below.
    def entry_key(self, widget, event, data=None):
        if (event.keyval == gtk.gdk.keyval_from_name('Return')):
            self.search_obj(self.btn)


    def __filtering_function(self, id, obj, expression):
        try:
            ret = eval(expression)
        except:
            return False
        return ret
    
    def search_obj(self,  widget, data=None):
        ships = gwp.ship_get_list()
        query_string = self.search.get_text()

        ## Fill ships list
        # make replacement based in regular expressions
        query = self.__transform_eval(query_string)
        # clean up the result space (store)
        self.store.clear()
        # let's look up which one fits to the quert
        for (key,obj) in ships.items():
            # use a filtering function to catch exceptions
            if self.__filtering_function(key,obj,query):
                # add the matching objects to the ship list
                self.store.append([key, obj.get_name(), obj.get_neutronium()])

        ## Fill planet list
        ## do the same with the planets
        planets = gwp.planet_get_list()
        query2 = self.__transform_eval(query_string)
        self.store2.clear()
        for (key,obj) in planets.items():
            if self.__filtering_function(key,obj,query):
                self.store2.append([key, obj.get_name(), obj.get_colonists()])

    # Hide window but not terminate plugin
    def delete_event(self, widget, event, data=None):
        self.window.hide()
        return gtk.TRUE

    # Another callback
    def destroy(self, widget, data=None):
        gtk.main_quit()

    def __create_gui(self):
        # create a new window
        self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
        self.window.set_title('Search')
        self.window.set_default_size(300, 500)
    
        self.window.connect("delete_event", self.delete_event)
        self.window.connect("destroy", self.destroy)
    
        # Sets the border width of the window.
        self.window.set_border_width(1)
    
        # Widgets
        self.vbox = gtk.VBox()
        self.hbox = gtk.HBox()
        self.vbox.set_homogeneous(gtk.FALSE)
        self.search = gtk.Entry(1024)
        self.list_scroll = gtk.ScrolledWindow()
        self.list_scroll.set_policy(gtk.POLICY_AUTOMATIC, gtk.POLICY_ALWAYS)
        self.list = gtk.TreeView()
        self.btn = gtk.Button('Search')
        # additions
        self.hbox.pack_start(self.search, gtk.TRUE, gtk.TRUE, 2)
        self.hbox.pack_start(self.btn, gtk.FALSE, gtk.FALSE, 2)
        self.vbox.pack_start(self.hbox, gtk.FALSE, gtk.FALSE, 0)
        self.vbox.pack_start(self.list_scroll, gtk.TRUE, gtk.TRUE, 0)
        self.list_scroll.add(self.list)
        self.window.add(self.vbox)
        # callbacks
        self.btn.connect("clicked", self.search_obj, None)
        self.search.connect("key_press_event", self.entry_key, None)
        # treeview setup
        self.store = gtk.ListStore(int, str, int)
        renderer = gtk.CellRendererText()
        # ID Column
        col_id = gtk.TreeViewColumn('#', renderer, text=0)
        col_id.set_sort_column_id(0)
        col_id.set_sort_indicator(gtk.TRUE)        
        # Name Column
        col_name = gtk.TreeViewColumn('Name', renderer, text=1)
        # Neu Column
        col_neu = gtk.TreeViewColumn('Neu', renderer, text=2)
        col_neu.set_sort_column_id(2)
        col_neu.set_sort_indicator(gtk.TRUE)
        # Add columns to model
        self.list.append_column(col_id)
        self.list.append_column(col_name)
        self.list.append_column(col_neu)
        self.list.set_model(self.store)
        ## second list
        self.list2_scroll = gtk.ScrolledWindow()
        self.list2_scroll.set_policy(gtk.POLICY_AUTOMATIC, gtk.POLICY_ALWAYS)
        self.list2 = gtk.TreeView()
        # additions
        self.vbox.pack_start(self.list2_scroll, gtk.TRUE, gtk.TRUE, 0)
        self.list2_scroll.add(self.list2)
        # treeview setup
        self.store2 = gtk.ListStore(int, str, int)
        renderer = gtk.CellRendererText()
        # ID Column
        col_id = gtk.TreeViewColumn('#', renderer, text=0)
        col_id.set_sort_column_id(0)
        col_id.set_sort_indicator(gtk.TRUE)        
        # Name Column
        col_name = gtk.TreeViewColumn('Name', renderer, text=1)
        # Colonos
        col_col = gtk.TreeViewColumn('Col', renderer, text=2)
        col_col.set_sort_column_id(2)
        col_col.set_sort_indicator(gtk.TRUE)
        # Add columns to model
        self.list2.append_column(col_id)
        self.list2.append_column(col_name)
        self.list2.append_column(col_col)
        self.list2.set_model(self.store2)

    # Dummy wrapper to real method
    def __main_menu_cb (self, widget, data=None):
        self.__main()

    def __main(self):
        # All PyGTK applications must have a gtk.main(). Control ends here
        # and waits for an event to occur (like a key press or mouse event).
        self.window.show_all()
        gtk.main()

    def register(self, pm):
        pm.set_hook_key (0, # No modifier
                         gtk.gdk.keyval_from_name('f'),
                         self.__main)
        pm.set_hook_menu ('_Finder',
                          self.__main_menu_cb)

    # Cleaning up
    def unregister(self, pm):
        pass
