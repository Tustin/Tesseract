const double pi = 3.1415926;
#pragma region Toggles
bool Open = false;
bool UnlockingTrophies = false;
bool SpamCash = false;
bool SuperMan = false;
bool SuperFast = false;
bool GodModePlayer = false;
bool veh_invincible = false;
bool PlayerVisible = true;
bool veh_invisible = false;
bool Explode = false;
bool ColorChange = false;
bool fixcar = false;
bool XMAS = false;
bool VDAY = false;
bool FOURTH = false;
bool SNOW = false;
bool FREE = false;
bool IDLE = false;
bool InfAmmo = false;
bool OnFire = false;
bool TextMessage = false;
bool Speedo = false;
bool ShowMessage = false;
bool setTimer = false;
bool Sound = false;
bool NoWanted = false;
bool Teleporting = false;
bool OnMe = false;
bool play_anim = false;
bool IsAnimPlaying = false;
bool KillAnim = false;
bool KillReturn = false;
bool invites = false;
bool doVibe = false;
bool kingmaker = false;
bool CashSpamAll = false;
bool BlowUpAll = false;
bool AddPed = false;
bool RemovePed = false;
bool GivePedGuns = false;
bool GuardAnims = false;
bool noclip = false;
bool slingshot = false;
bool deletecar = false;
bool protection = false;
bool kickplayer = false;
bool chatheads = true;
bool freezevehicle = false;
bool nocollision = true;
bool removeweaps = false;
bool flipcar = false;
bool fixplayercar = false;
bool fuckupcar = false;
bool randomplayercarcolor = false;
bool teleportplayer = false;
bool undriveable = false;
bool lockdoors = false;
bool upsidedown = false;
bool customcar = false;
bool customobj = false;
bool custommodel = false;
bool colorpicker = false;
bool customcarcolor = false;
bool customenucolor = false;
bool setcustomcarcolor = false;
bool invisiblemodel = false;
bool togglelock = false;
bool up, down, xaxisplus, xaxisminus, yaxisplus, yaxisminus, pitchplus, pitchminus, rollplus, rollminus, yawplus, yawminus, copy, del;
bool changeplate = false;
bool dosuper = false;
bool needtocheck = true;
bool selectobj = false;
bool addcash, setrp;
bool waypoint = false;
bool teleinfront = false;
bool teleport = false;
bool tracer = false;
bool superjump = false;
bool meweapons = false, clientweapons = false;
bool unlock;
bool showlobbyinfo = true;
bool showplayerstats = true;
bool flipmycar = false;
bool blowupped = false;
bool telepedtome = false;
bool playpedanim = false;
bool givepedgun = false;
bool setinclosestcar = false;
bool nos = false;
bool deleteallpeds = false;
bool allpedsdance = false, arepedsdancing = false;
bool spawncustomped = false;
bool gotkey = false;
bool Notification = false;
bool nfs = false;
bool keyboard = false;
bool shootvehweapons = false;
bool xenon = false;
bool givecash = false;
bool supe = false;
bool clone = false;
bool dev = false;
bool allfix = false, allcolor = false, allsupe = false, allweapons = false;
bool supeclient = false;
bool blowupallpeds = false;
bool cloneplayer = false;
bool nvg = false, seethru = false;
bool removemyweaps = false;
bool explosivemelee = false, explosiveammo = false, fireammo = false, gravity = false, fastswim = false, slideycars = false;
bool yachtloaded = false, nyloaded = false, loadyacht = false, loadny = false;
bool sticktoground = false;
bool supemyvehicle = false;
bool deletemyvehicle = false;
bool carjump = false;
bool forcefield = false;
bool neons = false;
bool rainbowneons = false;
bool dw = false;
bool spawnwater = false;
bool rockstarshirt = false;
bool mobileradio = false;
bool rockstartoggle = false;
bool toggleradio = false;
bool suicideall = false;
bool ownedexplosion = false;
bool swatplayer = false;
bool chopattack = false;
bool cockfight = false;
bool guardattack = false;
bool gokillclient = false;
bool removeallguards = false;
bool randomped = false;
bool doallpedsgodmode = false, toggleallgodmode = false;
bool openweaponsforguard = false, openweaponsforall = false;
bool godmodeguard = false;
bool kickguardfromgroup = false;
bool ufoloaded = false, torturelayerloaded = false, fameorshameloaded = false, jewleryheistloaded = false, carshowroomloaded = false, lifeinvaderloaded = false, spaceloader = false;
bool loadufo = false, loadtorturelayer = false, loadfameorshame = false, loadjewleryheist = false, loadcarshowroom = false, loadlifeinvader = false, loadspace = false;
bool cleararea = false;
bool da = false;
bool setupda = false;
bool clearmem = false;
bool clientforcefield = false;
bool teleporttosky = false;
bool isfirstperson = false;
bool togglefirstperson = false;
bool togglenoclip = false;
bool randomvehicle = false;
bool superun = false;
bool chauffeur = false;
bool playertroll = false;
bool setonfire = false;
bool attachtoclienttoggle = false, attachtocartoggle = false, attachobjecttoggle = false, customattachobj = false;
bool togglespy = false;
bool isspying = false;
bool boostplayer = false;
bool freezeveh = false, unfreezeveh = false;
bool rapeplayer = false, piggybackride = false;
bool clearallobjs = false;
bool goofball = false;
bool detachfromentity = false;
bool spawnforclient = false;
bool editlastattachedobj = false;
bool swagmobile = false;
bool teleportgun = false;
bool drawfps = false;
bool startup = false;
bool test = false;
bool rbumper0, rbumper1, rbumper2, rbumper3;
bool fbumper0, fbumper1, fbumper2, fbumper3;
bool spoiler0, spoiler1, spoiler2, spoiler3;
bool sskirt0, sskirt1, sskirt2, sskirt3;
bool hood0, hood1, hood2, hood3, hood4, hood5;
bool deletedoors = false;
bool spamcashonme = false;
bool cashdropmonitor = true;
bool wheels = false;
bool Wanted;
bool teleintoplayercar = false;
bool osok = false;
bool customrp, customcash;
bool osk;
bool givetoplayer;
bool trollmonitor = true;
bool testingthing = false;
bool bounty = false;
bool pegasus = false;
bool cargun = false;
bool randomveh = false;
bool spawncargun = false;
bool starttimer, timerrun;
bool load_buttons = false;
bool spawn_veh = false;
bool bat_loop = false;
bool bus_loop = false;
bool chauf_loop = false;
bool client_guard = false;
bool guard_loop = false;
bool model_loop = false;
bool goodie_loop = false;
bool armour_regen = false;
bool health_regen = false;
bool freeze_protection = false;
bool cm_loaded = false;
bool model_my_guard = false, model_client_guard = false;
bool _keyboard = false;
bool ped_manager = false;
bool spawn_veh_return = false;
bool aimbot_toggle = false;
bool particles = false;
bool seatbelt = false;
bool time_paused = false;
bool die = false;
bool rainbow_name = false;
bool request_clipset = false;
bool shoot_monies_toggle = false;
bool shoot_prop_toggle = false;
bool pm_waypoint_toggle = false;
bool spawn_deer_loop = false;
bool grav_gun = false;
bool spawn_invincible_vehicle = true;
bool spawn_inside_vehicle = true;
bool spawn_suped_up_vehicle = true;
bool spawn_goodies_looped = false;
bool text_all = false;
bool restricted_areas = false;
bool use_mph = true;
bool spawn_object_get_return = false;
bool attach_custom_object = false;
bool spawn_and_attach_object_loop = false;
bool play_anim_for_ped = false;
bool dev_toggle = false;
bool drive_on_wheel = false;
bool vehicle_freeze_protection = false;
bool prop_attach_protection = false;
bool animation_protection = false,
remove_weapons_protection = false,
explosion_protection = false,
ptfx_protection = false,
disable_tasks_protection = false;

#pragma endregion
#pragma region Player Stats Vars
float px;
float py;
float pz;
int phealth;
float pspeed;
char* pveh;
char* pseats;
float pdist;
#pragma endregion
#pragma region component vars
int cur_drawable;
int max_drawable;

int cur_texture;
int max_texture;

int cur_component;

int selected_ped;

#pragma endregion
#pragma region Addresses
Address NetHandleBuffer = 0x10070200;
Address TunablesPtr = 0x1E70374;
Address GlobalsPtr = 0x1E70370;
Address OTRPtr = 0x1E70394;
Address OTRGap = 0x22284;
Address TunablesAddress;
Address CamCoords = 0x10070220;
Address dev_mode = 0x3E30D8; //li r4, 0 original
int contents;
int drawtext = 0;
#pragma endregion
#pragma region Int vars
int bGuards[6];
int myGroup = 0;
int pedCount = 0;
int PedGun;
int delay;
int obj;
int counter = 0;
int Scroll = -1;
short WhichMenu = 0;
int objSet = -1;
short SelectedClient = -1;
short selectedped = -1;
short lastobj = -1;
short selectedobj = -1;
short neonsr = 0, neonsg = 0, neonsb = 0;
int waterobj = -1;
int firstpersoncam;
int noclipcam;
int timetick = 20;
int attachobj;
short itemsOnPage = 0;
float height;
int lastattachedobj = -1;
int wheeltype = -1, wheelindex = -1;
int carPrimary = 0, carSecondary = 0;
int devtype = 3;
int randommodelindex;
int game_ticks;
int mov = 0;
int veh_hash;
int client_guard_hash;
int guard_hash;
int player_model_hash;
int _ID;
int slowmo = 0;
int keyboard_len;
int keyboard_action;
int pm_ent;
int spikes[3];
const int PED_FLAG_CAN_FLY_THRU_WINDSCREEN = 32;
int color_type = 1; //primary, secondary
int vehicle_r = 0, vehicle_g = 0, vehicle_b = 0;
int name_color_index = 0; //none
int give_wep_index = 0;
int weapon_instance = 0; //0 - me, 1 - selected entity, 2 - bodyguard
int cur_wl_menu = 0;
int cur_menu_color_item = 0; //0 - header, 1 - background, 2 - scrollbar
int cur_menu_font_item = 0; //0 - header, 1 - menu options
int shoot_prop_object;
int kdr_kills;
int kdr_deaths;
int cur_win_item;
int cur_loss_item;
int current_neon_index = -1;
int current_garage;
#pragma endregion
int check;
const char* Message;
char *AnimDict;
char *Anim;
char* plate;
char* keyboard_result;
#pragma region Float vars
float statswindowtext1 = 0.723672;
float statswindowtext2 = 0.852959;
float objectcoordx, objectcoordy, objectcoordz, objectheading, objectpitch = 0, objectroll = 0, objectyaw = 0;
float telex, teley, telez;
float MenuTitleTextY = 0.258665;
float density_mul = 1, rpm_mul = 1, light_mul = 1, torque_mul = 1;
float timecycle_strength = 1;
float groundCheckHeight[] = {
	100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0,
	450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0
};
#pragma endregion
#pragma region MenuProperties
//rgba(41, 128, 185, 1.0)
//old header
//10, 102, 139
int MenuColorSelectedItem[3][3] =
{
	{ 41, 128, 185 }, //header
	{ 0, 0, 0 }, //background
	{ 41, 128, 185 }, //scroll
};
int MenuFontSelectedItem[2][1] =
{
	{ 1 }, //header
	{ 0 } //options
};
int MenuHeaderColor[3] = { 10, 102, 139 };
int MenuBackgroundColor[3] = { 0, 0, 0 };
int MenuScrollColor[3] = { 10, 102, 139 };

#pragma endregion

#pragma region object shit
size_t objcount = 0;
Object current_object_index;
Vector3 temp_obj_pos;
bool spawn_object = false;

Object get_returned_object;
#pragma endregion

Vehicle return_vehicle;
char* original = "empty";
char* changed_name = "empty";
Hash vehicle_weapons[5] = { 0x9F1A91DE, 0x7F7497E5, 0xBFEFFF6D, 0x787F0BB, 0xCF0896E0 };
Hash current_vehicle_weapon = 0;
int current_vehicle_weapon_index = 0;
Hash attach_object_hash;
Bone attach_object_bone;
int attach_object_bone_index = -1;
Ped ped_anim_id;
char* colors[] = { "~w~", "~p~", "~b~", "~l~", "~g~", "~y~", "~r~", "~o~", "~m~", "~f~" };
char* color_names[] = { "None", "Purple", "Blue", "Black", "Green", "Yellow", "Red", "Orange", "Dark Grey", "Light Blue" };
char *GuardName;
char *ObjName;
char *custom_attach_object_name = "None";
const char* clipset_name;
const char *guard_name;
Vector3 lastshot;
Vector3 vehicle_spawn_position;
float object_precision_plus[] = { 10.0, 5.0, 1.0, 0.1 };
float object_precision_minus[] = { -10.0, -5.0, -1.0, -0.1 };
int obj_precision_index = 0;
#pragma region MenuOptions 
char* Main[14] = { "Player", "Vehicle", "Network", "Vehicle Spawner", "Model Changer", "Bodyguards", "Animations", "Teleports", "Object Spawner", "Weather and Time", "Tunables", "Miscellaneous", "Settings", "Exit" }; //Menu 1
char* Self[16] = { "Appearance", "Weapons", "Cheats", "Visions", "Invincibility", "Invisiblity", "Cash Drop", "Never Wanted", "Explode", "The Master", "Clone", "Forcefield", "Superman", "Health Regen", "Armour Regen", "Suicide" }; //Menu 2
const char* Account[12] = { "RP menu", "Cash menu", "Inventory", "Skills", "Unlock all", "Skip tutorial", "Unlock event items", "Wipe reports", "Unlock all clothing", "Unlock Heist items", "Rockstar shirts", "Fast Combat Roll" }; //Menu 3
const char* VehicleMenu[24] = { "Mod Shop", "Neons", "Multipliers", "Invincibility", "Invisibility", "Vehicle Weapons", "Fix Vehicle", "Random Color", "Super Boost", "Need For Speed", "Teleport into Closest Vehicle", "Speedometer", "Freeze Position", "No Collision", "Change Plate", "Toggle Door Locks", "Nitrous", "Drive on Water", "Drive on Air", "Supe Up", "Delete", "Set on Wheels", "Vehicle Jumper", "Seatbelt" }; //Menu 4
const char* Models[13] = { "Players", "Animals", "Ambient Female", "Ambient Male", "Cutscene", "Female Gang Members", "Male Gang Members", "Story Characters", "Multiplayer", "Scenario Female", "Scenario Male", "Story Scenario Female", "Story Scenario Male" }; //Menu 5
const char* ObjectsMenu[13] = { "Edit object", "Manage objects", "All Props", "UFO", "Asteroid", "Alien egg", "Weed plant", "Ferris wheel", "Orange ball", "Ramp", "Poop", "Windmill", "Custom" }; //Menu 7
const char* WeatherOptions[16] = { "Extra sunny", "Clear", "Cloudy", "Smog", "Fog", "Overcast", "Rain", "Thunder", "Clearing", "Neutral", "Snow", "Blizzard", "Light snow", "Hour", "Minutes", "Seconds" }; //Menu 8
const char* Tunables[8] = { "XMAS DLC", "Valentine's DLC", "Independence DLC", "Snow", "Free stuff", "No idle kick", "Off the radar", "Reveal hidden players" }; //Menu 9
const char* PedComponents[14] = { "Default", "Random Variation", "Head", "Face", "Hair", "Shirt", "Pants", "Gadgets", "Feet", "Accessories", "Undershirts", "Armour", "Logos", "Jackets" }; //Menu 10
const char* VehicleList[23] = { "Supers", "Sports", "Classics", "Muscle", "Compact", "Off-road", "SUV", "Sedan", "Helicopters", "Motorcycles", "Military", "Emergency", "Heists", "Planes", "Boats", "Fun", "DLC", "Modder Favorites", "Random", "Custom", "Spawn invincible vehicles", "Spawn inside vehicles", "Spawn suped up vehicles" }; //Menu 11
const char* SuperVehicles[9] = { "Bullet", "Adder", "Infernus", "Zentorno", "Voltic", "Cheetah", "Turismo", "Vacca", "Entity XF" }; //Menu 12
const char* SportsVehicles[12] = { "Comet", "Cabrio", "9F", "Sultan", "Rapid GT", "Carbonizzare", "Feltzer", "Elegy RH8", "Jester", "Banshee", "Buffalo", "Coquette" }; //Menu 13
const char* ClassicVehicles[6] = { "Z-Type", "Monroe", "JB 700", "Pigalle", "Stinger GT", "Tornado" }; //Menu 14
const char* MuscleVehicles[10] = { "Rat-loader", "Dominator", "Blade", "Phoenix", "Voodoo", "Ruiner", "Picador", "Sabre Turbo", "Gauntlet", "Buccaneer" }; //Menu 15
const char* CompactVehicles[5] = { "Rhapsody", "Panto", "Blista", "Dilenttante", "Issi" }; //Menu 16
const char* MilitaryVehicles[4] = { "Rhino", "Barracks Semi", "Crusader", "Barracks" }; //Menu 17
const char* FunVehicles[8] = { "Space Docker", "Prison Bus", "Forklift", "Lawn Mower", "HVY Dump", "Dock Handler", "Clown Van", "Weed Van" }; //Menu 18
const char* DLCVehicles[17] = { "Hotknife", "Khamelion", "Carbon RS", "Roosevelt", "The Liberator", "Windsor", "Virgo", "Feltzer 3", "Osiris", "Swift 2", "Luxor 2", "Brawler", "T20", "Blackfin", "Chino", "Vindicator", "Toro" }; //Menu 19
const char* FavoriteVehicles[11] = { "Tustin", "Choco <3", "Kryptus", "Son-Of-A-Beach", "Octolus", "Amitoz", "HURT", "Slinky", "Slick", "KingBilly", "Kurt" }; //Menu 20
const char* PlayerMain[7] = { "Player Options", "Vehicle Options", "Attach Options", "Car Spawner", "Bodyguards", "[TEST] Give vehicle ownership", "[TEST] Steal vehicle ownership" }; //Menu 23, 21 is player menu
const char* AnimationOptions[5] = { "Presets", "Movement Styles", "Scenarios", "Natural Motion", "Stop animations" }; //Menu 24
const char* TeleportOptions[4] = { "Waypoint", "Forward", "Above", "Locations" }; //Menu 25
const char* ObjectEditor[10] = { "Select aimed object", "Precision", "X Axis", "Y Axis", "Z Axis", "Pitch", "Roll", "Yaw", "Copy", "Delete" }; //Menu 27
const char* AllPlayersMenu[7] = { "40k cash drop", "Explode all", "Fix all cars", "Randomize all car colors", "Supe up all cars", "Tracer", "Send custom text" }; //Menu 28
const char* BodyguardMenu[7] = { "Spawn new guard", "Modify peds", "Hit list", "All guards dance", "All guards invincible", "Remove all from group", "Delete all guards" }; //Menu 29
const char* PedOptions[7] = { "Randomize components", "Give a weapon", "Invincible", "Dance", "Remove from group", "Delete", "Teleport to me" }; //Menu 31
const char* MenuSettings[6] = { "Menu Colors", "Menu Fonts", "Toggle player stats window", "Toggle lobby stats", "Toggle players talking", "Metric System" }; //Menu 32
const char* HeistVehicles[14] = { "Casco", "Lectro", "Enduro", "Guardian", "Kuruma", "Kuruma 2", "Hydra", "Insurgent", "Insurgent 2", "Savage", "Technical", "Slamvan", "Barracks 3", "Valkyrie" }; //Menu 34
const char* ModShopMain[11] = { "Body", "Engine", "Transmission", "Brakes", "Suspension", "Armour", "Exhaust", "Bulletproof tires", "Plates", "Window tint", "Xenons" }; //Menu 36

const char* Network[5] = { "Online Players", "All Players", "Account", "Off the Radar", "Reveal hidden players" }; //Menu 43

const char* ModShopBodyMain[11] = { "Front Bumper", "Rear Bumper", "Spoilers", "Side Skirts", "Hood", "Grille", "Fender", "Roof", "Rims", "Colors", "Doors" }; //Menu 46

const char* EmergencyVehicles[8] = { "Ambulance", "Police Cruiser", "FIB Buffalo", "Police Buffalo", "Snow Police Car", "Snow Police Rancher", "Police Transport Van", "Police Bike" }; //Menu 54
const char* Visions[2] = { "Vision list", "Clear visions" }; //Menu 55
const char* VehicleMultipliers[4] = { "RPM Multiplier", "Density Multiplier", "Torque Multiplier", "Light Multiplier" }; //Menu 56 vehicle2
const char* Neons[8] = { "Toggle neons", "Blue neons", "Yellow neons", "Green neons", "Red neons", "Orange neons", "Pink neons", "Rainbow neons" }; //Menu 57
const char* VehicleWeapons[6] = { "Toggle vehicle weapons", "Hunter", "Fireworks", "JB-700", "Snowballs", "Plane Rocket", }; //Menu 58
const char* GuardWeapons[14] = { "Pistol", "SMG", "MG", "Assault shotgun", "AR", "Stungun", "Gusenberg", "Vintage pistol", "Fireworks", "Snowballs", "Flares", "Handcuffs", "Homing launcher", "Musket" }; //Menu 59
const char* MapMods[8] = { "Heist yacht", "North Yankton", "Destroyed hospital", "Jewelry store", "Morgue", "Life Invader office", "FIB lobby", "Slaughterhouse" }; //Menu 60
const char* Cheats[8] = { "Super jump", "Fire ammo", "Explosive melee", "Explosive ammo", "Super run", "Fast Swim", "Slidey Cars", "Slow-Mo", }; //Menu 61
const char* SedanVehicles[9] = { "Stanier", "Tailgater", "Super Diamond", "Stretch", "Regina", "Asea", "Hearse", "Washington", "Emperor" }; //Menu 63
const char* OffRoadVehicles[10] = { "Sandking SWB", "Sandking XL", "Blazer", "Rebel", "Rancher XL", "Bodhi", "Duneloader", "BF Injection", "Buggy", "Bifta" }; //Menu 64
const char* SUVVehicles[7] = { "Patriot", "BeeJay XL", "Baller", "Landstalker", "Granger", "Dubsta", "Huntley S" }; //Menu 65
const char* Helicopters[6] = { "Annihilator", "Buzzard", "Cargobob", "Frogger", "Maverick", "Skylift" }; //Menu 66
const char* Motorcycles[12] = { "Sovereign", "Daemon", "Bagger", "Vader", "PCJ 600", "Hakuchou", "Nemesis", "Ruffian", "Hexer", "Sanchez", "Double-T", "Akuma" }; //Menu 67
const char* Planes[6] = { "Blimp", "Cargo plane", "Duster", "Lazer", "Titan", "Mallard (stunt plane)" }; //Menu 68
const char* Boats[7] = { "Marquis", "Dinghy", "Police Predator", "Jetmax", "Suntrap", "Seashark", "Submarine" }; //Menu 69 LOL
const char* PlayerOptions[17] = { "Teleport to player on foot", "Teleport into player's car", "Drop 40k cash", "Give all weapons", "Remove all weapons", "Set owned explosion", "Explode player", "Clone", "SWAT player", "Chop attack", "Kick", "Send custom text message", "ESP", "Ram with Bus", "Copy Outfit", "Drop Goodies", "Freeze in place" }; //Menu 70
const char* PlayerVehicleOptions[11] = { "Fix car", "Random car color", "Slingshot", "Boost", "Set car upright", "Delete vehicle", "Fuck up vehicle", "Vehicle troll", "Freeze vehicle", "Unfreeze vehicle", "Kick out of vehicle" }; //Menu 71
const char* PlayerAttachOptions[5] = { "Attach self to player", "Piggyback ride", "Rape", "Attach an object to them", "Detach from entity" }; //Menu 72
const char* PlayerObjectOptions[5] = { "Attach Custom Object", "Traffic cone", "Hotdog", "Flatscreen", "Christmas tree" }; //Menu 73
const char* MiscOptions[17] = { "IPL Loader", "First person", "UFO mode", "Batmobile", "Chauffeur", "Clear Area", "Mobile Radio", "Clone Freeze Protection", "Ped Modifier", "Remove Area Restrictions", "Developer Mode", "Vehicle Freeze Protection", "Animation Protection", "Explosion Protection", "Remove Weapons Protection", "Particle FX Protection", "Disable Tasks Protection" }; //Menu 74
const char* Rims[7] = { "High End", "Lowrider", "Muscle", "Off-road", "Sports", "SUV", "Tuner" }; //Menu 75
const char* HighEndWheels[20] = { "Shadow", "Hyper", "Blade", "Diamond", "Supa Gee", "Chromatic Z", "Mercie ch.Lip", "Obey RS", "GT Chrome", "Cheetah R", "Solar", "Split Ten", "Dash VIP", "LozspeedTen", "Carbon Inferno", "Carbon Shadow", "Carbon Z", "Cabon Solar", "Carbon Cheetah R", "Carbon S Racer" }; //Menu 76
const char* LowriderWheels[15] = { "Flare", "Wired", "Triple Golds", "Big Worm", "Seven Fives", "Split six", "Fresh Mesh", "Lead Sled", "Turbine", "Super Fin", "Classic Rod", "Dollar", "Dukes", "Low Five", "Gooch" }; //Menu 78
const char* MuscleWheels[18] = { "Classic Five", "Dukes", "Muscle Freak", "Kracka", "Azrea", "Mecha", "Black Top", "Drag SPL", "Revolver", "Classic Rod", "Fairle", "Spooner", "Five Star", "Old School", "El Jefe", "Dodman", "Six Gun", "Mercenary" }; //Menu 79

const char* OffroadWheels[10] = { "Raider", "Mudslinger", "Nevis", "Cairngorm", "Amazon", "Challenger", "Dune Basher", "Five Star", "Rock Clawler", "Mill Spec Steelie" }; //Menu 81
const char* SportWheels[25] = { "Inferno", "Deep Five", "Lozspeed Mk.V", "Diamond Cut", "Chrono", "Feroci RR", "FiftyNine", "Mercie", "Synthetic Z", "Organic Type D", "Endo v.1", "GT One", "Duper 7", "Uzer", "GroundRide", "S Racer", "Venum", "Cosmo", "Dash VIP", "Ice Kid", "Ruff Weld", "Wangen Master", "Super Five", "Endo v.2", "Slit Six" }; //Menu 82

const char* SUVWheels[19] = { "VIP", "Benefactor", "Cosmo", "Bippu", "Royal Six", "Fagorme", "Deluxe", "Iced Out", "Cognoscenti", "LozSpeed Ten", "Supernova", "Obey RS", "LozSpeed Baller", "Extravagano", "Split Six", "Empowered", "Sunrise", "Dash VIP", "Cutter" }; //Menu 84

const char* TunerWheels[23] = { "Cosmo", "Super Mesh", "eXoOutsider", "Rollas", "Driftmeister", "Slicer", "El Quatro", "Dubbed", "Five Star", "Slideways", "Apex", "Stanced EG", "Countersteer", "Endo v.2", "Gruppe Z", "Choku-Dori", "Chicane", "Saisoku", "Dished Eight", "Fujiwara", "Zokusha", "Battle VIII", "Rally Master" }; //Menu 86

const char* ModShopBodyColors[2] = { "Primary", "Secondary" }; //Menu 88
const char* ModShopBodyDoors[7] = { "Open all doors", "Open driver door", "Open passenger door", "Open rear driver door", "Open rear passenger door", "Pop open hood", "Delete doors" }; //Menu 89
const char* AccountCash[5] = { "+ $100k", "+ $1 million", "+ $10 million", "+ $25 million", "Add custom" }; //Menu 90
const char* AccountRP[5] = { "Set level 120", "Set level 1000", "Set level 5000", "Set level 8000", "Custom input" }; //Menu 91
const char* TeleportLocations[3] = { "Inside", "Outside", "IPL Locations" }; //Menu 92

const char* HeadComponent[2] = { "Head", "Head Texture" };
const char* FaceComponent[2] = { "Face", "Face Texture" };
const char* HairComponent[2] = { "Hair", "Hair Texture" };
const char* ShirtComponent[2] = { "Shirt", "Shirt Texture" };
const char* PantsComponent[2] = { "Pants", "Pants Texture" };
const char* GadgetComponent[2] = { "Gadget", "Gadget Texture" };
const char* FeetComponent[2] = { "Feet", "Feet Texture" };
const char* AccessoriesComponent[2] = { "Accessory", "Accessory Texture" };
const char* UndershirtComponent[2] = { "Undershirt", "Undershirt Texture" };
const char* ArmourComponent[2] = { "Armour", "Armour Texture" };
const char* LogoComponent[2] = { "Logo", "Logo Texture" };
const char* JacketComponent[2] = { "Jacket", "Jacket Texture" };

const char* PedManager[10] = { "Randomize appearance", "Teleport to me", "Give a weapon", "Set as a guard", "Drive me to waypoint", "Clone", "Soul Switch", "Delete", "Kill", "Revive" };
const char* WeaponsMain[8] = { "Give a weapon", "Give all weapons", "Take all weapons", "Teleport gun", "Money gun", "One shot one kill", "Unlimited ammo", "Gravity gun" };
const char* WeaponsList[9] = { "Melee", "Handguns", "Submachine Guns", "Assault Rifles", "Light Machine Guns", "Shotguns", "Snipers", "Heavy", "Throwables" };
const char* Melee[9] = { "Baseball bat", "Knife", "Nightstick", "Crowbar", "Golf club", "Hammer", "Broken bottle", "Cavalry dagger", "Knuckle Duster" };
const char* Handguns[10] = { "Pistol", "Combat Pistol", "AP Pistol", "Stun gun", ".50 cal pistol", "SNS pistol", "Heavy pistol", "Vintage pistol", "Flare gun", "Marksman pistol" };
const char* SMGs[5] = { "Micro SMG", "SMG (MP5)", "Assault SMG", "Gusenberg", "PDW" };
const char* Shotguns[5] = { "Pump action", "Sawed-off", "Assault", "Bullpup", "Heavy" };
const char* ARs[5] = { "Assault Rifle", "Carbine", "Advanced Rifle", "Special Carbine", "Bullpup" };
const char* LMGs[2] = { "MG", "Combat MG" };
const char* Snipers[3] = { "Sniper Rifle", "Heavy Sniper", "Marksman Rifle" };
const char* Heavy[5] = { "RPG", "Grenade Launcher", "Minigun", "Firework Launcher", "Homing Launcher" };
const char* Throwables[7] = { "Sticky bomb", "Grenade", "Tear gas", "Molotov", "Proximity Mine", "Snowball", "Flare" };
const char* NameMenu[3] = { "Change name", "Colors", "Rockstar Logo" };

const char* PresetAnimations[8] = { "Fuck air", "Get fucked", "Go nuts", "Push ups", "Sit ups", "Give BJ", "Taze", "Pole dance" }; //Menu 24
const char* CustomRGB[3] = { "Red", "Green", "Blue" };

const char* MenuColors[4] = { "Menu Item", "Red", "Green", "Blue" };
const char* MenuFont[2] = { "Menu Item", "Font" };

const char* Inventory[4] = { "Unlimited snacks", "Stock up on ammo", "Unlimited Fireworks", "Unlimited Armour" };
const char* Skills[9] = { "Max all", "Max Stamina", "Max Strength", "Max Shooting", "Max Stealth", "Max Lung Capacity", "Max Driving", "Max Flying", "Reset All" };
const char* KDEditor[3] = { "Kills", "Death", "Set" };
const char* WinsLosses[4] = { "Car Races", "Sea Races", "Team Deathmatch", "Deathmatch" };
const char* WinLossTemplate[3] = { "Wins", "Losses", "Set" };
const char* RideableAnimals[4] = { "Spawn Deer", "Get on", "Get off", "Delete animal" };
const char* Goodies[5] = { "Health", "Armour", "Snacks", "Weapons", "Ammo" };
const char* TextMessages[6] = { "NextGenUpdate", "Tesseract by Tustin", "Fake Rockstar Message", "Stop asking for money!", "Sing for cash", "Custom Message" };

const char* AttachCustomObject[9] = { "Select Prop", "Body", "Head", "Pelvis", "Left Arm", "Right Arm", "Left Foot", "Right Foot", "Attach Object" };
#pragma endregion