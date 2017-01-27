#include <string.h>

#include <sys/ppu_thread.h>
#include <sys/process.h>
#include <sys/memory.h>
#include <sys/timer.h>
#include <sys/prx.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <cell/cell_fs.h>

#include <cellstatus.h>

#include "dialog.h"
#include "models.h"
#include "timecycles.h"
#include "natives.h"
#include "exports.h"

#include "ps3.h"
#include "implementations.h"
#include "functions.h"
#include "animations.h"
#include "teleports.h"

SYS_MODULE_INFO( Tesseract, 0, 1, 1);
SYS_MODULE_START( _Tesseract_prx_entry );

SYS_LIB_DECLARE_WITH_STUB( LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME );
SYS_LIB_EXPORT( _Tesseract_export_function, LIBNAME );
void constants()
{
	_ID = PLAYER_PED_ID();
	//sets Tesseract menu id
	SET_PLAYER_MAX_ARMOUR(PLAYER_ID(), 69);
	if (Speedo)
		Speedometer();
	if (kingmaker)
		TheMaster();
	if (CashSpamAll)
		AllPlayersCash();
	if (spamcashonme)
		DropCashOnMe();
	if (cashdropmonitor)
		DropCashOnClient();
	if (SuperMan)
		SuperManHax();
	if (tracer)
		ESPLines();
	if (superjump)
		SuperJump();
	if (explosiveammo)
		ExplosiveAmmo();
	if (fireammo)
		FireAmmo();
	if (explosivemelee)
		ExplosiveMelee();
	if (nos)
		Nitrous();
	if (nfs)
		NeedForSpeed();
	if (shootvehweapons)
		ShootVehicleWeapon();
	if (carjump)
		CarJumper();
	if (forcefield)
		Forcefield();
	if (neons)
		RunNeons();
	if (dw || da)
		DriveOnWater();
	if (chatheads)
		ChatHeads();
	if (isfirstperson)
		MoveFirstPerson();
	if (noclip)
		MoveNoClip();
	if (superun)
		SuperRun();
	if (teleportgun)
		TeleportGun();
	if (GodModePlayer)
		GodMode();
	if (Wanted)
		NeverWanted();
	if (rainbowneons)
		RainbowNeons();
	if (InfAmmo)
		Ammo();
	if (veh_invincible)
		vehicle_invincible();
	if (veh_invisible)
		vehicle_invisible(true);
	if (rainbow_name)
		name_color_cycle();
	if (shoot_monies_toggle)
		shoot_money();
	if (grav_gun)
		set_gravity_gun();
	if (osok)
		SET_PLAYER_WEAPON_DAMAGE_MODIFIER(PLAYER_ID(), 999);
	if (seatbelt)
	{
		SET_PED_CONFIG_FLAG(PLAYER_PED_ID(), PED_FLAG_CAN_FLY_THRU_WINDSCREEN, false);
		SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER_PED_ID(), false);
	}

	ESPClient();
	TrollPlayer();
	monitor_guards();
	explosive_bullets_clients_listener();
	freeze_in_place();

	if (IS_PED_IN_ANY_VEHICLE(_ID, 1), 1)
		SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME((float)density_mul);


	if (!cm_loaded)
		if (LoadTexture("CommonMenu") && LoadTexture("timerbars"))
			cm_loaded = true;

#pragma region request loops
	if (spawn_veh)
		if (CreateVehicle(veh_hash))
			spawn_veh = false;

	if (bat_loop)
	{
		if (CreateBatmobile())
			bat_loop = false;
	}
	if (bus_loop)
	{
		if (SpawnBus())
			bus_loop = false;
	}
	if (chauf_loop)
		if (SpawnChauffeur())
			chauf_loop = false;

	if (client_guard)
		if (CreateClientGuard(client_guard_hash))
			client_guard = false;

	if (guard_loop)
		if (CreateBodyguard(guard_hash, guard_name))
			guard_loop = false;

	if (model_loop)
		if (create_player_model(player_model_hash))
			model_loop = false;

	if (play_anim)
		if (RequestAnim(AnimDict, Anim))
			play_anim = false;

	if (play_anim_for_ped)
		if (PlayAnimForPed())
			play_anim_for_ped = false;

	if (swatplayer)
		if (CreateSWAT())
			swatplayer = false;

	if (chopattack)
		if (CreateChops())
			chopattack = false;

	if (spawn_veh_return)
		if (CreateVehicleGetReturn(veh_hash, vehicle_spawn_position))
			spawn_veh_return = false;
	if (request_clipset)
		if (load_clipset())
			request_clipset = false;

	if (pm_waypoint_toggle)
		if (pm_drive_to_waypoint())
			pm_waypoint_toggle = false;

	if (spawn_object)
		if (CreateObject())
			spawn_object = false;

	if (spawn_object_get_return)
		if (CreateReturnObject())
			spawn_object_get_return = false;

	if (drive_on_wheel)
		if (SpawnFerrisWheel())
			drive_on_wheel = false;

	if (spawn_and_attach_object_loop)
		if (SpawnAndAttachObject())
			spawn_and_attach_object_loop = false;

	//if (NETWORK_IS_IN_SESSION())
	//	global_write(2394218 + 2811, 0x1FD824AF);
#pragma endregion

	if (armour_regen)
		ArmourRegen();
	if (health_regen)
		HealthRegen();
	if (freeze_protection)
		FreezeProtection();
	if (_keyboard)
		ShowKeyboard();
	if (ped_manager)
		monitor_manager();
	if (restricted_areas)
		RemoveRestrictions();
	if (GET_ENTITY_MODEL(GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 0)) == GET_HASH_KEY("jb700"))
	{
		if (GET_VEHICLE_NUMBER_PLATE_TEXT(GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 1)) != "BOND")
			SET_VEHICLE_NUMBER_PLATE_TEXT(GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 1), "BOND");
		jb700_spikes();
		jb700_shoot();
		jb700_eject();
		jb700_spikes_listener();
	}

	if (has_switched)
		pm_ss_monitor();
#pragma region components
	if (WhichMenu >= 106 && WhichMenu <= 117) {
		max_drawable = GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER_PED_ID(), cur_component) - 1;
		cur_drawable = GET_PED_DRAWABLE_VARIATION(PLAYER_PED_ID(), cur_component);

		max_texture = GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER_PED_ID(), cur_component, cur_drawable) - 1;
		cur_texture = GET_PED_TEXTURE_VARIATION(PLAYER_PED_ID(), cur_component);
	}
#pragma endregion
}
void functions()
{
	if (Open)
	{
		if (teleport)
			Teleport(telex, teley, telez);
		if (rockstartoggle)
			RockstarLogo();
		if (kickguardfromgroup)
			KickGuardFromGroup();
		if (randomvehicle)
			RandomVehicle();

		if (deletedoors)
			delete_all_doors(PLAYER_PED_ID());
		if (wheels)
		{
			set_vehicle_wheels(wheeltype, wheelindex);
			wheels = false;
		}

		DisableControls();

		if (showlobbyinfo)
			GetLobbyInfo();

		PlayerMonitor();
	}
	ReturnKeyboard();
}
void render_menu()
{
	game_ticks = GET_GAME_TIMER();
	//console_write(Format("%i\n", game_ticks));
	if (Open)
	{
		if (itemsOnPage > 20)
		{
			height = (((float)22) * 0.026094) + 0.030943;
			DrawSprite("CommonMenu", "shop_arrows_upANDdown", 0.836826, 0.833398, 0.031250, 0.046719, 0, 255, 255, 255);
			DrawItemCount(Scroll + 1, itemsOnPage, 0.939736, 0.823438, 0.35);
		}

		else
			height = (((float)itemsOnPage) * 0.026094) + 0.030943;
		if (!NETWORK_IS_IN_SESSION())
		{
			DRAW_RECT(0.840576, 0.248187 + (height * 0.5), 0.249766, height, MenuColorSelectedItem[1][0], MenuColorSelectedItem[1][1], MenuColorSelectedItem[1][2], 60); //background
			DrawSprite("CommonMenu", "gradient_nav", 0.840576, 0.218187, 0.249766, 0.062500, 0, MenuColorSelectedItem[0][0], MenuColorSelectedItem[0][1], MenuColorSelectedItem[0][2]);
			//DrawSprite("CommonMenu", "header_gradient_script", 0.840576, 0.218187, 0.249766, 0.062500, 0, 0, 0, 0);


			//DRAW_RECT(0.840576, 0.218187, 0.249766, 0.062500, MenuColorSelectedItem[0][0], MenuColorSelectedItem[0][1], MenuColorSelectedItem[0][2], 90); //header

			//0.028708
			if (Scroll > 20)
				DRAW_RECT(0.840088, 0.274141 + (20 * 0.026094), 0.249023, 0.025708, MenuColorSelectedItem[2][0], MenuColorSelectedItem[2][1], MenuColorSelectedItem[2][2], 80); //Scrollbar
			else
				DRAW_RECT(0.840088, 0.274141 + (Scroll * 0.026094), 0.249023, 0.025708, MenuColorSelectedItem[2][0], MenuColorSelectedItem[2][1], MenuColorSelectedItem[2][2], 80); //Scrollbar
		}
		else {
			DRAW_RECT(0.840576, 0.248187 + (height * 0.5), 0.249766, height, MenuColorSelectedItem[1][0], MenuColorSelectedItem[1][1], MenuColorSelectedItem[1][2], 120); //background
			DrawSprite("CommonMenu", "gradient_nav", 0.840576, 0.218187, 0.249766, 0.062500, 0, MenuColorSelectedItem[0][0], MenuColorSelectedItem[0][1], MenuColorSelectedItem[0][2]);
			//DrawSprite("CommonMenu", "header_gradient_script", 0.840576, 0.218187, 0.249766, 0.062500, 0, 0, 0, 0);
			//DRAW_RECT(0.840576, 0.218187, 0.249766, 0.062500, MenuColorSelectedItem[0][0], MenuColorSelectedItem[0][1], MenuColorSelectedItem[0][2], 180); //header
			if (Scroll > 20)
				DRAW_RECT(0.840088, 0.274141 + (20 * 0.026094), 0.249023, 0.028708, MenuColorSelectedItem[2][0], MenuColorSelectedItem[2][1], MenuColorSelectedItem[2][2], 160); //Scrollbar
			else
				DRAW_RECT(0.840088, 0.274141 + (Scroll * 0.026094), 0.249023, 0.028708, MenuColorSelectedItem[2][0], MenuColorSelectedItem[2][1], MenuColorSelectedItem[2][2], 160); //Scrollbar
		}
		MenuToggles();
		switch (WhichMenu)
		{
		case 1:
			DrawMenuTitleText("The Sexyract");
			LoadMenuItems(Main, 14);
			switch (Scroll)
			{
			case 13:
				setup_instructions();
				add_instruction(0, "Close Menu", BUTTON_A);
				add_instruction(1, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			default:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Close Menu", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 2:
			DrawMenuTitleText("Player Options");
			LoadMenuItems(Self, 16);
			switch (Scroll)
			{
			case 0:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 1:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 2:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 3:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			default:
				setup_instructions();
				add_instruction(0, "Select", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 3:
			DrawMenuTitleText("Account");
			LoadMenuItems(Account, 12);
			switch (Scroll)
			{
			case 0:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 1:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 2:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 3:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 10:
				setup_instructions();
				add_instruction(0, "Select", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			default:
				setup_instructions();
				add_instruction(0, "Select", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 4:
			DrawMenuTitleText("Vehicle Options");
			LoadMenuItems(VehicleMenu, 24);
			switch (Scroll)
			{
			case 0:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 1:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 2:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 3:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			default:
				setup_instructions();
				add_instruction(0, "Select", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 5:
			if (showplayerstats && model_client_guard && NETWORK_IS_PLAYER_ACTIVE(SelectedClient))
				GrabStats(SelectedClient);
			DrawMenuTitleText("Player Models");
			LoadMenuItems(Models, 13);

			setup_instructions();
			add_instruction(0, "Select Menu", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 7:
			DrawMenuTitleText("Object Spawner");
			LoadMenuItems(ObjectsMenu, 13);
			switch (Scroll)
			{
			case 0:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 1:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 12:
				setup_instructions();
				add_instruction(0, "Open Keyboard", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			default:
				setup_instructions();
				add_instruction(0, "Spawn Object", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 8:
			DrawMenuTitleText("Weather and Time");
			LoadMenuItems(WeatherOptions, 16);
			switch (Scroll)
			{
			case 15:
			case 14:
			case 13:
				setup_instructions();
				add_instruction(0, "Change Time", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			default:
				setup_instructions();
				add_instruction(0, "Set Weather", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 9:
			DrawMenuTitleText("Tunables Editor");
			LoadMenuItems(Tunables, 6);
			setup_instructions();
			add_instruction(0, "Set Tunable", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 10:
			DrawMenuTitleText("Appearance");
			LoadMenuItems(PedComponents, 14);
			switch (Scroll)
			{
			case 0:
			case 1:
				setup_instructions();
				add_instruction(0, "Select", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			default:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 11:
			if (showplayerstats && spawnforclient && NETWORK_IS_PLAYER_ACTIVE(SelectedClient))
				GrabStats(SelectedClient);
			DrawMenuTitleText("Vehicle Classes");
			LoadMenuItems(VehicleList, 23);
			switch (Scroll)
			{
			case 18:
				setup_instructions();
				add_instruction(0, "Select", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 22:
			case 21:
			case 20:
				setup_instructions();
				add_instruction(0, "Toggle Option", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 19:
				setup_instructions();
				add_instruction(0, "Open Keyboard", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			default:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 12:
			DrawMenuTitleText("Super Vehicles");
			LoadMenuItems(SuperVehicles, 9);
			setup_instructions();
			add_instruction(0, "Spawn Vehicle", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 13:
			DrawMenuTitleText("Sports Vehicles");
			LoadMenuItems(SportsVehicles, 12);
			setup_instructions();
			add_instruction(0, "Spawn Vehicle", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 14:
			DrawMenuTitleText("Classic Vehicles");
			LoadMenuItems(ClassicVehicles, 6);
			setup_instructions();
			add_instruction(0, "Spawn Vehicle", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 15:
			DrawMenuTitleText("Muscle Vehicles");
			LoadMenuItems(MuscleVehicles, 10);
			setup_instructions();
			add_instruction(0, "Spawn Vehicle", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 16:
			DrawMenuTitleText("Compact Vehicles");
			LoadMenuItems(CompactVehicles, 5);
			setup_instructions();
			add_instruction(0, "Spawn Vehicle", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 17:
			DrawMenuTitleText("Military Vehicles");
			LoadMenuItems(MilitaryVehicles, 4);
			setup_instructions();
			add_instruction(0, "Spawn Vehicle", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 18:
			DrawMenuTitleText("Fun Vehicles");
			LoadMenuItems(FunVehicles, 8);
			setup_instructions();
			add_instruction(0, "Spawn Vehicle", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 19:
			DrawMenuTitleText("DLC Vehicles");
			LoadMenuItems(DLCVehicles, 17);
			setup_instructions();
			add_instruction(0, "Spawn Vehicle", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 20:
			DrawMenuTitleText("Favorite Vehicles");
			LoadMenuItems(FavoriteVehicles, 11);
			setup_instructions();
			add_instruction(0, "Spawn Vehicle", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 21:
			if (showplayerstats && NETWORK_IS_PLAYER_ACTIVE(Scroll))
				GrabStats(Scroll);
			DrawMenuTitleText("Players Menu");
			LoadPlayers();
			setup_instructions();
			add_instruction(0, "Select Player", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 23:
			if (showplayerstats && NETWORK_IS_PLAYER_ACTIVE(SelectedClient))
				GrabStats(SelectedClient);
			DrawMenuTitleText(GET_PLAYER_NAME(SelectedClient));
			LoadMenuItems(PlayerMain, 7);
			setup_instructions();
			add_instruction(0, "Select Menu", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 24:
			DrawMenuTitleText("Animation Options");
			LoadMenuItems(AnimationOptions, 5);
			switch (Scroll)
			{
			case 4:
				setup_instructions();
				add_instruction(0, "Select", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			default:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 25:
			DrawMenuTitleText("Teleports");
			LoadMenuItems(TeleportOptions, 4);
			switch (Scroll)
			{
			case 3:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			default:
				setup_instructions();
				add_instruction(0, "Teleport", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 27:
			DrawMenuTitleText("Object Editor");
			LoadMenuItems(ObjectEditor, 10);
			switch (Scroll)
			{
			case 1:
				setup_instructions();
				add_instruction(0, "Change Precision", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 2:
			case 3:
			case 4:
				setup_instructions();
				add_instruction(0, "Move Object", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 5:
			case 6:
			case 7:
				setup_instructions();
				add_instruction(0, "Rotate Object", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			default:
				setup_instructions();
				add_instruction(0, "Select", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 28:
			DrawMenuTitleText("All Players");
			LoadMenuItems(AllPlayersMenu, 7);
			setup_instructions();
			add_instruction(0, "Select", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 29:
			DrawMenuTitleText("Guard Options");
			LoadMenuItems(BodyguardMenu, 7);
			switch (Scroll)
			{
			case 0:
			case 1:
			case 2:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			default:
				setup_instructions();
				add_instruction(0, "Select", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 31:
			DrawMenuTitleText(peds[selectedped].name);
			LoadMenuItems(PedOptions, 7);
			switch (Scroll)
			{
			default:
				setup_instructions();
				add_instruction(0, "Select", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 1:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 32:
			DrawMenuTitleText("Menu Settings");
			LoadMenuItems(MenuSettings, 6);
			switch (Scroll)
			{
			case 0:
			case 1:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			default:
				setup_instructions();
				add_instruction(0, "Toggle", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 33:
			DrawMenuTitleText("Spawned Peds");
			LoadPeds();
			setup_instructions();
			add_instruction(0, "Select Ped", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 34:
			DrawMenuTitleText("Heist Vehicles");
			LoadMenuItems(HeistVehicles, 14);
			setup_instructions();
			add_instruction(0, "Spawn Vehicle", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 36:
			DrawMenuTitleText("Mod Shop");
			LoadMenuItems(ModShopMain, 11);
			switch (Scroll)
			{
			case 7:
			case 10:
				setup_instructions();
				add_instruction(0, "Select Vehicle Mod", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 0:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			default:
				setup_instructions();
				add_instruction(0, "Change Vehicle Mod", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 37:
			DrawMenuTitleText("Vehicle Livery");
			LoadLiveries();
			setup_instructions();
			add_instruction(0, "Set Livery", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 43:
			DrawMenuTitleText("Network");
			LoadMenuItems(Network, 5);
			switch (Scroll)
			{
			case 0:
			case 1:
			case 2:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			default:
				setup_instructions();
				add_instruction(0, "Select", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 46:
			DrawMenuTitleText("Body Modifications");
			LoadMenuItems(ModShopBodyMain, 11);
			switch (Scroll)
			{
			case 9:
			case 10:
			case 11:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			default:
				setup_instructions();
				add_instruction(0, "Change Vehicle Mod", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 52:
			DrawMenuTitleText("Object Manager");
			LoadObjects();
			setup_instructions();
			add_instruction(0, "Select Object", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 54:
			DrawMenuTitleText("Emergency Vehicles");
			LoadMenuItems(EmergencyVehicles, 8);
			setup_instructions();
			add_instruction(0, "Spawn Vehicle", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 55:
			DrawMenuTitleText("Vision Options");
			LoadMenuItems(Visions, 2);
			switch (Scroll)
			{
			case 0:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 1:
				setup_instructions();
				add_instruction(0, "Clear Visions", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 56:
			DrawMenuTitleText("Vehicle Multipliers");
			LoadMenuItems(VehicleMultipliers, 4);
			setup_instructions();
			add_instruction(0, "Change Multiplier", BUTTON_DPAD_LEFT_RIGHT);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 57:
			DrawMenuTitleText("Neons");
			LoadMenuItems(Neons, 8);
			switch (Scroll)
			{
			case 0:
			case 7:
				setup_instructions();
				add_instruction(0, "Toggle", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			default:
				setup_instructions();
				add_instruction(0, "Select Color", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 58:
			DrawMenuTitleText("Vehicle Weapons");
			LoadMenuItems(VehicleWeapons, 6);
			switch (Scroll)
			{
			case 0:
				setup_instructions();
				add_instruction(0, "Toggle", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			default:
				setup_instructions();
				add_instruction(0, "Select Weapon", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 60:
			DrawMenuTitleText("IPL Loader");
			LoadMenuItems(MapMods, 8);
			setup_instructions();
			add_instruction(0, "Toggle IPL", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 61:
			DrawMenuTitleText("Cheats");
			LoadMenuItems(Cheats, 8);
			switch (Scroll)
			{
			default:
				setup_instructions();
				add_instruction(0, "Toggle Cheat", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 7:
				setup_instructions();
				add_instruction(0, "Change Timescale", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 63:
			DrawMenuTitleText("Sedans");
			LoadMenuItems(SedanVehicles, 9);
			setup_instructions();
			add_instruction(0, "Spawn Vehicle", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 64:
			DrawMenuTitleText("Off-Road");
			LoadMenuItems(OffRoadVehicles, 10);
			setup_instructions();
			add_instruction(0, "Spawn Vehicle", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 65:
			DrawMenuTitleText("SUVs");
			LoadMenuItems(SUVVehicles, 7);
			setup_instructions();
			add_instruction(0, "Spawn Vehicle", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 66:
			DrawMenuTitleText("Helicopters");
			LoadMenuItems(Helicopters, 6);
			setup_instructions();
			add_instruction(0, "Spawn Vehicle", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 67:
			DrawMenuTitleText("Motorcycles");
			LoadMenuItems(Motorcycles, 12);
			setup_instructions();
			add_instruction(0, "Spawn Vehicle", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 68:
			DrawMenuTitleText("Planes");
			LoadMenuItems(Planes, 6);
			setup_instructions();
			add_instruction(0, "Spawn Vehicle", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 69:
			DrawMenuTitleText("Boats");
			LoadMenuItems(Boats, 7);
			setup_instructions();
			add_instruction(0, "Spawn Vehicle", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 70:
			if (showplayerstats && NETWORK_IS_PLAYER_ACTIVE(SelectedClient))
				GrabStats(SelectedClient);
			DrawMenuTitleText("Player Options");
			LoadMenuItems(PlayerOptions, 17);
			setup_instructions();
			add_instruction(0, "Select", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 71:
			if (showplayerstats && NETWORK_IS_PLAYER_ACTIVE(SelectedClient))
				GrabStats(SelectedClient);
			DrawMenuTitleText("Vehicle Options");
			LoadMenuItems(PlayerVehicleOptions, 11);
			setup_instructions();
			add_instruction(0, "Select", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 72:
			if (showplayerstats && NETWORK_IS_PLAYER_ACTIVE(SelectedClient))
				GrabStats(SelectedClient);
			DrawMenuTitleText("Attach Options");
			LoadMenuItems(PlayerAttachOptions, 5);
			setup_instructions();
			add_instruction(0, "Select", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 73:
			if (showplayerstats && NETWORK_IS_PLAYER_ACTIVE(SelectedClient))
				GrabStats(SelectedClient);
			DrawMenuTitleText("Attach Object");
			LoadMenuItems(PlayerObjectOptions, 5);
			switch (Scroll)
			{
			case 0:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			default:
				setup_instructions();
				add_instruction(0, "Attach Object", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 74:
			DrawMenuTitleText("Miscellaneous");
			LoadMenuItems(MiscOptions, 17);
			switch (Scroll)
			{
			case 0:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 3:
			case 4:
			case 5:
				setup_instructions();
				add_instruction(0, "Select", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			default:
				setup_instructions();
				add_instruction(0, "Toggle", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 75:
			DrawMenuTitleText("Rims");
			LoadMenuItems(Rims, 7);
			setup_instructions();
			add_instruction(0, "Choose Class", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 76:
			DrawMenuTitleText("High End");
			LoadMenuItems(HighEndWheels, 20);
			setup_instructions();
			add_instruction(0, "Select Rims", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 78:
			DrawMenuTitleText("Lowrider");
			LoadMenuItems(LowriderWheels, 15);
			setup_instructions();
			add_instruction(0, "Select Rims", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 79:
			DrawMenuTitleText("Muscle");
			LoadMenuItems(MuscleWheels, 18);
			setup_instructions();
			add_instruction(0, "Select Rims", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 81:
			DrawMenuTitleText("Off-road");
			LoadMenuItems(OffroadWheels, 9);
			setup_instructions();
			add_instruction(0, "Select Rims", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 82:
			DrawMenuTitleText("Sport");
			LoadMenuItems(SportWheels, 25);
			setup_instructions();
			add_instruction(0, "Select Rims", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 84:
			DrawMenuTitleText("SUV");
			LoadMenuItems(SUVWheels, 19);
			setup_instructions();
			add_instruction(0, "Select Rims", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 86:
			DrawMenuTitleText("Tuner");
			LoadMenuItems(TunerWheels, 23);
			setup_instructions();
			add_instruction(0, "Select Rims", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 88:
			DrawMenuTitleText("Vehicle Color Type");
			LoadMenuItems(ModShopBodyColors, 2);
			setup_instructions();
			add_instruction(0, "Select Menu", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 89:
			DrawMenuTitleText("Door Options");
			LoadMenuItems(ModShopBodyDoors, 7);
			setup_instructions();
			add_instruction(0, "Select", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 90:
			DrawMenuTitleText("Cash Editor");
			LoadMenuItems(AccountCash, 5);
			switch (Scroll)
			{
			case 0:
			case 1:
			case 2:
			case 3:
				setup_instructions();
				add_instruction(0, "Add Cash", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 4:
				setup_instructions();
				add_instruction(0, "Open Keyboard", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 91:
			DrawMenuTitleText("RP Editor");
			LoadMenuItems(AccountRP, 5);
			switch (Scroll)
			{
			default:
				setup_instructions();
				add_instruction(0, "Set Level", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 4:
				setup_instructions();
				add_instruction(0, "Open Keyboard", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 92:
			DrawMenuTitleText("Locations");
			LoadMenuItems(TeleportLocations, 3);
			setup_instructions();
			add_instruction(0, "Select Menu", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 93:
			DrawMenuTitleText("Main Characters");
			LoadMenuItems(MainCharactersDisplay, 3);
			setup_instructions();
			add_instruction(0, "Choose Model", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 94:
			DrawMenuTitleText("Animals");
			LoadMenuItems(AnimalsDisplay, 22);
			setup_instructions();
			add_instruction(0, "Choose Model", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 95:
			DrawMenuTitleText("Ambient Female");
			LoadMenuItems(AmbientFemalesDisplay, 69);
			setup_instructions();
			add_instruction(0, "Choose Model", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 96:
			DrawMenuTitleText("Ambient Male");
			LoadMenuItems(AmbientMaleDisplay, 168);
			setup_instructions();
			add_instruction(0, "Choose Model", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 97:
			DrawMenuTitleText("Cutscene");
			LoadMenuItems(CutsceneDisplay, 41);
			setup_instructions();
			add_instruction(0, "Choose Model", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 98:
			DrawMenuTitleText("Female Gang Members");
			LoadMenuItems(GangFemaleDisplay, 4);
			setup_instructions();
			add_instruction(0, "Choose Model", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 99:
			DrawMenuTitleText("Male Gang Members");
			LoadMenuItems(GangMaleDisplay, 37);
			setup_instructions();
			add_instruction(0, "Choose Model", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 100:
			DrawMenuTitleText("Story Characters");
			LoadMenuItems(StoryDisplay, 96);
			setup_instructions();
			add_instruction(0, "Choose Model", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 101:
			DrawMenuTitleText("Multiplayer Characters");
			LoadMenuItems(MultiplayerDisplay, 15);
			setup_instructions();
			add_instruction(0, "Choose Model", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 102:
			DrawMenuTitleText("Scenario Female");
			LoadMenuItems(ScenarioFemaleDisplay, 23);
			setup_instructions();
			add_instruction(0, "Choose Model", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 103:
			DrawMenuTitleText("Scenario Male");
			LoadMenuItems(ScenarioMaleDisplay, 91);
			setup_instructions();
			add_instruction(0, "Choose Model", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 104:
			DrawMenuTitleText("Story Scenario Female");
			LoadMenuItems(StoryScenarioFemaleDisplay, 15);
			setup_instructions();
			add_instruction(0, "Choose Model", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 105:
			DrawMenuTitleText("Story Scenario Male");
			LoadMenuItems(StoryScenarioMaleDisplay, 45);
			setup_instructions();
			add_instruction(0, "Choose Model", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 106:
			DrawMenuTitleText("Head");
			LoadMenuItems(HeadComponent, 2);
			switch (Scroll)
			{
			case 0:
				setup_instructions();
				add_instruction(0, "Change Component", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 1:
				setup_instructions();
				add_instruction(0, "Change Texture", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 107:
			DrawMenuTitleText("Face");
			LoadMenuItems(FaceComponent, 2);
			switch (Scroll)
			{
			case 0:
				setup_instructions();
				add_instruction(0, "Change Component", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 1:
				setup_instructions();
				add_instruction(0, "Change Texture", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 108:
			DrawMenuTitleText("Hair");
			LoadMenuItems(HairComponent, 2);
			switch (Scroll)
			{
			case 0:
				setup_instructions();
				add_instruction(0, "Change Component", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 1:
				setup_instructions();
				add_instruction(0, "Change Texture", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 109:
			DrawMenuTitleText("Shirt");
			LoadMenuItems(ShirtComponent, 2);
			switch (Scroll)
			{
			case 0:
				setup_instructions();
				add_instruction(0, "Change Component", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 1:
				setup_instructions();
				add_instruction(0, "Change Texture", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 110:
			DrawMenuTitleText("Pants");
			LoadMenuItems(PantsComponent, 2);
			switch (Scroll)
			{
			case 0:
				setup_instructions();
				add_instruction(0, "Change Component", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 1:
				setup_instructions();
				add_instruction(0, "Change Texture", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 111:
			DrawMenuTitleText("Gadgets");
			LoadMenuItems(GadgetComponent, 2);
			switch (Scroll)
			{
			case 0:
				setup_instructions();
				add_instruction(0, "Change Component", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 1:
				setup_instructions();
				add_instruction(0, "Change Texture", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 112:
			DrawMenuTitleText("Feet");
			LoadMenuItems(FeetComponent, 2);
			switch (Scroll)
			{
			case 0:
				setup_instructions();
				add_instruction(0, "Change Component", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 1:
				setup_instructions();
				add_instruction(0, "Change Texture", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 113:
			DrawMenuTitleText("Accessories");
			LoadMenuItems(AccessoriesComponent, 2);
			switch (Scroll)
			{
			case 0:
				setup_instructions();
				add_instruction(0, "Change Component", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 1:
				setup_instructions();
				add_instruction(0, "Change Texture", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 114:
			DrawMenuTitleText("Undershirts");
			LoadMenuItems(UndershirtComponent, 2);
			switch (Scroll)
			{
			case 0:
				setup_instructions();
				add_instruction(0, "Change Component", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 1:
				setup_instructions();
				add_instruction(0, "Change Texture", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 115:
			DrawMenuTitleText("Armour");
			LoadMenuItems(ArmourComponent, 2);
			switch (Scroll)
			{
			case 0:
				setup_instructions();
				add_instruction(0, "Change Component", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 1:
				setup_instructions();
				add_instruction(0, "Change Texture", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 116:
			DrawMenuTitleText("Logos");
			LoadMenuItems(LogoComponent, 2);
			switch (Scroll)
			{
			case 0:
				setup_instructions();
				add_instruction(0, "Change Component", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 1:
				setup_instructions();
				add_instruction(0, "Change Texture", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 117:
			DrawMenuTitleText("Jackets");
			LoadMenuItems(JacketComponent, 2);
			switch (Scroll)
			{
			case 0:
				setup_instructions();
				add_instruction(0, "Change Component", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 1:
				setup_instructions();
				add_instruction(0, "Change Texture", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 118:
			DrawMenuTitleText("Visions");
			LoadMenuItems(Timecycles, 472);
			setup_instructions();
			add_instruction(0, "Set Vision", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 119:
			DrawMenuTitleText(Format("Ped Manager (%s)", IS_ENTITY_DEAD(pm_ent) ? "Dead" : "Alive"));
			LoadMenuItems(PedManager, 10);
			switch (Scroll)
			{
			default:
				setup_instructions();
				add_instruction(0, "Select", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 2:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 120:
			DrawMenuTitleText("Weapon Editor");
			LoadMenuItems(WeaponsMain, 8);
			switch (Scroll)
			{
			case 1:
			case 2:
				setup_instructions();
				add_instruction(0, "Select", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 0:
				setup_instructions();
				add_instruction(0, "Select Menu", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			default:
				setup_instructions();
				add_instruction(0, "Toggle", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 121:
			DrawMenuTitleText("Weapon Categories");
			LoadMenuItems(WeaponsList, 9);
			setup_instructions();
			add_instruction(0, "Select Weapon Category", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 122:
			DrawMenuTitleText("Melee");
			LoadMenuItems(Melee, 9);
			setup_instructions();
			add_instruction(0, "Select Weapon", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 123:
			DrawMenuTitleText("Handguns");
			LoadMenuItems(Handguns, 10);
			setup_instructions();
			add_instruction(0, "Select Weapon", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 124:
			DrawMenuTitleText("SMG");
			LoadMenuItems(SMGs, 5);
			setup_instructions();
			add_instruction(0, "Select Weapon", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 125:
			DrawMenuTitleText("Shotguns");
			LoadMenuItems(Shotguns, 5);
			setup_instructions();
			add_instruction(0, "Select Weapon", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 126:
			DrawMenuTitleText("Assault Rifles");
			LoadMenuItems(ARs, 5);
			setup_instructions();
			add_instruction(0, "Select Weapon", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 127:
			DrawMenuTitleText("LMG");
			LoadMenuItems(LMGs, 2);
			setup_instructions();
			add_instruction(0, "Select Weapon", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 128:
			DrawMenuTitleText("Snipers");
			LoadMenuItems(Snipers, 3);
			setup_instructions();
			add_instruction(0, "Select Weapon", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 129:
			DrawMenuTitleText("Heavy");
			LoadMenuItems(Heavy, 5);
			setup_instructions();
			add_instruction(0, "Select Weapon", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 130:
			DrawMenuTitleText("Throwables");
			LoadMenuItems(Throwables, 7);
			setup_instructions();
			add_instruction(0, "Select Weapon", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 131:
			DrawMenuTitleText("Name Editor");
			LoadMenuItems(NameMenu, 3);
			switch (Scroll)
			{
			case 0:
				setup_instructions();
				add_instruction(0, "Open Keyboard", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 1:
				setup_instructions();
				add_instruction(0, "Change Color", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Set Color", BUTTON_A);
				add_instruction(2, "Back", BUTTON_B);
				add_instruction(3, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 2:
				setup_instructions();
				add_instruction(0, "Set Logo", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			case 3:
				setup_instructions();
				add_instruction(0, "Select", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 132:
			DrawMenuTitleText("Preset Animations");
			LoadMenuItems(PresetAnimations, 8);
			setup_instructions();
			add_instruction(0, "Play Animation", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 133:
			DrawMenuTitleText("Movement Types");
			LoadMenuItems(Movements, 82);
			setup_instructions();
			add_instruction(0, "Set Movement Type", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 134:
			DrawMenuTitleText("Scenarios");
			LoadMenuItems(Scenarios, 110);
			setup_instructions();
			add_instruction(0, "Play Scenario", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 135:
			switch (color_type)
			{
			case 1:
				DrawMenuTitleText("Primary Colors");
				break;
			case 2:
				DrawMenuTitleText("Secondary Colors");
				break;
			default:
				DrawMenuTitleText("Vehicle Colors");
				break;
			}
			LoadMenuItems(Colors, 160);
			setup_instructions();
			add_instruction(0, "Select Color", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 136:
			DrawMenuTitleText("Vehicle RGB");
			LoadMenuItems(CustomRGB, 3);
			setup_instructions();
			add_instruction(0, "Set Custom Value", BUTTON_DPAD_LEFT_RIGHT);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 137:
			DrawMenuTitleText("Menu Colors");
			LoadMenuItems(MenuColors, 4);
			switch (Scroll)
			{
			case 0:
				setup_instructions();
				add_instruction(0, "Change Menu Item", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			default:
				setup_instructions();
				add_instruction(0, "Set Custom Value", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 138:
			DrawMenuTitleText("Menu Fonts");
			LoadMenuItems(MenuFont, 2);
			switch (Scroll)
			{
			case 0:
				setup_instructions();
				add_instruction(0, "Change Menu Item", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			default:
				setup_instructions();
				add_instruction(0, "Set Font", BUTTON_DPAD_LEFT_RIGHT);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				close_instructions();
				break;
			}
			break;
		case 139:
			DrawMenuTitleText("Inventory");
			LoadMenuItems(Inventory, 4);
			setup_instructions();
			add_instruction(0, "Select", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 140:
			DrawMenuTitleText("Skills");
			LoadMenuItems(Skills, 9);
			setup_instructions();
			add_instruction(0, "Set", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 141:
			DrawMenuTitleText("K/D Editor");
			LoadMenuItems(KDEditor, 3);
			break;
		case 142:
			DrawMenuTitleText("Car Races");
			LoadMenuItems(WinsLosses, 4);
			break;
		case 143:
			DrawMenuTitleText("Rideable Animals");
			LoadMenuItems(RideableAnimals, 4);
			break;
		case 144:
			if (showplayerstats && attach_custom_object && NETWORK_IS_PLAYER_ACTIVE(SelectedClient))
				GrabStats(SelectedClient);
			DrawMenuTitleText("All Props");
			LoadMenuItems(PropsRaw, 3284);
			setup_instructions();
			add_instruction(0, "Spawn Prop", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 145:
			DrawMenuTitleText("Inside Locations");
			LoadMenuItems(Inside, 17);
			setup_instructions();
			add_instruction(0, "Teleport", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 146:
			DrawMenuTitleText("Outside Locations");
			LoadMenuItems(Outside, 54);
			setup_instructions();
			add_instruction(0, "Teleport", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 147:
			DrawMenuTitleText("IPL Locations");
			LoadMenuItems(IPL_Locations, 6);
			setup_instructions();
			add_instruction(0, "Teleport", BUTTON_A);
			add_instruction(1, "Back", BUTTON_B);
			add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
			close_instructions();
			break;
		case 148:
			if (showplayerstats && NETWORK_IS_PLAYER_ACTIVE(SelectedClient))
				GrabStats(SelectedClient);
			DrawMenuTitleText("Goodies");
			LoadMenuItems(Goodies, 5);
			setup_instructions();
			switch (Scroll)
			{
			default:
				add_instruction(0, "Drop", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				break;
			case 5:
				add_instruction(0, "Toggle", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				break;
			}
			close_instructions();
			break;
		case 149:
			if (!text_all && showplayerstats && NETWORK_IS_PLAYER_ACTIVE(SelectedClient))
				GrabStats(SelectedClient);
			DrawMenuTitleText("Text Messages");
			LoadMenuItems(TextMessages, 6);
			setup_instructions();
			switch (Scroll)
			{
			default:
				add_instruction(0, "Send Text", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				break;
			case 5:
				add_instruction(0, "Open Keyboard", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				break;
			}
			close_instructions();
			break;
		case 150:
			if (showplayerstats && NETWORK_IS_PLAYER_ACTIVE(SelectedClient))
				GrabStats(SelectedClient);
			DrawMenuTitleText("Attach Custom Object");
			LoadMenuItems(AttachCustomObject, 9);
			setup_instructions();
			switch (Scroll)
			{
			case 0:
				add_instruction(0, "Select Object", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				break;
			case 8:
				add_instruction(0, "Attach Object", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				break;
			default:
				add_instruction(0, "Select Bone To Spawn On", BUTTON_A);
				add_instruction(1, "Back", BUTTON_B);
				add_instruction(2, "Scroll", BUTTON_DPAD_UP_DOWN);
				break;
			}
			close_instructions();
			break;
		}
	}
}
void monitor()
{
	if (Open)
	{
		if (get_key_just_pressed(203, 70))
		{
			Scroll++;
			switch (WhichMenu)
			{
			case 1: //Main menu
				if (Scroll == 14)
					Scroll = 0;
				break;
			case 2: //Main mods
				if (Scroll == 16)
					Scroll = 0;
				break;
			case 3: //Account menu
				if (Scroll == 12)
					Scroll = 0;
				break;
			case 4: //Vehicle menu
				if (Scroll == 24)
					Scroll = 0;
				break;
			case 5: //Model changer
				if (Scroll == 13)
					Scroll = 0;
				break;
			case 6: //Model changer 2/2
				if (Scroll == 14) {
					WhichMenu = 5;
					Scroll = 0;
				}
				break;
			case 7: //Objects menu
				if (Scroll == 13)
					Scroll = 0;
				break;
			case 8: //Weather menu
				if (Scroll == 16)
					Scroll = 0;
				break;
			case 9: //Tunables menu
				if (Scroll == 6)
					Scroll = 0;
				break;
			case 10: //Components menu
				if (Scroll == 14)
					Scroll = 0;
				break;
			case 11: //Vehicle Spawn List
				if (Scroll == 23)
					Scroll = 0;
				break;
			case 12: //Super vehicles
				if (Scroll == 9)
					Scroll = 0;
				break;
			case 13: //Sports vehicles
				if (Scroll == 12)
					Scroll = 0;
				break;
			case 14: //Classic vehicles
				if (Scroll == 6)
					Scroll = 0;
				break;
			case 15: //Muscle vehicles
				if (Scroll == 10)
					Scroll = 0;
				break;
			case 16: //Compact vehicles
				if (Scroll == 5)
					Scroll = 0;
				break;
			case 17: //Military vehicles
				if (Scroll == 4)
					Scroll = 0;
				break;
			case 18: //Fun vehicles
				if (Scroll == 8)
					Scroll = 0;
				break;
			case 19: //DLC vehicles
				if (Scroll == 17)
					Scroll = 0;
				break;
			case 20: //Favorite vehicles
				if (Scroll == 11)
					Scroll = 0;
				break;
			case 21: //Players menu
				if (Scroll == 16)
					Scroll = 0;
				break;
			case 22: //Dirty options
				if (Scroll == 13)
					Scroll = 0;
				break;
			case 23: //Player options
				if (Scroll == 7)
					Scroll = 0;
				break;
			case 24: //Animation options
				if (Scroll == 5)
					Scroll = 0;
				break;
			case 25: //Teleport options
				if (Scroll == 4)
					Scroll = 0;
				break;
			case 26: //Debug options
				if (Scroll == 10)
					Scroll = 0;
				break;
			case 27: //Object editor
				if (Scroll == 10)
					Scroll = 0;
				break;
			case 28: //All player options
				if (Scroll == 7)
					Scroll = 0;
				break;
			case 29: //Bodyguards menu
				if (Scroll == 7)
					Scroll = 0;
				break;
			case 30: //Bodyguards list
				if (Scroll == 14)
					Scroll = 0;
				break;
			case 31: //ped options
				if (Scroll == 7)
					Scroll = 0;
				break;
			case 32: //menu settings
				if (Scroll == 6)
					Scroll = 0;
				break;
			case 33: //spawned peds
				if (Scroll == 6)
					Scroll = 0;
				break;
			case 34: //heist cars
				if (Scroll == 14)
					Scroll = 0;
				break;
			case 35: //sprx loader
				if (Scroll == 5)
					Scroll = 0;
				break;
			case 36: //mod shop main
				if (Scroll == 11)
					Scroll = 0;
				break;
			case 37:
				Vehicle veh = GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 0);
				if (Scroll == GET_VEHICLE_LIVERY_COUNT(veh) + 1)
					Scroll = 0;
				break;
			case 38: //mod shop tranny
				if (Scroll == 4)
					Scroll = 0;
				break;
			case 39: //mod shop brakes
				if (Scroll == 4)
					Scroll = 0;
				break;
			case 40: //mod shop suspension
				if (Scroll == 5)
					Scroll = 0;
				break;
			case 41: //mod shop exhaust
				if (Scroll == 5)
					Scroll = 0;
				break;
			case 42: //mod shop armour
				if (Scroll == 6)
					Scroll = 0;
				break;
			case 43: //network
				if (Scroll == 5)
					Scroll = 0;
				break;
			case 44: //mod shop plates
				if (Scroll == 6)
					Scroll = 0;
				break;
			case 45: //mod shop tints
				if (Scroll == 5)
					Scroll = 0;
				break;
			case 46: //mod shop body main
				if (Scroll == 11)
					Scroll = 0;
				break;
			case 47: //mod shop body front bumper
				if (Scroll == 4)
					Scroll = 0;
				break;
			case 48: //mod shop body rear bumper
				if (Scroll == 4)
					Scroll = 0;
				break;
			case 49: //mod shop body spoiler
				if (Scroll == 4)
					Scroll = 0;
				break;
			case 50: //mod shop body side skirts
				if (Scroll == 4)
					Scroll = 0;
				break;
			case 51: //mod shop body hood
				if (Scroll == 6)
					Scroll = 0;
				break;
			case 52: //object manager 1/2
				if (Scroll == 30)
					Scroll = 0;
				break;
			case 53:
				break;
			case 54:
				if (Scroll == 8)
					Scroll = 0;
				break;
			case 55:
				if (Scroll == 2)
					Scroll = 0;
				break;
			case 56:
				if (Scroll == 4)
					Scroll = 0;
				break;
			case 57:
				if (Scroll == 8)
					Scroll = 0;
				break;
			case 58:
				if (Scroll == 6)
					Scroll = 0;
				break;
			case 59:
				if (Scroll == 14)
					Scroll = 0;
				break;
			case 60:
				if (Scroll == 8)
					Scroll = 0;
				break;
			case 61:
				if (Scroll == 8)
					Scroll = 0;
				break;
			case 62:
				break;
			case 63:
				if (Scroll == 9)
					Scroll = 0;
				break;
			case 64:
				if (Scroll == 10)
					Scroll = 0;
				break;
			case 65:
				if (Scroll == 7)
					Scroll = 0;
				break;
			case 66:
				if (Scroll == 6)
					Scroll = 0;
				break;
			case 67:
				if (Scroll == 12)
					Scroll = 0;
				break;
			case 68:
				if (Scroll == 6)
					Scroll = 0;
				break;
			case 69:
				if (Scroll == 7)
					Scroll = 0;
				break;
			case 70:
				if (Scroll == 17)
					Scroll = 0;
				break;
			case 71:
				if (Scroll == 11)
					Scroll = 0;
				break;
			case 72:
				if (Scroll == 5)
					Scroll = 0;
				break;
			case 73:
				if (Scroll == 5)
					Scroll = 0;
				break;
			case 74:
				if (Scroll == 17)
					Scroll = 0;
				break;
			case 75:
				if (Scroll == 7)
					Scroll = 0;
				break;
			case 76:
				if (Scroll == 20)
					Scroll = 0;
				break;
			case 77:
				break;
			case 78:
				if (Scroll == 15)
					Scroll = 0;
				break;
			case 79:
				if (Scroll == 18)
					Scroll = 0;
				break;
			case 80:
				break;
			case 81:
				if (Scroll == 9)
					Scroll = 0;
				break;
			case 82:
				if (Scroll == 25)
					Scroll = 0;
				break;
			case 83:
				break;
			case 84:
				if (Scroll == 19)
					Scroll = 0;
				break;
			case 85:
				break;
			case 86:
				if (Scroll == 23)
					Scroll = 0;
				break;
			case 87:
				break;
			case 88:
				if (Scroll == 2)
					Scroll = 0;
				break;
			case 89:
				if (Scroll == 7)
					Scroll = 0;
				break;
			case 90:
				if (Scroll == 5)
					Scroll = 0;
				break;
			case 91:
				if (Scroll == 5)
					Scroll = 0;
				break;
			case 92:
				if (Scroll == 3)
					Scroll = 0;
				break;
			case 93:
				if (Scroll == 3)
					Scroll = 0;
				break;
			case 94:
				if (Scroll == 22)
					Scroll = 0;
				break;
			case 95:
				if (Scroll == 69)
					Scroll = 0;
				break;
			case 96:
				if (Scroll == 168)
					Scroll = 0;
				break;
			case 97:
				if (Scroll == 41)
					Scroll = 0;
				break;
			case 98:
				if (Scroll == 4)
					Scroll = 0;
				break;
			case 99:
				if (Scroll == 37)
					Scroll = 0;
				break;
			case 100:
				if (Scroll == 96)
					Scroll = 0;
				break;
			case 101:
				if (Scroll == 15)
					Scroll = 0;
				break;
			case 102:
				if (Scroll == 23)
					Scroll = 0;
				break;
			case 103:
				if (Scroll == 91)
					Scroll = 0;
				break;
			case 104:
				if (Scroll == 15)
					Scroll = 0;
				break;
			case 105:
				if (Scroll == 45)
					Scroll = 0;
				break;
			case 106:
				if (Scroll == 2)
					Scroll = 0;
				break;
			case 107:
				if (Scroll == 2)
					Scroll = 0;
				break;
			case 108:
				if (Scroll == 2)
					Scroll = 0;
				break;
			case 109:
				if (Scroll == 2)
					Scroll = 0;
				break;
			case 110:
				if (Scroll == 2)
					Scroll = 0;
				break;
			case 111:
				if (Scroll == 2)
					Scroll = 0;
				break;
			case 112:
				if (Scroll == 2)
					Scroll = 0;
				break;
			case 113:
				if (Scroll == 2)
					Scroll = 0;
				break;
			case 114:
				if (Scroll == 2)
					Scroll = 0;
				break;
			case 115:
				if (Scroll == 2)
					Scroll = 0;
				break;
			case 116:
				if (Scroll == 2)
					Scroll = 0;
				break;
			case 117:
				if (Scroll == 2)
					Scroll = 0;
				break;
			case 118:
				if (Scroll == 472)
					Scroll = 0;
				break;
			case 119:
				if (Scroll == 10)
					Scroll = 0;
				break;
			case 120:
				if (Scroll == 8)
					Scroll = 0;
				break;
			case 121:
				if (Scroll == 9)
					Scroll = 0;
				break;
			case 122:
				if (Scroll == 9)
					Scroll = 0;
				break;
			case 123:
				if (Scroll == 10)
					Scroll = 0;
				break;
			case 124:
				if (Scroll == 5)
					Scroll = 0;
				break;
			case 125:
				if (Scroll == 5)
					Scroll = 0;
				break;
			case 126:
				if (Scroll == 5)
					Scroll = 0;
				break;
			case 127:
				if (Scroll == 2)
					Scroll = 0;
				break;
			case 128:
				if (Scroll == 3)
					Scroll = 0;
				break;
			case 129:
				if (Scroll == 5)
					Scroll = 0;
				break;
			case 130:
				if (Scroll == 7)
					Scroll = 0;
				break;
			case 131:
				if (Scroll == 3)
					Scroll = 0;
				break;
			case 132:
				if (Scroll == 8)
					Scroll = 0;
				break;
			case 133:
				if (Scroll == 82)
					Scroll = 0;
				break;
			case 134:
				if (Scroll == 110)
					Scroll = 0;
				break;
			case 135:
				if (Scroll == 160)
					Scroll = 0;
				break;
			case 136:
				if (Scroll == 3)
					Scroll = 0;
				break;
			case 137:
				if (Scroll == 4)
					Scroll = 0;
				break;
			case 138:
				if (Scroll == 2)
					Scroll = 0;
				break;
			case 139:
				if (Scroll == 4)
					Scroll = 0;
				break;
			case 140:
				if (Scroll == 9)
					Scroll = 0;
				break;
			case 141:
				if (Scroll == 3)
					Scroll = 0;
				break;
			case 142:
				if (Scroll == 3)
					Scroll = 0;
				break;
			case 143:
				if (Scroll == 4)
					Scroll = 0;
				break;
			case 144:
				if (Scroll == 3284)
					Scroll = 0;
				break;
			case 145:
				if (Scroll == 17)
					Scroll = 0;
				break;
			case 146:
				if (Scroll == 53)
					Scroll = 0;
				break;
			case 147:
				if (Scroll == 6)
					Scroll = 0;
				break;
			case 148:
				if (Scroll == 5)
					Scroll = 0;
				break;
			case 149:
				if (Scroll == 6)
					Scroll = 0;
				break;
			case 150:
				if (Scroll == 9)
					Scroll = 0;
				break;
			case 151:
				if (Scroll == 1324)
					Scroll = 0;
				break;
			}
			PlaySound("NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET");
		}
		if (get_key_just_pressed(202, 70))
		{
			Scroll--;
			switch (WhichMenu)
			{
			case 1: //Main menu
				if (Scroll == -1)
					Scroll = 13;
				break;
			case 2: //Main mods
				if (Scroll == -1)
					Scroll = 15;
				break;
			case 3: //Account menu
				if (Scroll == -1)
					Scroll = 11;
				break;
			case 4: //Vehicle menu
				if (Scroll == -1)
					Scroll = 23;
				break;
			case 5: //Model changer 
				if (Scroll == -1)
					Scroll = 12;
				break;
			case 6: //Model changer 2/2
				if (Scroll == -1) {
					WhichMenu = 5;
					Scroll = 13;
				}
				break;
			case 7: //Objects menu
				if (Scroll == -1)
					Scroll = 12;
				break;
			case 8: //Weather menu
				if (Scroll == -1)
					Scroll = 15;
				break;
			case 9: //Tunables menu
				if (Scroll == -1)
					Scroll = 5;
				break;
			case 10: //Components menu
				if (Scroll == -1)
					Scroll = 13;
				break;
			case 11: //Vehicle spawn menu
				if (Scroll == -1)
					Scroll = 22;
				break;
			case 12: //Super vehicles
				if (Scroll == -1)
					Scroll = 8;
				break;
			case 13: //Sports vehicles
				if (Scroll == -1)
					Scroll = 11;
				break;
			case 14: //Classic vehicles
				if (Scroll == -1)
					Scroll = 5;
				break;
			case 15: //Muscle vehicles
				if (Scroll == -1)
					Scroll = 9;
				break;
			case 16: //Compact vehicles
				if (Scroll == -1)
					Scroll = 4;
				break;
			case 17: //Military vehicles
				if (Scroll == -1)
					Scroll = 3;
				break;
			case 18: //Fun vehicles
				if (Scroll == -1)
					Scroll = 7;
				break;
			case 19: //DLC vehicles
				if (Scroll == -1)
					Scroll = 16;
				break;
			case 20: //Favorite vehicles
				if (Scroll == -1)
					Scroll = 10;
				break;
			case 21: //Players list
				if (Scroll == -1)
					Scroll = 15;
				break;
			case 22: //Dirty options
				if (Scroll == -1)
					Scroll = 12;
				break;
			case 23: //Player options
				if (Scroll == -1)
					Scroll = 6;
				break;
			case 24: //Animation options
				if (Scroll == -1)
					Scroll = 4;
				break;
			case 25: //Teleport options
				if (Scroll == -1)
					Scroll = 3;
				break;
			case 26: //Debug options
				if (Scroll == -1)
					Scroll = 9;
				break;
			case 27: //Object Editor
				if (Scroll == -1)
					Scroll = 9;
				break;
			case 28: //All player options
				if (Scroll == -1)
					Scroll = 6;
				break;
			case 29: //Bodyguard menu
				if (Scroll == -1)
					Scroll = 6;
				break;
			case 30: //Bodyguards list
				if (Scroll == -1)
					Scroll = 13;
				break;
			case 31: //ped options
				if (Scroll == -1)
					Scroll = 6;
				break;
			case 32: //menu settings
				if (Scroll == -1)
					Scroll = 5;
				break;
			case 33: //spawned peds
				if (Scroll == -1)
					Scroll = 5;
				break;
			case 34: //heist cars
				if (Scroll == -1)
					Scroll = 13;
				break;
			case 35: //sprx loader
				if (Scroll == -1)
					Scroll = 4;
				break;
			case 36: //mod shop main
				if (Scroll == -1)
					Scroll = 10;
				break;
			case 37: //mod shop engine
				Vehicle veh = GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 0);
				if (Scroll == -1)
					Scroll = GET_VEHICLE_LIVERY_COUNT(veh);
				break;
			case 38: //mod shop tranny
				if (Scroll == -1)
					Scroll = 3;
				break;
			case 39: //mod shop brakes
				if (Scroll == -1)
					Scroll = 3;
				break;
			case 40: //mod shop suspension
				if (Scroll == -1)
					Scroll = 4;
				break;
			case 41: //mod shop exhaust
				if (Scroll == -1)
					Scroll = 4;
				break;
			case 42: //mod shop armour
				if (Scroll == -1)
					Scroll = 5;
				break;
			case 43: //network
				if (Scroll == -1)
					Scroll = 4;
				break;
			case 44: //mod shop plates
				if (Scroll == -1)
					Scroll = 5;
				break;
			case 45: //mod shop tints
				if (Scroll == -1)
					Scroll = 4;
				break;
			case 46: //mod shop body main
				if (Scroll == -1)
					Scroll = 10;
				break;
			case 47: //mod shop body front bumper
				if (Scroll == -1)
					Scroll = 3;
				break;
			case 48: //mod shop body rear bumper
				if (Scroll == -1)
					Scroll = 3;
				break;
			case 49: //mod shop body spoiler
				if (Scroll == -1)
					Scroll = 3;
				break;
			case 50: //mod shop body side skirts
				if (Scroll == -1)
					Scroll = 3;
				break;
			case 51: //mod shop body hood
				if (Scroll == -1)
					Scroll = 5;
				break;
			case 52: //object manager 1/2
				if (Scroll == -1)
					Scroll = 29;
				break;
			case 53:
				break;
			case 54:
				if (Scroll == -1)
					Scroll = 7;
				break;
			case 55:
				if (Scroll == -1)
					Scroll = 1;
				break;
			case 56:
				if (Scroll == -1)
					Scroll = 3;
				break;
			case 57:
				if (Scroll == -1)
					Scroll = 7;
				break;
			case 58:
				if (Scroll == -1)
					Scroll = 5;
				break;
			case 59:
				if (Scroll == -1)
					Scroll = 13;
				break;
			case 60:
				if (Scroll == -1)
					Scroll = 7;
				break;
			case 61:
				if (Scroll == -1)
					Scroll = 7;
				break;
			case 62:
				break;
			case 63:
				if (Scroll == -1)
					Scroll = 8;
				break;
			case 64:
				if (Scroll == -1)
					Scroll = 9;
				break;
			case 65:
				if (Scroll == -1)
					Scroll = 6;
				break;
			case 66:
				if (Scroll == -1)
					Scroll = 5;
				break;
			case 67:
				if (Scroll == -1)
					Scroll = 11;
				break;
			case 68:
				if (Scroll == -1)
					Scroll = 5;
				break;
			case 69:
				if (Scroll == -1)
					Scroll = 6;
				break;
			case 70:
				if (Scroll == -1)
					Scroll = 16;
				break;
			case 71:
				if (Scroll == -1)
					Scroll = 10;
				break;
			case 72:
				if (Scroll == -1)
					Scroll = 4;
				break;
			case 73:
				if (Scroll == -1)
					Scroll = 4;
				break;
			case 74:
				if (Scroll == -1)
					Scroll = 16;
				break;
			case 75:
				if (Scroll == -1)
					Scroll = 6;
				break;
			case 76:
				if (Scroll == -1)
					Scroll = 19;
				break;
			case 77:
				break;
			case 78:
				if (Scroll == -1)
					Scroll = 14;
				break;
			case 79:
				if (Scroll == -1)
					Scroll = 17;
				break;
			case 80:
				break;
			case 81:
				if (Scroll == -1)
					Scroll = 8;
				break;
			case 82:
				if (Scroll == -1)
					Scroll = 24;
				break;
			case 83:
				break;
			case 84:
				if (Scroll == -1)
					Scroll = 18;
				break;
			case 85:
				break;
			case 86:
				if (Scroll == -1)
					Scroll = 22;
				break;
			case 87:
				break;
			case 88:
				if (Scroll == -1)
					Scroll = 1;
				break;
			case 89:
				if (Scroll == -1)
					Scroll = 6;
				break;
			case 90:
				if (Scroll == -1)
					Scroll = 4;
				break;
			case 91:
				if (Scroll == -1)
					Scroll = 4;
				break;
			case 92:
				if (Scroll == -1)
					Scroll = 2;
				break;
			case 93:
				if (Scroll == -1)
					Scroll = 2;
				break;
			case 94:
				if (Scroll == -1)
					Scroll = 21;
				break;
			case 95:
				if (Scroll == -1)
					Scroll = 68;
				break;
			case 96:
				if (Scroll == -1)
					Scroll = 167;
				break;
			case 97:
				if (Scroll == -1)
					Scroll = 40;
				break;
			case 98:
				if (Scroll == -1)
					Scroll = 3;
				break;
			case 99:
				if (Scroll == -1)
					Scroll = 36;
				break;
			case 100:
				if (Scroll == -1)
					Scroll = 95;
				break;
			case 101:
				if (Scroll == -1)
					Scroll = 14;
				break;
			case 102:
				if (Scroll == -1)
					Scroll = 22;
				break;
			case 103:
				if (Scroll == -1)
					Scroll = 90;
				break;
			case 104:
				if (Scroll == -1)
					Scroll = 14;
				break;
			case 105:
				if (Scroll == -1)
					Scroll = 44;
				break;
			case 106:
				if (Scroll == -1)
					Scroll = 1;
				break;
			case 107:
				if (Scroll == -1)
					Scroll = 1;
				break;
			case 108:
				if (Scroll == -1)
					Scroll = 1;
				break;
			case 109:
				if (Scroll == -1)
					Scroll = 1;
				break;
			case 110:
				if (Scroll == -1)
					Scroll = 1;
				break;
			case 111:
				if (Scroll == -1)
					Scroll = 1;
				break;
			case 112:
				if (Scroll == -1)
					Scroll = 1;
				break;
			case 113:
				if (Scroll == -1)
					Scroll = 1;
				break;
			case 114:
				if (Scroll == -1)
					Scroll = 1;
				break;
			case 115:
				if (Scroll == -1)
					Scroll = 1;
				break;
			case 116:
				if (Scroll == -1)
					Scroll = 1;
				break;
			case 117:
				if (Scroll == -1)
					Scroll = 1;
				break;
			case 118:
				if (Scroll == -1)
					Scroll = 471;
				break;
			case 119:
				if (Scroll == -1)
					Scroll = 9;
				break;
			case 120:
				if (Scroll == -1)
					Scroll = 7;
				break;
			case 121:
				if (Scroll == -1)
					Scroll = 8;
				break;
			case 122:
				if (Scroll == -1)
					Scroll = 8;
				break;
			case 123:
				if (Scroll == -1)
					Scroll = 9;
				break;
			case 124:
				if (Scroll == -1)
					Scroll = 4;
				break;
			case 125:
				if (Scroll == -1)
					Scroll = 4;
				break;
			case 126:
				if (Scroll == -1)
					Scroll = 4;
				break;
			case 127:
				if (Scroll == -1)
					Scroll = 1;
				break;
			case 128:
				if (Scroll == -1)
					Scroll = 2;
				break;
			case 129:
				if (Scroll == -1)
					Scroll = 4;
				break;
			case 130:
				if (Scroll == -1)
					Scroll = 6;
				break;
			case 131:
				if (Scroll == -1)
					Scroll = 2;
				break;
			case 132:
				if (Scroll == -1)
					Scroll = 7;
			case 133:
				if (Scroll == -1)
					Scroll = 81;
				break;
			case 134:
				if (Scroll == -1)
					Scroll = 109;
				break;
			case 135:
				if (Scroll == -1)
					Scroll = 159;
				break;
			case 136:
				if (Scroll == -1)
					Scroll = 2;
				break;
			case 137:
				if (Scroll == -1)
					Scroll = 3;
				break;
			case 138:
				if (Scroll == -1)
					Scroll = 1;
				break;
			case 139:
				if (Scroll == -1)
					Scroll = 3;
				break;
			case 140:
				if (Scroll == -1)
					Scroll = 8;
				break;
			case 141:
				if (Scroll == -1)
					Scroll = 2;
				break;
			case 142:
				if (Scroll == -1)
					Scroll = 2;
				break;
			case 143:
				if (Scroll == -1)
					Scroll = 3;
				break;
			case 144:
				if (Scroll == -1)
					Scroll = 3283;
				break;
			case 145:
				if (Scroll == -1)
					Scroll = 16;
				break;
			case 146:
				if (Scroll == -1)
					Scroll = 52;
				break;
			case 147:
				if (Scroll == -1)
					Scroll = 5;
				break;
			case 148:
				if (Scroll == -1)
					Scroll = 4;
				break;
			case 149:
				if (Scroll == -1)
					Scroll = 5;
				break;
			case 150:
				if (Scroll == -1)
					Scroll = 8;
				break;
			case 151:
				if (Scroll == -1)
					Scroll = 1323;
				break;
			}
			PlaySound("NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET");
		}
		if (get_action_key_just_pressed(193, 175))
		{
			if (WhichMenu == 1) //Main
			{
				switch (Scroll)
				{
				case 0:
					WhichMenu = 2;
					Scroll = 0;
					goto end;
				case 1:
					WhichMenu = 4;
					Scroll = 0;
					goto end;
				case 2:
					WhichMenu = 43;
					Scroll = 0;
					goto end;
				case 3:
					WhichMenu = 11;
					Scroll = 0;
					goto end;
				case 4:
					WhichMenu = 5;
					Scroll = 0;
					goto end;
				case 5:
					WhichMenu = 29;
					Scroll = 0;
					goto end;
				case 6:
					WhichMenu = 24;
					Scroll = 0;
					goto end;
				case 7:
					WhichMenu = 25;
					Scroll = 0;
					goto end;
				case 8:
					WhichMenu = 7;
					Scroll = 0;
					goto end;
				case 9:
					WhichMenu = 8;
					Scroll = 0;
					goto end;
				case 10:
					FindTunablesPointer();
					if (TunablesAddress != 0 && NETWORK_IS_IN_SESSION())
					{
						WhichMenu = 9;
						Scroll = 0;
					}
					else {
						PrintMessage("Error - Tunables only work online");
					}
					goto end;
				case 11:
					WhichMenu = 74;
					Scroll = 0;
					goto end;
				case 12:
					WhichMenu = 32;
					Scroll = 0;
					goto end;
				case 13:
					Open = false;
					goto end;
				case 14:
					WhichMenu = 26;
					Scroll = 0;
					goto end;
				}
			}
			if (WhichMenu == 2) //Main mods
			{
				switch (Scroll)
				{
				case 0:
					WhichMenu = 10;
					Scroll = 0;
					goto end;
				case 1:
					WhichMenu = 120;
					Scroll = 0;
					goto end;
				case 2:
					WhichMenu = 61;
					Scroll = 0;
					goto end;
				case 3:
					WhichMenu = 55;
					Scroll = 0;
					goto end;
				case 4:
					GodModePlayer = !GodModePlayer;
					if (!GodModePlayer)
						SET_ENTITY_CAN_BE_DAMAGED(PLAYER_PED_ID(), true);
					PrintMessage(GodModePlayer ? "Invincibility enabled" : "Invincibility disabled");
					break;
				case 5:
					Invisible();
					break;
				case 6:
					spamcashonme = !spamcashonme;
					PrintMessage(spamcashonme ? "Cash drop enabled" : "Cash drop disabled");
					break;
				case 7:
					Wanted = !Wanted;
					if (!Wanted)
						SET_MAX_WANTED_LEVEL(5);
					PrintMessage(Wanted ? "No wanted level on" : "No wanted level off");
					break;
				case 8:
					ExplodePlayer(PLAYER_PED_ID(), true, false);
					PrintMessage("BOOM!");
					break;
				case 9:
					kingmaker = !kingmaker;
					PrintMessage(kingmaker ? "You are now The Master\nYour foes stand no chance" : "The Master turned off");
					break;
				case 10:
					Clone(PLAYER_PED_ID());
					break;
				case 11:
					forcefield = !forcefield;
					PrintMessage(forcefield ? "Forcefield enabled" : "Forcefield disabled");
					break;
				case 12:
					SuperMan = !SuperMan;
					if (SuperMan)
						GIVE_DELAYED_WEAPON_TO_PED(_ID, 0xFBAB5776, 1, 1);
					PrintMessage(SuperMan ? "Superman enabled" : "Superman disabled");
					break;
				case 13:
					health_regen = !health_regen;
					PrintMessage(health_regen ? "Health regen enabled\nYou will regenerate health over time" : "Health regen disabled");
					break;
				case 14:
					armour_regen = !armour_regen;
					PrintMessage(armour_regen ? "Armour regen enabled\nYou will regenerate armour over time" : "Armour regen disabled");
					break;
				case 15:
					suicide();
					break;
				case 16:
					break;
				}
			}
			if (WhichMenu == 3) //Account
			{
				switch (Scroll)
				{
				case 0:
					WhichMenu = 91;
					Scroll = 0;
					goto end;
				case 1:
					WhichMenu = 90;
					Scroll = 0;
					goto end;
				case 2:
					WhichMenu = 139;
					Scroll = 0;
					goto end;
				case 3:
					WhichMenu = 140;
					Scroll = 0;
					goto end;
					//case 4:
					//	STAT_GET_INT(GET_HASH_KEY("MPPLY_KILLS_PLAYERS"), &kdr_kills, 0);
					//	STAT_GET_INT(GET_HASH_KEY("MPPLY_DEATHS_PLAYER"), &kdr_deaths, 0);
					//	WhichMenu = 141;
					//	Scroll = 0;
					//	goto end;
					//case 5:
					//	STAT_GET_INT(GET_HASH_KEY("MP0_RACES_WON"), &cur_win_item, 0);
					//	STAT_GET_INT(GET_HASH_KEY("MP0_RACES_LOST"), &cur_loss_item, 0);
					//	WhichMenu = 142;
					//	Scroll = 0;
					//	goto end;
				case 4:
					DoUnlocks();
					break;
				case 5:
					DoSkipTutorial();
					break;
				case 6:
					EventShirts();
					break;
				case 7:
					WipeReports();
					break;
				case 8:
					UnlockAllClothing();
					break;
				case 9:
					HeistUnlocks();
					break;
					//12 is rockstar shirts (scroll)
				case 11:
					ModdedRolls();
					PrintMessage("Set modded combat roll");
					break;
				}
			}
			if (WhichMenu == 4) //Vehicle
			{
				switch (Scroll)
				{
				case 0:
					if (LoadMods())
					{
						WhichMenu = 36;
						Scroll = 0;
						goto end;
					}
					else
						PrintMessage("Error - Not in vehicle");
					break;
				case 1:
					WhichMenu = 57;
					Scroll = 0;
					goto end;
				case 2:
					WhichMenu = 56;
					Scroll = 0;
					goto end;
				case 3:
					veh_invincible = !veh_invincible;
					if (!veh_invincible)
						disable_vehicle_invincible();
					PrintMessage(veh_invincible ? "Vehicle invincibility enabled" : "Vehicle invincibility disabled");
					break;
				case 4:
					veh_invisible = !veh_invisible;
					if (!veh_invisible)
						vehicle_invisible(false);
					PrintMessage(veh_invisible ? "Vehicle invisibility enabled" : "Vehicle invisibility disabled");
					break;
				case 5:
					current_vehicle_weapon = vehicle_weapons[0];
					shootvehweapons = !shootvehweapons;
					PrintMessage(shootvehweapons ? "Vehicle weapons enabled\nPress L3 to shoot" : "Vehicle weapons disabled");
					break;
				case 6:
					FixCar();
					break;
				case 7:
					ColorCycle();
					break;
				case 8:
					SuperSpeed();
					break;
				case 9:
					nfs = !nfs;
					PrintMessage(nfs ? "Need for Speed on\nthanks to ~y~ap ii intense~w~ for the idea" : "Need for Speed off");
					break;
				case 10:
					FindClosestVeh();
					break;
				case 11:
					Speedo = !Speedo;
					PrintMessage(Speedo ? "Speedometer on" : "Speedometer off");
					break;
				case 12:
					FreezePosition();
					break;
				case 13:
					NoCollision();
					break;
				case 14:
					keyboard_action = 2;
					DrawKeyboard(8);
					break;
				case 15:
					ToggleLocks();
					break;
				case 16:
					nos = !nos;
					PrintMessage(nos ? "Nitrous on\nPress L3 to use" : "Nitrous off");
					break;
				case 17:
					if (!DOES_ENTITY_EXIST(wheel_object_id))
						CreateWheelObject();
					dw = !dw;
					if (dw)
						da = false;
					PrintMessage(dw ? "Drive on water enabled" : "Drive on water disabled");
					break;
				case 18:
					if (!DOES_ENTITY_EXIST(wheel_object_id))
						CreateWheelObject();
					da = !da;
					if (da)
					{
						dw = false;
						Vehicle e = GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 0);
						Vector3 c = GET_ENTITY_COORDS(PLAYER_PED_ID(), 1);
						SET_ENTITY_COORDS(e, c.x, c.y, 365, 1, 0, 0, 1);
					}
					PrintMessage(da ? "Drive on air enabled" : "Drive on air disabled");
					break;
				case 19:
					if (IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 1))
						SupeVehicle(GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 1));
					else
						PrintMessage("Not in vehicle");
					break;
				case 20:
					DeleteMyVehicle();
					break;
				case 21:
					FlipMyCar();
					break;
				case 22:
					carjump = !carjump;
					PrintMessage(carjump ? "Car jumper active\nProps to jdmalex\nPress X to jump!" : "Car jumper disabled");
					break;
				case 23:
					seatbelt = !seatbelt;
					if (!seatbelt)
					{
						SET_PED_CONFIG_FLAG(PLAYER_PED_ID(), PED_FLAG_CAN_FLY_THRU_WINDSCREEN, true);
						SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER_PED_ID(), true);
					}
					PrintMessage(seatbelt ? "Seatbelt enabled" : "Seatbelt disabled");
					break;
				}
			}
			if (WhichMenu == 5) //Model changer 2/2
			{
				switch (Scroll)
				{
				case 0:
					WhichMenu = 93;
					Scroll = 0;
					goto end;
				case 1:
					WhichMenu = 94;
					Scroll = 0;
					goto end;
				case 2:
					WhichMenu = 95;
					Scroll = 0;
					goto end;
				case 3:
					WhichMenu = 96;
					Scroll = 0;
					goto end;
				case 4:
					WhichMenu = 97;
					Scroll = 0;
					goto end;
				case 5:
					WhichMenu = 98;
					Scroll = 0;
					goto end;
				case 6:
					WhichMenu = 99;
					Scroll = 0;
					goto end;
				case 7:
					WhichMenu = 100;
					Scroll = 0;
					goto end;
				case 8:
					WhichMenu = 101;
					Scroll = 0;
					goto end;
				case 9:
					WhichMenu = 102;
					Scroll = 0;
					goto end;
				case 10:
					WhichMenu = 103;
					Scroll = 0;
					goto end;
				case 11:
					WhichMenu = 104;
					Scroll = 0;
					goto end;
				case 12:
					WhichMenu = 105;
					Scroll = 0;
					goto end;
				}
			}
			if (WhichMenu == 7) //Objects
			{
				switch (Scroll)
				{
				case 0:
					WhichMenu = 27;
					Scroll = 0;
					goto end;
				case 1:
					WhichMenu = 52;
					Scroll = 0;
					goto end;
				case 2:
					WhichMenu = 144;
					Scroll = 0;
					goto end;
				case 3:
					SpawnObject(0xB467C540, "UFO");
					break;
				case 4:
					SpawnObject(0xB467C540, "UFO");
					ObjName = "Asteroid";
					objSet = 0xDF9841D7; //asteroid
					break;
				case 5:
					SpawnObject(0x6B795EBC, "Alien egg");
					break;
				case 6:
					SpawnObject(0x1AFA6A0A, "Weed plant");
					break;
				case 7:
					SpawnObject(0xc42c019a, "Ferris wheel");
					break;
				case 8:
					SpawnObject(0x8DA1C0E, "Orange ball");
					break;
				case 9:
					SpawnObject(0xb157c9e4, "Ramp");
					break;
				case 10:
					SpawnObject(-2071359746, "Poop");
					break;
				case 11:
					SpawnObject(0x745f3383, "Windmill");
					break;
				case 12:
					keyboard_action = 7;
					DrawKeyboard(32);
					break;
				}
			}
			if (WhichMenu == 8) //Weather
			{
				switch (Scroll)
				{
				case 13:
					break;
				case 14:
					break;
				case 15:
					break;
				default:
					const char* Weather[15] = { "EXTRASUNNY", "CLEAR", "CLOUDS", "SMOG", "FOGGY", "OVERCAST", "RAIN", "THUNDER", "CLEARING", "NEUTRAL", "SNOW", "BLIZZARD", "SNOWLIGHT", "+ Hour", "- Hour" };
					SET_WEATHER_TYPE_NOW(Weather[Scroll]);
					SET_WEATHER_TYPE_NOW_PERSIST(Weather[Scroll]);
					SET_WEATHER_TYPE_PERSIST(Weather[Scroll]);
					SET_OVERRIDE_WEATHER(Weather[Scroll]);
					PrintMessage(Format("Set %s weather", WeatherOptions[Scroll]));
					break;
				}
			}
			if (WhichMenu == 9) //Tunables
			{
				switch (Scroll)
				{
				case 0:
					if (XMAS) {
						SetTunable(4724, 0x00000000);
						XMAS = false;
						PrintMessage("XMAS DLC disabled");
						break;
					}
					else {
						SetTunable(4724, 0x00000001);
						XMAS = true;
						PrintMessage("XMAS DLC enabled");
						break;
					}
				case 1:
					if (VDAY) {
						SetTunable(4827, 0x00000000);
						VDAY = false;
						PrintMessage("Valentine's DLC disabled");
						break;
					}
					else {
						SetTunable(4827, 0x00000001);
						VDAY = true;
						PrintMessage("Valentine's DLC enabled");
						break;
					}
				case 2:
					if (FOURTH) {
						SetTunable(6003, 0x00000000);
						SetTunable(6016, 0x00000000);
						SetTunable(6017, 0x00000000);
						FOURTH = false;
						PrintMessage("Independence DLC disabled");
						break;
					}
					else {
						SetTunable(6003, 0x00000001);
						SetTunable(6016, 0x00000001);
						SetTunable(6017, 0x00000001);
						FOURTH = true;
						PrintMessage("Independence DLC enabled");
						break;
					}
				case 3:
					if (SNOW) {
						SetTunable(4715, 0x00000000);
						SNOW = false;
						PrintMessage("Snow disabled");
						break;
					}
					else {
						SetTunable(4715, 0x00000001);
						SNOW = true;
						PrintMessage("Snow enabled");
						break;
					}
				case 4:
					if (FREE) {
						SetTunable(59, 0x3F800000);
						SetTunable(60, 0x3F800000);
						SetTunable(61, 0x3F800000);
						SetTunable(62, 0x3F800000);
						SetTunable(63, 0x3F800000);
						SetTunable(64, 0x3F800000);
						SetTunable(65, 0x3F800000);
						SetTunable(66, 0x3F800000);
						SetTunable(67, 0x3F800000);
						SetTunable(68, 0x3F800000);
						SetTunable(69, 0x3F800000);
						FREE = false;
						PrintMessage("Free online shopping disabled");
						break;
					}
					else {
						SetTunable(59, 0x00000000);
						SetTunable(60, 0x00000000);
						SetTunable(61, 0x00000000);
						SetTunable(62, 0x00000000);
						SetTunable(63, 0x00000000);
						SetTunable(64, 0x00000000);
						SetTunable(65, 0x00000000);
						SetTunable(66, 0x00000000);
						SetTunable(67, 0x00000000);
						SetTunable(68, 0x00000000);
						SetTunable(69, 0x00000000);
						FREE = true;
						PrintMessage("Free online shopping enabled");
						break;
					}
				case 5:
					if (IDLE) {
						SetTunable(73, 0x00007530);
						SetTunable(74, 0x0000EA60);
						SetTunable(75, 0x00015F90);
						IDLE = false;
						PrintMessage("No idle disabled");
						break;
					}
					else {
						SetTunable(73, 0x7FFFFFFF);
						SetTunable(74, 0x7FFFFFFF);
						SetTunable(75, 0x7FFFFFFF);
						IDLE = true;
						PrintMessage("No idle enabled");
						break;
					}
				}
			}
			if (WhichMenu == 10)
			{
				switch (Scroll)
				{
				case 0:
					SET_PED_DEFAULT_COMPONENT_VARIATION(_ID);
					PrintMessage("Set default variation");
					break;
				case 1:
					if (GET_ENTITY_MODEL(_ID) == GET_HASH_KEY("mp_m_freemode_01") || GET_ENTITY_MODEL(_ID) == GET_HASH_KEY("mp_f_freemode_01"))
						PrintMessage("You cannot do this with your current model");
					else {
						SET_PED_RANDOM_COMPONENT_VARIATION(_ID, 0);
						PrintMessage("Set random variation");
					}
					break;
				case 2:
					cur_component = Head;
					WhichMenu = 106;
					Scroll = 0;
					goto end;
				case 3:
					cur_component = Face;
					WhichMenu = 107;
					Scroll = 0;
					goto end;
				case 4:
					cur_component = Hair;
					WhichMenu = 108;
					Scroll = 0;
					goto end;
				case 5:
					cur_component = Shirt;
					WhichMenu = 109;
					Scroll = 0;
					goto end;
				case 6:
					cur_component = Pants;
					WhichMenu = 110;
					Scroll = 0;
					goto end;
				case 7:
					cur_component = Gadgets;
					WhichMenu = 111;
					Scroll = 0;
					goto end;
				case 8:
					cur_component = Feet;
					WhichMenu = 112;
					Scroll = 0;
					goto end;
				case 9:
					cur_component = Accessories;
					WhichMenu = 113;
					Scroll = 0;
					goto end;
				case 10:
					cur_component = Undershirts;
					WhichMenu = 114;
					Scroll = 0;
					goto end;
				case 11:
					cur_component = HeistGadgets;
					WhichMenu = 115;
					Scroll = 0;
					goto end;
				case 12:
					cur_component = Logos;
					WhichMenu = 116;
					Scroll = 0;
					goto end;
				case 13:
					cur_component = Jackets;
					WhichMenu = 117;
					Scroll = 0;
					goto end;
				}
			}
			if (WhichMenu == 11) //Spawn car menu
			{
				switch (Scroll)
				{
				case 0:
					WhichMenu = 12;
					Scroll = 0;
					goto end;
				case 1:
					WhichMenu = 13;
					Scroll = 0;
					goto end;
				case 2:
					WhichMenu = 14;
					Scroll = 0;
					goto end;
				case 3:
					WhichMenu = 15;
					Scroll = 0;
					goto end;
				case 4:
					WhichMenu = 16;
					Scroll = 0;
					goto end;
				case 5:
					WhichMenu = 64;
					Scroll = 0;
					goto end;
				case 6:
					WhichMenu = 65;
					Scroll = 0;
					goto end;
				case 7:
					WhichMenu = 63;
					Scroll = 0;
					goto end;
				case 8:
					WhichMenu = 66;
					Scroll = 0;
					goto end;
				case 9:
					WhichMenu = 67;
					Scroll = 0;
					goto end;
				case 10:
					WhichMenu = 17;
					Scroll = 0;
					goto end;
				case 11:
					WhichMenu = 54;
					Scroll = 0;
					goto end;
				case 12:
					WhichMenu = 34;
					Scroll = 0;
					goto end;
				case 13:
					WhichMenu = 68;
					Scroll = 0;
					goto end;
				case 14:
					WhichMenu = 69;
					Scroll = 0;
					goto end;
				case 15:
					WhichMenu = 18;
					Scroll = 0;
					goto end;
				case 16:
					WhichMenu = 19;
					Scroll = 0;
					goto end;
				case 17:
					WhichMenu = 20;
					Scroll = 0;
					goto end;
				case 18:
					RandomVehicle();
					break;
				case 19:
					keyboard_action = 1;
					DrawKeyboard(24);
					break;
				case 20:
					spawn_invincible_vehicle = !spawn_invincible_vehicle;
					PrintMessage(spawn_invincible_vehicle ? "Vehicles will spawn with invincibility" : "Vehicles will spawn normally");
					break;
				case 21:
					spawn_inside_vehicle = !spawn_inside_vehicle;
					PrintMessage(spawn_inside_vehicle ? "You will be set inside spawned vehicles" : "Vehicles will spawn next to you");
					break;
				case 22:
					spawn_suped_up_vehicle = !spawn_suped_up_vehicle;
					PrintMessage(spawn_suped_up_vehicle ? "Vehicles will spawn with max upgrades" : "Vehicles will spawn with no upgrades");
					break;
				}
			}
			if (WhichMenu == 12) //Supers
			{
				switch (Scroll)
				{
				case 0:
					SpawnVehicle(0x9AE6DDA1);
					break;
				case 1:
					SpawnVehicle(0xB779A091);
					break;
				case 2:
					SpawnVehicle(0x18F25AC7);
					break;
				case 3:
					SpawnVehicle(0xAC5DF515);
					break;
				case 4:
					SpawnVehicle(0x9F4B77BE);
					break;
				case 5:
					SpawnVehicle(0xB1D95DA0);
					break;
				case 6:
					SpawnVehicle(0x185484E1);
					break;
				case 7:
					SpawnVehicle(0x142E0DC3);
					break;
				case 8:
					SpawnVehicle(0xB2FE5CF9);
					break;
				}
			}
			if (WhichMenu == 13) //Supers
			{
				switch (Scroll)
				{
				case 0:
					SpawnVehicle(0xC1AE4D16);
					break;
				case 1:
					SpawnVehicle(0x13B57D8A);
					break;
				case 2:
					SpawnVehicle(0x3D8FA25C);
					break;
				case 3:
					SpawnVehicle(0x39DA2754);
					break;
				case 4:
					SpawnVehicle(0x8CB29A14);
					break;
				case 5:
					SpawnVehicle(0x7B8AB45F);
					break;
				case 6:
					SpawnVehicle(0x8911B9F5);
					break;
				case 7:
					SpawnVehicle(0xDE3D9D22);
					break;
				case 8:
					SpawnVehicle(0xB2A716A3);
					break;
				case 9:
					SpawnVehicle(0xC1E908D2);
					break;
				case 10:
					SpawnVehicle(0xEDD516C6);
					break;
				case 11:
					SpawnVehicle(0x067BC037);
					break;
				}
			}
			if (WhichMenu == 14) //Supers
			{
				switch (Scroll)
				{
				case 0:
					SpawnVehicle(0x2D3BD401);
					break;
				case 1:
					SpawnVehicle(0xE62B361B);
					break;
				case 2:
					SpawnVehicle(0x3EAB5555);
					break;
				case 3:
					SpawnVehicle(0x404B6381);
					break;
				case 4:
					SpawnVehicle(0x82E499FA);
					break;
				case 5:
					SpawnVehicle(0x1BB290BC);
					break;
				}
			}
			if (WhichMenu == 15) //Supers
			{
				switch (Scroll)
				{
				case 0:
					SpawnVehicle(0xD83C13CE);
					break;
				case 1:
					SpawnVehicle(0x04CE68AC);
					break;
				case 2:
					SpawnVehicle(0xB820ED5E);
					break;
				case 3:
					SpawnVehicle(0x831A21D5);
					break;
				case 4:
					SpawnVehicle(0x1F3766E3);
					break;
				case 5:
					SpawnVehicle(0xF26CEFF9);
					break;
				case 6:
					SpawnVehicle(0x59E0FBF3);
					break;
				case 7:
					SpawnVehicle(0x9B909C94);
					break;
				case 8:
					SpawnVehicle(0x94B395C5);
					break;
				case 9:
					SpawnVehicle(0xD756460C);
					break;
				}
			}
			if (WhichMenu == 16) //Supers
			{
				switch (Scroll)
				{
				case 0:
					SpawnVehicle(0x322CF98F);
					break;
				case 1:
					SpawnVehicle(0xE644E480);
					break;
				case 2:
					SpawnVehicle(0xEB70965F);
					break;
				case 3:
					SpawnVehicle(0xBC993509);
					break;
				case 4:
					SpawnVehicle(0xB9CB3B69);
					break;
				}
			}
			if (WhichMenu == 17) //Military
			{
				switch (Scroll)
				{
				case 0:
					SpawnVehicle(0x2EA68690);
					break;
				case 1:
					SpawnVehicle(0x4008EABB);
					break;
				case 2:
					SpawnVehicle(0x132D5A1A);
					break;
				case 3:
					SpawnVehicle(0xCEEA3F4B);
					break;
				}
			}
			if (WhichMenu == 18) //Fun
			{
				switch (Scroll)
				{
				case 0:
					SpawnVehicle(0x1FD824AF);
					break;
				case 1:
					SpawnVehicle(0x885F3671);
					break;
				case 2:
					SpawnVehicle(0x58E49664);
					break;
				case 3:
					SpawnVehicle(0x6A4BD8F6);
					break;
				case 4:
					SpawnVehicle(0x810369E2);
					break;
				case 5:
					SpawnVehicle(0x1A7FCEFA);
					break;
				case 6:
					SpawnVehicle(0x2B6DC64A);
					break;
				case 7:
					SpawnVehicle(0x38408341);
					break;
				}
			}
			if (WhichMenu == 19) //DLC
			{
				switch (Scroll)
				{
				case 0:
					SpawnVehicle(0x0239E390);
					break;
				case 1:
					SpawnVehicle(0x206D1B68);
					break;
				case 2:
					SpawnVehicle(0x00ABB0C0);
					break;
				case 3:
					SpawnVehicle(0x06FF6914);
					break;
				case 4:
					SpawnVehicle(0xCD93A7DB);
					break;
				case 5:
					SpawnVehicle(0x5E4327C8);
					break;
				case 6:
					SpawnVehicle(0xE2504942);
					break;
				case 7:
					SpawnVehicle(0xA29D6D10);
					break;
				case 8:
					SpawnVehicle(0x767164D6);
					break;
				case 9:
					SpawnVehicle(0x4019CB4C);
					break;
				case 10:
					SpawnVehicle(0xB79F589E);
					break;
				case 11:
					SpawnVehicle(-1479664699);
					break;
				case 12:
					SpawnVehicle(1663218586);
					break;
				case 13:
					SpawnVehicle(784565758);
					break;
				case 14:
					SpawnVehicle(349605904);
					break;
				case 15:
					SpawnVehicle(-1353081087);
					break;
				case 16:
					SpawnVehicle(1070967343);
					break;
				}
			}
			if (WhichMenu == 20) //Favs
			{
				switch (Scroll)
				{
				case 0: //Tustin
					SpawnVehicle(0x3C4E2113);
					break;
				case 1: //Choco
					SpawnVehicle(0x8A63C7B9);
					break;
				case 2: //Kryptus
					SpawnVehicle(0x2BEC3CBE);
					break;
				case 3: //SOAB
					SpawnVehicle(0xE5A2D6C6);
					break;
				case 4: //An0ny
					SpawnVehicle(0x15F27762);
					break;
				case 5: //Amitoz
					SpawnVehicle(0x9DC66994);
					break;
				case 6: //HURT
					SpawnVehicle(0x2B6DC64A);
					break;
				case 7: //Slinky
					SpawnVehicle(0x32B29A4B);
					break;
				case 8: //Slick
					SpawnVehicle(0x38408341);
					break;
				case 9: //KingBilly
					SpawnVehicle(0x43779C54);
					break;
				case 10: //gay Kurt
					SpawnVehicle(0x0350D1AB);
					break;
				}
			}

			if (WhichMenu == 21)
			{
				if (strcmp(GET_PLAYER_NAME(Scroll), "**Invalid**") == 0)
					PrintMessage("Invalid player selected");
				else
				{
					if (guardattack)
					{
						SelectedClient = Scroll;
						GuardsKillClient();
						WhichMenu = 29;
						Scroll = 2;
						guardattack = false;
					}
					else {
						SelectedClient = Scroll;
						WhichMenu = 23;
						Scroll = 0;
						goto end;
					}
				}
			}

			if (WhichMenu == 23)
			{
				switch (Scroll)
				{
				case 0:
					WhichMenu = 70;
					Scroll = 0;
					goto end;
				case 1:
					WhichMenu = 71;
					Scroll = 0;
					goto end;
				case 2:
					WhichMenu = 72;
					Scroll = 0;
					goto end;
				case 3:
					WhichMenu = 11;
					Scroll = 0;
					spawnforclient = true;
					break;
				case 4:
					WhichMenu = 5;
					Scroll = 0;
					model_client_guard = true;
					break;
				case 5:
					give_ownership();
					break;
				case 6:
					steal_ownership();
					break;
				}
			}
			if (WhichMenu == 24)
			{
				switch (Scroll)
				{
				case 0:
					WhichMenu = 132;
					Scroll = 0;
					goto end;
				case 1:
					WhichMenu = 133;
					Scroll = 0;
					goto end;
				case 2:
					WhichMenu = 134;
					Scroll = 0;
					goto end;
				case 3:
					WhichMenu = 134;
					Scroll = 0;
					goto end;
				case 4:
					StopAnim();
					PrintMessage("Stopped animations");
					break;
				}
			}
			if (WhichMenu == 25)
			{
				switch (Scroll)
				{
				case 0:
					TeleportToWaypoint();
					break;
				case 1:
					TeleportForward();
					break;
				case 2:
					TeleportAbove();
					break;
				case 3:
					WhichMenu = 92;
					Scroll = 0;
					goto end;
				}
			}

			if (WhichMenu == 27) //Object editor
			{
				switch (Scroll)
				{
				case 0:
					get_current_object_aimed_at();
					break;
				case 8:
					copy_object();
					break;
				case 9:
					delete_object();
					break;
				}
			}
			if (WhichMenu == 28) //All player options
			{
				switch (Scroll)
				{
				case 0:
					CashSpamAll = !CashSpamAll;
					PrintMessage(CashSpamAll ? "Dropping cash on all players" : "Disabled all player cash drop");
					break;
				case 1:
					ExplodeAll();
					PrintMessage("Blew all players up");
					break;
				case 2:
					VehicleFixAll();
					PrintMessage("Fixed all player vehicles");
					break;
				case 3:
					VehicleColorAll();
					PrintMessage("Randomly colored all player vehicles");
					break;
				case 4:
					SupeUpAllVehicles();
					PrintMessage("Suped up all player vehicles");
					break;
				case 5:
					tracer = !tracer;
					PrintMessage(tracer ? "Tracer on" : "Tracer off");
					break;
				case 6:
					text_all = true;
					WhichMenu = 149;
					Scroll = 0;
					goto end;
				}
			}
			if (WhichMenu == 29) //Ped options
			{
				switch (Scroll)
				{
				case 0:
					WhichMenu = 5;
					Scroll = 0;
					model_my_guard = true;
					goto end;
				case 1:
					WhichMenu = 33;
					Scroll = 0;
					goto end;
				case 2:
					guardattack = true;
					WhichMenu = 21;
					Scroll = 0;
					goto end;
				case 3:
					AllPedsDance();
					break;
				case 4:
					AllGuardsInvincible();
					break;
				case 5:
					RemoveAllGuards();
					break;
				case 6:
					DeletePeds();
					break;
				}
			}
			if (WhichMenu == 31) //Bodyguard options
			{
				if (!IS_ENTITY_DEAD(peds[selectedped].id))
				{
					switch (Scroll)
					{
					case 0:
						RandomizeGuard();
						break;
					case 1:
						give_wep_index = peds[selectedped].id;
						weapon_instance = 2;
						WhichMenu = 121;
						Scroll = 0;
						goto end;
					case 2:
						GuardInvincible();
						break;
					case 3:
						MakePedDance();
						break;
					case 4:
						KickGuardFromGroup();
						break;
					case 5:
						DeletePed();
						WhichMenu = 33;
						Scroll = selectedped;
						goto end;
					case 6:
						TeleportPedToMe();
						break;
					}
				}
				else
				{
					WhichMenu = 33;
					Scroll = selectedped;
					PrintMessage("Guard died");
					goto end;
				}
			}
			if (WhichMenu == 32) //menu settings
			{
				switch (Scroll)
				{
				case 0:
					WhichMenu = 137;
					Scroll = 0;
					break;
				case 1:
					WhichMenu = 138;
					Scroll = 0;
					break;
				case 2:
					showplayerstats = !showplayerstats;
					PrintMessage(showplayerstats ? "Showing player stats window" : "Player stats window turned off");
					break;
				case 3:
					showlobbyinfo = !showlobbyinfo;
					PrintMessage(showlobbyinfo ? "Showing lobby information" : "Lobby information turned off");
					break;
				case 4:
					chatheads = !chatheads;
					PrintMessage(chatheads ? "Showing talking players" : "Disabled players talking");
					break;
				case 5:
					use_mph = !use_mph;
					PrintMessage(use_mph ? "Using MPH" : "Using KPH");
					break;
				}
			}
			if (WhichMenu == 33) //ped manager
			{
				if (peds[Scroll].name == "None")
				{
					PrintMessage("Invalid guard selected");
				}
				else {
					selectedped = Scroll;
					WhichMenu = 31;
					Scroll = 0;
					goto end;
				}
			}
			if (WhichMenu == 34) //heist
			{
				switch (Scroll)
				{
				case 0:
					SpawnVehicle(0x3822BDFE);
					break;
				case 1:
					SpawnVehicle(0x26321E67);
					break;
				case 2:
					SpawnVehicle(0x6882FA73);
					break;
				case 3:
					SpawnVehicle(0x825A9F4C);
					break;
				case 4:
					SpawnVehicle(0xAE2BFE94);
					break;
				case 5:
					SpawnVehicle(0x187D938D);
					break;
				case 6:
					SpawnVehicle(0x39D6E83F);
					break;
				case 7:
					SpawnVehicle(0x9114EADA);
					break;
				case 8:
					SpawnVehicle(0x7B7E56F0);
					break;
				case 9:
					SpawnVehicle(0xFB133A17);
					break;
				case 10:
					SpawnVehicle(0x83051506);
					break;
				case 11:
					SpawnVehicle(0x31ADBBFC);
					break;
				case 12:
					SpawnVehicle(0x2592B5CF);
					break;
				case 13:
					SpawnVehicle(0xA09E15FD);
					break;
				}
			}
			if (WhichMenu == 36) //mop shop main
			{
				switch (Scroll)
				{
				case 0:
					if (LoadMods())
					{
						WhichMenu = 46;
						Scroll = 0;
						goto end;
					}
					else
						PrintMessage("Error - Not in vehicle");
					break;
				case 7:
					set_vehicle_tyres_can_burst(PLAYER_PED_ID());
					PrintMessage("Set bulletproof tires");
					break;
				case 10:
					int val = get_vehicle_mod(22);
					if (val != -2)
					{
						toggle_vehicle_mod(22, (bool)val);
						PrintMessage((bool)val ? "Xenons given" : "Removed xenons");
					}
					else
						PrintMessage("Not in vehicle");
					break;
				}
			}
			if (WhichMenu == 37)
			{
				Vehicle veh = GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 0);
				SET_VEHICLE_LIVERY(veh, Scroll);
			}
			if (WhichMenu == 43) //network
			{
				switch (Scroll)
				{
				case 0:
					WhichMenu = 21;
					Scroll = 0;
					goto end;
				case 1:
					WhichMenu = 28;
					Scroll = 0;
					goto end;
				case 2:
					Vector3 coords = GET_ENTITY_COORDS(PLAYER_PED_ID(), 1);
					for (int i = 0; i < 18; i++)
					{
						int address = (0x31197000 + (i * 0x2520)) + 0x70;
						*(float*)address = coords.x;
						*(float*)(address + 0x04) = coords.y;
						*(float*)(address + 0x08) = coords.z;
						SET_ENTITY_COORDS(GET_PLAYER_PED(i), coords.x, coords.y, coords.z, 0, 0, 0, 1);
					}
					//0x31197000 + 0x70
					Ped test = GET_PLAYER_PED(SelectedClient);
					PrintMessage(Format("%i", test));
					//PrintMessage(Format("Y %f", (*(float*)0x31197000 + 0x74)));
					//PrintMessage(Format("Z %f", (*(float*)0x31197000 + 0x78)));
					//fx_test("scr_rcbarry1", "scr_alien_teleport");
					//PrintMessage("Will be added back next update");
					//if (NETWORK_IS_IN_SESSION())
					//{
					//	WhichMenu = 3;
					//	Scroll = 0;
					//}
					//else
					//	PrintMessage("Error - Not online");
					goto end;
					//case 3:
					//	if (strcmp(changed_name, "empty") == 0)
					//		changed_name = GET_PLAYER_NAME(PLAYER_ID());
					//	WhichMenu = 131;
					//	Scroll = 0;
					//	goto end;
				case 3:
					if (global_read(2390201 + PLAYER_ID() * 223 + 170) != 1)
					{
						int shit = *(int*)(OTRPtr)+OTRGap;
						*(int*)shit = 2147483647;
						global_write(2390201 + PLAYER_ID() * 223 + 170, 1);
						global_write(2394218 + 55, 2147483647);
						PrintMessage("Enabled off the radar");
					}
					else {
						int shit = *(int*)(OTRPtr)+OTRGap;
						*(int*)shit = 0;
						PrintMessage("Disabled off the radar");

					}
					goto end;
				case 4:
					if (global_read(2390201 + PLAYER_ID() * 223 + 172) != 1)
					{
						global_write(2394218 + 56, 2147483647);
						global_write(2390201 + PLAYER_ID() * 223 + 172, 1);
						PrintMessage("Revealed all players");
					}
					else {
						global_write(2390201 + PLAYER_ID() * 223 + 172, 0);
						PrintMessage("No longer revealing players");
					}
					goto end;
				}
			}
			if (WhichMenu == 46) //mod shop body main
			{
				switch (Scroll)
				{
				case 8:
					WhichMenu = 75;
					Scroll = 0;
					goto end;
				case 9:
					get_vehicle_colours();
					WhichMenu = 88;
					Scroll = 0;
					goto end;
				case 10:
					WhichMenu = 89;
					Scroll = 0;
					goto end;
				case 11:
					if (IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 0))
					{
						Vehicle veh = GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 0);
						if (GET_VEHICLE_LIVERY_COUNT(veh) > -1)
						{

						}
						else
							PrintMessage("Vehicle has no liveries");
					}
					else
						PrintMessage("Not in vehicle");

				}

			}
			if (WhichMenu == 52)
			{
				if (objects[Scroll].name != "None")
				{
					current_object_index = Scroll;
					WhichMenu = 27;
					Scroll = 0;
				}
			}
			if (WhichMenu == 54)
			{
				switch (Scroll)
				{
				case 0:
					SpawnVehicle(0x45D56ADA);
					break;
				case 1:
					SpawnVehicle(0x79FBB0C5);
					break;
				case 2:
					SpawnVehicle(0x432EA949);
					break;
				case 3:
					SpawnVehicle(0x9F05F101);
					break;
				case 4:
					SpawnVehicle(0x95F4C618);
					break;
				case 5:
					SpawnVehicle(0xA46462F7);
					break;
				case 6:
					SpawnVehicle(0x1B38E955);
					break;
				case 7:
					SpawnVehicle(0xFDEFAEC3);
					break;
				}
			}
			if (WhichMenu == 55)
			{
				switch (Scroll)
				{
				case 0:
					WhichMenu = 118;
					Scroll = 0;
					goto end;
				case 1:
					CLEAR_TIMECYCLE_MODIFIER();
					PrintMessage("Cleared visions");
					break;
				}
			}
			if (WhichMenu == 56)
			{

			}
			if (WhichMenu == 57)
			{
				switch (Scroll)
				{
				case 0:
					neons = !neons;
					if (!neons)
						current_neon_index = -1;
					PrintMessage(neons ? "Neons enabled" : "Neons disabled");
					break;
				case 1:
					neonsr = 0, neonsg = 0, neonsb = 255;
					current_neon_index = 0;
					PrintMessage("Neons set to blue");
					break;
				case 2:
					neonsr = 255, neonsg = 255, neonsb = 0;
					current_neon_index = 1;
					PrintMessage("Neons set to yellow");
					break;
				case 3:
					neonsr = 0, neonsg = 255, neonsb = 0;
					current_neon_index = 2;
					PrintMessage("Neons set to green");
					break;
				case 4:
					neonsr = 255, neonsg = 0, neonsb = 0;
					current_neon_index = 3;
					PrintMessage("Neons set to red");
					break;
				case 5:
					neonsr = 255, neonsg = 102, neonsb = 0;
					current_neon_index = 4;
					PrintMessage("Neons set to orange");
					break;
				case 6:
					neonsr = 255, neonsg = 105, neonsb = 180;
					current_neon_index = 5;
					PrintMessage("Neons set to pink");
					break;
				case 7:
					rainbowneons = !rainbowneons;
					PrintMessage(rainbowneons ? "Rainbow neons active" : "Rainbow neons deactivated");
					break;
				}
			}
			if (WhichMenu == 58)
			{
				switch (Scroll)
				{
				case 0:

					break;
				case 1:
					current_vehicle_weapon = vehicle_weapons[0];
					current_vehicle_weapon_index = 0;
					PrintMessage("Set Hunter bullets");
					break;
				case 2:
					current_vehicle_weapon = vehicle_weapons[1];
					current_vehicle_weapon_index = 1;
					PrintMessage("Set Fireworks");
					break;
				case 3:
					current_vehicle_weapon = vehicle_weapons[2];
					current_vehicle_weapon_index = 2;
					PrintMessage("Set JB-700 bullets");
					break;
				case 4:
					current_vehicle_weapon = vehicle_weapons[3];
					current_vehicle_weapon_index = 3;
					PrintMessage("Set Snowballs");
					break;
				case 5:
					current_vehicle_weapon = vehicle_weapons[4];
					current_vehicle_weapon_index = 4;
					PrintMessage("Set Plane Rockets");
					break;
				}
			}
			if (WhichMenu == 59)
			{
				switch (Scroll)
				{
				case 0:
					if (openweaponsforall)
						GivePedsGuns(0x1B06D571);
					else
						GivePedGun(0x1B06D571);
					break;
				case 1:
					if (openweaponsforall)
						GivePedsGuns(0x2BE6766B);
					else
						GivePedGun(0x2BE6766B);
					break;
				case 2:
					if (openweaponsforall)
						GivePedsGuns(0x9D07F764);
					else
						GivePedGun(0x9D07F764);
					break;
				case 3:
					if (openweaponsforall)
						GivePedsGuns(0xE284C527);
					else
						GivePedGun(0xE284C527);
					break;
				case 4:
					if (openweaponsforall)
						GivePedsGuns(0xBFEFFF6D);
					else
						GivePedGun(0xBFEFFF6D);
					break;
				case 5:
					if (openweaponsforall)
						GivePedsGuns(0x3656C8C1);
					else
						GivePedGun(0x3656C8C1);
					break;
				case 6:
					if (openweaponsforall)
						GivePedsGuns(0x61012683);
					else
						GivePedGun(0x61012683);
					break;
				case 7:
					if (openweaponsforall)
						GivePedsGuns(0x083839C4);
					else
						GivePedGun(0x083839C4);
					break;
				case 8:
					if (openweaponsforall)
						GivePedsGuns(0x7F7497E5);
					else
						GivePedGun(0x7F7497E5);
					break;
				case 9:
					if (openweaponsforall)
						GivePedsGuns(0x787F0BB);
					else
						GivePedGun(0x787F0BB);
					break;
				case 10:
					if (openweaponsforall)
						GivePedsGuns(0x47757124);
					else
						GivePedGun(0x47757124);
					break;
				case 11:
					if (openweaponsforall)
						GivePedsGuns(0xD04C944D);
					else
						GivePedGun(0xD04C944D);
					break;
				case 12:
					if (openweaponsforall)
						GivePedsGuns(0x63AB0442);
					else
						GivePedGun(0x63AB0442);
					break;
				case 13:
					if (openweaponsforall)
						GivePedsGuns(0xA89CB99E);
					else
						GivePedGun(0xA89CB99E);
					break;
				}
			}
			if (WhichMenu == 60)
			{
				switch (Scroll)
				{
				case 0:
					LoadYacht();
					break;
				case 1:
					LoadNY();
					break;
				case 2:
					hospital_ipl();
					break;
				case 3:
					jewelry_ipl();
					break;
				case 4:
					morgue_ipl();
					break;
				case 5:
					life_invader_ipl();
					break;
				case 6:
					fib_lobby_ipl();
					break;
				case 7:
					cluckn_bell_ipl();
					break;
				}
			}
			if (WhichMenu == 61)
			{
				switch (Scroll)
				{
				case 0:
					superjump = !superjump;
					PrintMessage(superjump ? "Super jump on" : "Super jump off");
					break;
				case 1:
					fireammo = !fireammo;
					PrintMessage(fireammo ? "Fire ammo on" : "Fire ammo off");
					break;
				case 2:
					explosivemelee = !explosivemelee;
					PrintMessage(explosivemelee ? "Explosive melee on" : "Explosive melee off");
					break;
				case 3:
					explosiveammo = !explosiveammo;
					PrintMessage(explosiveammo ? "Explosive ammo on" : "Explosive ammo off");
					break;
				case 4:
					superun = !superun;
					SET_PED_CAN_RAGDOLL(PLAYER_PED_ID(), !superun);
					PrintMessage(superun ? "Super run on" : "Super run off");
					break;
				case 5:
					fastswim = !fastswim;
					_0xB986FF47(PLAYER_ID(), fastswim ? 1.49 : 1);
					PrintMessage(fastswim ? "Fast swim on" : "Fast swim off");
					break;
				case 6:
					slideycars = !slideycars;
					Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
					SET_VEHICLE_REDUCE_GRIP(veh, slideycars ? 1 : 0);
					PrintMessage(slideycars ? "Slidey cars on" : "Slidey cars off");
					break;
				}
			}
			if (WhichMenu == 63)
			{
				switch (Scroll)
				{
				case 0:
					SpawnVehicle(0xA7EDE74D);
					break;
				case 1:
					SpawnVehicle(0xC3DDFDCE);
					break;
				case 2:
					SpawnVehicle(0x42F2ED16);
					break;
				case 3:
					SpawnVehicle(0x8B13F083);
					break;
				case 4:
					SpawnVehicle(0xFF22D208);
					break;
				case 5:
					SpawnVehicle(0x94204D89);
					break;
				case 6:
					SpawnVehicle(0x2560B2FC);
					break;
				case 7:
					SpawnVehicle(0x69F06B57);
					break;
				case 8:
					SpawnVehicle(0xD7278283);
					break;
				}
			}
			if (WhichMenu == 64)
			{
				switch (Scroll)
				{
				case 0:
					SpawnVehicle(0x3AF8C345);
					break;
				case 1:
					SpawnVehicle(0xB9210FD0);
					break;
				case 2:
					SpawnVehicle(0x8125BCF9);
					break;
				case 3:
					SpawnVehicle(0xB802DD46);
					break;
				case 4:
					SpawnVehicle(0x6210CBB0);
					break;
				case 5:
					SpawnVehicle(0xAA699BB6);
					break;
				case 6:
					SpawnVehicle(0x698521E3);
					break;
				case 7:
					SpawnVehicle(0x432AA566);
					break;
				case 8:
					SpawnVehicle(0x9CF21E0F);
					break;
				case 9:
					SpawnVehicle(0xEB298297);
					break;
				}
			}
			if (WhichMenu == 65)
			{
				switch (Scroll)
				{
				case 0:
					SpawnVehicle(0xCFCFEB3B);
					break;
				case 1:
					SpawnVehicle(0x32B29A4B);
					break;
				case 2:
					SpawnVehicle(0xCFCA3668);
					break;
				case 3:
					SpawnVehicle(0x4BA4E8DC);
					break;
				case 4:
					SpawnVehicle(0x9628879C);
					break;
				case 5:
					SpawnVehicle(0x462FE277);
					break;
				case 6:
					SpawnVehicle(0x1D06D681);
					break;
				}
			}
			if (WhichMenu == 66)
			{
				switch (Scroll)
				{
				case 0:
					SpawnVehicle(0x31F0B376);
					break;
				case 1:
					SpawnVehicle(0x2F03547B);
					break;
				case 2:
					SpawnVehicle(0xFCFCB68B);
					break;
				case 3:
					SpawnVehicle(0x2C634FBD);
					break;
				case 4:
					SpawnVehicle(0x9D0450CA);
					break;
				case 5:
					SpawnVehicle(0x3E48BF23);
					break;
				}
			}
			if (WhichMenu == 67)
			{
				switch (Scroll)
				{
				case 0:
					SpawnVehicle(0x2C509634);
					break;
				case 1:
					SpawnVehicle(0x77934CEE);
					break;
				case 2:
					SpawnVehicle(0x806B9CC3);
					break;
				case 3:
					SpawnVehicle(0xF79A00F7);
					break;
				case 4:
					SpawnVehicle(0xC9CEAF06);
					break;
				case 5:
					SpawnVehicle(0x4B6C568A);
					break;
				case 6:
					SpawnVehicle(0xDA288376);
					break;
				case 7:
					SpawnVehicle(0xCABD11E8);
					break;
				case 8:
					SpawnVehicle(0x11F76C14);
					break;
				case 9:
					SpawnVehicle(0x2EF89E46);
					break;
				case 10:
					SpawnVehicle(0x9C669788);
					break;
				case 11:
					SpawnVehicle(0x63ABADE7);
					break;
				}
			}
			if (WhichMenu == 68)
			{
				switch (Scroll)
				{
				case 0:
					SpawnVehicle(0xF7004C86);
					break;
				case 1:
					SpawnVehicle(0x15F27762);
					break;
				case 2:
					SpawnVehicle(0x39D6779E);
					break;
				case 3:
					SpawnVehicle(0xB39B0AE6);
					break;
				case 4:
					SpawnVehicle(0x761E2AD3);
					break;
				case 5:
					SpawnVehicle(0x81794C70);
					break;
				}
			}
			if (WhichMenu == 69)
			{
				switch (Scroll)
				{
				case 0:
					SpawnVehicle(0xC1CE1183);
					break;
				case 1:
					SpawnVehicle(0x3D961290);
					break;
				case 2:
					SpawnVehicle(0xE2E7D4AB);
					break;
				case 3:
					SpawnVehicle(0x33581161);
					break;
				case 4:
					SpawnVehicle(0xEF2295C9);
					break;
				case 5:
					SpawnVehicle(0xC2974024);
					break;
				case 6:
					SpawnVehicle(0x2DFF622F);
					break;
				}
			}
			if (WhichMenu == 70)
			{
				switch (Scroll)
				{
				case 0:
					TeleportToClient();
					break;
				case 1:
					TeleportIntoPlayerCar();
					break;
				case 2:
					players[SelectedClient].dropcash = !players[SelectedClient].dropcash;
					PrintMessage(Format(players[SelectedClient].dropcash ? "Cash drop enabled for %s" : "Cash drop disabled for %s", players[SelectedClient].name));
					break;
				case 3:
					GiveClientWeapons();
					break;
				case 4:
					RemoveAllWeapons();
					break;
				case 5:
					OwnedExplosion();
					break;
				case 6:
					ExplodePlayer(GET_PLAYER_PED(SelectedClient), true, false);
					break;
				case 7:
					Clone(GET_PLAYER_PED(SelectedClient));
					break;
				case 8:
					SpawnSWAT();
					break;
				case 9:
					SpawnChops();
					break;
				case 10:
					KickPlayer();
					break;
				case 11:
					WhichMenu = 149;
					Scroll = 0;
					goto end;
				case 12:
					players[SelectedClient].esp = !players[SelectedClient].esp;
					PrintMessage(Format(players[SelectedClient].esp ? "Now tracking %s" : "Stopped tracking %s", players[SelectedClient].name));
					break;
				case 13:
					RamWithBus();
					break;
				case 14:
					StealOutfit();
					break;
				case 15:
					WhichMenu = 148;
					Scroll = 0;
					goto end;
				case 16:
					players[SelectedClient].freeze_in_place = !players[SelectedClient].freeze_in_place;
					PrintMessage(Format(players[SelectedClient].freeze_in_place ? "%s is stuck in place" : "%s can now move", players[SelectedClient].name));
					break;
				}
			}
			if (WhichMenu == 71)
			{
				switch (Scroll)
				{
				case 0:
					FixNetCar();
					break;
				case 1:
					RandomNetCarColor();
					break;
				case 2:
					Slingshot();
					break;
				case 3:
					BoostPlayerVehicle();
					break;
				case 4:
					FlipCarOver();
					break;
				case 5:
					DeleteVehicle();
					break;
				case 6:
					FuckUpCar();
					break;
				case 7:
					players[SelectedClient].troll = !players[SelectedClient].troll;
					PrintMessage(Format(players[SelectedClient].troll ? "Vehicle troll enabled for %s\nAny cars they get into will be deleted" : "Vehicle troll disabled for %s", players[SelectedClient].name));
					break;
				case 8:
					FreezePlayerCar();
					break;
				case 9:
					UnfreezePlayerCar();
					break;
				case 10:
					jack_vehicle();
					break;
				}
			}
			if (WhichMenu == 72)
			{
				switch (Scroll)
				{
				case 0:
					AttachToClient();
					break;
				case 1:
					PiggyBackRide();
					break;
				case 2:
					RapePlayer();
					break;
				case 3:
					WhichMenu = 73;
					Scroll = 0;
					goto end;
				case 4:
					DetachFromEntity();
					break;
				}
			}
			if (WhichMenu == 73)
			{
				switch (Scroll)
				{
				case 0:
					WhichMenu = 150;
					Scroll = 0;
					goto end;
				case 1:
					LoopSpawnAndAttach(0xE0264F5D, SKEL_Head);
					break;
				case 2:
					LoopSpawnAndAttach(0x98EE1ACD, SKEL_Pelvis);
					break;
				case 3:
					LoopSpawnAndAttach(0x3DC31836, SKEL_ROOT);
					break;
				case 4:
					LoopSpawnAndAttach(0x0E3BA450, SKEL_ROOT);
					break;
				}
			}
			if (WhichMenu == 74)
			{
				switch (Scroll)
				{
				case 0:
					WhichMenu = 60;
					Scroll = 0;
					goto end;
				case 1:
					FirstPerson();
					break;
				case 2:
					NoClip();
					break;
				case 3:
					SpawnBatmobile();
					break;
				case 4:
					Chauffeur();
					break;
				case 5:
					ClearArea();
					break;
				case 6:
					MobileRadio();
					break;
				case 7:
					freeze_protection = !freeze_protection;
					PrintMessage(freeze_protection ? "Protection enabled\nClone spam freezing will be prevented" : "Protection disabled");
					break;
				case 8:
					ped_manager = !ped_manager;
					PrintMessage(ped_manager ? "Ped Manager enabled\nAim at a ped to modify!" : "Ped Manager disabled");
					break;
				case 9:
					restricted_areas = !restricted_areas;
					PrintMessage(restricted_areas ? "Area restrictions removed\nYou can now access Fort Zancudo and more without getting cops!" : "Restricted areas normalized", 4000);
					break;
				case 10:
					developer_mode();
					break;
				case 11:
					vehicle_freeze_protection = !vehicle_freeze_protection;
					VehicleFreezeProtection(vehicle_freeze_protection);
					PrintMessage(vehicle_freeze_protection ? "Vehicle freeze protection enabled" : "Vehicle freeze protection disabled");
					break;
				case 12:
					animation_protection = !animation_protection;
					patchGameEvent(NETWORK_START_SYNCED_SCENE_EVENT, animation_protection);
					PrintMessage(animation_protection ? "Animation/Teleport protection enabled" : "Animation/Teleport protection disabled");
					break;
				case 13:
					explosion_protection = !explosion_protection;
					patchGameEvent(FIRE_EVENT, explosion_protection);
					patchGameEvent(EXPLOSION_EVENT, explosion_protection);
					PrintMessage(explosion_protection ? "Explosion protection enabled" : "Explosion protection disabled");
					break;
				case 14:
					remove_weapons_protection = !remove_weapons_protection;
					patchGameEvent(REMOVE_WEAPON_EVENT, animation_protection);
					patchGameEvent(REMOVE_ALL_WEAPONS_EVENT, animation_protection);
					PrintMessage(animation_protection ? "Remove weapons protection enabled" : "Remove weapons protection disabled");
					break;
				case 15:
					ptfx_protection = !ptfx_protection;
					patchGameEvent(NETWORK_PTFX_EVENT, ptfx_protection);
					PrintMessage(ptfx_protection ? "Particle FX protection enabled" : "Particle FX protection disabled");
					break;
				case 16:
					disable_tasks_protection = !disable_tasks_protection;
					patchGameEvent(NETWORK_CLEAR_PED_TASKS_EVENT, disable_tasks_protection);
					PrintMessage(disable_tasks_protection ? "Disable tasks protection enabled" : "Disable tasks protection disabled");
					break;
				}
			}
			if (WhichMenu == 75)
			{
				switch (Scroll)
				{
				case 0:
					WhichMenu = 76;
					Scroll = 0;
					goto end;
				case 1:
					WhichMenu = 78;
					Scroll = 0;
					goto end;
				case 2:
					WhichMenu = 79;
					Scroll = 0;
					goto end;
				case 3:
					WhichMenu = 81;
					Scroll = 0;
					goto end;
				case 4:
					WhichMenu = 82;
					Scroll = 0;
					goto end;
				case 5:
					WhichMenu = 84;
					Scroll = 0;
					goto end;
				case 6:
					WhichMenu = 86;
					Scroll = 0;
					goto end;
				}
			}
			if (WhichMenu == 76)
			{
				wheeltype = HighEnd;
				wheelindex = Scroll;
				wheels = true;
			}
			if (WhichMenu == 78)
			{
				wheeltype = Lowrider;
				wheelindex = Scroll;
				wheels = true;
			}
			if (WhichMenu == 79)
			{
				wheeltype = Muscle;
				wheelindex = Scroll;
				wheels = true;
			}
			if (WhichMenu == 81)
			{
				wheeltype = Offroad;
				wheelindex = Scroll;
				wheels = true;
			}
			if (WhichMenu == 82)
			{
				wheeltype = Sport;
				wheelindex = Scroll;
				wheels = true;
			}
			if (WhichMenu == 84)
			{
				wheeltype = SUV;
				wheelindex = Scroll;
				wheels = true;
			}
			if (WhichMenu == 86)
			{
				wheeltype = Tuner;
				wheelindex = Scroll;
				wheels = true;
			}
			if (WhichMenu == 88)
			{
				switch (Scroll)
				{
				case 0:
					color_type = 1;
					WhichMenu = 135;
					Scroll = 0;
					goto end;
				case 1:
					color_type = 2;
					WhichMenu = 135;
					Scroll = 0;
					goto end;
				}
			}
			if (WhichMenu == 89)
			{
				switch (Scroll)
				{
				case 0:
					open_all_doors(PLAYER_PED_ID());
					break;
				case 1:
					open_door(PLAYER_PED_ID(), 0);
					break;
				case 2:
					open_door(PLAYER_PED_ID(), 1);
					break;
				case 3:
					open_door(PLAYER_PED_ID(), 2);
					break;
				case 4:
					open_door(PLAYER_PED_ID(), 3);
					break;
				case 5:
					open_door(PLAYER_PED_ID(), 4);
					break;
				case 6:
					delete_all_doors(PLAYER_PED_ID());
					break;
				}
			}
			if (WhichMenu == 90)
			{
				switch (Scroll)
				{
				case 0:
					NETWORK_EARN_FROM_ROCKSTAR(100000);
					PrintMessage("Added 100k cash to account");
					break;
				case 1:
					NETWORK_EARN_FROM_ROCKSTAR(1000000);
					PrintMessage("Added 1 million cash to account");
					break;
				case 2:
					NETWORK_EARN_FROM_ROCKSTAR(10000000);
					PrintMessage("Added 10 million cash to account");
					break;
				case 3:
					NETWORK_EARN_FROM_ROCKSTAR(25000000);
					PrintMessage("Added 25 million cash to account");
					break;
				case 4:
					keyboard_action = 5;
					DrawKeyboard(9);
					break;

				}
			}
			if (WhichMenu == 91)
			{
				switch (Scroll)
				{
				case 0:
					STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_XP_FM"), Levels[120 - 1], 0);
					STAT_SET_INT(GET_HASH_KEY("MP1_CHAR_XP_FM"), Levels[120 - 1], 0);
					PrintMessage("Set level 120");
					break;
				case 1:
					STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_XP_FM"), Levels[1000 - 1], 0);
					STAT_SET_INT(GET_HASH_KEY("MP1_CHAR_XP_FM"), Levels[1000 - 1], 0);
					PrintMessage("Set level 1000");
					break;
				case 2:
					STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_XP_FM"), Levels[5000 - 1], 0);
					STAT_SET_INT(GET_HASH_KEY("MP1_CHAR_XP_FM"), Levels[5000 - 1], 0);
					PrintMessage("Set level 5000");
					break;
				case 3:
					STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_XP_FM"), Levels[8000 - 1], 0);
					STAT_SET_INT(GET_HASH_KEY("MP1_CHAR_XP_FM"), Levels[8000 - 1], 0);
					PrintMessage("Set level 8000");
					break;
				case 4:
					keyboard_action = 6;
					DrawKeyboard(4);
					break;
				}
			}
			if (WhichMenu == 92)
			{
				switch (Scroll)
				{
				case 0:
					WhichMenu = 145;
					Scroll = 0;
					goto end;
				case 1:
					WhichMenu = 146;
					Scroll = 0;
					goto end;
				case 2:
					WhichMenu = 147;
					Scroll = 0;
					goto end;
				}
			}
			if (WhichMenu == 93)
			{
				if (model_client_guard)
					SpawnClientGuard(GET_HASH_KEY(MainCharacters[Scroll]));
				else if (model_my_guard)
					SpawnBodyguard(GET_HASH_KEY(MainCharacters[Scroll]), MainCharactersDisplay[Scroll]);
				else {
					set_player_model(GET_HASH_KEY(MainCharacters[Scroll]));
					PrintMessage(Format("Set model to %s", MainCharactersDisplay[Scroll]));
				}
			}
			if (WhichMenu == 94)
			{
				if (model_client_guard)
					SpawnClientGuard(GET_HASH_KEY(Animals[Scroll]));
				else if (model_my_guard)
					SpawnBodyguard(GET_HASH_KEY(Animals[Scroll]), AnimalsDisplay[Scroll]);
				else {
					set_player_model(GET_HASH_KEY(Animals[Scroll]));
					PrintMessage(Format("Set model to %s", AnimalsDisplay[Scroll]));
				}
			}
			if (WhichMenu == 95)
			{
				if (model_client_guard)
					SpawnClientGuard(GET_HASH_KEY(AmbientFemales[Scroll]));
				else if (model_my_guard)
					SpawnBodyguard(GET_HASH_KEY(AmbientFemales[Scroll]), AmbientFemalesDisplay[Scroll]);
				else {
					set_player_model(GET_HASH_KEY(AmbientFemales[Scroll]));
					PrintMessage(Format("Set model to %s", AmbientFemalesDisplay[Scroll]));
				}
			}
			if (WhichMenu == 96)
			{
				if (model_client_guard)
					SpawnClientGuard(GET_HASH_KEY(AmbientMale[Scroll]));
				else if (model_my_guard)
					SpawnBodyguard(GET_HASH_KEY(AmbientMale[Scroll]), AmbientMaleDisplay[Scroll]);
				else {
					set_player_model(GET_HASH_KEY(AmbientMale[Scroll]));
					PrintMessage(Format("Set model to %s", AmbientMaleDisplay[Scroll]));
				}
			}
			if (WhichMenu == 97)
			{
				if (model_client_guard)
					SpawnClientGuard(GET_HASH_KEY(Cutscene[Scroll]));
				else if (model_my_guard)
					SpawnBodyguard(GET_HASH_KEY(Cutscene[Scroll]), CutsceneDisplay[Scroll]);
				else {
					set_player_model(GET_HASH_KEY(Cutscene[Scroll]));
					PrintMessage(Format("Set model to %s", CutsceneDisplay[Scroll]));
				}
			}
			if (WhichMenu == 98)
			{
				if (model_client_guard)
					SpawnClientGuard(GET_HASH_KEY(GangFemale[Scroll]));
				else if (model_my_guard)
					SpawnBodyguard(GET_HASH_KEY(GangFemale[Scroll]), GangFemaleDisplay[Scroll]);
				else {
					set_player_model(GET_HASH_KEY(GangFemale[Scroll]));
					PrintMessage(Format("Set model to %s", GangFemaleDisplay[Scroll]));
				}
			}
			if (WhichMenu == 99)
			{
				if (model_client_guard)
					SpawnClientGuard(GET_HASH_KEY(GangMale[Scroll]));
				else if (model_my_guard)
					SpawnBodyguard(GET_HASH_KEY(GangMale[Scroll]), GangMaleDisplay[Scroll]);
				else {
					set_player_model(GET_HASH_KEY(GangMale[Scroll]));
					PrintMessage(Format("Set model to %s", GangMaleDisplay[Scroll]));
				}
			}
			if (WhichMenu == 100)
			{
				if (model_client_guard)
					SpawnClientGuard(GET_HASH_KEY(Story[Scroll]));
				else if (model_my_guard)
					SpawnBodyguard(GET_HASH_KEY(Story[Scroll]), StoryDisplay[Scroll]);
				else {
					set_player_model(GET_HASH_KEY(Story[Scroll]));
					PrintMessage(Format("Set model to %s", StoryDisplay[Scroll]));
				}
			}
			if (WhichMenu == 101)
			{
				if (model_client_guard)
					SpawnClientGuard(GET_HASH_KEY(Multiplayer[Scroll]));
				else if (model_my_guard)
					SpawnBodyguard(GET_HASH_KEY(Multiplayer[Scroll]), MultiplayerDisplay[Scroll]);
				else {
					set_player_model(GET_HASH_KEY(Multiplayer[Scroll]));
					PrintMessage(Format("Set model to %s", MultiplayerDisplay[Scroll]));
				}
			}
			if (WhichMenu == 102)
			{
				if (model_client_guard)
					SpawnClientGuard(GET_HASH_KEY(ScenarioFemale[Scroll]));
				else if (model_my_guard)
					SpawnBodyguard(GET_HASH_KEY(ScenarioFemale[Scroll]), ScenarioFemaleDisplay[Scroll]);
				else {
					set_player_model(GET_HASH_KEY(ScenarioFemale[Scroll]));
					PrintMessage(Format("Set model to %s", ScenarioFemaleDisplay[Scroll]));
				}
			}
			if (WhichMenu == 103)
			{
				if (model_client_guard)
					SpawnClientGuard(GET_HASH_KEY(ScenarioMale[Scroll]));
				else if (model_my_guard)
					SpawnBodyguard(GET_HASH_KEY(ScenarioMale[Scroll]), ScenarioMaleDisplay[Scroll]);
				else {
					set_player_model(GET_HASH_KEY(ScenarioMale[Scroll]));
					PrintMessage(Format("Set model to %s", ScenarioMaleDisplay[Scroll]));
				}
			}
			if (WhichMenu == 104)
			{
				if (model_client_guard)
					SpawnClientGuard(GET_HASH_KEY(StoryScenarioFemale[Scroll]));
				else if (model_my_guard)
					SpawnBodyguard(GET_HASH_KEY(StoryScenarioFemale[Scroll]), StoryScenarioFemaleDisplay[Scroll]);
				else {
					set_player_model(GET_HASH_KEY(StoryScenarioFemale[Scroll]));
					PrintMessage(Format("Set model to %s", StoryScenarioFemaleDisplay[Scroll]));
				}
			}
			if (WhichMenu == 105)
			{
				if (model_client_guard)
					SpawnClientGuard(GET_HASH_KEY(StoryScenarioMale[Scroll]));
				else if (model_my_guard)
					SpawnBodyguard(GET_HASH_KEY(StoryScenarioMale[Scroll]), StoryScenarioMaleDisplay[Scroll]);
				else {
					set_player_model(GET_HASH_KEY(StoryScenarioMale[Scroll]));
					PrintMessage(Format("Set model to %s", StoryScenarioMaleDisplay[Scroll]));
				}
			}
			if (WhichMenu == 118)
			{
				SET_TIMECYCLE_MODIFIER(Timecycles[Scroll]);
				PrintMessage(Format("Set vision to %s", Timecycles[Scroll]));
			}
			if (WhichMenu == 119)
			{
				switch (Scroll)
				{
				case 0:
					SET_PED_RANDOM_COMPONENT_VARIATION(pm_ent, 1);
					PrintMessage("Randomized ped's clothing");
					break;
				case 1:
					pm_to_me();
					break;
				case 2:
					give_wep_index = pm_ent;
					weapon_instance = 1;
					WhichMenu = 121;
					Scroll = 0;
					goto end;
				case 3:
					pm_set_as_guard();
					break;
				case 4:
					pm_waypoint_loop();
					break;
				case 5:
					CLONE_PED(pm_ent, 0, 1, 0);
					PrintMessage("Cloned ped");
					break;
				case 6:
					if (!NETWORK_IS_IN_SESSION())
						pm_switch_to_entity();
					else
						PrintMessage("This doesn't work online");
					break;
				case 7:
					SET_ENTITY_AS_MISSION_ENTITY(pm_ent, 0, 1);
					DELETE_PED(&pm_ent);
					PrintMessage("Deleted ped");
					Open = false;
					break;
				case 8:
					pm_kill();
					break;
				case 9:
					pm_revive();
					break;
				}
			}
			if (WhichMenu == 120)
			{
				switch (Scroll)
				{
				case 0:
					give_wep_index = PLAYER_PED_ID();
					weapon_instance = 0;
					WhichMenu = 121;
					Scroll = 0;
					goto end;
				case 1:
					GiveMeWeapons();
					break;
				case 2:
					RemoveMyWeapons();
					break;
				case 3:
					teleportgun = !teleportgun;
					PrintMessage(teleportgun ? "Teleport gun enabled" : "Teleport gun disabled");
					break;
				case 4:
					shoot_monies_toggle = !shoot_monies_toggle;
					PrintMessage(shoot_monies_toggle ? "Money gun enabled" : "Money gun disabled");
					break;
				case 5:
					osok = !osok;
					if (!osok)
						SET_PLAYER_WEAPON_DAMAGE_MODIFIER(PLAYER_ID(), 1.00f);
					PrintMessage(osok ? "One shot one kill enabled" : "One shot one kill disabled");
					break;
				case 6:
					InfAmmo = !InfAmmo;
					PrintMessage(InfAmmo ? "Unlimited ammo enabled" : "Unlimited ammo disabled");
					break;
				case 7:
					grav_gun = !grav_gun;
					PrintMessage(grav_gun ? "Gravity gun enabled" : "Gravity gun disabled");
					break;
				}
			}
			if (WhichMenu == 121)
			{
				switch (Scroll)
				{
				case 0:
					WhichMenu = 122;
					Scroll = 0;
					goto end;
				case 1:
					WhichMenu = 123;
					Scroll = 0;
					goto end;
				case 2:
					WhichMenu = 124;
					Scroll = 0;
					goto end;
				case 3:
					WhichMenu = 126;
					Scroll = 0;
					goto end;
				case 4:
					WhichMenu = 127;
					Scroll = 0;
					goto end;
				case 5:
					WhichMenu = 125;
					Scroll = 0;
					goto end;
				case 6:
					WhichMenu = 128;
					Scroll = 0;
					goto end;
				case 7:
					WhichMenu = 129;
					Scroll = 0;
					goto end;
				case 8:
					WhichMenu = 130;
					Scroll = 0;
					goto end;
				}
			}
			if (WhichMenu == 122)
			{
				switch (Scroll)
				{
				case 0:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_BAT"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_BAT"), 1);
					break;
				case 1:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_KNIFE"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_KNIFE"), 1);
					break;
				case 2:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_NIGHTSTICK"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_NIGHTSTICK"), 1);
					break;
				case 3:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_CROWBAR"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_CROWBAR"), 1);
					break;
				case 4:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_GOLFCLUB"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_GOLFCLUB"), 1);
					break;
				case 5:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_HAMMER"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_HAMMER"), 1);
					break;
				case 6:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_BOTTLE"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_BOTTLE"), 1);
					break;
				case 7:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_DAGGER"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_DAGGER"), 1);
					break;
				case 8:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_KNUCKLE"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_KNUCKLE"), 1);
					break;
				}
			}

			if (WhichMenu == 123)
			{
				switch (Scroll)
				{
				case 0:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_PISTOL"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_PISTOL"), 1);
					break;
				case 1:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_COMBATPISTOL"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_COMBATPISTOL"), 1);
					break;
				case 2:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_APPISTOL"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_APPISTOL"), 1);
					break;
				case 3:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_STUNGUN"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_STUNGUN"), 1);
					break;
				case 4:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_PISTOL50"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_PISTOL50"), 1);
					break;
				case 5:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_SNSPISTOL"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_SNSPISTOL"), 1);
					break;
				case 6:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_HEAVYPISTOL"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_HEAVYPISTOL"), 1);
					break;
				case 7:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_VINTAGEPISTOL"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_VINTAGEPISTOL"), 1);
					break;
				case 8:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_FLAREGUN"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_FLAREGUN"), 1);
					break;
				case 9:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_MARKSMANPISTOL"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_MARKSMANPISTOL"), 1);
					break;
				}
			}

			if (WhichMenu == 124)
			{
				switch (Scroll)
				{
				case 0:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_MICROSMG"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_MICROSMG"), 1);
					break;
				case 1:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_SMG"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_SMG"), 1);
					break;
				case 2:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_ASSAULTSMG"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_ASSAULTSMG"), 1);
					break;
				case 3:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_GUSENBERG"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_GUSENBERG"), 1);
					break;
				case 4:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_COMBATPDW"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_COMBATPDW"), 1);
					break;
				}
			}

			if (WhichMenu == 125)
			{
				switch (Scroll)
				{
				case 0:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_PUMPSHOTGUN"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_PUMPSHOTGUN"), 1);
					break;
				case 1:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_SAWNOFFSHOTGUN"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_SAWNOFFSHOTGUN"), 1);
					break;
				case 2:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_ASSAULTSHOTGUN"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_ASSAULTSHOTGUN"), 1);
					break;
				case 3:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_BULLPUPSHOTGUN"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_BULLPUPSHOTGUN"), 1);
					break;
				case 4:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_HEAVYSHOTGUN"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_HEAVYSHOTGUN"), 1);
					break;
				}
			}

			if (WhichMenu == 126)
			{
				switch (Scroll)
				{
				case 0:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_ASSAULTRIFLE"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_ASSAULTRIFLE"), 1);
					break;
				case 1:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_CARBINERIFLE"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_CARBINERIFLE"), 1);
					break;
				case 2:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_ADVANCEDRIFLE"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_ADVANCEDRIFLE"), 1);
					break;
				case 3:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_SPECIALCARBINE"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_SPECIALCARBINE"), 1);
					break;
				case 4:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_BULLPUPRIFLE"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_BULLPUPRIFLE"), 1);
					break;
				}
			}

			if (WhichMenu == 127)
			{
				switch (Scroll)
				{
				case 0:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_MG"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_MG"), 1);
					break;
				case 1:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_COMBATMG"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_COMBATMG"), 1);
					break;
				}
			}


			if (WhichMenu == 128)
			{
				switch (Scroll)
				{
				case 0:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_SNIPERRIFLE"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_SNIPERRIFLE"), 1);
					break;
				case 1:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_HEAVYSNIPER"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_HEAVYSNIPER"), 1);
					break;
				case 2:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_MARKSMANRIFLE"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_MARKSMANRIFLE"), 1);
					break;
				}
			}

			if (WhichMenu == 129)
			{
				switch (Scroll)
				{
				case 0:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_RPG"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_RPG"), 1);
					break;
				case 1:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_GRENADELAUNCHER"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_GRENADELAUNCHER"), 1);
					break;
				case 2:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_MINIGUN"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_MINIGUN"), 1);
					break;
				case 3:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_FIREWORK"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_FIREWORK"), 1);
					break;
				case 4:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_HOMINGLAUNCHER"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_HOMINGLAUNCHER"), 1);
					break;
				}
			}


			if (WhichMenu == 130)
			{
				switch (Scroll)
				{
				case 0:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_STICKYBOMB"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_STICKYBOMB"), 1);
					break;
				case 1:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_GRENADE"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_GRENADE"), 1);
					break;
				case 2:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_BZGAS"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_BZGAS"), 1);
					break;
				case 3:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_MOLOTOV"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_MOLOTOV"), 1);
					break;
				case 4:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_PROXMINE"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_PROXMINE"), 1);
					break;
				case 5:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_SNOWBALL"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_SNOWBALL"), 1);
					break;
				case 6:
					GIVE_DELAYED_WEAPON_TO_PED(give_wep_index, GET_HASH_KEY("WEAPON_FLARE"), 9999, 1);
					SET_CURRENT_PED_WEAPON(give_wep_index, GET_HASH_KEY("WEAPON_FLARE"), 1);
					break;
				}
			}
			if (WhichMenu == 131)
			{
				switch (Scroll)
				{
				case 0:
					keyboard_action = 3;
					DrawKeyboard(24);
					break;
				case 1:
					change_name_color(colors[name_color_index]);
					break;
				case 2:
					rockstar_logo();
					break;
				}
			}
			if (WhichMenu == 132)
			{
				switch (Scroll)
				{
				case 0:
					PlayAnim("rcmpaparazzo_2", "shag_loop_a");
					break;
				case 1:
					PlayAnim("rcmpaparazzo_2", "shag_loop_poppy");
					break;
				case 2:
					PlayAnim("ragdoll@human", "on_fire");
					break;
				case 3:
					PlayAnim("amb@world_human_push_ups@male@base", "base");
					break;
				case 4:
					PlayAnim("amb@world_human_sit_ups@male@base", "base");
					break;
				case 5:
					PlayAnim("mini@prostitutes@sexnorm_veh", "bj_loop_prostitute");
					break;
				case 6:
					PlayAnim("stungun@standing", "damage");
					break;
				case 7:
					PlayAnim("mini@strip_club@pole_dance@pole_dance1", "pd_dance_01");
					break;
				}
			}

			if (WhichMenu == 133)
			{
				set_movement(MovementsRaw[Scroll]);
				PrintMessage(Format("Set movement type to %s", Movements[Scroll]));
			}

			if (WhichMenu == 134)
			{
				TASK_START_SCENARIO_IN_PLACE(PLAYER_PED_ID(), RawScenarios[Scroll], 0, true);
				PrintMessage(Format("Playing scenario %s", Scenarios[Scroll]));
			}

			if (WhichMenu == 135)
			{
				switch (color_type)
				{
				case 1: //primary
					switch (Scroll)
					{
					case 0:
						Vehicle veh = GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 1);
						GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, &vehicle_r, &vehicle_g, &vehicle_b);
						WhichMenu = 136;
						Scroll = 0;
						goto end;
					case 1:
						ColorCycle();
						break;
					default:
						carPrimary = Scroll - 2;
						set_vehicle_colours();
					}
					break;
				case 2: //secondary
					switch (Scroll)
					{
					case 0:
						Vehicle veh = GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 1);
						GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, &vehicle_r, &vehicle_g, &vehicle_b);
						WhichMenu = 136;
						Scroll = 0;
						goto end;
					case 1:
						ColorCycle();
						break;
					default:
						carSecondary = Scroll - 2;
						set_vehicle_colours();
						break;
					}
					break;
				}
			}

			if (WhichMenu == 139)
			{
				switch (Scroll)
				{
				case 0:
					UnlimitedSnacks();
					break;
				case 1:
					StockUpAmmo();
					break;
				case 2:
					UnlimitedFireworks();
					break;
				case 3:
					UnlimitedArmour();
					break;
				}
			}
			if (WhichMenu == 140)
			{
				switch (Scroll)
				{
				case 0:
					MaxAllSkills();
					break;
				case 1:
					MaxSkill("MP0_SCRIPT_INCREASE_STAM");
					MaxSkill("MP1_SCRIPT_INCREASE_STAM");
					PrintMessage("Maxed out Stamina");
					break;
				case 2:
					MaxSkill("MP0_SCRIPT_INCREASE_STRN");
					MaxSkill("MP1_SCRIPT_INCREASE_STRN");
					PrintMessage("Maxed out Strength");
					break;
				case 3:
					MaxSkill("MP0_SCRIPT_INCREASE_SHO");
					MaxSkill("MP1_SCRIPT_INCREASE_SHO");
					PrintMessage("Maxed out Shooting");
					break;
				case 4:
					MaxSkill("MP0_SCRIPT_INCREASE_STL");
					MaxSkill("MP1_SCRIPT_INCREASE_STL");
					PrintMessage("Maxed out Stealth");
					break;
				case 5:
					MaxSkill("MP0_SCRIPT_INCREASE_LUNG");
					MaxSkill("MP1_SCRIPT_INCREASE_LUNG");
					PrintMessage("Maxed out Lung Capacity");
					break;
				case 6:
					MaxSkill("MP0_SCRIPT_INCREASE_DRIV");
					MaxSkill("MP1_SCRIPT_INCREASE_DRIV");
					PrintMessage("Maxed out Driving");
					break;
				case 7:
					MaxSkill("MP0_SCRIPT_INCREASE_FLY");
					MaxSkill("MP1_SCRIPT_INCREASE_FLY");
					PrintMessage("Maxed out Flying");
					break;
				case 8:
					ResetAllSkills();
					break;
				}
			}

			if (WhichMenu == 141)
			{
				switch (Scroll)
				{
				case 0:
					keyboard_action = 8;
					DrawKeyboard(8);
					break;
				case 1:
					keyboard_action = 9;
					DrawKeyboard(8);
					break;
				case 2:
					SetKills(kdr_kills);
					SetDeaths(kdr_deaths);
					PrintMessage("Applied kills and deaths to account");
					break;
				}
			}

			if (WhichMenu == 142)
			{
				switch (Scroll)
				{
				case 0:
					keyboard_action = 10;
					DrawKeyboard(8);
					break;
				case 1:
					keyboard_action = 11;
					DrawKeyboard(8);
					break;
				case 2:
					SetWins(cur_win_item);
					SetLosses(cur_loss_item);
					PrintMessage("Applied wins and losses to account");
				}
			}

			if (WhichMenu == 143)
			{

			}

			if (WhichMenu == 144)
			{
				if (!attach_custom_object)
					SpawnObject(GET_HASH_KEY(PropsRaw[Scroll]), (char*)PropsRaw[Scroll]);
				else
				{
					custom_attach_object_name = (char*)PropsRaw[Scroll];
					attach_custom_object = false;
					WhichMenu = 150;
					Scroll = 0;
					goto end;
				}
			}
			if (WhichMenu == 145)
			{
				Teleport(InsideCoords[Scroll][0], InsideCoords[Scroll][1], InsideCoords[Scroll][2]);
			}
			if (WhichMenu == 146)
			{
				Teleport(OutsideCoords[Scroll][0], OutsideCoords[Scroll][1], OutsideCoords[Scroll][2]);
			}
			if (WhichMenu == 147)
			{
				Teleport(IPLCoords[Scroll][0], IPLCoords[Scroll][1], IPLCoords[Scroll][2]);
			}
			if (WhichMenu == 148)
			{
				switch (Scroll)
				{
				case 0:
					GoodieSpawner(PICKUP_HEALTH_STANDARD);
					PrintMessage(Format("Dropped health for %s", players[SelectedClient].name));
					break;
				case 1:
					GoodieSpawner(PICKUP_ARMOUR_STANDARD);
					PrintMessage(Format("Dropped armour for %s", players[SelectedClient].name));
					break;
				case 2:
					GoodieSpawner(PICKUP_HEALTH_SNACK);
					GoodieSpawner(PICKUP_HEALTH_SNACK);
					GoodieSpawner(PICKUP_HEALTH_SNACK);
					GoodieSpawner(PICKUP_HEALTH_SNACK);
					GoodieSpawner(PICKUP_HEALTH_SNACK);
					GoodieSpawner(PICKUP_HEALTH_SNACK);
					PrintMessage(Format("Dropped snacks for %s", players[SelectedClient].name));
					break;
				case 3:
					GoodieSpawner(PICKUP_WEAPON_PISTOL);
					GoodieSpawner(PICKUP_WEAPON_MICROSMG);
					GoodieSpawner(PICKUP_WEAPON_CARBINERIFLE);
					GoodieSpawner(PICKUP_WEAPON_HEAVYSNIPER);
					GoodieSpawner(PICKUP_WEAPON_MG);
					GoodieSpawner(PICKUP_WEAPON_MINIGUN);
					GoodieSpawner(PICKUP_WEAPON_RPG);
					GoodieSpawner(PICKUP_WEAPON_GRENADELAUNCHER);
					GoodieSpawner(PICKUP_PARACHUTE);
					PrintMessage(Format("Dropped weapons for %s", players[SelectedClient].name));
					break;
				case 4:
					GoodieSpawner(PICKUP_AMMO_BULLET_MP);
					GoodieSpawner(PICKUP_AMMO_BULLET_MP);
					GoodieSpawner(PICKUP_AMMO_BULLET_MP);
					GoodieSpawner(PICKUP_AMMO_BULLET_MP);
					GoodieSpawner(PICKUP_AMMO_BULLET_MP);
					GoodieSpawner(PICKUP_AMMO_BULLET_MP);
					GoodieSpawner(PICKUP_AMMO_BULLET_MP);
					GoodieSpawner(PICKUP_AMMO_BULLET_MP);
					PrintMessage(Format("Dropped ammo for %s", players[SelectedClient].name));
					break;
				}
			}

			if (WhichMenu == 149)
			{
				switch (Scroll)
				{
				case 0:
					if (!text_all)
					{
						SendText("~f~NextGenUpdate.com!", SelectedClient);
						PrintMessage(Format("Sent '~f~NextGenUpdate.com!~w~' to %s", players[SelectedClient].name));
					}
					else
					{
						SendTextToAll("~f~NextGenUpdate.com!");
						PrintMessage("Sent '~f~NextGenUpdate.com!~w~' to all players");
					}
					break;
				case 1:
					if (!text_all)
					{
						SendText("Sent using The Tesseract by Tustin!", SelectedClient);
						PrintMessage(Format("Sent 'Sent using The Tesseract by Tustin' to %s", players[SelectedClient].name));
					}
					else
					{
						SendTextToAll("Sent using The Tesseract by Tustin!");
						PrintMessage("Sent 'Sent using The Tesseract by Tustin!' to all players");
					}
					break;
				case 2:
					if (!text_all)
					{
						SendText("~y~Rockstar~w~ has added $10000 to your account", SelectedClient);
						PrintMessage(Format("Sent '~y~Rockstar~w~ has added $10000 to your account' to %s", players[SelectedClient].name));
					}
					else
					{
						SendTextToAll("~y~Rockstar~w~ has added $10000 to your account");
						PrintMessage("Sent '~y~Rockstar~w~ has added $10000 to your account' to all players");
					}
					break;
				case 3:
					if (!text_all)
					{
						SendText("Ask for money = FREEZE", SelectedClient);
						PrintMessage(Format("Sent 'Ask for money = FREEZE' to %s", players[SelectedClient].name));
					}
					else
					{
						SendTextToAll("Ask for money = FREEZE");
						PrintMessage("Sent 'Ask for money = FREEZE' to all players");
					}
					break;
				case 4:
					if (!text_all)
					{
						SendText("Sing in your mic for ~y~$$$", SelectedClient);
						PrintMessage(Format("Sent 'Sing in your mic for ~y~$$$~w~' to %s", players[SelectedClient].name));
					}
					else
					{
						SendTextToAll("Sing in your mic for ~y~$$$");
						PrintMessage("Sent 'Sing in your mic for ~y~$$$~w~' to all players");
					}
					break;
				case 5:
					if (!text_all)
						keyboard_action = 12;
					else
						keyboard_action = 13;
					DrawKeyboard(24);
					break;
				}
			}

			if (WhichMenu == 150)
			{
				switch (Scroll)
				{
				case 0:
					attach_custom_object = true;
					WhichMenu = 144;
					Scroll = 0;
					goto end;
				case 8:
					if (custom_attach_bone_index > -1)
					{
						if (custom_attach_object_name != "None")
						{
							LoopSpawnAndAttach(GET_HASH_KEY(custom_attach_object_name), custom_attach_bone_index);
							custom_attach_object_name = "None";
							custom_attach_bone_index = -1;
							attach_object_bone_index = -1;
							WhichMenu = 73;
							Scroll = 0;
							goto end;
						}
						else
							PrintMessage("Choose an object to place first!");
					}
					else
						PrintMessage("Choose a bone to place the object on first!");
					break;
				default:
					custom_attach_bone_index = attach_bones[Scroll - 1];
					attach_object_bone_index = Scroll;
					break;

				}
			}
			if (WhichMenu == 151)
			{
				SET_PED_TO_RAGDOLL(PLAYER_PED_ID(), 4000, 5000, 1, 1, 1, 0);
				CREATE_NM_MESSAGE(true, Scroll);
				GIVE_PED_NM_MESSAGE(PLAYER_PED_ID());
			}
		end:
			PlaySound("SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET");
		}
		if (get_back_key_just_pressed(195, 250))
		{
			switch (WhichMenu)
			{
			case 1:
				Open = !Open;
				break;
			case 2:
				WhichMenu = 1;
				Scroll = 0;
				break;
			case 3:
				WhichMenu = 43;
				Scroll = 2;
				break;
			case 4:
				WhichMenu = 1;
				Scroll = 1;
				break;
			case 5:
				if (model_client_guard) {
					WhichMenu = 23;
					Scroll = 4;
					model_client_guard = false;
				}
				else if (model_my_guard)
				{
					WhichMenu = 29;
					Scroll = 0;
					model_my_guard = false;
				}
				else {
					WhichMenu = 1;
					Scroll = 4;
				}
				break;
			case 6:
				WhichMenu = 1;
				Scroll = 4;
				break;
			case 7:
				WhichMenu = 1;
				Scroll = 8;
				break;
			case 8:
				WhichMenu = 1;
				Scroll = 9;
				break;
			case 9:
				WhichMenu = 1;
				Scroll = 10;
				break;
			case 10:
				WhichMenu = 2;
				Scroll = 0;
				break;
			case 11:
				if (spawnforclient)
				{
					WhichMenu = 23;
					Scroll = 3;
					spawnforclient = false;
				}
				else {
					WhichMenu = 1;
					Scroll = 3;
				}
				break;
			case 12:
				WhichMenu = 11;
				Scroll = 0;
				break;
			case 13:
				WhichMenu = 11;
				Scroll = 1;
				break;
			case 14:
				WhichMenu = 11;
				Scroll = 2;
				break;
			case 15:
				WhichMenu = 11;
				Scroll = 3;
				break;
			case 16:
				WhichMenu = 11;
				Scroll = 4;
				break;
			case 17:
				WhichMenu = 11;
				Scroll = 10;
				break;
			case 18:
				WhichMenu = 11;
				Scroll = 15;
				break;
			case 19:
				WhichMenu = 11;
				Scroll = 16;
				break;
			case 20:
				WhichMenu = 11;
				Scroll = 17;
				break;
			case 21:
				if (guardattack)
				{
					WhichMenu = 29;
					Scroll = 2;
					guardattack = false;
				}
				else {
					WhichMenu = 43;
					Scroll = 0;
				}
				break;
			case 22:
				WhichMenu = 23;
				Scroll = 0;
				break;
			case 23:
				WhichMenu = 21;
				Scroll = SelectedClient;
				break;
			case 24:
				WhichMenu = 1;
				Scroll = 6;
				break;
			case 25:
				WhichMenu = 1;
				Scroll = 7;
				break;
			case 26:
				WhichMenu = 1;
				Scroll = 15;
				break;
			case 27:
				if (editlastattachedobj)
				{
					WhichMenu = 73;
					Scroll = 0;
					editlastattachedobj = false;
				}
				else {
					WhichMenu = 7;
					Scroll = 0;
				}
				break;
			case 28:
				WhichMenu = 43;
				Scroll = 1;
				break;
			case 29:
				WhichMenu = 1;
				Scroll = 5;
				break;
			case 30:
				WhichMenu = 29;
				Scroll = 0;
				break;
			case 31:
				WhichMenu = 33;
				Scroll = selectedped;
				break;
			case 32:
				WhichMenu = 1;
				Scroll = 12;
				break;
			case 33:
				WhichMenu = 29;
				Scroll = 1;
				break;
			case 34:
				WhichMenu = 11;
				Scroll = 12;
				break;
			case 35:
				WhichMenu = 1;
				Scroll = 13;
				break;
			case 36:
				WhichMenu = 4;
				Scroll = 0;
				break;
			case 37:
				WhichMenu = 36;
				Scroll = 1;
				break;
			case 38:
				WhichMenu = 36;
				Scroll = 2;
				break;
			case 39:
				WhichMenu = 36;
				Scroll = 3;
				break;
			case 40:
				WhichMenu = 36;
				Scroll = 4;
				break;
			case 41:
				WhichMenu = 36;
				Scroll = 5;
				break;
			case 42:
				WhichMenu = 36;
				Scroll = 5;
				break;
			case 43:
				WhichMenu = 1;
				Scroll = 2;
				break;
			case 44:
				WhichMenu = 36;
				Scroll = 7;
				break;
			case 45:
				WhichMenu = 36;
				Scroll = 8;
				break;
			case 46:
				WhichMenu = 36;
				Scroll = 0;
				break;
			case 47:
				WhichMenu = 46;
				Scroll = 0;
				break;
			case 48:
				WhichMenu = 46;
				Scroll = 1;
				break;
			case 49:
				WhichMenu = 46;
				Scroll = 2;
				break;
			case 50:
				WhichMenu = 46;
				Scroll = 3;
				break;
			case 51:
				WhichMenu = 46;
				Scroll = 4;
				break;
			case 52:
				WhichMenu = 7;
				Scroll = 1;
				break;
			case 53:
				WhichMenu = 7;
				Scroll = 1;
				break;
			case 54:
				WhichMenu = 11;
				Scroll = 11;
				break;
			case 55:
				WhichMenu = 2;
				Scroll = 3;
				break;
			case 56:
				WhichMenu = 4;
				Scroll = 3;
				break;
			case 57:
				WhichMenu = 4;
				Scroll = 1;
				break;
			case 58:
				WhichMenu = 4;
				Scroll = 2;
				break;
			case 59:
				if (openweaponsforall) {
					WhichMenu = 29;
					Scroll = 4;
				}
				else {
					WhichMenu = 31;
					Scroll = 1;
				}
				break;
			case 60:
				WhichMenu = 74;
				Scroll = 0;
				break;
			case 61:
				WhichMenu = 2;
				Scroll = 2;
				break;
			case 62:
				break;
			case 63:
				WhichMenu = 11;
				Scroll = 7;
				break;
			case 64:
				WhichMenu = 11;
				Scroll = 5;
				break;
			case 65:
				WhichMenu = 11;
				Scroll = 6;
				break;
			case 66:
				WhichMenu = 11;
				Scroll = 8;
				break;
			case 67:
				WhichMenu = 11;
				Scroll = 9;
				break;
			case 68:
				WhichMenu = 11;
				Scroll = 13;
				break;
			case 69:
				WhichMenu = 11;
				Scroll = 14;
				break;
			case 70:
				WhichMenu = 23;
				Scroll = 0;
				break;
			case 71:
				WhichMenu = 23;
				Scroll = 1;
				break;
			case 72:
				WhichMenu = 23;
				Scroll = 2;
				break;
			case 73:
				WhichMenu = 72;
				Scroll = 3;
				break;
			case 74:
				WhichMenu = 1;
				Scroll = 11;
				break;
			case 75:
				WhichMenu = 46;
				Scroll = 8;
				break;
			case 76:
				WhichMenu = 75;
				Scroll = 0;
				break;
			case 77:
				WhichMenu = 75;
				Scroll = 0;
				break;
			case 78:
				WhichMenu = 75;
				Scroll = 1;
				break;
			case 79:
				WhichMenu = 75;
				Scroll = 2;
				break;
			case 80:
				WhichMenu = 75;
				Scroll = 2;
				break;
			case 81:
				WhichMenu = 75;
				Scroll = 3;
				break;
			case 82:
				WhichMenu = 75;
				Scroll = 4;
				break;
			case 83:
				WhichMenu = 75;
				Scroll = 4;
				break;
			case 84:
				WhichMenu = 75;
				Scroll = 5;
				break;
			case 85:
				WhichMenu = 75;
				Scroll = 5;
				break;
			case 86:
				WhichMenu = 75;
				Scroll = 6;
				break;
			case 87:
				WhichMenu = 75;
				Scroll = 6;
				break;
			case 88:
				WhichMenu = 46;
				Scroll = 9;
				break;
			case 89:
				WhichMenu = 46;
				Scroll = 10;
				break;
			case 90:
				WhichMenu = 3;
				Scroll = 1;
				break;
			case 91:
				WhichMenu = 3;
				Scroll = 0;
				break;
			case 92:
				WhichMenu = 25;
				Scroll = 3;
				break;
			case 93:
				WhichMenu = 5;
				Scroll = 0;
				break;
			case 94:
				WhichMenu = 5;
				Scroll = 1;
				break;
			case 95:
				WhichMenu = 5;
				Scroll = 2;
				break;
			case 96:
				WhichMenu = 5;
				Scroll = 3;
				break;
			case 97:
				WhichMenu = 5;
				Scroll = 4;
				break;
			case 98:
				WhichMenu = 5;
				Scroll = 5;
				break;
			case 99:
				WhichMenu = 5;
				Scroll = 6;
				break;
			case 100:
				WhichMenu = 5;
				Scroll = 7;
				break;
			case 101:
				WhichMenu = 5;
				Scroll = 8;
				break;
			case 102:
				WhichMenu = 5;
				Scroll = 9;
				break;
			case 103:
				WhichMenu = 5;
				Scroll = 10;
				break;
			case 104:
				WhichMenu = 5;
				Scroll = 11;
				break;
			case 105:
				WhichMenu = 5;
				Scroll = 12;
				break;
			case 106:
				WhichMenu = 10;
				Scroll = 2;
				break;
			case 107:
				WhichMenu = 10;
				Scroll = 3;
				break;
			case 108:
				WhichMenu = 10;
				Scroll = 4;
				break;
			case 109:
				WhichMenu = 10;
				Scroll = 5;
				break;
			case 110:
				WhichMenu = 10;
				Scroll = 6;
				break;
			case 111:
				WhichMenu = 10;
				Scroll = 7;
				break;
			case 112:
				WhichMenu = 10;
				Scroll = 8;
				break;
			case 113:
				WhichMenu = 10;
				Scroll = 9;
				break;
			case 114:
				WhichMenu = 10;
				Scroll = 10;
				break;
			case 115:
				WhichMenu = 10;
				Scroll = 11;
				break;
			case 116:
				WhichMenu = 10;
				Scroll = 12;
				break;
			case 117:
				WhichMenu = 10;
				Scroll = 13;
				break;
			case 118:
				WhichMenu = 55;
				Scroll = 0;
				break;
			case 119:
				Open = false;
				break;
			case 120:
				WhichMenu = 2;
				Scroll = 1;
				break;
			case 121:
				switch (weapon_instance)
				{
				case 0:
					WhichMenu = 120;
					Scroll = 0;
					break;
				case 1:
					WhichMenu = 119;
					Scroll = 2;
					break;
				case 2:
					WhichMenu = 31;
					Scroll = 1;
					break;
				}
				break;
			case 122:
				WhichMenu = 121;
				Scroll = 0;
				break;
			case 123:
				WhichMenu = 121;
				Scroll = 1;
				break;
			case 124:
				WhichMenu = 121;
				Scroll = 2;
				break;
			case 125:
				WhichMenu = 121;
				Scroll = 5;
				break;
			case 126:
				WhichMenu = 121;
				Scroll = 3;
				break;
			case 127:
				WhichMenu = 121;
				Scroll = 4;
				break;
			case 128:
				WhichMenu = 121;
				Scroll = 6;
				break;
			case 129:
				WhichMenu = 121;
				Scroll = 7;
				break;
			case 130:
				WhichMenu = 121;
				Scroll = 8;
				break;
			case 131:
				WhichMenu = 43;
				Scroll = 3;
				break;
			case 132:
				WhichMenu = 24;
				Scroll = 0;
				break;
			case 133:
				WhichMenu = 24;
				Scroll = 1;
				break;
			case 134:
				WhichMenu = 24;
				Scroll = 2;
				break;
			case 135:
				WhichMenu = 88;
				switch (color_type)
				{
				default:
					Scroll = 0;
					break;
				case 2:
					Scroll = 1;
					break;
				}
				break;
			case 136:
				WhichMenu = 135;
				Scroll = 0;
				break;
			case 137:
				WhichMenu = 32;
				Scroll = 0;
				break;
			case 138:
				WhichMenu = 32;
				Scroll = 1;
				break;
			case 139:
				WhichMenu = 3;
				Scroll = 2;
				break;
			case 140:
				WhichMenu = 3;
				Scroll = 3;
				break;
			case 141:
				WhichMenu = 3;
				Scroll = 4;
				break;
			case 142:
				WhichMenu = 3;
				Scroll = 5;
				break;
			case 143:
				WhichMenu = 74;
				Scroll = 1;
				break;
			case 144:
				if (!attach_custom_object)
				{
					WhichMenu = 7;
					Scroll = 2;
				}
				else
				{
					attach_custom_object = false;
					WhichMenu = 150;
					Scroll = 0;
				}
				break;
			case 145:
				WhichMenu = 92;
				Scroll = 0;
				break;
			case 146:
				WhichMenu = 92;
				Scroll = 1;
				break;
			case 147:
				WhichMenu = 92;
				Scroll = 2;
				break;
			case 148:
				WhichMenu = 70;
				Scroll = 16;
				break;
			case 149:
				if (!text_all)
				{
					WhichMenu = 70;
					Scroll = 11;
				}
				else {
					WhichMenu = 28;
					Scroll = 6;
					text_all = false;
				}
				break;
			case 150:
				WhichMenu = 73;
				Scroll = 0;
				break;
			case 151:
				WhichMenu = 24;
				Scroll = 3;
				break;
			}
			PlaySound("CANCEL", "HUD_FRONTEND_DEFAULT_SOUNDSET");
		}
		if (get_left_key_just_pressed(0xcc, 75))
		{
			if (WhichMenu == 3)
			{
				switch (Scroll)
				{
				case 10:
					devtype--;
					if (devtype < 0)
						devtype = 3;
					rockstartoggle = true;
					break;
				}
			}
			if (WhichMenu == 61)
			{
				switch (Scroll)
				{
				case 7:
					slowmo--;
					if (slowmo < 0)
						slowmo = 3;
					switch (slowmo) {
					case 0:
						SET_TIME_SCALE(1);
						break;
					case 1:
						SET_TIME_SCALE(0.6);
						break;
					case 2:
						SET_TIME_SCALE(0.4);
						break;
					case 3:
						SET_TIME_SCALE(0.2);
						break;
					}
					break;
				}
			}
			if (WhichMenu == 27)
			{
				switch (Scroll)
				{
				case 1:
					obj_precision_index--;
					if (obj_precision_index < 0)
						obj_precision_index = 3;
					PrintMessage(Format("Set object editor precision to %.1f", object_precision_plus[obj_precision_index]));
					break;
				}
			}

			if (WhichMenu == 137)
			{
				switch (Scroll)
				{
				case 0:
					cur_menu_color_item--;
					if (cur_menu_color_item < 0)
						cur_menu_color_item = 2;
					break;
				}
			}

			if (WhichMenu == 106 + cur_component)
			{
				switch (Scroll)
				{
				case 0:
					if (cur_drawable == 0) {
						SET_PED_COMPONENT_VARIATION(_ID, cur_component, max_drawable, 0, 0);
					}
					else
						SET_PED_COMPONENT_VARIATION(_ID, cur_component, cur_drawable - 1, 0, 0);

					break;
				case 1:
					if (cur_texture == 0) {
						SET_PED_COMPONENT_VARIATION(_ID, cur_component, cur_drawable, max_texture, 0);
					}
					else
						SET_PED_COMPONENT_VARIATION(_ID, cur_component, cur_drawable, cur_texture - 1, 0);
					break;
				}
			}
			if (WhichMenu == 131)
			{
				switch (Scroll)
				{
				case 1:
					name_color_index--;
					if (name_color_index < 0)
						name_color_index = 9;
					break;
				}
			}

			if (WhichMenu == 138)
			{
				switch (Scroll)
				{
				case 0:
					cur_menu_font_item--;
					if (cur_menu_font_item < 0)
						cur_menu_font_item = 1;
					break;
				case 1:
					MenuFontSelectedItem[cur_menu_font_item][0]--;
					if (MenuFontSelectedItem[cur_menu_font_item][0] < 0)
						MenuFontSelectedItem[cur_menu_font_item][0] = 6;
					break;
				}
			}

			if (WhichMenu == 36)
			{
				if (LoadMods())
				{
					switch (Scroll)
					{
					case 1:
						vehicle_mods.engine--;
						if (vehicle_mods.engine < -1)
							vehicle_mods.engine = max.maxengine;
						if (vehicle_mods.engine != -1)
							set_vehicle_mod(Engine, vehicle_mods.engine);
						else
							remove_vehicle_mod(Engine);
						break;
					case 2:
						vehicle_mods.transmission--;
						if (vehicle_mods.transmission < -1)
							vehicle_mods.transmission = max.maxtransmission;
						if (vehicle_mods.transmission != -1)
							set_vehicle_mod(Transmission, vehicle_mods.transmission);
						else
							remove_vehicle_mod(Transmission);
						break;
					case 3:
						vehicle_mods.brakes--;
						if (vehicle_mods.brakes < -1)
							vehicle_mods.brakes = max.maxbrakes;
						if (vehicle_mods.brakes != -1)
							set_vehicle_mod(Brakes, vehicle_mods.brakes);
						else
							remove_vehicle_mod(Brakes);
						break;
					case 4:
						vehicle_mods.suspension--;
						if (vehicle_mods.suspension < -1)
							vehicle_mods.suspension = max.maxsuspension;
						if (vehicle_mods.suspension != -1)
							set_vehicle_mod(Suspension, vehicle_mods.suspension);
						else
							remove_vehicle_mod(Suspension);
						break;
					case 5:
						vehicle_mods.armour--;
						if (vehicle_mods.armour < -1)
							vehicle_mods.armour = max.maxarmour;
						if (vehicle_mods.armour != -1)
							set_vehicle_mod(Armour, vehicle_mods.armour);
						else
							remove_vehicle_mod(Armour);
						break;
					case 6:
						vehicle_mods.exhaust--;
						if (vehicle_mods.exhaust < -1)
							vehicle_mods.exhaust = max.maxexhaust;
						if (vehicle_mods.exhaust != -1)
							set_vehicle_mod(Exhaust, vehicle_mods.exhaust);
						else
							remove_vehicle_mod(Exhaust);
						break;
					case 8:
						vehicle_mods.plates--;
						if (vehicle_mods.plates < 0)
							vehicle_mods.plates = 5;
						set_vehicle_number_plate_text_index(vehicle_mods.plates);
						break;
					case 9:
						vehicle_mods.tint--;
						if (vehicle_mods.tint < 1)
							vehicle_mods.tint = 5;
						set_vehicle_window_tint(vehicle_mods.tint);
						break;
					}
				}
				else
					PrintMessage("Not in vehicle");
			}

			if (WhichMenu == 46)
			{
				if (LoadMods())
				{
					switch (Scroll)
					{
					case 0:
						vehicle_mods.fbumper--;
						if (vehicle_mods.fbumper < -1)
							vehicle_mods.fbumper = max.maxfbumper;
						if (vehicle_mods.fbumper != -1)
							set_vehicle_mod(FrontBumper, vehicle_mods.fbumper);
						else
							remove_vehicle_mod(FrontBumper);
						break;
					case 1:
						vehicle_mods.rbumper--;
						if (vehicle_mods.rbumper < -1)
							vehicle_mods.rbumper = max.maxrbumper;
						if (vehicle_mods.rbumper != -1)
							set_vehicle_mod(RearBumper, vehicle_mods.rbumper);
						else
							remove_vehicle_mod(RearBumper);
						break;
					case 2:
						vehicle_mods.spoiler--;
						if (vehicle_mods.spoiler < -1)
							vehicle_mods.spoiler = max.maxspoiler;
						if (vehicle_mods.spoiler != -1)
							set_vehicle_mod(Spoiler, vehicle_mods.spoiler);
						else
							remove_vehicle_mod(Spoiler);
						break;
					case 3:
						vehicle_mods.skirts--;
						if (vehicle_mods.skirts < -1)
							vehicle_mods.skirts = max.maxskirts;
						if (vehicle_mods.skirts != -1)
							set_vehicle_mod(Skirts, vehicle_mods.skirts);
						else
							remove_vehicle_mod(Skirts);
						break;
					case 4:
						vehicle_mods.hood--;
						if (vehicle_mods.hood < -1)
							vehicle_mods.hood = max.maxhood;
						if (vehicle_mods.hood != -1)
							set_vehicle_mod(Hood, vehicle_mods.hood);
						else
							remove_vehicle_mod(Hood);
						break;
					case 5:
						vehicle_mods.grille--;
						if (vehicle_mods.grille < -1)
							vehicle_mods.grille = max.maxgrille;
						if (vehicle_mods.grille != -1)
							set_vehicle_mod(Grille, vehicle_mods.grille);
						else
							remove_vehicle_mod(Grille);
						break;
					case 6:
						vehicle_mods.fender--;
						if (vehicle_mods.fender < -1)
							vehicle_mods.fender = max.maxfender;
						if (vehicle_mods.fender != -1)
							set_vehicle_mod(Fender, vehicle_mods.fender);
						else
							remove_vehicle_mod(Fender);
						break;
					case 7:
						vehicle_mods.roof--;
						if (vehicle_mods.roof < -1)
							vehicle_mods.roof = max.maxroof;
						if (vehicle_mods.roof != -1)
							set_vehicle_mod(Roof, vehicle_mods.roof);
						else
							remove_vehicle_mod(Roof);
						break;
					}
				}
				else PrintMessage("Not in vehicle");
			}
		}
		if (get_left_key_pressed(0xCC, 70))
		{
			if (WhichMenu == 8)
			{
				switch (Scroll)
				{
				case 13:
					int hours = GET_CLOCK_HOURS() - 1;
					if (hours < 0)
						hours = 23;
					NETWORK_OVERRIDE_CLOCK_TIME(hours, GET_CLOCK_MINUTES(), GET_CLOCK_SECONDS());
					break;
				case 14:
					int minutes = GET_CLOCK_MINUTES() - 1;
					if (minutes < 0)
						minutes = 59;
					NETWORK_OVERRIDE_CLOCK_TIME(GET_CLOCK_HOURS(), minutes, GET_CLOCK_SECONDS());
					break;
				case 15:
					int seconds = GET_CLOCK_SECONDS() - 1;
					if (seconds < 0)
						seconds = 59;
					NETWORK_OVERRIDE_CLOCK_TIME(GET_CLOCK_HOURS(), GET_CLOCK_MINUTES(), seconds);
					break;
				}
			}
			if (WhichMenu == 27)
			{
				switch (Scroll)
				{
				case 2:
					move_object_pos(0, object_precision_minus[obj_precision_index]);
					break;
				case 3:
					move_object_pos(1, object_precision_minus[obj_precision_index]);
					break;
				case 4:
					move_object_pos(2, object_precision_minus[obj_precision_index]);
					break;
				case 5:
					move_object_rot(0, object_precision_minus[obj_precision_index]);
					break;
				case 6:
					move_object_rot(1, object_precision_minus[obj_precision_index]);
					break;
				case 7:
					move_object_rot(2, object_precision_minus[obj_precision_index]);
					break;
				}
			}
			if (WhichMenu == 56)
			{
				switch (Scroll)
				{
				case 0:
					if (IS_PED_IN_ANY_VEHICLE(_ID, 1)) {
						rpm_mul--;
						if (rpm_mul < 0)
							rpm_mul = 100;
						Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
						_0xE943B09C(veh, rpm_mul);
						PrintMessage(Format("Decremented RPM multiplier to %f", rpm_mul));
					}
					break;
				case 1:
					if (IS_PED_IN_ANY_VEHICLE(_ID, 1)) {
						density_mul--;
						if (density_mul < 0)
							density_mul = 100;
						PrintMessage(Format("Decremented density multiplier to %i\nThis is set to all vehicles automatically", density_mul));
					}
					break;
				case 2:
					if (IS_PED_IN_ANY_VEHICLE(_ID, 1)) {
						torque_mul--;
						if (torque_mul < 0)
							torque_mul = 100;
						Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
						_0x642DA5AA(veh, (float)torque_mul);
						PrintMessage(Format("Decremented torque multiplier to %i", torque_mul));
					}
					break;
				case 3:
					if (IS_PED_IN_ANY_VEHICLE(_ID, 1)) {
						light_mul--;
						if (light_mul < 0)
							light_mul = 100;
						Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
						SET_VEHICLE_LIGHT_MULTIPLIER(veh, (float)light_mul);
						PrintMessage(Format("Decremented light multiplier to %i", light_mul));
					}
					break;
				}
			}

			if (WhichMenu == 136)
			{
				if (IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 1))
				{
					Vehicle veh = GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 1);
					switch (color_type)
					{
					case 1:
						GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, &vehicle_r, &vehicle_g, &vehicle_b);
						switch (Scroll)
						{
						case 0:
							vehicle_r--;
							if (vehicle_r < 0)
								vehicle_r = 255;
							SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, vehicle_r, vehicle_g, vehicle_b);
							break;
						case 1:
							vehicle_g--;
							if (vehicle_g < 0)
								vehicle_g = 255;
							SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, vehicle_r, vehicle_g, vehicle_b);
							break;
						case 2:
							vehicle_b--;
							if (vehicle_b < 0)
								vehicle_b = 255;
							SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, vehicle_r, vehicle_g, vehicle_b);
							break;
						}
						break;
					case 2:
						GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, &vehicle_r, &vehicle_g, &vehicle_b);
						switch (Scroll)
						{
						case 0:
							vehicle_r--;
							if (vehicle_r < 0)
								vehicle_r = 255;
							SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, vehicle_r, vehicle_g, vehicle_b);
							break;
						case 1:
							vehicle_g--;
							if (vehicle_g < 0)
								vehicle_g = 255;
							SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, vehicle_r, vehicle_g, vehicle_b);
							break;
						case 2:
							vehicle_b--;
							if (vehicle_b < 0)
								vehicle_b = 255;
							SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, vehicle_r, vehicle_g, vehicle_b);
							break;
						}
						break;
					}
				}
				else PrintMessage("Not in vehicle");
			}

			if (WhichMenu == 137)
			{
				switch (Scroll)
				{
				case 1:
					MenuColorSelectedItem[cur_menu_color_item][0]--;
					if (MenuColorSelectedItem[cur_menu_color_item][0] < 0)
						MenuColorSelectedItem[cur_menu_color_item][0] = 255;
					break;
				case 2:
					MenuColorSelectedItem[cur_menu_color_item][1]--;
					if (MenuColorSelectedItem[cur_menu_color_item][1] < 0)
						MenuColorSelectedItem[cur_menu_color_item][1] = 255;
					break;
				case 3:
					MenuColorSelectedItem[cur_menu_color_item][2]--;
					if (MenuColorSelectedItem[cur_menu_color_item][2] < 0)
						MenuColorSelectedItem[cur_menu_color_item][2] = 255;
					break;
				}
			}
			PlaySound("SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET");
		}

		if (get_right_key_just_pressed(0xCD, 75))
		{
			if (WhichMenu == 3)
			{
				switch (Scroll)
				{
				case 10:
					devtype++;
					if (devtype > 3)
						devtype = 0;
					rockstartoggle = true;
					break;
				}
			}

			if (WhichMenu == 27)
			{
				switch (Scroll)
				{
				case 1:
					obj_precision_index++;
					if (obj_precision_index > 3)
						obj_precision_index = 0;
					PrintMessage(Format("Set object editor precision to %f", object_precision_plus[obj_precision_index]));
					break;
				}
			}
			if (WhichMenu == 36)
			{
				if (LoadMods())
				{
					switch (Scroll)
					{
					case 1:
						vehicle_mods.engine++;
						if (vehicle_mods.engine > max.maxengine)
							vehicle_mods.engine = -1;
						if (vehicle_mods.engine != -1)
							set_vehicle_mod(Engine, vehicle_mods.engine);
						else
							remove_vehicle_mod(Engine);
						break;
					case 2:
						vehicle_mods.transmission++;
						if (vehicle_mods.transmission > max.maxtransmission)
							vehicle_mods.transmission = -1;
						if (vehicle_mods.transmission != -1)
							set_vehicle_mod(Transmission, vehicle_mods.transmission);
						else
							remove_vehicle_mod(Transmission);
						break;
					case 3:
						vehicle_mods.brakes++;
						if (vehicle_mods.brakes > max.maxbrakes)
							vehicle_mods.brakes = -1;
						if (vehicle_mods.brakes != -1)
							set_vehicle_mod(Brakes, vehicle_mods.brakes);
						else
							remove_vehicle_mod(Brakes);
						break;
					case 4:
						vehicle_mods.suspension++;
						if (vehicle_mods.suspension > max.maxsuspension)
							vehicle_mods.suspension = -1;
						if (vehicle_mods.suspension != -1)
							set_vehicle_mod(Suspension, vehicle_mods.suspension);
						else
							remove_vehicle_mod(Suspension);
						break;
					case 5:
						vehicle_mods.armour++;
						if (vehicle_mods.armour > max.maxarmour)
							vehicle_mods.armour = -1;
						if (vehicle_mods.armour != -1)
							set_vehicle_mod(Armour, vehicle_mods.armour);
						else
							remove_vehicle_mod(Armour);
						break;
					case 6:
						vehicle_mods.exhaust++;
						if (vehicle_mods.exhaust > max.maxexhaust)
							vehicle_mods.exhaust = -1;
						if (vehicle_mods.exhaust != -1)
							set_vehicle_mod(Exhaust, vehicle_mods.exhaust);
						else
							remove_vehicle_mod(Exhaust);
						break;
					case 8:
						vehicle_mods.plates++;
						if (vehicle_mods.plates > 5)
							vehicle_mods.plates = 0;
						set_vehicle_number_plate_text_index(vehicle_mods.plates);
						break;
					case 9:
						vehicle_mods.tint++;
						if (vehicle_mods.tint > 5)
							vehicle_mods.tint = 1;
						set_vehicle_window_tint(vehicle_mods.tint);
						break;
					}
				}
				else PrintMessage("Not in vehicle");
			}

			if (WhichMenu == 46)
			{
				if (LoadMods())
				{
					switch (Scroll)
					{
					case 0:
						vehicle_mods.fbumper++;
						if (vehicle_mods.fbumper > max.maxfbumper)
							vehicle_mods.fbumper = -1;
						if (vehicle_mods.fbumper != -1)
							set_vehicle_mod(FrontBumper, vehicle_mods.fbumper);
						else
							remove_vehicle_mod(FrontBumper);
						break;
					case 1:
						vehicle_mods.rbumper++;
						if (vehicle_mods.rbumper > max.maxrbumper)
							vehicle_mods.rbumper = -1;
						if (vehicle_mods.rbumper != -1)
							set_vehicle_mod(RearBumper, vehicle_mods.rbumper);
						else
							remove_vehicle_mod(RearBumper);
						break;
					case 2:
						vehicle_mods.spoiler++;
						if (vehicle_mods.spoiler > max.maxspoiler)
							vehicle_mods.spoiler = -1;
						if (vehicle_mods.spoiler != -1)
							set_vehicle_mod(Spoiler, vehicle_mods.spoiler);
						else
							remove_vehicle_mod(Spoiler);
						break;
					case 3:
						vehicle_mods.skirts++;
						if (vehicle_mods.skirts > max.maxskirts)
							vehicle_mods.skirts = -1;
						if (vehicle_mods.skirts != -1)
							set_vehicle_mod(Skirts, vehicle_mods.skirts);
						else
							remove_vehicle_mod(Skirts);
						break;
					case 4:
						vehicle_mods.hood++;
						if (vehicle_mods.hood > max.maxhood)
							vehicle_mods.hood = -1;
						if (vehicle_mods.hood != -1)
							set_vehicle_mod(Hood, vehicle_mods.hood);
						else
							remove_vehicle_mod(Hood);
						break;
					case 5:
						vehicle_mods.grille++;
						if (vehicle_mods.grille > max.maxgrille)
							vehicle_mods.grille = -1;
						if (vehicle_mods.grille != -1)
							set_vehicle_mod(Grille, vehicle_mods.grille);
						else
							remove_vehicle_mod(Grille);
						break;
					case 6:
						vehicle_mods.fender++;
						if (vehicle_mods.fender > max.maxfender)
							vehicle_mods.fender = -1;
						if (vehicle_mods.fender != -1)
							set_vehicle_mod(Fender, vehicle_mods.fender);
						else
							remove_vehicle_mod(Fender);
						break;
					case 7:
						vehicle_mods.roof++;
						if (vehicle_mods.roof > max.maxroof)
							vehicle_mods.roof = -1;
						if (vehicle_mods.roof != -1)
							set_vehicle_mod(Roof, vehicle_mods.roof);
						else
							remove_vehicle_mod(Roof);
						break;
					}
				}
				else PrintMessage("Not in vehicle");
			}
			if (WhichMenu == 61)
			{
				switch (Scroll)
				{
				case 7:
					slowmo++;
					if (slowmo > 3)
						slowmo = 0;
					switch (slowmo) {
					case 0:
						SET_TIME_SCALE(1);
						break;
					case 1:
						SET_TIME_SCALE(0.6);
						break;
					case 2:
						SET_TIME_SCALE(0.4);
						break;
					case 3:
						SET_TIME_SCALE(0.2);
						break;
					}
					break;
				}
			}
			if (WhichMenu == 131)
			{
				switch (Scroll)
				{
				case 1:
					name_color_index++;
					if (name_color_index > 9)
						name_color_index = 0;
					break;
				}
			}
			if (WhichMenu == 137)
			{
				switch (Scroll)
				{
				case 0:
					cur_menu_color_item++;
					if (cur_menu_color_item > 2)
						cur_menu_color_item = 0;
					break;
				}
			}
			if (WhichMenu == 138)
			{
				switch (Scroll)
				{
				case 0:
					cur_menu_font_item++;
					if (cur_menu_font_item > 1)
						cur_menu_font_item = 0;
					break;
				case 1:
					MenuFontSelectedItem[cur_menu_font_item][0]++;
					if (MenuFontSelectedItem[cur_menu_font_item][0] > 6)
						MenuFontSelectedItem[cur_menu_font_item][0] = 0;
					break;
				}
			}
		}

		if (get_right_key_pressed(0xCD, 70))
		{
			if (WhichMenu == 8)
			{
				switch (Scroll)
				{
				case 13:
					int hours = GET_CLOCK_HOURS() + 1;
					if (hours > 23)
						hours = 0;
					NETWORK_OVERRIDE_CLOCK_TIME(hours, GET_CLOCK_MINUTES(), GET_CLOCK_SECONDS());
					break;
				case 14:
					int minutes = GET_CLOCK_MINUTES() + 1;
					if (minutes > 59)
						minutes = 0;
					NETWORK_OVERRIDE_CLOCK_TIME(GET_CLOCK_HOURS(), minutes, GET_CLOCK_SECONDS());
					break;
				case 15:
					int seconds = GET_CLOCK_SECONDS() + 1;
					if (seconds > 59)
						seconds = 0;
					NETWORK_OVERRIDE_CLOCK_TIME(GET_CLOCK_HOURS(), GET_CLOCK_MINUTES(), seconds);
					break;
				}
			}
			if (WhichMenu == 27)
			{
				switch (Scroll)
				{
				case 2:
					move_object_pos(0, object_precision_plus[obj_precision_index]);
					break;
				case 3:
					move_object_pos(1, object_precision_plus[obj_precision_index]);
					break;
				case 4:
					move_object_pos(2, object_precision_plus[obj_precision_index]);
					break;
				case 5:
					move_object_rot(0, object_precision_plus[obj_precision_index]);
					break;
				case 6:
					move_object_rot(1, object_precision_plus[obj_precision_index]);
					break;
				case 7:
					move_object_rot(2, object_precision_plus[obj_precision_index]);
					break;
				}
			}
			if (WhichMenu == 56)
			{
				switch (Scroll)
				{
				case 0:
					if (IS_PED_IN_ANY_VEHICLE(_ID, 1)) {
						rpm_mul++;
						if (rpm_mul > 100)
							rpm_mul = 0;
						Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
						_0xE943B09C(veh, rpm_mul);
						PrintMessage(Format("Incremented RPM multiplier to %.0f", rpm_mul));
					}
					break;
				case 1:
					if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
					{
						density_mul++;
						if (density_mul > 100)
							density_mul = 0;
						PrintMessage(Format("Incremented density multiplier to %.0f\nThis is set to all vehicles automatically", density_mul));
					}
					break;
				case 2:
					if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
					{
						torque_mul++;
						if (torque_mul > 100)
							torque_mul = 0;
						Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
						_0x642DA5AA(veh, torque_mul);
						PrintMessage(Format("Incremented torque multiplier to %.0f", torque_mul));
					}
					break;
				case 3:
					if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
					{
						light_mul++;
						if (light_mul > 100)
							light_mul = 0;
						Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
						SET_VEHICLE_LIGHT_MULTIPLIER(veh, light_mul);
						PrintMessage(Format("Incremented light multiplier to %.0f", light_mul));
					}
					break;
				}
			}

			if (WhichMenu == 88)
			{
				switch (Scroll)
				{
				case 0:
					carPrimary++;
					if (carPrimary > 157)
						carPrimary = 0;
					set_vehicle_colours();
					break;
				case 1:
					carSecondary++;
					if (carSecondary > 157)
						carSecondary = 0;
					set_vehicle_colours();
					break;
				}
			}
			if (WhichMenu == 106 + cur_component)
			{
				switch (Scroll)
				{
				case 0:
					if (cur_drawable < max_drawable) {
						SET_PED_COMPONENT_VARIATION(_ID, cur_component, cur_drawable + 1, 0, 0);
					}
					else
						SET_PED_COMPONENT_VARIATION(_ID, cur_component, 0, 0, 0);


					break;
				case 1:
					if (cur_texture < max_texture) {
						SET_PED_COMPONENT_VARIATION(_ID, cur_component, cur_drawable, cur_texture + 1, 0);
					}
					else
						SET_PED_COMPONENT_VARIATION(_ID, cur_component, cur_drawable, 0, 0);
					break;
				}
			}

			if (WhichMenu == 136)
			{
				if (IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 1))
				{
					Vehicle veh = GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 1);
					switch (color_type)
					{
					case 1:
						GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, &vehicle_r, &vehicle_g, &vehicle_b);
						switch (Scroll)
						{
						case 0:
							vehicle_r++;
							if (vehicle_r > 255)
								vehicle_r = 0;
							SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, vehicle_r, vehicle_g, vehicle_b);
							break;
						case 1:
							vehicle_g++;
							if (vehicle_g > 255)
								vehicle_g = 0;
							SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, vehicle_r, vehicle_g, vehicle_b);
							break;
						case 2:
							vehicle_b++;
							if (vehicle_b > 255)
								vehicle_b = 0;
							SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, vehicle_r, vehicle_g, vehicle_b);
							break;
						}
						break;
					case 2:
						GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, &vehicle_r, &vehicle_g, &vehicle_b);
						switch (Scroll)
						{
						case 0:
							vehicle_r++;
							if (vehicle_r > 255)
								vehicle_r = 0;
							SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, vehicle_r, vehicle_g, vehicle_b);
							break;
						case 1:
							vehicle_g++;
							if (vehicle_g > 255)
								vehicle_g = 0;
							SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, vehicle_r, vehicle_g, vehicle_b);
							break;
						case 2:
							vehicle_b++;
							if (vehicle_b > 255)
								vehicle_b = 0;
							SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, vehicle_r, vehicle_g, vehicle_b);
							break;
						}
						break;
					}
				}
				else PrintMessage("Not in vehicle");
			}

			if (WhichMenu == 137)
			{
				switch (Scroll)
				{
				case 1:
					MenuColorSelectedItem[cur_menu_color_item][0]++;
					if (MenuColorSelectedItem[cur_menu_color_item][0] > 255)
						MenuColorSelectedItem[cur_menu_color_item][0] = 0;
					break;
				case 2:
					MenuColorSelectedItem[cur_menu_color_item][1]++;
					if (MenuColorSelectedItem[cur_menu_color_item][1] > 255)
						MenuColorSelectedItem[cur_menu_color_item][1] = 0;
					break;
				case 3:
					MenuColorSelectedItem[cur_menu_color_item][2]++;
					if (MenuColorSelectedItem[cur_menu_color_item][2] > 255)
						MenuColorSelectedItem[cur_menu_color_item][2] = 0;
					break;
				}
			}
			PlaySound("SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET");
		}
	}
	else
	{
		if (game_ticks < 60000)
			Tooltip("The Tesseract by Tustin~n~Press ~INPUT_FRONTEND_RS~ + ~INPUT_FRONTEND_LEFT~ to open");

		if (IS_CONTROL_JUST_PRESSED(2, 0xcc) && IS_CONTROL_JUST_PRESSED(2, 0xc9) || IS_DISABLED_CONTROL_PRESSED(2, 0xcc) && IS_DISABLED_CONTROL_PRESSED(2, 0xc9))
		{
			Open = true;
			Scroll = 0;
			WhichMenu = 1;
			PlaySound("SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET");
			NotifyAboveMap("Welcome to <FONT SIZE='18' COLOR='#3498db' FACE='$Font5'>The Tesseract</FONT>");
		}
	}
}
void main()
{
	constants();
	functions();
	monitor();
	is_player_online();
}
void draw_ui()
{
	render_menu();
	is_player_online();
}
void SetUpPeds()
{
	for (int i = 0; i < 6; i++)
	{
		peds[i].name = "None";
	}
}
void SetUpObjects()
{
	for (int i = 0; i < 30; i++)
	{
		objects[i].name = "None";
	}
}
extern "C" int _Tesseract_export_function(void)
{
    return CELL_OK;
}

extern "C" int _Tesseract_prx_entry(void)
{
	SetUpPeds();
	SetUpObjects();

	HookFunctionStart(0x3E3A20, (int)is_player_online, (int)main, 2); //IS_PLAYER_ONLINE
	HookFunctionStart(0x3D7B04, (int)is_player_online, (int)draw_ui, 2); //GET_INDEX_OF_CURRENT_LEVEL

	Dialog::msgdialog_mode = 2;
	Dialog::Show("Welcome to The Tesseract\n\nMenu opens up with R3 + DPAD Left\nhttp://NextGenUpdate.com\nhttps://tusticles.com");
    return SYS_PRX_RESIDENT;
}
