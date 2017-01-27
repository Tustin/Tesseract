#include "globals.h"
#include "colors.h"
#include "rp.h"
#include "vehicles.h"
#include "props.h"
#include "structures.h"
#include "enums.h"

opd_s LASTIMPACT = { 0x468F40, TOC };
bool(*GET_PED_LAST_WEAPON_IMPACT_COORD)(int id, Vector3 *coord) = (bool(*)(int, Vector3*))&LASTIMPACT;

opd_s CAMROT = { 0x3A39D8, TOC };
void(*SET_CAM_ROT)(int cam, Vector3 *rot, int unk) = (void(*)(int, Vector3*, int))&CAMROT;

opd_s CAMCOORD = { 0x3A38D0, TOC };
void(*SET_CAM_COORD)(int cam, Vector3 *pos) = (void(*)(int, Vector3*))&CAMCOORD;

opd_s GETVEHHASH = { 0x3EA514, TOC };
int(*_0xF8D7AF3B)(int playerId) = (int(*)(int))&GETVEHHASH;

opd_s PFXENT = { 0x1576784, TOC };
void(*PARTICLE_FX_ENTITY)(char* p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) = (void(*)(char* p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11))&PFXENT;

opd_s sprntf = { 0x14FE110, TOC };
int(*_sprintf)(char * s, size_t n, const char * format, ...) = (int(*)(char*, size_t, const char*, ...))&sprntf;

Objects objects[31];
_peds peds[6];
Players players[16];
MaxMods max;
VehicleMods vehicle_mods;

int attach_bones[7] = { SKEL_ROOT, SKEL_Head, SKEL_Pelvis, SKEL_L_UpperArm, SKEL_R_UpperArm, SKEL_L_Foot, SKEL_R_Foot };
Bone custom_attach_bone_index = -1;

int irand(int min, int max)
{
	return GET_RANDOM_INT_IN_RANGE(min, max);
}
int FindSeat(int entity)
{
	int seats = GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(entity);
	int num = -1;
	while (num < seats)
	{
		if (IS_VEHICLE_SEAT_FREE(entity, num))
			return num;
		num++;
	}
	return -2;
}
int delay_time = 0,
action_delay_time = 0,
back_delay_time = 0,
right_delay_time = 0,
left_delay_time = 0;
bool get_key_pressed(int control, int delay)
{
	if (game_ticks - delay_time < delay)
		return false;
	if (IS_DISABLED_CONTROL_PRESSED(2, control))
	{
		delay_time = game_ticks;
		return true;
	}
	return false;
}
bool get_key_just_pressed(int control, int delay)
{
	if (game_ticks - delay_time < delay)
		return false;
	if (IS_DISABLED_CONTROL_JUST_PRESSED(2, control))
	{
		delay_time = game_ticks;
		return true;
	}
	return false;
}
bool get_action_key_just_pressed(int control, int delay)
{
	if (game_ticks - action_delay_time < delay)
		return false;
	if (IS_DISABLED_CONTROL_JUST_PRESSED(2, control))
	{
		action_delay_time = game_ticks;
		return true;
	}
	return false;
}
bool get_back_key_just_pressed(int control, int delay)
{
	if (game_ticks - back_delay_time < delay)
		return false;
	if (IS_DISABLED_CONTROL_PRESSED(2, control))
	{
		back_delay_time = game_ticks;
		return true;
	}
	return false;
}
bool get_right_key_just_pressed(int control, int delay)
{
	if (game_ticks - right_delay_time < delay)
		return false;
	if (IS_DISABLED_CONTROL_JUST_PRESSED(2, control))
	{
		right_delay_time = game_ticks;
		return true;
	}
	return false;
}
bool get_right_key_pressed(int control, int delay)
{
	if (game_ticks - right_delay_time < delay)
		return false;
	if (IS_DISABLED_CONTROL_PRESSED(2, control))
	{
		right_delay_time = game_ticks;
		return true;
	}
	return false;
}
bool get_left_key_just_pressed(int control, int delay)
{
	if (game_ticks - left_delay_time < delay)
		return false;
	if (IS_DISABLED_CONTROL_JUST_PRESSED(2, control))
	{
		left_delay_time = game_ticks;
		return true;
	}
	return false;
}
bool get_left_key_pressed(int control, int delay)
{
	if (game_ticks - left_delay_time < delay)
		return false;
	if (IS_DISABLED_CONTROL_PRESSED(2, control))
	{
		left_delay_time = game_ticks;
		return true;
	}
	return false;
}
char msg[128];
const char *Format(const char *string, int ivar, ...)
{
	_sys_snprintf(msg, sizeof(msg), string, ivar);
	return msg;
}
const char *Format(const char *string, float fvar, ...)
{
	_sys_snprintf(msg, sizeof(msg), string, fvar);
	return msg;
}
const char *Format(const char *string, const char* svar, ...)
{
	_sys_snprintf(msg, sizeof(msg), string, svar);
	return msg;
}
const char *Format2(const char *string, const char* svar, const char* svar2)
{
	_sys_snprintf(msg, sizeof(msg), string, svar, svar2);
	return msg;
}
const char *Format2(const char *string, int ivar, int ivar2)
{
	_sys_snprintf(msg, sizeof(msg), string, ivar, ivar2);
	return msg;
}
const char *FormatSpeed(const char *string, const char* svar, float fvar)
{
	_sprintf(msg, sizeof(msg), string, svar, fvar);
	return msg;
}
Vector2 get_random_position_on_circumference(float radius)
{
	float rad = radius, x, y, angle = _rand() * pi * 2;
	x = COS(angle)*rad;
	y = SIN(angle)*rad;
	Vector2 pos = { x, y };
	return pos;
}

//reversed by Chr0m3
int global_read(int a_uiGlobalID)
{
	int Ptr = *(int*)((TunablesPtr - 0x04) + (((a_uiGlobalID / 0x40000) & 0x3F) * 4));
	if (Ptr != 0)
		return *(int*)(Ptr + ((a_uiGlobalID % 0x40000) * 4));
	return 0;
}
bool global_write(int a_uiGlobalID, int a_uiValue)
{
	int Ptr = *(int*)((TunablesPtr - 0x04) + (((a_uiGlobalID / 0x40000) & 0x3F) * 4));
	if (Ptr != 0)
	{
		*(int*)(Ptr + ((a_uiGlobalID % 0x40000) * 4)) = a_uiValue;
		return true;
	}
	return false;
}
void patchGameEvent(Address gEvent, bool toggle = true)
{
	int blr[] = { 0x4E800020 };
	int mflr[] = { 0x7C0802A6 };
	sys_dbg_write_process_memory(gEvent, toggle ? blr : mflr, 4);
	//write_process((void *)gEvent, toggle ? blr : mflr, 4);
}
#pragma region Drawing
void DrawText(const char* txt, int font, float x, float y, float size, int r, int g, int b, int a, bool center, bool right = false, bool outline = false)
{
	SET_TEXT_FONT(font);
	SET_TEXT_SCALE(size, size);
	SET_TEXT_COLOUR(r, g, b, a);
	SET_TEXT_OUTLINE();
	SET_TEXT_CENTRE(center);
	if (right)
	{
		SET_TEXT_RIGHT_JUSTIFY(true);
		SET_TEXT_WRAP(0, x);
	}
	SET_TEXT_ENTRY("STRING");
	ADD_TEXT_COMPONENT_STRING(txt);
	DRAW_TEXT(x, y);
}
void DrawText(const char* txt, int font, float x, float y, float size, int r, int g, int b, int a, bool center, bool outline)
{
	SET_TEXT_FONT(font);
	SET_TEXT_SCALE(size, size);
	SET_TEXT_COLOUR(r, g, b, a);
	if (outline)
		SET_TEXT_OUTLINE();
	SET_TEXT_CENTRE(center);
	SET_TEXT_ENTRY("STRING");
	ADD_TEXT_COMPONENT_STRING(txt);
	DRAW_TEXT(x, y);
}
void DrawTwoStrings(const char* txt1, char* txt2, int font, float x, float y, float size, int r, int g, int b, int a, bool center)
{
	SET_TEXT_FONT(font);
	SET_TEXT_SCALE(size, size);
	SET_TEXT_COLOUR(r, g, b, a);
	SET_TEXT_OUTLINE();
	SET_TEXT_CENTRE(center);
	SET_TEXT_ENTRY("TWOSTRINGS");
	ADD_TEXT_COMPONENT_STRING(txt1);
	ADD_TEXT_COMPONENT_STRING(txt2);
	DRAW_TEXT(x, y);
}
void DrawNumber(int num, int font, float x, float y, float size, int r, int g, int b, int a)
{
	SET_TEXT_FONT(font);
	SET_TEXT_SCALE(size, size);
	SET_TEXT_COLOUR(r, g, b, a);
	SET_TEXT_OUTLINE();
	SET_TEXT_ENTRY("NUMBER");
	ADD_TEXT_COMPONENT_INTEGER(num);
	DRAW_TEXT(x, y);
}
void DrawFloat(float num, int font, float x, float y, float size, int r, int g, int b, int a, int places)
{
	SET_TEXT_FONT(font);
	SET_TEXT_SCALE(size, size);
	SET_TEXT_COLOUR(r, g, b, a);
	SET_TEXT_OUTLINE();
	SET_TEXT_ENTRY("NUMBER");
	ADD_TEXT_COMPONENT_FLOAT(num, places);
	DRAW_TEXT(x, y);
}
void DrawMenuTitleText(const char* textBuffer)
{
	DrawText(textBuffer, MenuFontSelectedItem[0][0], 0.839844, 0.191832, 1.05, 255, 255, 255, 255, true);
}
void DrawItemCount(int scroll, int len, float x, float y, float size)
{
	SET_TEXT_SCALE(size, size);
	SET_TEXT_OUTLINE();
	SET_TEXT_CENTRE(true);
	SET_TEXT_ENTRY("CM_ITEM_COUNT");
	ADD_TEXT_COMPONENT_INTEGER(scroll);
	ADD_TEXT_COMPONENT_INTEGER(len);
	DRAW_TEXT(x, y);
}
void set_text_component(const char *type)
{
	_0x3AC9CB55("STRING");
	ADD_TEXT_COMPONENT_STRING(type);
	_0x386CE0B8();
}
void setup_instructions()
{
	mov = REQUEST_SCALEFORM_MOVIE("instructional_buttons");
	_0x7B48E696(mov, 255, 255, 255, 0);
	_0x215ABBE8(mov, "CLEAR_ALL");
	_0x02DBF2D7();
	_0x215ABBE8(mov, "SET_CLEAR_SPACE");
	_0x716777CB(200);
	_0x02DBF2D7();
}
void add_instruction(int index, char *text, int button)
{
	_0x215ABBE8(mov, "SET_DATA_SLOT");
	_0x716777CB(index);
	_0x716777CB(button);
	set_text_component(text);
	_0x02DBF2D7();
}
void close_instructions()
{
	_0x215ABBE8(mov, "DRAW_INSTRUCTIONAL_BUTTONS");
	_0x02DBF2D7();
	_0x215ABBE8(mov, "SET_BACKGROUND_COLOUR");
	_0x716777CB(0);
	_0x716777CB(0);
	_0x716777CB(0);
	_0x716777CB(80);
	_0x02DBF2D7();
}
void DrawInstructionalComponent()
{
	mov = REQUEST_SCALEFORM_MOVIE("instructional_buttons");
	_0x7B48E696(mov, 255, 255, 255, 0);
	_0x215ABBE8(mov, "CLEAR_ALL");
	_0x02DBF2D7();
	_0x215ABBE8(mov, "SET_CLEAR_SPACE");
	_0x716777CB(200);
	_0x02DBF2D7();
	_0x215ABBE8(mov, "SET_DATA_SLOT");
	_0x716777CB(0);
	_0x716777CB(BUTTON_A);
	set_text_component("Select");
	_0x02DBF2D7();
	_0x215ABBE8(mov, "SET_DATA_SLOT");
	_0x716777CB(1);
	_0x716777CB(BUTTON_B);
	set_text_component("Back");
	_0x02DBF2D7();
	_0x215ABBE8(mov, "SET_DATA_SLOT");
	_0x716777CB(2);
	_0x716777CB(BUTTON_DPAD_UP_DOWN);
	set_text_component("Scroll");
	_0x02DBF2D7();
	_0x215ABBE8(mov, "DRAW_INSTRUCTIONAL_BUTTONS");
	_0x02DBF2D7();
	_0x215ABBE8(mov, "SET_BACKGROUND_COLOUR");
	_0x716777CB(0);
	_0x716777CB(0);
	_0x716777CB(0);
	_0x716777CB(80);
	_0x02DBF2D7();
}
void PrintMessage(const char* Message)
{
	_0xF42C43C7("STRING");
	ADD_TEXT_COMPONENT_STRING(Message);
	_0x38F82261(2000, 1);
}
void PrintMessage(const char* Message, int ms)
{
	_0xF42C43C7("STRING");
	ADD_TEXT_COMPONENT_STRING(Message);
	_0x38F82261(ms, 1);
}
void NotifyAboveMap(const char* Message)
{
	_0x574EE85C("STRING");
	ADD_TEXT_COMPONENT_STRING(Message);
	_DRAW_NOTIFICATION(0, 1);
}
void Tooltip(const char* Message)
{
	_0xB245FC10("STRING");
	ADD_TEXT_COMPONENT_STRING(Message);
	_0xB59B530D(0, 0, 1, -1);
}
bool LoadTexture(char *dict)
{
	REQUEST_STREAMED_TEXTURE_DICT(dict, false);
	return HAS_STREAMED_TEXTURE_DICT_LOADED(dict);
}
void DrawSprite(char* dict, char* texture, float x, float y, float width, float height, float rot, int r, int g, int b, int alpha = 255)
{
	DRAW_SPRITE(dict, texture, x, y, width, height, rot, r, g, b, alpha);
}
int max_item_len = 20;
void LoadMenuItems(const char* arr[], int len)
{
	itemsOnPage = 0;
	for (int i = 0; i < len; i++)
	{
		if (Scroll < (max_item_len + 1) && i < (max_item_len + 1))
		{
			if (i == Scroll) {
				DrawText(arr[i], MenuFontSelectedItem[1][0], 0.729657, 0.25647797 + (i * 0.026094), 0.437500, 173, 216, 230, 255, false);
			}
			else {
				DrawText(arr[i], MenuFontSelectedItem[1][0], 0.729657, 0.25647797 + (i * 0.026094), 0.437500, 255, 255, 255, 255, false);
			}
		}
		else if (Scroll > max_item_len) {
			if (i == Scroll) {
				DrawText(arr[i], MenuFontSelectedItem[1][0], 0.729657, 0.25647797 + (max_item_len * 0.026094), 0.437500, 173, 216, 230, 255, false);
			}
			else if (i >= Scroll - (max_item_len) && i < Scroll) {
				int temp = i - (Scroll - max_item_len);
				DrawText(arr[i], MenuFontSelectedItem[1][0], 0.729657, 0.25647797 + (temp * 0.026094), 0.437500, 255, 255, 255, 255, false);
			}
		}
		itemsOnPage++;
	}
}
char* hash2car(Hash hash)
{
	for (int i = 0; i < 358; i++)
	{
		if (hash == GET_HASH_KEY(Vehicles[i]))
			return Vehicles[i];
	}
	return "Empty";
}
void DrawSwitch(const char* buffer, int line)
{
	if (Scroll < (max_item_len + 1) && line < (max_item_len + 1))
		DrawText(buffer, MenuFontSelectedItem[1][0], 0.921831, 0.25647797 + (line * 0.026094), 0.437500, 255, 255, 255, 255, true);
	else if (Scroll > max_item_len)
	{
		if (Scroll == line)
		{
			int temp = line - (Scroll - max_item_len);
			DrawText(buffer, MenuFontSelectedItem[1][0], 0.921831, 0.25647797 + (temp * 0.026094), 0.437500, 255, 255, 255, 255, true);
		}
		else if (line >= (Scroll - max_item_len) && line < Scroll) {
			int temp = line - (Scroll - max_item_len);
			DrawText(buffer, MenuFontSelectedItem[1][0], 0.921831, 0.25647797 + (temp * 0.026094), 0.437500, 255, 255, 255, 255, true);
		}
	}
}
void DrawSwitch(bool toggle, int line)
{
	const char* box_type = toggle ? "shop_box_tick" : "shop_box_blank";
	if (Scroll < (max_item_len + 1) && line < (max_item_len + 1))
		DrawSprite("CommonMenu", (char*)box_type, 0.950151, 0.27391547 + (line * 0.0262182617188), 0.031350, 0.046729, 0, 255, 255, 255);
	else if (Scroll > max_item_len)
	{
		if (Scroll == line)
		{
			int temp = line - (Scroll - max_item_len);
			DrawSprite("CommonMenu", (char*)box_type, 0.950151, 0.27391547 + (temp * 0.0262182617188), 0.031350, 0.046729, 0, 255, 255, 255);
		}
		else if (line >= (Scroll - max_item_len) && line < Scroll) {
			int temp = line - (Scroll - max_item_len);
			DrawSprite("CommonMenu", (char*)box_type, 0.950151, 0.27391547 + (temp * 0.0262182617188), 0.031350, 0.046729, 0, 255, 255, 255);
		}
	}
}
void DrawSwitch(int line)
{
	const char* tick = "shop_tick_icon";
	if (Scroll < (max_item_len + 1) && line < (max_item_len + 1))
		DrawSprite("CommonMenu", (char*)tick, 0.950151, 0.27391547 + (line * 0.0262182617188), 0.031350, 0.046729, 0, 255, 255, 255);
	else if (Scroll > max_item_len)
	{
		if (Scroll == line)
		{
			int temp = line - (Scroll - max_item_len);
			DrawSprite("CommonMenu", (char*)tick, 0.950151, 0.27391547 + (temp * 0.0262182617188), 0.031350, 0.046729, 0, 255, 255, 255);
		}
		else if (line >= (Scroll - max_item_len) && line < Scroll) {
			int temp = line - (Scroll - max_item_len);
			DrawSprite("CommonMenu", (char*)tick, 0.950151, 0.27391547 + (temp * 0.0262182617188), 0.031350, 0.046729, 0, 255, 255, 255);
		}
	}
}
void MenuToggles()
{
	if (WhichMenu == 2)
	{
		DrawSwitch(GodModePlayer, 4);
		DrawSwitch(!PlayerVisible, 5);
		DrawSwitch(spamcashonme, 6);
		DrawSwitch(Wanted, 7);
		DrawSwitch(kingmaker, 9);
		DrawSwitch(forcefield, 11);
		DrawSwitch(SuperMan, 12);
		DrawSwitch(health_regen, 13);
		DrawSwitch(armour_regen, 14);

	}
	if (WhichMenu == 3)
	{
		switch (devtype) {
		case 0:
			DrawSwitch("< black >", 10);
			break;
		case 1:
			DrawSwitch("< yellow >", 10);
			break;
		case 2:
			DrawSwitch("< blue >", 10);
			break;
		case 3:
			DrawSwitch("< none >", 10);
			break;
		}
	}
	if (WhichMenu == 4)
	{
		DrawSwitch(veh_invincible, 3);
		DrawSwitch(veh_invisible, 4);
		DrawSwitch(shootvehweapons, 5);
		DrawSwitch(nfs, 9);
		DrawSwitch(Speedo, 11);
		DrawSwitch(freezevehicle, 12);
		DrawSwitch(!nocollision, 13);
		DrawSwitch(nos, 16);
		DrawSwitch(dw, 17);
		DrawSwitch(da, 18);
		DrawSwitch(carjump, 22);
		DrawSwitch(seatbelt, 23);
	}
	if (WhichMenu == 8)
	{
		DrawSwitch(Format("< %i >", GET_CLOCK_HOURS()), 13);
		DrawSwitch(Format("< %i >", GET_CLOCK_MINUTES()), 14);
		DrawSwitch(Format("< %i >", GET_CLOCK_SECONDS()), 15);
	}
	if (WhichMenu == 9)
	{
		DrawSwitch(XMAS, 0);
		DrawSwitch(VDAY, 1);
		DrawSwitch(FOURTH, 2);
		DrawSwitch(SNOW, 3);
		DrawSwitch(FREE, 4);
		DrawSwitch(IDLE, 5);
	}
	if (WhichMenu == 11)
	{
		DrawSwitch(spawn_invincible_vehicle, 20);
		DrawSwitch(spawn_inside_vehicle, 21);
		DrawSwitch(spawn_suped_up_vehicle, 22);
	}
	if (WhichMenu == 27)
	{
		Vector3 pos = GET_ENTITY_COORDS(objects[current_object_index].id, 1), rot = GET_ENTITY_ROTATION(objects[current_object_index].id, 2);
		switch (obj_precision_index)
		{
		case 0:
			DrawSwitch("< Whole [10] >", 1);
			break;
		case 1:
			DrawSwitch("< Whole [5] >", 1);
			break;
		case 2:
			DrawSwitch("< Whole [1] >", 1);
			break;
		case 3:
			DrawSwitch("< Tenth [0.1] >", 1);
			break;
		}
		DrawSwitch(Format("< %.1f >", pos.x), 2);
		DrawSwitch(Format("< %.1f >", pos.y), 3);
		DrawSwitch(Format("< %.1f >", pos.z), 4);
		DrawSwitch(Format("< %.1f >", rot.x), 5);
		DrawSwitch(Format("< %.1f >", rot.y), 6);
		DrawSwitch(Format("< %.1f >", rot.z), 7);
	}

	if (WhichMenu == 28)
	{
		DrawSwitch(CashSpamAll, 0);
		DrawSwitch(tracer, 5);
	}
	if (WhichMenu == 29)
	{
		DrawSwitch(arepedsdancing, 3);
		DrawSwitch(doallpedsgodmode, 4);

	}
	if (WhichMenu == 31)
	{
		DrawSwitch(peds[selectedped].invincible, 2);
		DrawSwitch(peds[selectedped].dancing, 3);
	}
	if (WhichMenu == 32)
	{
		DrawSwitch(showplayerstats, 2);
		DrawSwitch(showlobbyinfo, 3);
		DrawSwitch(chatheads, 4);
		DrawSwitch(!use_mph, 5);
	}
	if (WhichMenu == 36)
	{
		DrawSwitch(Format2("%i/%i", vehicle_mods.engine + 1, max.maxengine + 1), 1);
		DrawSwitch(Format2("%i/%i", vehicle_mods.transmission + 1, max.maxtransmission + 1), 2);
		DrawSwitch(Format2("%i/%i", vehicle_mods.brakes + 1, max.maxbrakes + 1), 3);
		DrawSwitch(Format2("%i/%i", vehicle_mods.suspension + 1, max.maxsuspension + 1), 4);
		DrawSwitch(Format2("%i/%i", vehicle_mods.armour + 1, max.maxarmour + 1), 5);
		DrawSwitch(Format2("%i/%i", vehicle_mods.exhaust + 1, max.maxexhaust + 1), 6);
		char* plate_name = "Default";
		switch (vehicle_mods.plates)
		{
		case 0:
			plate_name = "Black & White 1";
			break;
		case 1:
			plate_name = "Yellow & Black";
			break;
		case 2:
			plate_name = "Yellow & Blue";
			break;
		case 3:
			plate_name = "Black & White 2";
			break;
		case 4:
			plate_name = "Black & White 3";
			break;
		case 5:
			plate_name = "North Yankton";
			break;
		}
		DrawSwitch(Format("< %s >", plate_name), 8);
		char* tint_name = "None";
		switch (vehicle_mods.tint)
		{
		case 4:
			tint_name = "None";
			break;
		case 3:
			tint_name = "Light Smoke";
			break;
		case 2:
			tint_name = "Dark Smoke";
			break;
		case 1:
			tint_name = "Limo";
			break;
		case 5:
			tint_name = "Pitch Black";
			break;
		}
		DrawSwitch(Format("< %s >", tint_name), 9);

	}
	if (WhichMenu == 46)
	{
		DrawSwitch(Format2("%i/%i", vehicle_mods.fbumper + 1, max.maxfbumper + 1), 0);
		DrawSwitch(Format2("%i/%i", vehicle_mods.rbumper + 1, max.maxrbumper + 1), 1);
		DrawSwitch(Format2("%i/%i", vehicle_mods.spoiler + 1, max.maxspoiler + 1), 2);
		DrawSwitch(Format2("%i/%i", vehicle_mods.skirts + 1, max.maxskirts + 1), 3);
		DrawSwitch(Format2("%i/%i", vehicle_mods.hood + 1, max.maxhood + 1), 4);
		DrawSwitch(Format2("%i/%i", vehicle_mods.grille + 1, max.maxgrille + 1), 5);
		DrawSwitch(Format2("%i/%i", vehicle_mods.fender + 1, max.maxfender + 1), 6);
		DrawSwitch(Format2("%i/%i", vehicle_mods.roof + 1, max.maxroof + 1), 7);
	}
	if (WhichMenu == 56)
	{
		DrawSwitch(Format("< %.0f >", rpm_mul), 0);
		DrawSwitch(Format("< %.0f >", density_mul), 1);
		DrawSwitch(Format("< %.0f >", torque_mul), 2);
		DrawSwitch(Format("< %.0f >", light_mul), 3);
	}
	if (WhichMenu == 61)
	{
		DrawSwitch(superjump, 0);
		DrawSwitch(fireammo, 1);
		DrawSwitch(explosivemelee, 2);
		DrawSwitch(explosiveammo, 3);
		DrawSwitch(superun, 4);
		DrawSwitch(fastswim, 5);
		DrawSwitch(slideycars, 6);
		switch (slowmo)
		{
		case 0:
			DrawSwitch("< off >", 7);
			break;
		default:
			DrawSwitch(Format("< %i >", slowmo), 7);
			break;
		}
	}
	if (WhichMenu == 57)
	{
		DrawSwitch(neons, 0);
		if (neons && current_neon_index != -1)
			DrawSwitch(current_neon_index + 1);
		DrawSwitch(rainbowneons, 7);

	}
	if (WhichMenu == 58)
	{
		if (shootvehweapons)
			DrawSwitch(current_vehicle_weapon_index + 1);
	}
	if (WhichMenu == 70)
	{
		DrawSwitch(players[SelectedClient].dropcash, 2);
		DrawSwitch(players[SelectedClient].esp, 12);
		DrawSwitch(players[SelectedClient].freeze_in_place, 16);

	}
	if (WhichMenu == 71)
	{
		DrawSwitch(players[SelectedClient].troll, 7);
	}
	if (WhichMenu == 74)
	{
		DrawSwitch(isfirstperson, 1);
		DrawSwitch(noclip, 2);
		DrawSwitch(mobileradio, 6);
		DrawSwitch(freeze_protection, 7);
		DrawSwitch(ped_manager, 8);
		DrawSwitch(restricted_areas, 9);
		DrawSwitch(dev_toggle, 10);
		DrawSwitch(vehicle_freeze_protection, 11);
		DrawSwitch(animation_protection, 12);
		DrawSwitch(explosion_protection, 13);
		DrawSwitch(remove_weapons_protection, 14);
		DrawSwitch(ptfx_protection, 15);
		DrawSwitch(disable_tasks_protection, 16);
	}

	if (WhichMenu == 106 + cur_component)
	{
		if (max_drawable == -1)
			DrawSwitch("N/A", 0);
		else {
			if (max_drawable == 0)
				DrawSwitch("0", 0);
			else
				DrawSwitch(Format2("< %i/%i >", cur_drawable, max_drawable), 0);
		}
		if (max_texture == -1)
			DrawSwitch("N/A", 1);
		else {
			if (max_texture == 0)
				DrawSwitch("0", 1);
			else
				DrawSwitch(Format2("< %i/%i >", cur_texture, max_texture), 1);
		}
	}
	if (WhichMenu == 120)
	{
		DrawSwitch(teleportgun, 3);
		DrawSwitch(shoot_monies_toggle, 4);
		DrawSwitch(osok, 5);
		DrawSwitch(InfAmmo, 6);
		DrawSwitch(grav_gun, 7);
	}
	if (WhichMenu == 131)
	{
		DrawSwitch(GET_PLAYER_NAME(PLAYER_ID()), 0);
		DrawSwitch(Format("< %s >", color_names[name_color_index]), 1);
	}
	if (WhichMenu == 136)
	{
		DrawSwitch(Format("< %i >", vehicle_r), 0);
		DrawSwitch(Format("< %i >", vehicle_g), 1);
		DrawSwitch(Format("< %i >", vehicle_b), 2);
	}
	if (WhichMenu == 137)
	{
		char* item = "< Header >";

		switch (cur_menu_color_item)
		{
		case 0:
			item = "< Header >";
			break;
		case 1:
			item = "< Background >";
			break;
		case 2:
			item = "< Scrollbar >";
			break;
		}

		DrawSwitch(item, 0);
		DrawSwitch(Format("< %i >", MenuColorSelectedItem[cur_menu_color_item][0]), 1);
		DrawSwitch(Format("< %i >", MenuColorSelectedItem[cur_menu_color_item][1]), 2);
		DrawSwitch(Format("< %i >", MenuColorSelectedItem[cur_menu_color_item][2]), 3);
	}

	if (WhichMenu == 138)
	{
		char* item = "< Header >";
		switch (cur_menu_font_item)
		{
		case 0:
			item = "< Header >";
			break;
		case 1:
			item = "< Options >";
			break;
		}
		DrawSwitch(item, 0);

		char* font = "< London 1960 >";
		switch (MenuFontSelectedItem[cur_menu_font_item][0])
		{
		case 0:
			font = "< London 1960 >";
			break;
		case 1:
			font = "< Sign Painter >";
			break;
		case 2:
			font = "< Rockstar TAG >";
			break;
		case 3:
			font = "< GTA V Leaderboard >";
			break;
		case 4:
			font = "< Cologne 60 >";
			break;
		case 5:
			font = "< London 1960 Numb >";
			break;
		case 6:
			font = "< Pricedown >";
			break;
		}
		DrawSwitch(font, 1);
	}

	if (WhichMenu == 141)
	{
		DrawSwitch(Format("%i", kdr_kills), 0);
		DrawSwitch(Format("%i", kdr_deaths), 1);
	}

	if (WhichMenu == 142)
	{
		DrawSwitch(Format("%i", cur_win_item), 0);
		DrawSwitch(Format("%i", cur_loss_item), 1);
	}
	if (WhichMenu == 150)
	{
		DrawSwitch(custom_attach_object_name, 0);
		if (attach_object_bone_index > -1)
			DrawSwitch(attach_object_bone_index);
	}
}
const char *menu_type;
void GrabStats(int index)
{
	const char* Stats[5] = { "~y~X: ~w~%f", "~y~Y: ~w~%f", "~y~Z: ~w~%f", "~y~Health: ~w~%i", "~y~Vehicle: ~w~%s" };
	const char* Stats2[4] = { "~y~Speed: ~w~%f", "~y~Room in car: ~w~%s", "~y~Distance: ~w~%f", "~y~Menu: ~w~%s" };
	Vector3 theirs, mine;
	theirs = GET_ENTITY_COORDS(GET_PLAYER_PED(index), 1);
	phealth = GET_ENTITY_HEALTH(GET_PLAYER_PED(index));
	pspeed = GET_ENTITY_SPEED(GET_PLAYER_PED(index)) * 3.6;
	if (use_mph)
		pspeed /= 1.60934;

	if (!IS_ENTITY_DEAD(GET_PLAYER_PED(index)))
	{
		if (IS_PED_IN_ANY_VEHICLE(GET_PLAYER_PED(index), 1))
		{
			Vehicle veh = GET_VEHICLE_PED_IS_IN(GET_PLAYER_PED(index), 0);
			int model = GET_ENTITY_MODEL(veh);
			pveh = GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model);
			if (FindSeat(veh) != -2)
				pseats = "Yes";
			else
				pseats = "No";
		}
		else {
			pveh = "On foot";
			pseats = "On foot";
		}
	}
	else
	{
		pveh = "Dead";
		pseats = "Dead";
	}
	switch (GET_PLAYER_MAX_ARMOUR(index))
	{
	case 2027:
		menu_type = "Limbo"; break;
	case 1327:
		menu_type = "Independence"; break;
	case 1234:
		menu_type = "Lexicon"; break;
	case 1337:
		menu_type = "Plethora"; break;
	case 5141:
		menu_type = "iLLiCiT"; break;
	case 666:
		menu_type = "YetAnotherGTAMenu"; break;
	case 5759:
		menu_type = "Trinity SPRX"; break;
	case 7777:
		menu_type = "Predator SPRX"; break;
	case 631:
		menu_type = "GNXKS"; break;
	case 69:
		menu_type = "Tesseract"; break;
	case 420:
		menu_type = "Glisten Is Gay"; break;
	case 28:
		menu_type = "Jarvis"; break;
	case 88:
		menu_type = "Phoenix"; break;
	case 97:
		menu_type = "Serendipity"; break;
	case 23:
		menu_type = "Metropolis"; break;
	case 71:
		menu_type = "SPRX_K"; break;
	case 1996:
		menu_type = "Power SPRX"; break;
	case 2001:
		menu_type = "Project Eke"; break;
	case 2000:
		menu_type = "ICE"; break;
	case 337:
		menu_type = "GenocideFreeze"; break;
	case 1084:
		menu_type = "BlueWindow"; break;
	default:
		menu_type = "None"; break;
	}
	mine = GET_ENTITY_COORDS(_ID, 1);
	pdist = GET_DISTANCE_BETWEEN_COORDS(mine.x, mine.y, mine.z, theirs.x, theirs.y, theirs.z, 1);
	/* END DATA BEGIN DRAWING */
	px = theirs.x;
	py = theirs.y;
	pz = theirs.z;
	if (!NETWORK_IS_IN_SESSION())
	{
		DRAW_RECT(0.840576, 0.125305, 0.249766, 0.117656, 0, 0, 0, 60); //background
		DrawSprite("CommonMenu", "gradient_nav", 0.840576, 0.050641, 0.249766, 0.031262, 0, MenuColorSelectedItem[0][0], MenuColorSelectedItem[0][1], MenuColorSelectedItem[0][2]);
		DrawSprite("CommonMenu", "header_gradient_script", 0.840576, 0.050641, 0.249766, 0.031262, 0, 0, 0, 0);
	}
	else
	{
		DRAW_RECT(0.840576, 0.125305, 0.249766, 0.117656, 0, 0, 0, 120); //background
		DrawSprite("CommonMenu", "gradient_nav", 0.840576, 0.050641, 0.249766, 0.031262, 0, MenuColorSelectedItem[0][0], MenuColorSelectedItem[0][1], MenuColorSelectedItem[0][2]);
		DrawSprite("CommonMenu", "header_gradient_script", 0.840576, 0.050641, 0.249766, 0.031262, 0, 0, 0, 0);
	}
	DrawText(GET_PLAYER_NAME(index), 4, 0.833235, 0.029364, 0.625000, 215, 215, 215, 215, true); //Player name

	DrawText(Format(Stats[0], px), 4, statswindowtext1, 0.066291 + (0 * 0.021), 0.5, 215, 215, 215, 215, false);
	DrawText(Format(Stats[1], py), 4, statswindowtext1, 0.066291 + (1 * 0.021), 0.5, 215, 215, 215, 215, false);
	DrawText(Format(Stats[2], pz), 4, statswindowtext1, 0.066291 + (2 * 0.021), 0.5, 215, 215, 215, 215, false);
	DrawText(Format(Stats[3], phealth), 4, statswindowtext1, 0.066291 + (3 * 0.021), 0.5, 215, 215, 215, 215, false);
	DrawText(Format(Stats[4], pveh), 4, statswindowtext1, 0.066291 + (4 * 0.021), 0.5, 215, 215, 215, 215, false);

	DrawText(Format(Stats2[0], pspeed), 4, statswindowtext2, 0.066291 + (0 * 0.021), 0.5, 215, 215, 215, 215, false);
	DrawText(Format(Stats2[1], pseats), 4, statswindowtext2, 0.066291 + (1 * 0.021), 0.5, 215, 215, 215, 215, false);
	DrawText(Format(Stats2[2], pdist), 4, statswindowtext2, 0.066291 + (2 * 0.021), 0.5, 215, 215, 215, 215, false);
	DrawText(Format(Stats2[3], menu_type), 4, statswindowtext2, 0.066291 + (3 * 0.021), 0.5, 215, 215, 215, 215, false);
}
void GetLobbyInfo()
{
	if (!NETWORK_IS_IN_SESSION()) return;
	float y = 0.737500;

	int host = NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0);
	int active = 16 - NETWORK_GET_NUM_CONNECTED_PLAYERS();
	DrawText(Format("~f~Host:~w~ %s", GET_PLAYER_NAME(host)), 4, 0.228125, y, 0.6, 255, 255, 255, 255, false);
	DrawText(Format("~f~Free Spots:~w~ %i", active), 4, 0.2281252, y += 0.04, 0.6, 255, 255, 255, 255, false);
}
void ESPLines()
{
	for (int i = 0; i < 16; i++)
	{
		if (NETWORK_IS_PLAYER_ACTIVE(i)) {
			Vector3 me, player;
			me = GET_ENTITY_COORDS(_ID, 1);
			player = GET_ENTITY_COORDS(GET_PLAYER_PED(i), 1);
			DRAW_LINE(me.x, me.y, me.z, player.x, player.y, player.z, 234, 235, 221, 225);
		}
	}
}
void Teleport(float x, float y, float z)
{
	Vector3 c;
	c.x = x;
	c.y = y;
	c.z = z;
	if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
		SET_ENTITY_COORDS(GET_VEHICLE_PED_IS_IN(_ID, 1), c.x, c.y, c.z, 1, 0, 0, 1);
	else
		SET_ENTITY_COORDS(_ID, c.x, c.y, c.z, 1, 0, 0, 1);

	PrintMessage("Teleported");
}
#pragma endregion
#pragma region Includes
void LoadPlayers()
{
	itemsOnPage = 0;
	for (int i = 0; i < 16; i++)
	{
		if (i == Scroll) {
			if (!NETWORK_IS_PLAYER_ACTIVE(i))
				DrawText("Empty", MenuFontSelectedItem[1][0], 0.729657, 0.25647797 + (i * 0.026094), 0.437500, 173, 216, 230, 255, false);
			else
				DrawText(GET_PLAYER_NAME(i), MenuFontSelectedItem[1][0], 0.729657, 0.25647797 + (i * 0.026094), 0.437500, 173, 216, 230, 255, false);
		}
		else {
			if (!NETWORK_IS_PLAYER_ACTIVE(i))
				DrawText("Empty", MenuFontSelectedItem[1][0], 0.729657, 0.25647797 + (i * 0.026094), 0.437500, 255, 255, 255, 255, false);
			else
				DrawText(GET_PLAYER_NAME(i), MenuFontSelectedItem[1][0], 0.729657, 0.25647797 + (i * 0.026094), 0.437500, 255, 255, 255, 255, false);
		}
		itemsOnPage++;
	}
}
void PlayerMonitor()
{
	for (int i = 0; i < 16; i++)
	{
		players[i].id = i;
		players[i].name = GET_PLAYER_NAME(i);
	}
}
void LoadPeds()
{
	itemsOnPage = 0;
	for (int i = 0; i < 6; i++)
	{
		if (i == Scroll)
			DrawText(peds[i].name, MenuFontSelectedItem[1][0], 0.729657, 0.25647797 + (i * 0.026094), 0.437500, 173, 216, 230, 255, false);
		else
			DrawText(peds[i].name, MenuFontSelectedItem[1][0], 0.729657, 0.25647797 + (i * 0.026094), 0.437500, 255, 255, 255, 255, false);
		itemsOnPage++;
	}
}
void LoadObjects()
{
	itemsOnPage = 0;
	for (int i = 0; i < 30; i++)
	{
		if (Scroll < (max_item_len + 1) && i < (max_item_len + 1))
		{
			if (i == Scroll)
				DrawText(objects[i].name, MenuFontSelectedItem[1][0], 0.729657, 0.25647797 + (i * 0.026094), 0.437500, 173, 216, 230, 255, false);
			else
				DrawText(objects[i].name, MenuFontSelectedItem[1][0], 0.729657, 0.25647797 + (i * 0.026094), 0.437500, 255, 255, 255, 255, false);
		}
		else if (Scroll > max_item_len) {
			if (i == Scroll) {
				DrawText(objects[i].name, MenuFontSelectedItem[1][0], 0.729657, 0.25647797 + (max_item_len * 0.026094), 0.437500, 173, 216, 230, 255, false);
			}
			else if (i >= Scroll - (max_item_len) && i < Scroll) {
				int temp = i - (Scroll - max_item_len);
				DrawText(objects[i].name, MenuFontSelectedItem[1][0], 0.729657, 0.25647797 + (temp * 0.026094), 0.437500, 255, 255, 255, 255, false);
			}
		}
		itemsOnPage++;
	}
}
void LoadLiveries()
{
	itemsOnPage = 0;
	Vehicle veh = GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 0);
	int liveries = GET_VEHICLE_LIVERY_COUNT(veh);
	for (int i = 0; i < liveries + 1; i++)
	{
		if (Scroll < (max_item_len + 1) && i < (max_item_len + 1))
		{
			if (i == Scroll)
				DrawText(Format("Livery %i", liveries + 1), MenuFontSelectedItem[1][0], 0.729657, 0.25647797 + (i * 0.026094), 0.437500, 173, 216, 230, 255, false);
			else
				DrawText(Format("Livery %i", liveries + 1), MenuFontSelectedItem[1][0], 0.729657, 0.25647797 + (i * 0.026094), 0.437500, 255, 255, 255, 255, false);
		}
		else if (Scroll > max_item_len) {
			if (i == Scroll) {
				DrawText(Format("Livery %i", liveries + 1), MenuFontSelectedItem[1][0], 0.729657, 0.25647797 + (max_item_len * 0.026094), 0.437500, 173, 216, 230, 255, false);
			}
			else if (i >= Scroll - (max_item_len) && i < Scroll) {
				int temp = i - (Scroll - max_item_len);
				DrawText(Format("Livery %i", liveries + 1), MenuFontSelectedItem[1][0], 0.729657, 0.25647797 + (temp * 0.026094), 0.437500, 255, 255, 255, 255, false);
			}
		}
		itemsOnPage++;
	}
}
void DisableControls()
{
	SET_CINEMATIC_BUTTON_ACTIVE(0);
	DISABLE_CONTROL_ACTION(0, 0 + 3);
	SET_INPUT_EXCLUSIVE(2, 176 + 3);
	SET_INPUT_EXCLUSIVE(2, 174 + 3);
	SET_INPUT_EXCLUSIVE(2, 175 + 3);
	SET_INPUT_EXCLUSIVE(2, 161 + 3);
	SET_INPUT_EXCLUSIVE(2, 162 + 3);
	DISABLE_CONTROL_ACTION(2, 174 + 3);
	DISABLE_CONTROL_ACTION(2, 175 + 3);
	DISABLE_CONTROL_ACTION(2, 163 + 3);
	DISABLE_CONTROL_ACTION(2, 164 + 3);
	DISABLE_CONTROL_ACTION(2, 161 + 3);
	DISABLE_CONTROL_ACTION(2, 162 + 3);
	SET_INPUT_EXCLUSIVE(2, 163 + 3);
	SET_INPUT_EXCLUSIVE(2, 164 + 3);
}
void PlaySound(char* sound, char* soundSet)
{
	PLAY_SOUND_FRONTEND(-1, sound, soundSet);
}

bool RequestLoop(int id)
{
	if (!NETWORK_IS_IN_SESSION()) return true;
	if (DOES_ENTITY_EXIST(id)) {
		int tries = 0;
		while (!NETWORK_HAS_CONTROL_OF_ENTITY(id) && tries < 10000)
		{
			NETWORK_REQUEST_CONTROL_OF_ENTITY(id);
			tries++;
		}
		return NETWORK_HAS_CONTROL_OF_ENTITY(id);
	}
	else {
		PrintMessage("Entity doesn't exist");
		return false;
	}
}

Vector3 get_coords_from_cam(float distance)
{
	Vector3 Rot = GET_GAMEPLAY_CAM_ROT(2);
	Vector3 Coord = GET_GAMEPLAY_CAM_COORD();

	Rot.y = distance * COS(Rot.x);
	Coord.x = Coord.x + Rot.y * SIN(Rot.z * -1.0f);
	Coord.y = Coord.y + Rot.y * COS(Rot.z * -1.0f);
	Coord.z = Coord.z + distance * SIN(Rot.x);

	return Coord;
}
#pragma endregion
#pragma region PlayerOptions
void DropCashOnMe()
{
	int prop = 0x113fd533;
	if (IS_MODEL_IN_CDIMAGE(prop))
		REQUEST_MODEL(prop);
	if (HAS_MODEL_LOADED(prop))
	{
		Vector3 c;
		c = GET_ENTITY_COORDS(_ID, 1);
		CREATE_AMBIENT_PICKUP(0xCE6FDD6B, c.x, c.y, c.z + 1, 0, 40000, prop, 0, 1);
	}
}
void DropCashAround(Ped player)
{
	int prop = 0x113fd533;
	if (IS_MODEL_IN_CDIMAGE(prop))
		REQUEST_MODEL(prop);
	if (HAS_MODEL_LOADED(prop))
	{
		Vector2 pos = get_random_position_on_circumference(4.0);
		Vector3 c;
		c = GET_ENTITY_COORDS(PLAYER_PED_ID(), 1);
		CREATE_AMBIENT_PICKUP(0xCE6FDD6B, c.x + pos.x, c.y + pos.y, c.z, 0, 40000, prop, 0, 1);
	}

}
void SuperJump()
{
	SET_SUPER_JUMP_THIS_FRAME(PLAYER_ID());
}
void Invisible()
{
	PlayerVisible = !PlayerVisible;
	SET_ENTITY_VISIBLE(_ID, PlayerVisible);
	PrintMessage(PlayerVisible ? "Invisibility off" : "Invisibility on");
}
void NeverWanted()
{
	CLEAR_PLAYER_WANTED_LEVEL(PLAYER_ID());
	SET_MAX_WANTED_LEVEL(0);
}
void ExplodePlayer(int id, bool isAudible, bool isInvisible)
{
	Vector3 c = GET_ENTITY_COORDS(id, 1);
	ADD_EXPLOSION(c.x, c.y, c.z, 5, 7.0f, isAudible, isInvisible, 0.0f);
}
void SuperManHax()
{
	Vector3 force = { 0, 100, 100 };
	Vector3 angle = { 0, 0, 0 };
	if (_0xCD71F11B(_ID))
		APPLY_FORCE_TO_ENTITY(_ID, 1, 0, 100, 100, 0, 0, 0, 0, 1, 0, 0, 0, 1);
}
void GiveMeWeapons()
{
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x3656C8C1, 9999, 1); // stun gun
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x99B507EA, 9999, 1); // knife
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x678B81B1, 9999, 1); // night stick
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x4E875F73, 9999, 1); // hammer
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x958A4A8F, 9999, 1); // bat
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x440E4788, 9999, 1); // golf club
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x84BD7BFD, 9999, 1); // crowbar
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x1B06D571, 9999, 5); // pistol
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x5EF9FEC4, 9999, 1); // combat pistol
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x22D8FE39, 9999, 1); // ap pistol
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x99AEEB3B, 9999, 1); // pistol 50.
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x13532244, 9999, 1); // micro smg
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x2BE6766B, 9999, 1); // smg
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0xEFE7E2DF, 9999, 1); // assault smg
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0xBFEFFF6D, 9999, 1); // assault rifle
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x83BF0278, 9999, 1); // carbine rifle
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0xAF113F99, 9999, 1); // advanced rifle
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x9D07F764, 9999, 1); // MG
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x7FD62962, 9999, 1); // combat mg
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x1D073A89, 9999, 1); // pump shotgun
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x7846A318, 9999, 1); // sawnoff shotgun
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0xE284C527, 9999, 1); // assault shotgun
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x9D61E50F, 9999, 1); // bullpupshotgun
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x05FC3C11, 9999, 1); // sniper
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x0C472FE2, 9999, 1); // heavy sniper
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0xA284510B, 9999, 1); // grenade launcher
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0xB1CA77B1, 9999, 1); // rpg
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x42BF8A85, 9999, 1); // minigun
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x93E220BD, 9999, 1); // grenades
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x2C3731D9, 9999, 1); // sticky bomb
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0xFDBC8A50, 9999, 1); // smoke grenade
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x34A67B97, 9999, 1); // petrol can
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x060EC506, 9999, 1); // fire extinguisher
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x24B17070, 9999, 1); // moltovs
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x497FACC3, 9999, 1); // flare
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0xFDBADCED, 9999, 1); // digiscanner
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x687652CE, 9999, 1); // stinger
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 600439132, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x61012683, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0xC0A3098D, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0xD205520E, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0xBFD21232, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x7F229F94, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x92A27487, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0xA89CB99E, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x3AABBBAA, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0xC734385A, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x63AB0442, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0xAB564B93, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x0787F0BB, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0xE232C28C, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0xD04C944D, 9999, 1); // ball 
	GIVE_DELAYED_WEAPON_TO_PED(_ID, 0x7F7497E5, 9999, 1);
}
void TheMaster()
{
	for (int i = 0; i < 16; i++)
	{
		if (NETWORK_IS_PLAYER_ACTIVE(i)) {
			if ((PLAYER_PED_ID() != GET_PLAYER_PED(i)) && (IS_PLAYER_FREE_AIMING_AT_ENTITY(i, _ID)) || (IS_PLAYER_TARGETTING_ENTITY(i, _ID)) && (!IS_ENTITY_DEAD(GET_PLAYER_PED(i))))
			{
				Vector3 c = GET_ENTITY_COORDS(GET_PLAYER_PED(i), 1);
				ADD_EXPLOSION(c.x, c.y, c.z, BLIMP, 15.00f, false, true, 0);
				PrintMessage("Who dares look at The Master?!");
			}
		}
	}
}
void Clone(int id)
{
	CLONE_PED(id, 0, 0, 0);
	PrintMessage("Cloned player");
}
void Ammo()
{
	Hash weap;
	GET_CURRENT_PED_WEAPON(_ID, &weap, 1);
	if (IS_WEAPON_VALID(weap))
	{
		int max;
		if (GET_MAX_AMMO(_ID, weap, &max))
		{
			SET_PED_AMMO(_ID, weap, max);

			max = GET_MAX_AMMO_IN_CLIP(_ID, weap, 1);
			if (max > 0)
				SET_AMMO_IN_CLIP(_ID, weap, max);
		}
	}
}
void RemoveMyWeapons()
{
	REMOVE_ALL_PED_WEAPONS(_ID, 1);
	PrintMessage("Removed all weapons");
}
void ExplosiveAmmo()
{
	SET_EXPLOSIVE_AMMO_THIS_FRAME(PLAYER_ID());
}
void FireAmmo()
{
	SET_FIRE_AMMO_THIS_FRAME(PLAYER_ID());
}
void ExplosiveMelee()
{
	SET_EXPLOSIVE_MELEE_THIS_FRAME(PLAYER_ID());
}
#pragma region IPLs
void LoadYacht()
{
	if (IS_IPL_ACTIVE("hei_yacht_heist"))
	{
		REMOVE_IPL("hei_yacht_heist");
		REMOVE_IPL("CJ_IOABoat");
		REMOVE_IPL("smboat");
		PrintMessage("Unloaded heist yacht");
	}
	else {
		REQUEST_IPL("hei_yacht_heist");
		REQUEST_IPL("CJ_IOABoat");
		REQUEST_IPL("smboat");

		Teleport(-2045.8f, -1031.2f, 11.9f);
		PrintMessage("Loaded heist yacht");
	}
}
void LoadNY()
{
	if (IS_IPL_ACTIVE("prologue01"))
	{
		REMOVE_IPL("prologue01");
		REMOVE_IPL("prologue01c");
		REMOVE_IPL("prologue01d");
		REMOVE_IPL("prologue01e");
		REMOVE_IPL("prologue01f");
		REMOVE_IPL("prologue01g");
		REMOVE_IPL("prologue01h");
		REMOVE_IPL("prologue01i");
		REMOVE_IPL("prologue01j");
		REMOVE_IPL("prologue01k");
		REMOVE_IPL("prologue01z");
		REMOVE_IPL("prologue02");
		REMOVE_IPL("prologue03");
		REMOVE_IPL("prologue03b");
		REMOVE_IPL("prologue04");
		REMOVE_IPL("prologue04b");
		REMOVE_IPL("prologue05");
		REMOVE_IPL("prologue05b");
		REMOVE_IPL("prologue06");
		REMOVE_IPL("prologue06b");
		REMOVE_IPL("prologue06_int");
		REMOVE_IPL("prologuerd");
		REMOVE_IPL("prologuerdb");
		REMOVE_IPL("prologue_DistantLights");
		REMOVE_IPL("prologue_LODLights");
		REMOVE_IPL("prologue_m2_door");

		PrintMessage("Unloaded North Yankton");
	}
	else
	{
		REQUEST_IPL("prologue01");
		REQUEST_IPL("prologue01c");
		REQUEST_IPL("prologue01d");
		REQUEST_IPL("prologue01e");
		REQUEST_IPL("prologue01f");
		REQUEST_IPL("prologue01g");
		REQUEST_IPL("prologue01h");
		REQUEST_IPL("prologue01i");
		REQUEST_IPL("prologue01j");
		REQUEST_IPL("prologue01k");
		REQUEST_IPL("prologue01z");
		REQUEST_IPL("prologue02");
		REQUEST_IPL("prologue03");
		REQUEST_IPL("prologue03b");
		REQUEST_IPL("prologue04");
		REQUEST_IPL("prologue04b");
		REQUEST_IPL("prologue05");
		REQUEST_IPL("prologue05b");
		REQUEST_IPL("prologue06");
		REQUEST_IPL("prologue06b");
		REQUEST_IPL("prologue06_int");
		REQUEST_IPL("prologuerd");
		REQUEST_IPL("prologuerdb");
		REQUEST_IPL("prologue_DistantLights");
		REQUEST_IPL("prologue_LODLights");
		REQUEST_IPL("prologue_m2_door");

		Teleport(3360.19f, -4849.67f, 111.8f);
		PrintMessage("Loaded North Yankton");
	}
}

void hospital_ipl()
{
	if (IS_IPL_ACTIVE("RC12B_Destroyed"))
	{
		REMOVE_IPL("RC12B_Destroyed");
		REMOVE_IPL("RC12B_HospitalInterior");
		REQUEST_IPL("RC12B_Default");
		REQUEST_IPL("RC12B_Fixed");

		PrintMessage("Removed destroyed hospital");
	}
	else
	{
		REMOVE_IPL("RC12B_Default");
		REMOVE_IPL("RC12B_Fixed");
		REQUEST_IPL("RC12B_Destroyed");
		REQUEST_IPL("RC12B_HospitalInterior");

		Teleport(356.8, -590.1f, 43.3f);
		PrintMessage("Loaded destroyed hospital");
	}
}

void jewelry_ipl()
{
	if (IS_IPL_ACTIVE("post_hiest_unload"))
	{
		REMOVE_IPL("post_hiest_unload");
		REQUEST_IPL("jewel2fake");
		REQUEST_IPL("bh1_16_refurb");

		PrintMessage("Removed jewelry store");
	}
	else
	{
		REMOVE_IPL("jewel2fake");
		REMOVE_IPL("bh1_16_refurb");
		REQUEST_IPL("post_hiest_unload");

		Teleport(-630.4f, -236.7f, 40.0f);
		PrintMessage("Loaded jewelry store");
	}
}
void morgue_ipl()
{
	if (IS_IPL_ACTIVE("Coroner_Int_on"))
	{
		REMOVE_IPL("Coroner_Int_on");

		PrintMessage("Removed morgue");
	}
	else
	{
		REQUEST_IPL("Coroner_Int_on");

		Teleport(244.9f, -1374.7f, 39.5f);
		PrintMessage("Loaded morgue");
	}
}

void life_invader_ipl()
{
	if (IS_IPL_ACTIVE("facelobby"))
	{
		REMOVE_IPL("facelobby");

		PrintMessage("Removed Life Invader Office");
	}
	else
	{
		REQUEST_IPL("facelobby");

		Teleport(-1047.9f, -233.0f, 39.0f);
		PrintMessage("Loaded Life Invader Office");
	}
}

void fib_lobby_ipl()
{
	if (IS_IPL_ACTIVE("FIBlobby"))
	{
		REMOVE_IPL("FIBlobby");

		PrintMessage("Removed FIB lobby");
	}
	else
	{
		REQUEST_IPL("FIBlobby");

		Teleport(110.4f, -744.2f, 45.7f);
		PrintMessage("Loaded FIB lobby");
	}
}

void cluckn_bell_ipl()
{
	if (IS_IPL_ACTIVE("CS1_02_cf_onmission1"))
	{
		REQUEST_IPL("CS1_02_cf_offmission"); // doors
		REMOVE_IPL("CS1_02_cf_onmission1");
		REMOVE_IPL("CS1_02_cf_onmission2");
		REMOVE_IPL("CS1_02_cf_onmission3");
		REMOVE_IPL("CS1_02_cf_onmission4");

		PrintMessage("Removed slaughterhouse interior");
	}
	else
	{
		REMOVE_IPL("CS1_02_cf_offmission"); // remove the doors so you can enter
		REQUEST_IPL("CS1_02_cf_onmission1");
		REQUEST_IPL("CS1_02_cf_onmission2");
		REQUEST_IPL("CS1_02_cf_onmission3");
		REQUEST_IPL("CS1_02_cf_onmission4");

		Teleport(-72.68752, 6253.72656, 31.08991);
		PrintMessage("Loaded slaughterhouse interior");
	}

}

#pragma endregion
void Forcefield()
{
	if (IS_PED_ON_FOOT(_ID))
	{
		SET_ENTITY_CAN_BE_DAMAGED(_ID, false);
		Vector3 c;
		c = GET_ENTITY_COORDS(_ID, 1);
		ADD_EXPLOSION(c.x, c.y, c.z, BLIMP, 9999.99f, false, true, 0);
		ADD_EXPLOSION(c.x, c.y, c.z, TRAIN, 9999.99f, false, true, 0);
	}
}
void RockstarLogo()
{
	switch (devtype)
	{
	case fm_rstar_m_tshirt_000:
		CLEAR_PED_DECORATIONS(_ID);
		_0x70559AC7(_ID, GET_HASH_KEY("mphipster_overlays"), GET_HASH_KEY("fm_rstar_m_tshirt_000"));
		STAT_SET_INT(GET_HASH_KEY("TSHIRT_DECAL_HASH"), GET_HASH_KEY("fm_rstar_m_tshirt_000"), 0);
		PrintMessage("Set black dev logo");
		break;
	case fm_rstar_m_tshirt_001:
		CLEAR_PED_DECORATIONS(_ID);
		_0x70559AC7(_ID, GET_HASH_KEY("mphipster_overlays"), GET_HASH_KEY("fm_rstar_m_tshirt_001"));
		STAT_SET_INT(GET_HASH_KEY("TSHIRT_DECAL_HASH"), GET_HASH_KEY("fm_rstar_m_tshirt_001"), 0);
		PrintMessage("Set yellow dev logo");
		break;
	case fm_rstar_m_tshirt_002:
		CLEAR_PED_DECORATIONS(_ID);
		_0x70559AC7(_ID, GET_HASH_KEY("mphipster_overlays"), GET_HASH_KEY("fm_rstar_m_tshirt_002"));
		STAT_SET_INT(GET_HASH_KEY("TSHIRT_DECAL_HASH"), GET_HASH_KEY("fm_rstar_m_tshirt_002"), 0);
		PrintMessage("Set blue dev logo");
		break;
	case 3:
		CLEAR_PED_DECORATIONS(_ID);
		PrintMessage("Removed dev logo");
		break;
	}
	rockstartoggle = false;
}
void MobileRadio()
{
	if (mobileradio)
	{
		SET_MOBILE_PHONE_RADIO_STATE(0);
		SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(0);
		PrintMessage("Mobile radio turned off");
		mobileradio = false;
	}
	else {
		SET_MOBILE_PHONE_RADIO_STATE(1);
		SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(1);
		PrintMessage("Mobile radio turned on");
		mobileradio = true;
	}
}
void ClearArea()
{
	Vector3 c = GET_ENTITY_COORDS(_ID, 1);
	CLEAR_AREA(c.x, c.y, c.z, 500.00f, 1, 0, 0, 0);
	PrintMessage("Area cleared");
}
void FirstPerson()
{
	Vector3 pos = { 0.0, 0.15, 0.01 };
	if (!isfirstperson) {
		if (!DOES_CAM_EXIST(firstpersoncam))
		{
			firstpersoncam = CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
			ATTACH_CAM_TO_PED_BONE(firstpersoncam, _ID, 31086, pos.x, pos.y, pos.z, 1);
		}
		SET_CAM_ACTIVE(firstpersoncam, true);
		RENDER_SCRIPT_CAMS(1, 0, 3000, 1, 0);
		PrintMessage("First person cam active");
		isfirstperson = true;
	}
	else {
		SET_CAM_ACTIVE(firstpersoncam, false);
		DESTROY_CAM(firstpersoncam, 0);
		RENDER_SCRIPT_CAMS(0, 0, 3000, 1, 0);
		PrintMessage("First person disabled");
		isfirstperson = false;
	}
}
void NoClip()
{
	if (!noclip) {
		if (!DOES_CAM_EXIST(noclipcam))
		{
			noclipcam = CREATE_CAM("DEFAULT_SCRIPTED_FLY_CAMERA", 1);
		}
		Vector3 c;
		if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
			c = GET_ENTITY_COORDS(GET_VEHICLE_PED_IS_IN(_ID, 1), 1);
		else
			c = GET_ENTITY_COORDS(_ID, 1);
		SET_CAM_COORD(noclipcam, &c);
		SET_CAM_ACTIVE(noclipcam, true);
		RENDER_SCRIPT_CAMS(1, 0, 3000, 1, 0);
		if (IS_PED_IN_ANY_VEHICLE(_ID, 1)) {
			Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
			SET_ENTITY_VISIBLE(veh, 0);
			SET_ENTITY_COLLISION(veh, 0, 0);
			SET_ENTITY_CAN_BE_DAMAGED(veh, 0);
			FREEZE_ENTITY_POSITION(veh, 1);
		}
		else {
			SET_ENTITY_VISIBLE(_ID, 0);
			SET_ENTITY_COLLISION(_ID, 0, 0);
			SET_ENTITY_CAN_BE_DAMAGED(_ID, 0);
			FREEZE_ENTITY_POSITION(_ID, 1);
		}
		PrintMessage("UFO cam enabled\nUse L2 and R2 to go up/down\nSelect again to stop");
		noclip = true;
	}
	else {
		Vector3 c = GET_CAM_COORD(noclipcam);
		if (IS_PED_IN_ANY_VEHICLE(_ID, 1)) {
			Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
			SET_ENTITY_COORDS(veh, c.x, c.y, c.z, 0, 0, 0, 1);
			SET_ENTITY_VISIBLE(veh, 1);
			SET_ENTITY_COLLISION(veh, 1, 1);
			SET_ENTITY_CAN_BE_DAMAGED(veh, 1);
			FREEZE_ENTITY_POSITION(veh, 0);
		}
		else {
			SET_ENTITY_COORDS(_ID, c.x, c.y, c.z, 0, 0, 0, 1);
			SET_ENTITY_VISIBLE(_ID, 1);
			SET_ENTITY_COLLISION(_ID, 1, 1);
			SET_ENTITY_CAN_BE_DAMAGED(_ID, 1);
			FREEZE_ENTITY_POSITION(_ID, 0);
		}
		SET_CAM_ACTIVE(noclipcam, false);
		DESTROY_CAM(noclipcam, 0);
		RENDER_SCRIPT_CAMS(0, 0, 3000, 1, 0);
		PrintMessage("UFO cam disabled");
		noclip = false;
	}
}
void MoveNoClip()
{
	if (DOES_CAM_EXIST(noclipcam))
	{
		Vector3 rot = GET_GAMEPLAY_CAM_ROT(2);
		SET_CAM_ROT(noclipcam, &rot, 2);
	}
}
void MoveFirstPerson()
{
	if (DOES_CAM_EXIST(firstpersoncam))
	{
		Vector3 rot = GET_GAMEPLAY_CAM_ROT(2);
		SET_CAM_ROT(firstpersoncam, &rot, 2);
	}
}
void SuperRun()
{
	if (IS_CONTROL_PRESSED(2, 193))
	{
		if (IS_PED_ON_FOOT(_ID))
		{
			APPLY_FORCE_TO_ENTITY(_ID, true, 0, 1.5, 0, 0, 0, 0, true, true, true, true, false, true);
		}
	}
}

void TeleportGun()
{
	if (IS_PED_SHOOTING(_ID))
	{
		Vector3 bullet;
		if (GET_PED_LAST_WEAPON_IMPACT_COORD(_ID, &bullet))
		{
			if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
			{
				Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
				SET_ENTITY_COORDS(veh, bullet.x, bullet.y, bullet.z, 1, 0, 0, 1);
			}
			else
				SET_ENTITY_COORDS(_ID, bullet.x, bullet.y, bullet.z, 1, 0, 0, 1);
		}
	}
}
void set_player_model(Hash hash)
{
	player_model_hash = hash;
	model_loop = true;
}
bool create_player_model(Hash hash)
{
	if (IS_MODEL_IN_CDIMAGE(hash))
		REQUEST_MODEL(hash);
	if (HAS_MODEL_LOADED(hash))
	{
		SET_PLAYER_MODEL(PLAYER_ID(), hash);
		SET_PED_DEFAULT_COMPONENT_VARIATION(_ID);
		GiveMeWeapons();
		SET_MODEL_AS_NO_LONGER_NEEDED(hash);
		return true;
	}
	return false;
}
void VehicleFreezeProtection(bool enabled)
{
	char nop[] = { 0x60, 0x00, 0x00, 0x00 };
	sys_dbg_write_process_memory(0x13C0C98, enabled ? nop : (char*)0x4BB33c79, 4);
	sys_dbg_write_process_memory(0x13C0CF0, enabled ? nop : (char*)0x4BA7DF3D, 4);
	sys_dbg_write_process_memory(0x13C0D38, enabled ? nop : (char*)0x4BB3E8FD, 4);
	sys_dbg_write_process_memory(0x13C0D60, enabled ? nop : (char*)0x4BB36D71, 4);
	sys_dbg_write_process_memory(0x13C0654, enabled ? nop : (char*)0x41820030, 4);
	sys_dbg_write_process_memory(0x13C1008, enabled ? nop : (char*)0x4BB33C75, 4);
	sys_dbg_write_process_memory(0x13C1028, enabled ? nop : (char*)0x4BA7DC05, 4);
	sys_dbg_write_process_memory(0x13C0D84, enabled ? nop : (char*)0x4180FFAC, 4);
	sys_dbg_write_process_memory(0x0EE0764, enabled ? nop : (char*)0x4BFFFD05, 4);
	sys_dbg_write_process_memory(0x0EE080C, enabled ? nop : (char*)0x4BFFFC5D, 4);
	sys_dbg_write_process_memory(0x0EE2EC0, enabled ? nop : (char*)0x4BFFD5A9, 4);
	sys_dbg_write_process_memory(0x0EE2ED4, enabled ? nop : (char*)0x4BFFD595, 4);
}
void ChangeName(char* name)
{
	strncpy((char*)0x41143344, name, strlen(name));
	*(char*)(0x41143344 + strlen(name)) = 0;
	strncpy((char*)0x0200255C, name, strlen(name));
	*(char*)(0x0200255C + strlen(name)) = 0;
	PrintMessage(Format("Changed name to %s", name));
}
#pragma endregion
#pragma region VehicleOptions
void SuperSpeed()
{
	if (IS_PED_IN_ANY_VEHICLE(_ID, 1)) {
		Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
		SET_VEHICLE_FORWARD_SPEED(veh, 100.00f);
	}
}
void Speedometer()
{
	if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
		float speed = GET_ENTITY_SPEED(veh) * 3.6;
		if (use_mph)
			speed /= 1.60934;

		DrawSprite("timerbars", "all_black_bg", 0.846201, 0.950873, 0.156016, 0.042969, 0, 255, 255, 255, 60);
		DrawText(Format("%s", use_mph ? "MPH" : "KPH"), 4, 0.791514, 0.943061, 0.503125, 255, 255, 255, 255, false, true, false);
		DrawText(Format("%.1f", speed), 4, 0.903818, 0.933342, 0.690625, 255, 255, 255, 255, false, true, false);
		//DrawText(, 4, 0.03125, 0.03125, 0.6, 255, 255, 255, 255, false);
	}
}
void FixCar()
{
	if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
		SET_VEHICLE_FIXED(veh);
		PrintMessage("Vehicle fixed");
	}
	else {
		PrintMessage("Not in vehicle");
	}
}
void set_vehicle_mod(int index, int value)
{
	if (IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 1)) {
		Vehicle veh = GET_VEHICLE_PED_IS_USING(PLAYER_PED_ID());
		SET_VEHICLE_MOD_KIT(veh, 0);
		SET_VEHICLE_MOD(veh, index, value, 0);
	}
	else
		PrintMessage("Not in vehicle");
}
void set_vehicle_mod(int id, int index, int value)
{
	if (IS_PED_IN_ANY_VEHICLE(id, 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_USING(id);
		SET_VEHICLE_MOD_KIT(veh, 0);
		SET_VEHICLE_MOD(veh, index, value, 0);
	}
}
void set_wheel_stuff(int id, int value)
{
	if (IS_PED_IN_ANY_VEHICLE(id, 1)) {
		Vehicle veh = GET_VEHICLE_PED_IS_IN(id, 1);
		SET_VEHICLE_MOD_KIT(veh, 0);
		SET_VEHICLE_MOD(veh, 23, 0, value);
		PrintMessage("Set tire mod");
	}
	else
		PrintMessage("Not in vehicle");
}
void toggle_vehicle_mod(int index, bool value)
{
	if (IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 1)) {
		Vehicle veh = GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 1);
		SET_VEHICLE_MOD_KIT(veh, 0);
		TOGGLE_VEHICLE_MOD(veh, index, value);
	}
	else
		PrintMessage("Not in vehicle");
}
int get_vehicle_mod(int index)
{
	if (IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 1);
		SET_VEHICLE_MOD_KIT(veh, 0);
		return GET_VEHICLE_MOD(veh, index);
	}
	return -2;
}
void remove_vehicle_mod(int index)
{
	if (IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 1)) {
		Vehicle veh = GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 1);
		SET_VEHICLE_MOD_KIT(veh, 0);
		REMOVE_VEHICLE_MOD(veh, index);
	}
	else
		PrintMessage("Not in vehicle");
}
void set_vehicle_tyres_can_burst(bool value)
{
	if (IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 1)) {
		Vehicle veh = GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 1);
		SET_VEHICLE_MOD_KIT(veh, 0);
		SET_VEHICLE_TYRES_CAN_BURST(veh, value);

	}
	else
		PrintMessage("Not in vehicle");
}
void set_vehicle_wheels(int wheelType, int wheelIndex)
{
	if (IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 1)) {
		Vehicle veh = GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 1);
		SET_VEHICLE_MOD_KIT(veh, 0);
		SET_VEHICLE_WHEEL_TYPE(veh, wheelType);
		SET_VEHICLE_MOD(veh, 23, wheelIndex, 0);
	}
	else
		PrintMessage("Not in vehicle");
}
void set_vehicle_number_plate_text_index(int value)
{
	if (IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 1);
		SET_VEHICLE_MOD_KIT(veh, 0);
		SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh, value);
	}
	else
		PrintMessage("Not in vehicle");
}
void set_vehicle_number_plate_text_index(int id, int value)
{
	if (IS_PED_IN_ANY_VEHICLE(id, 1)) {
		Vehicle veh = GET_VEHICLE_PED_IS_IN(id, 1);
		SET_VEHICLE_MOD_KIT(veh, 0);
		SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh, value);
	}
}
void set_vehicle_window_tint(int value)
{
	if (IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 1)) {
		Vehicle veh = GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 1);
		SET_VEHICLE_MOD_KIT(veh, 0);
		SET_VEHICLE_WINDOW_TINT(veh, value);
		PrintMessage("Set window tint");
	}
	else
		PrintMessage("Not in vehicle");
}
void set_vehicle_window_tint(int id, int value)
{
	if (IS_PED_IN_ANY_VEHICLE(id, 1)) {
		Vehicle veh = GET_VEHICLE_PED_IS_IN(id, 1);
		SET_VEHICLE_MOD_KIT(veh, 0);
		SET_VEHICLE_WINDOW_TINT(veh, value);
	}
}
bool LoadMods()
{
	if (!IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 1))
		return false;

	Vehicle veh = GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 1);

	SET_VEHICLE_MOD_KIT(veh, 0);

	/* Set max mods */
	max.maxarmour = GET_NUM_VEHICLE_MODS(veh, Armour) - 1;
	max.maxbodywork = GET_NUM_VEHICLE_MODS(veh, BodyWork) - 1;
	max.maxbrakes = GET_NUM_VEHICLE_MODS(veh, Brakes) - 1;
	max.maxengine = GET_NUM_VEHICLE_MODS(veh, Engine) - 1;
	max.maxexhaust = GET_NUM_VEHICLE_MODS(veh, Exhaust) - 1;
	max.maxfbumper = GET_NUM_VEHICLE_MODS(veh, FrontBumper) - 1;
	max.maxrbumper = GET_NUM_VEHICLE_MODS(veh, RearBumper) - 1;
	max.maxfender = GET_NUM_VEHICLE_MODS(veh, Fender) - 1;
	max.maxgrille = GET_NUM_VEHICLE_MODS(veh, Grille) - 1;
	max.maxhood = GET_NUM_VEHICLE_MODS(veh, Hood) - 1;
	max.maxroof = GET_NUM_VEHICLE_MODS(veh, Roof) - 1;
	max.maxskirts = GET_NUM_VEHICLE_MODS(veh, Skirts) - 1;
	max.maxspoiler = GET_NUM_VEHICLE_MODS(veh, Spoiler) - 1;
	max.maxsuspension = GET_NUM_VEHICLE_MODS(veh, Suspension) - 1;
	max.maxtransmission = GET_NUM_VEHICLE_MODS(veh, Transmission) - 1;

	vehicle_mods.armour = GET_VEHICLE_MOD(veh, Armour);
	vehicle_mods.bodywork = GET_VEHICLE_MOD(veh, BodyWork);
	vehicle_mods.brakes = GET_VEHICLE_MOD(veh, Brakes);
	vehicle_mods.engine = GET_VEHICLE_MOD(veh, Engine);
	vehicle_mods.exhaust = GET_VEHICLE_MOD(veh, Exhaust);
	vehicle_mods.fbumper = GET_VEHICLE_MOD(veh, FrontBumper);
	vehicle_mods.fender = GET_VEHICLE_MOD(veh, Fender);
	vehicle_mods.grille = GET_VEHICLE_MOD(veh, Grille);
	vehicle_mods.hood = GET_VEHICLE_MOD(veh, Hood);
	vehicle_mods.rbumper = GET_VEHICLE_MOD(veh, RearBumper);
	vehicle_mods.roof = GET_VEHICLE_MOD(veh, Roof);
	vehicle_mods.skirts = GET_VEHICLE_MOD(veh, Skirts);
	vehicle_mods.spoiler = GET_VEHICLE_MOD(veh, Spoiler);
	vehicle_mods.suspension = GET_VEHICLE_MOD(veh, Suspension);
	vehicle_mods.transmission = GET_VEHICLE_MOD(veh, Transmission);
	vehicle_mods.plates = GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh);
	vehicle_mods.tint = GET_VEHICLE_WINDOW_TINT(veh);
	vehicle_mods.xenons = GET_VEHICLE_MOD(veh, Xenon);
	vehicle_mods.bulletproof = GET_VEHICLE_TYRES_CAN_BURST(veh);
	vehicle_mods.turbo = GET_VEHICLE_MOD(veh, Turbo);

	return true;
}
void open_door(int id, int door)
{
	if (IS_PED_IN_ANY_VEHICLE(id, 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_USING(id);;
		SET_VEHICLE_DOOR_OPEN(veh, id, false, false);
		PrintMessage("Door opened");
	}
	else {
		PrintMessage("Not in vehicle");
	}
}
void open_all_doors(int id)
{
	if (IS_PED_IN_ANY_VEHICLE(id, 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_USING(id);
		for (int i = 0; i < 7; i++)
		{
			SET_VEHICLE_DOOR_OPEN(veh, i, 0, 0);
		}
		PrintMessage("All doors opened");
	}
	else {
		PrintMessage("Not in vehicle");
	}
}
void delete_all_doors(int id)
{
	if (IS_PED_IN_ANY_VEHICLE(id, 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_USING(id);
		for (int i = 0; i < 7; i++)
		{
			SET_VEHICLE_DOOR_BROKEN(veh, i, true);
		}
		PrintMessage("Deleted all doors");
	}
	else
		PrintMessage("Not in vehicle");
}
void set_vehicle_colours()
{
	if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
		CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh);
		CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh);
		SET_VEHICLE_COLOURS(veh, carPrimary, carSecondary);
	}
	else {
		PrintMessage("Not in vehicle");
	}
}
void get_vehicle_colours()
{
	if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
		GET_VEHICLE_COLOURS(veh, &carPrimary, &carSecondary);
	}
}
void Nitrous()
{
	if (IS_PED_IN_ANY_VEHICLE(_ID, 1)) {
		if (IS_DISABLED_CONTROL_PRESSED(2, 0xC5 + 3) || IS_CONTROL_PRESSED(2, 0xC5 + 3) && !IS_CONTROL_JUST_PRESSED(2, 0xc6 + 3))
		{
			Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
			SET_HORN_ENABLED(veh, 0);
			SET_VEHICLE_BOOST_ACTIVE(veh, 1);
			_0x1D980479("RaceTurbo", 0, 0);
			SET_VEHICLE_FORWARD_SPEED(veh, 50.0f);
			SET_VEHICLE_BOOST_ACTIVE(veh, 0);
			SET_HORN_ENABLED(veh, 1);
		}
	}
}
void SetInCar(Vehicle veh)
{
	if (DOES_ENTITY_EXIST(veh))
	{
		int seat = FindSeat(veh);
		if (seat != -2) {
			SET_PED_INTO_VEHICLE(_ID, veh, seat);
			PrintMessage("Set in car");
		}
		else
		{
			PrintMessage("No room in car");
		}
	}
}
void FindClosestVeh()
{
	Vector3 c = GET_ENTITY_COORDS(_ID, 1);
	Vehicle veh = GET_CLOSEST_VEHICLE(c.x, c.y, c.z, 500.0f, 0, 70);
	if (veh != 0)
	{
		SetInCar(veh);
	}
}
void ColorCycle()
{
	if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
		SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, irand(0, 255), irand(0, 255), irand(0, 255));
		SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, irand(0, 255), irand(0, 255), irand(0, 255));
		PrintMessage("Set random color");
	}
	else
		PrintMessage("Not in vehicle");
}
void vehicle_invisible(bool value)
{
	if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
		SET_ENTITY_VISIBLE(veh, !value);
	}

}
void vehicle_invincible()
{
	if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
		SET_ENTITY_INVINCIBLE(veh, true);
		SET_ENTITY_PROOFS(veh, 1, 1, 1, 1, 1, 1, 1, 1);
		SET_VEHICLE_TYRES_CAN_BURST(veh, 0);
		SET_VEHICLE_WHEELS_CAN_BREAK(veh, 0);
		SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(veh, 0);
	}
}
void disable_vehicle_invincible()
{
	if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
		SET_ENTITY_INVINCIBLE(veh, false);
		SET_ENTITY_PROOFS(veh, 0, 0, 0, 0, 0, 0, 0, 0);
		SET_VEHICLE_TYRES_CAN_BURST(veh, 1);
		SET_VEHICLE_WHEELS_CAN_BREAK(veh, 1);
		SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(veh, 1);
	}
}
void ShootVehicleWeapon()
{
	if (IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 0) && IS_CONTROL_PRESSED(2, 0xc8) || IS_CONTROL_JUST_PRESSED(2, 0xc8))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 0);
		int distance = 250;
		float speed = 1500.0f;
		Vector3 coords1 = { 0.6f, 0.6707f, 0.3711f };
		Vector3 getcoords1 = GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, coords1.x, coords1.y, coords1.z);
		Vector3 coords2 = { -0.6f, 0.6707f, 0.3711f };
		Vector3 getcoords2 = GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, coords2.x, coords2.y, coords2.z);
		Vector3 coords3 = { 0.6f, 5.0707f, 0.3711f };
		Vector3 getcoords3 = GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, coords3.x, coords3.y, coords3.z);
		Vector3 coords4 = { -0.6f, 5.0707f, 0.3711f };
		Vector3 getcoords4 = GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, coords4.x, coords4.y, coords4.z);
		Vector3 final1 = { getcoords1.x, getcoords1.y, getcoords1.z };
		Vector3 final2 = { getcoords2.x, getcoords2.y, getcoords2.z };
		Vector3 final3 = { getcoords3.x, getcoords3.y, getcoords3.z };
		Vector3 final4 = { getcoords4.x, getcoords4.y, getcoords4.z };
		SHOOT_SINGLE_BULLET_BETWEEN_COORDS(final1.x, final1.y, final1.z, final3.x, final3.y, final3.z, distance, 0, current_vehicle_weapon, PLAYER_PED_ID(), 1, 1, speed);
		SHOOT_SINGLE_BULLET_BETWEEN_COORDS(final2.x, final2.y, final2.z, final4.x, final4.y, final4.z, distance, 0, current_vehicle_weapon, PLAYER_PED_ID(), 1, 1, speed);
	}
}
void FlipMyCar()
{
	if (IS_PED_IN_ANY_VEHICLE(PLAYER_PED_ID(), 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
		SET_VEHICLE_ON_GROUND_PROPERLY(veh);
		PrintMessage("Set vehicle on wheels");
	}
	else {
		PrintMessage("Not in vehicle");
	}
}
void ToggleLocks()
{
	if (IS_PED_IN_ANY_VEHICLE(_ID, 1)) {
		Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
		if (GET_VEHICLE_DOOR_LOCK_STATUS(veh)) {
			SET_VEHICLE_DOORS_LOCKED(veh, false);
			PrintMessage("Doors unlocked");
		}
		else {
			SET_VEHICLE_DOORS_LOCKED(veh, true);
			PrintMessage("Doors locked");
		}
	}
	else
		PrintMessage("Not in vehicle");
}

void NeedForSpeed()
{
	if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
	{
		if (IS_DISABLED_CONTROL_PRESSED(2, 0xc7))
		{
			Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
			SET_VEHICLE_FORWARD_SPEED(veh, 30.0f);
		}
		if (IS_DISABLED_CONTROL_PRESSED(2, 0xc6))
		{
			Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
			SET_VEHICLE_FORWARD_SPEED(veh, 0);
		}
		if (IS_DISABLED_CONTROL_PRESSED(2, 0xc5))
		{
			Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
			float heading = GET_ENTITY_HEADING(veh);
			heading -= 0.5;
			SET_ENTITY_HEADING(veh, heading);
		}
		if (IS_DISABLED_CONTROL_PRESSED(2, 0xc4))
		{
			Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
			float heading = GET_ENTITY_HEADING(veh);
			heading += 0.5;
			SET_ENTITY_HEADING(veh, heading);
		}
	}
}
void NoCollision()
{
	if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
	{
		nocollision = !nocollision;
		Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
		SET_ENTITY_COLLISION(veh, nocollision, 1);
		PrintMessage(nocollision ? "No collision disabled" : "No collision enabled");
	}
	else
		PrintMessage("Not in vehicle");
}
void FreezePosition()
{
	if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
	{
		freezevehicle = !freezevehicle;
		Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
		FREEZE_ENTITY_POSITION(veh, freezevehicle);
		PrintMessage(freezevehicle ? "Vehicle frozen" : "Vehicle unfrozen");
	}
	else {
		PrintMessage("Not in vehicle");
	}
}
void ChangePlate(char* text)
{
	if (IS_PED_IN_ANY_VEHICLE(_ID, 1)) {
		if (!IS_STRING_NULL_OR_EMPTY(text)) {
			Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
			SET_VEHICLE_NUMBER_PLATE_TEXT(veh, text);
			PrintMessage(Format("Changed plate to %s", text));
		}
		else
			PrintMessage("No text entered");
	}
	else
		PrintMessage("Not in vehicle");
}
void StickToGround()
{
	if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
		SET_VEHICLE_ON_GROUND_PROPERLY(veh);
	}
}
void SupeVehicle(Vehicle veh)
{
	set_vehicle_mod(_ID, 11, 3);
	set_vehicle_mod(_ID, 13, 2);
	set_vehicle_mod(_ID, 12, 2);
	set_vehicle_mod(_ID, 15, 3);
	set_vehicle_mod(_ID, 4, 3);
	set_vehicle_mod(_ID, 16, 4);
	set_vehicle_tyres_can_burst(_ID);
	set_vehicle_number_plate_text_index(_ID, 5);
	set_vehicle_window_tint(_ID, 5);
}
void DeleteMyVehicle()
{
	if (IS_PED_IN_ANY_VEHICLE(_ID, 1)) {
		Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
		SET_ENTITY_AS_MISSION_ENTITY(veh, 0, 1);
		DELETE_VEHICLE(&veh);
		PrintMessage("Deleted vehicle");
	}
	else {
		PrintMessage("Not in vehicle");
	}
}
void CarJumper()
{
	if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
	{
		Vector3 force = { 0, 0, 1 };
		Vector3 ang = { 0, 0, 0 };
		Vehicle veh = GET_VEHICLE_PED_IS_USING(_ID);
		if (IS_CONTROL_PRESSED(2, 193))
		{
			if (IS_VEHICLE_ON_ALL_WHEELS(veh))
				APPLY_FORCE_TO_ENTITY(veh, 1, 0, 0, 0.5f, 0, 0, 0, 1, 1, 1, 1, 0, 1);
		}
	}
}
void RunNeons()
{
	if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
		Vector3 c = GET_ENTITY_COORDS(veh, 1);
		c.z = c.z - 0;
		DRAW_LIGHT_WITH_RANGE(c.x, c.y, c.z, neonsr, neonsg, neonsb, 4.0, 2.5);
	}
}
int last_rainbow = 0;
void RainbowNeons()
{
	if (neons && last_rainbow < GET_GAME_TIMER())
	{
		if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
		{
			neonsr = GET_RANDOM_INT_IN_RANGE(0, 255);
			neonsg = GET_RANDOM_INT_IN_RANGE(0, 255);
			neonsb = GET_RANDOM_INT_IN_RANGE(0, 255);
		}
		last_rainbow = GET_GAME_TIMER() + 50;
	}
}

void ChatHeads()
{
	int pos = 0;
	if (NETWORK_IS_IN_SESSION())
	{
		for (int i = 0; i < 16; ++i)
		{
			if (NETWORK_IS_PLAYER_ACTIVE(i))
			{
				if (NETWORK_IS_PLAYER_TALKING(i) && !NETWORK_IS_PLAYER_MUTED_BY_ME(i))
				{

					DrawText(Format("~f~Talking:~w~ %s", GET_PLAYER_NAME(i)), 4, 0.031250, 0.127188 + (pos * 0.024), 0.525, 255, 255, 255, 255, false);
					pos++;
				}
			}
		}
	}
}
bool set_rpm_multiplier(float val)
{
	if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
		_0xE943B09C(veh, val);
	}
}
#pragma endregion
#pragma region AccountOptions
void SetKills(int val)
{
	STAT_SET_INT(GET_HASH_KEY("MPPLY_KILLS_PLAYERS"), val, 0);
}
void SetDeaths(int val)
{
	STAT_SET_INT(GET_HASH_KEY("MPPLY_DEATHS_PLAYER"), val, 0);
}
void SetWins(int val)
{
	STAT_SET_INT(GET_HASH_KEY("MP0_RACES_WON"), val, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_RACES_WON"), val, 0);

}
void SetLosses(int val)
{
	STAT_SET_INT(GET_HASH_KEY("MP0_RACES_LOST"), val, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_RACES_LOST"), val, 0);
}
void MaxSkill(char* name)
{
	STAT_SET_INT(GET_HASH_KEY(name), 100, 0);
}
void ModdedRolls()
{
	STAT_SET_INT(GET_HASH_KEY("MP0_SHOOTING_ABILITY"), 150, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SHOOTING_ABILITY"), 150, 0);
}
void MaxAllSkills()
{
	STAT_SET_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, 0);

	STAT_SET_INT(GET_HASH_KEY("MP1_SCRIPT_INCREASE_STAM"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SCRIPT_INCREASE_STRN"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SCRIPT_INCREASE_LUNG"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SCRIPT_INCREASE_DRIV"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SCRIPT_INCREASE_FLY"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SCRIPT_INCREASE_SHO"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SCRIPT_INCREASE_STL"), 100, 0);
	PrintMessage("Maxed out all skills");
}
void ResetAllSkills()
{
	STAT_SET_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 0, 0);

	STAT_SET_INT(GET_HASH_KEY("MP1_SCRIPT_INCREASE_STAM"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SCRIPT_INCREASE_STRN"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SCRIPT_INCREASE_LUNG"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SCRIPT_INCREASE_DRIV"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SCRIPT_INCREASE_FLY"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SCRIPT_INCREASE_SHO"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SCRIPT_INCREASE_STL"), 0, 0);
	PrintMessage("Reset all skills");
}
void DoUnlocks()
{
	STAT_SET_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_RACES_WON"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_PISTOL_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CMBTPISTOL_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_APPISTOL_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MICROSMG_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SMG_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ASLTSMG_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ASLTRIFLE_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CRBNRIFLE_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ADVRIFLE_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_HVYSNIPER_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SNIPERRFL_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ASLTSHTGN_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_PUMP_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_GRNLAUNCH_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_RPG_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MINIGUNS_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ASLTSMG_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ASLTRIFLE_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CRBNRIFLE_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ADVRIFLE_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_HVYSNIPER_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SNIPERRFL_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MG_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CMBTMG_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_PISTOL_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CMBTPISTOL_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_APPISTOL_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MICROSMG_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SMG_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ASLTSMG_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ASLTRIFLE_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CRBNRIFLE_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ADVRIFLE_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_HVYSNIPER_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SNIPERRFL_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ASLTSHTGN_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_PUMP_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_GRNLAUNCH_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_RPG_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MINIGUNS_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ASLTSMG_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ASLTRIFLE_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CRBNRIFLE_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ADVRIFLE_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_HVYSNIPER_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SNIPERRFL_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MG_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CMBTMG_ENEMY_KILLS"), 600, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP0_AWD_FMRACEWORLDRECHOLDER"), 1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_ENEMYDRIVEBYKILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_USJS_COMPLETED"), 50, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_USJS_FOUND"), 50, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP0_AWD_FMWINALLRACEMODES"), 1, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP0_AWD_FMWINEVERYGAMEMODE"), 1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DB_PLAYER_KILLS"), 1000, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_KILLS_PLAYERS"), 1000, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_FMHORDWAVESSURVIVE"), 21, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_CAR_BOMBS_ENEMY_KILLS"), 25, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_FM_TDM_MVP"), 60, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_HOLD_UP_SHOPS"), 20, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_RACES_WON"), 101, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_NO_ARMWRESTLING_WINS"), 21, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP0_AWD_FMATTGANGHQ"), 1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_FMBBETWIN"), 50000, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 51, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP0_AWD_FMFULLYMODDEDCAR"), 1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_FM_DM_TOTALKILLS"), 500, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MPPLY_DM_TOTAL_DEATHS"), 412, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MPPLY_TIMES_FINISH_DM_TOP_3"), 36, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_PLAYER_HEADSHOTS"), 623, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 63, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_FM_TDM_WINS"), 13, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_FM_GTA_RACES_WON"), 12, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_FM_GOLF_WON"), 2, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_TG_WON"), 2, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_RT_WON"), 2, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_CT_WON"), 2, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_GRAN_WON"), 2, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_FM_TENNIS_WON"), 2, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MPPLY_TENNIS_MATCHES_WON"), 2, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MPPLY_TOTAL_TDEATHMATCH_WON"), 63, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MPPLY_TOTAL_RACES_WON"), 101, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MPPLY_TOTAL_DEATHMATCH_LOST"), 23, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MPPLY_TOTAL_RACES_LOST"), 36, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_25_KILLS_STICKYBOMBS"), 50, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_50_KILLS_GRENADES"), 50, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_GRENADE_ENEMY_KILLS"), 50, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_20_KILLS_MELEE"), 50, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP0_AWD_FMMOSTKILLSSURVIVE"), 1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_FMRALLYWONDRIVE"), 2, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_FMWINSEARACE"), 2, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_FMWINAIRRACE"), 2, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MPPLY_TIMES_RACE_BEST_LAP"), 101, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_NUMBER_TURBO_STARTS_IN_RACE"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_FM_RACES_FASTEST_LAP"), 101, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_NUMBER_SLIPSTREAMS_IN_RACE"), 105, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MPPLY_RACE_CHEAT_START"), 130, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MPPLY_RACE_CHEAT_END"), 119, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MPPLY_RACE_CHEAT_QUIT"), 11, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MPPLY_DM_CHEAT_START"), 140, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MPPLY_DM_CHEAT_END"), 115, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MPPLY_DM_CHEAT_QUIT"), 25, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MPPLY_MC_CHEAT_START"), 113, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MPPLY_MC_CHEAT_END"), 97, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MPPLY_MC_CHEAT_QUIT"), 16, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MPPLY_OVERALL_CHEAT"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_LAP_DANCED_BOUGHT"), 50, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_FMKILLBOUNTY"), 50, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP0_AWD_FMKILL3ANDWINGTARACE"), 1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_FMREVENGEKILLSDM"), 60, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_AWD_SECURITY_CARS_ROBBED"), 40, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP0_AWD_FMPICKUPDLCCRATE1ST"), 1, 0);

	STAT_SET_INT(GET_HASH_KEY("MP1_SCRIPT_INCREASE_STAM"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SCRIPT_INCREASE_STRN"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SCRIPT_INCREASE_LUNG"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SCRIPT_INCREASE_DRIV"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SCRIPT_INCREASE_FLY"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SCRIPT_INCREASE_SHO"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SCRIPT_INCREASE_STL"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_RACES_WON"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_PISTOL_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CMBTPISTOL_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_APPISTOL_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MICROSMG_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SMG_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ASLTSMG_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ASLTRIFLE_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CRBNRIFLE_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ADVRIFLE_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_HVYSNIPER_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SNIPERRFL_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ASLTSHTGN_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_PUMP_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_GRNLAUNCH_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_RPG_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MINIGUNS_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ASLTSMG_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ASLTRIFLE_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CRBNRIFLE_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ADVRIFLE_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_HVYSNIPER_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SNIPERRFL_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MG_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CMBTMG_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_PISTOL_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CMBTPISTOL_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_APPISTOL_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MICROSMG_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SMG_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ASLTSMG_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ASLTRIFLE_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CRBNRIFLE_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ADVRIFLE_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_HVYSNIPER_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SNIPERRFL_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ASLTSHTGN_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_PUMP_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_GRNLAUNCH_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_RPG_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MINIGUNS_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ASLTSMG_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ASLTRIFLE_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CRBNRIFLE_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ADVRIFLE_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_HVYSNIPER_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SNIPERRFL_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MG_ENEMY_KILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CMBTMG_ENEMY_KILLS"), 600, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP1_AWD_FMRACEWORLDRECHOLDER"), 1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_ENEMYDRIVEBYKILLS"), 600, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_USJS_COMPLETED"), 50, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_USJS_FOUND"), 50, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP1_AWD_FMWINALLRACEMODES"), 1, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP1_AWD_FMWINEVERYGAMEMODE"), 1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DB_PLAYER_KILLS"), 1000, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_KILLS_PLAYERS"), 1000, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_FMHORDWAVESSURVIVE"), 21, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_CAR_BOMBS_ENEMY_KILLS"), 25, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_FM_TDM_MVP"), 60, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_HOLD_UP_SHOPS"), 20, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_RACES_WON"), 101, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_NO_ARMWRESTLING_WINS"), 21, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP1_AWD_FMATTGANGHQ"), 1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_FMBBETWIN"), 50000, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_FM_DM_WINS"), 51, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP1_AWD_FMFULLYMODDEDCAR"), 1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_FM_DM_TOTALKILLS"), 500, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MPPLY_DM_TOTAL_DEATHS"), 412, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MPPLY_TIMES_FINISH_DM_TOP_3"), 36, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_PLAYER_HEADSHOTS"), 623, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_FM_DM_WINS"), 63, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_FM_TDM_WINS"), 13, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_FM_GTA_RACES_WON"), 12, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_FM_GOLF_WON"), 2, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_FM_SHOOTRANG_TG_WON"), 2, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_FM_SHOOTRANG_RT_WON"), 2, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_FM_SHOOTRANG_CT_WON"), 2, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_FM_SHOOTRANG_GRAN_WON"), 2, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_FM_TENNIS_WON"), 2, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MPPLY_TENNIS_MATCHES_WON"), 2, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MPPLY_TOTAL_TDEATHMATCH_WON"), 63, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MPPLY_TOTAL_RACES_WON"), 101, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MPPLY_TOTAL_DEATHMATCH_LOST"), 23, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MPPLY_TOTAL_RACES_LOST"), 36, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_25_KILLS_STICKYBOMBS"), 50, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_50_KILLS_GRENADES"), 50, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_GRENADE_ENEMY_KILLS"), 50, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_20_KILLS_MELEE"), 50, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP1_AWD_FMMOSTKILLSSURVIVE"), 1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_FMRALLYWONDRIVE"), 2, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_FMWINSEARACE"), 2, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_FMWINAIRRACE"), 2, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MPPLY_TIMES_RACE_BEST_LAP"), 101, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_NUMBER_TURBO_STARTS_IN_RACE"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_FM_RACES_FASTEST_LAP"), 101, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_NUMBER_SLIPSTREAMS_IN_RACE"), 105, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MPPLY_RACE_CHEAT_START"), 130, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MPPLY_RACE_CHEAT_END"), 119, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MPPLY_RACE_CHEAT_QUIT"), 11, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MPPLY_DM_CHEAT_START"), 140, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MPPLY_DM_CHEAT_END"), 115, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MPPLY_DM_CHEAT_QUIT"), 25, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MPPLY_MC_CHEAT_START"), 113, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MPPLY_MC_CHEAT_END"), 97, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MPPLY_MC_CHEAT_QUIT"), 16, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MPPLY_OVERALL_CHEAT"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_LAP_DANCED_BOUGHT"), 50, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_FMKILLBOUNTY"), 50, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP1_AWD_FMKILL3ANDWINGTARACE"), 1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_FMREVENGEKILLSDM"), 60, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_AWD_SECURITY_CARS_ROBBED"), 40, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP1_AWD_FMPICKUPDLCCRATE1ST"), 1, 0);
	PrintMessage("Unlocked all awards + maxed stats");
}
void DoSkipTutorial()
{
	STAT_SET_BOOL(2187123212, true, 0);
	STAT_SET_BOOL(3580365573, true, 0);
	STAT_SET_BOOL(211659663, true, 0);
	STAT_SET_BOOL(129572558, true, 0);
	STAT_SET_BOOL(2478049476, true, 0);
	STAT_SET_BOOL(1485187367, true, 0);
	PrintMessage("Skipped tutorial missions");
}
void UnlimitedSnacks()
{
	STAT_SET_INT(GET_HASH_KEY("MP0_NO_BOUGHT_YUM_SNACKS"), 2147483647, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_NO_BOUGHT_HEALTH_SNACKS"), 2147483647, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_NO_BOUGHT_EPIC_SNACKS"), 2147483647, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_NO_BOUGHT_YUM_SNACKS"), 2147483647, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_NUMBER_OF_ORANGE_BOUGHT"), 2147483647, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_NUMBER_OF_BOURGE_BOUGHT"), 2147483647, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CIGARETTES_BOUGHT"), 2147483647, 0);

	STAT_SET_INT(GET_HASH_KEY("MP1_NO_BOUGHT_YUM_SNACKS"), 2147483647, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_NO_BOUGHT_HEALTH_SNACKS"), 2147483647, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_NO_BOUGHT_EPIC_SNACKS"), 2147483647, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_NO_BOUGHT_YUM_SNACKS"), 2147483647, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_NUMBER_OF_ORANGE_BOUGHT"), 2147483647, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_NUMBER_OF_BOURGE_BOUGHT"), 2147483647, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CIGARETTES_BOUGHT"), 2147483647, 0);
}
void EventShirts()
{
	STAT_SET_BOOL(GET_HASH_KEY("MP0_UNLOCK_DM_HIPSTER_TSHIRT"), 1, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP0_UNLOCK_RACE_HIPSTER_TSHIRT"), 1, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP0_UNLOCK_HIPSTER_TSHIRT_DOG"), 1, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP0_UNLOCK_HIPSTER_TSHIRT_VINYL"), 1, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP0_UNLOCK_HIPSTER_TSHIRT_MESS"), 1, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP0_UNLOCK_RACE_HIPSTER_TSHIRT"), 1, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP0_UNLOCK_RACE_HIPSTER_TSHIRT"), 1, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP1_UNLOCK_DM_HIPSTER_TSHIRT"), 1, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP1_UNLOCK_RACE_HIPSTER_TSHIRT"), 1, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP1_UNLOCK_HIPSTER_TSHIRT_DOG"), 1, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP1_UNLOCK_HIPSTER_TSHIRT_VINYL"), 1, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP1_UNLOCK_HIPSTER_TSHIRT_MESS"), 1, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP1_UNLOCK_RACE_HIPSTER_TSHIRT"), 1, 0);
	STAT_SET_BOOL(GET_HASH_KEY("MP1_UNLOCK_RACE_HIPSTER_TSHIRT"), 1, 0);
	PrintMessage("Unlocked event shirts");
}
void StockUpAmmo()
{
	STAT_SET_INT(GET_HASH_KEY("MP0_PISTOL_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_PISTOL_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CMBTPISTOL_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CMBTPISTOL_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_PISTOL50_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_PISTOL50_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_APPISTOL_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_APPISTOL_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MICROSMG_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MICROSMG_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SMG_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SMG_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ASLTSMG_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ASLTSMG_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ASLTRIFLE_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ASLTRIFLE_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CRBNRIFLE_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CRBNRIFLE_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ADVRIFLE_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ADVRIFLE_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MG_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MG_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CMBTMG_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CMBTMG_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ASLTMG_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ASLTMG_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_PUMP_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_PUMP_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SAWNOFF_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SAWNOFF_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_BULLPUP_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_BULLPUP_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ASLTSHTGN_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ASLTSHTGN_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_STUNGUN_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_STUNGUN_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SNIPERRFL_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SNIPERRFL_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_HVYSNIPER_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_HVYSNIPER_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ASLTSNIP_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ASLTSNIP_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_GRNLAUNCH_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_GRNLAUNCH_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_RPG_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_RPG_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MINIGUNS_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MINIGUNS_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_GRENADE_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_GRENADE_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SMKGRENADE_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_SMKGRENADE_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_STKYBMB_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_STKYBMB_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MOLOTOV_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_MOLOTOV_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_PARACHUTE_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_PARACHUTE_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_PISTOL_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_PISTOL_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CMBTPISTOL_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CMBTPISTOL_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_PISTOL50_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_PISTOL50_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_APPISTOL_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_APPISTOL_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MICROSMG_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MICROSMG_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SMG_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SMG_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ASLTSMG_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ASLTSMG_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ASLTRIFLE_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ASLTRIFLE_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CRBNRIFLE_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CRBNRIFLE_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ADVRIFLE_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ADVRIFLE_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MG_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MG_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CMBTMG_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CMBTMG_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ASLTMG_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ASLTMG_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_PUMP_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_PUMP_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SAWNOFF_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SAWNOFF_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_BULLPUP_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_BULLPUP_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ASLTSHTGN_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ASLTSHTGN_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_STUNGUN_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_STUNGUN_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SNIPERRFL_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SNIPERRFL_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_HVYSNIPER_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_HVYSNIPER_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ASLTSNIP_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ASLTSNIP_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_GRNLAUNCH_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_GRNLAUNCH_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_RPG_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_RPG_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MINIGUNS_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MINIGUNS_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_GRENADE_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_GRENADE_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SMKGRENADE_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_SMKGRENADE_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_STKYBMB_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_STKYBMB_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MOLOTOV_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_MOLOTOV_FM_AMMO_CURRENT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_PARACHUTE_FM_AMMO_BOUGHT"), 9999, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_PARACHUTE_FM_AMMO_CURRENT"), 9999, 0);
	PrintMessage("Stocked up on ammo");
}
void WipeReports()
{
	STAT_SET_INT(GET_HASH_KEY("MPPLY_REPORT_STRENGTH"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MPPLY_COMMEND_STRENGTH"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MPPLY_FRIENDLY"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MPPLY_HELPFUL"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MPPLY_GRIEFING"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MPPLY_VC_ANNOYINGME"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MPPLY_VC_HATE"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MPPLY_OFFENSIVE_LANGUAGE"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MPPLY_OFFENSIVE_TAGPLATE"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MPPLY_OFFENSIVE_UGC"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MPPLY_BAD_CREW_NAME"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MPPLY_BAD_CREW_MOTTO"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MPPLY_BAD_CREW_STATUS"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MPPLY_BAD_CREW_EMBLEM"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MPPLY_GAME_EXPLOITS"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MPPLY_EXPLOITS"), 0, 0);
	STAT_SET_INT(GET_HASH_KEY("MPPLY_ISPUNISHED"), 0, 0);
	PrintMessage("Reports wiped and set as good player");

}
void UnlockAllClothing()
{
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_8"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_9"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_10"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_OUTFIT"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_8"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_9"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_10"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_OUTFIT"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TORSO"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL2_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_DECL"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TORSO"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL2_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_DECL"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TEETH"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TEETH_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TEETH_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_0"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_8"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_9"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_10"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_11"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_12"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_13"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_14"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_15"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_16"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_17"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_18"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_19"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_20"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_21"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_22"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_23"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_24"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_25"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_26"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_27"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_28"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_29"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_30"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_3-"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_32"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_33"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_34"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_35"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_36"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_37"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_38"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_39"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_40"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_8"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_9"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_10"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_11"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ADMIN_CLOTHES_RM_BS_10"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_10"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ADMIN_CLOTHES_RM_BS_11"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_11"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ADMIN_CLOTHES_RM_BS_12"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_12"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_8"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_9"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_10"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_OUTFIT"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_8"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_9"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_10"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_OUTFIT"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_TORSO"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL2_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_DECL"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_TEETH"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_TEETH_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_AVAILABLE_TEETH_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_TORSO"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL2_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_DECL"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_TEETH"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_TEETH_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_CLTHS_ACQUIRED_TEETH_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_0"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_8"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_9"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_10"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_11"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_12"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_13"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_14"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_15"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_16"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_17"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_18"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_19"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_20"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_21"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_22"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_23"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_24"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_25"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_26"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_27"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_28"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_29"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_30"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_3-"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_32"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_33"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_34"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_35"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_36"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_37"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_38"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_39"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_DLC_APPAREL_ACQUIRED_40"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ADMIN_CLOTHES_GV_BS_1"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ADMIN_CLOTHES_GV_BS_2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ADMIN_CLOTHES_GV_BS_3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ADMIN_CLOTHES_GV_BS_4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ADMIN_CLOTHES_GV_BS_5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ADMIN_CLOTHES_GV_BS_6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ADMIN_CLOTHES_GV_BS_7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ADMIN_CLOTHES_GV_BS_8"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ADMIN_CLOTHES_GV_BS_9"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ADMIN_CLOTHES_GV_BS_10"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ADMIN_CLOTHES_GV_BS_11"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ADMIN_CLOTHES_RM_BS_10"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ADMIN_CLOTHES_GV_BS_10"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ADMIN_CLOTHES_RM_BS_11"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ADMIN_CLOTHES_GV_BS_11"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ADMIN_CLOTHES_RM_BS_12"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP1_ADMIN_CLOTHES_GV_BS_12"), -1, 0);
	PrintMessage("Unlocked all clothing");
}
void HeistUnlocks()
{
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE2"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE3"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE4"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE5"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE6"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE7"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE8"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE9"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE10"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE11"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_KIT_FM_PURCHASE12"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_KIT_1_FM_UNLCK"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_KIT_2_FM_UNLCK"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_KIT_3_FM_UNLCK"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_KIT_4_FM_UNLCK"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_KIT_5_FM_UNLCK"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_KIT_6_FM_UNLCK"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_KIT_7_FM_UNLCK"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_KIT_8_FM_UNLCK"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_KIT_9_FM_UNLCK"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_KIT_10_FM_UNLCK"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_KIT_11_FM_UNLCK"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_KIT_12_FM_UNLCK"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_races_won"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_number_turbo_starts_in_race"), 100, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_usjs_found"), 50, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_usjs_completed"), 50, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_awd_fmwinairrace"), 50, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_awd_fmwinsearace"), 50, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_awd_fmrallywonnav"), 50, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_awd_fmrallywondrive"), 500, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_awd_fm_races_fastest_lap"), 500, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_char_fm_carmod_0_unlck"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_char_fm_carmod_1_unlck"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_char_fm_carmod_2_unlck"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_char_fm_carmod_3_unlck"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_char_fm_carmod_4_unlck"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_char_fm_carmod_5_unlck"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_char_fm_carmod_6_unlck"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_char_fm_carmod_7_unlck"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_FM_VEHICLE_1_UNLCK"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_FM_VEHICLE_2_UNLCK"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_FM_ABILITY_1_UNLCK"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_FM_ABILITY_2_UNLCK"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_FM_ABILITY_3_UNLCK"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_1_COLLECT"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_2_COLLECT"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_3_COLLECT"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_4_COLLECT"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_5_COLLECT"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_6_COLLECT"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_7_COLLECT"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_8_COLLECT"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_FM_PACKAGE_9_COLLECT"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_FM_HEALTH_1_UNLCK"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_FM_HEALTH_2_UNLCK"), -1, 0);
	STAT_SET_INT(GET_HASH_KEY("MP0_HOLDUPS_BITSET"), -1, 0);
	PrintMessage("All heist items unlocked");
}
void UnlimitedFireworks()
{
	char* fireworks[24] = { "MP0_FIREWORK_TYPE_1_WHITE", "MP0_FIREWORK_TYPE_1_RED", "MP0_FIREWORK_TYPE_1_BLUE", "MP0_FIREWORK_TYPE_2_WHITE", "MP0_FIREWORK_TYPE_2_RED", "MP0_FIREWORK_TYPE_2_BLUE", "MP0_FIREWORK_TYPE_3_WHITE", "MP0_FIREWORK_TYPE_3_RED", "MP0_FIREWORK_TYPE_3_BLUE", "MP0_FIREWORK_TYPE_4_WHITE", "MP0_FIREWORK_TYPE_4_RED", "MP0_FIREWORK_TYPE_4_BLUE", "MP1_FIREWORK_TYPE_1_WHITE", "MP1_FIREWORK_TYPE_1_RED", "MP1_FIREWORK_TYPE_1_BLUE", "MP1_FIREWORK_TYPE_2_WHITE", "MP1_FIREWORK_TYPE_2_RED", "MP1_FIREWORK_TYPE_2_BLUE", "MP0_FIREWORK_TYPE_3_WHITE", "MP1_FIREWORK_TYPE_3_RED", "MP1_FIREWORK_TYPE_3_BLUE", "MP1_FIREWORK_TYPE_4_WHITE", "MP1_FIREWORK_TYPE_4_RED", "MP1_FIREWORK_TYPE_4_BLUE" };
	for (int i = 0; i < 24; i++)
	{
		STAT_SET_INT(GET_HASH_KEY(fireworks[i]), 2147483647, 1);
	}
	PrintMessage("Set unlimited fireworks");
}
void UnlimitedArmour()
{
	char* armour[10] = { "MP0_MP_CHAR_ARMOUR_1_COUNT", "MP0_MP_CHAR_ARMOUR_2_COUNT", "MP0_MP_CHAR_ARMOUR_3_COUNT", "MP0_MP_CHAR_ARMOUR_4_COUNT", "MP0_MP_CHAR_ARMOUR_5_COUNT", "MP1_MP_CHAR_ARMOUR_1_COUNT", "MP1_MP_CHAR_ARMOUR_2_COUNT", "MP1_MP_CHAR_ARMOUR_3_COUNT", "MP1_MP_CHAR_ARMOUR_4_COUNT", "MP1_MP_CHAR_ARMOUR_5_COUNT" };
	for (int i = 0; i < 10; i++)
	{
		STAT_SET_INT(GET_HASH_KEY(armour[i]), 2147483647, 1);
	}
	PrintMessage("Set unlimited armour");
}
#pragma endregion
#pragma region AnimationOptions
bool RequestAnim(char *dict, char* anim)
{
	REQUEST_ANIM_DICT(dict);
	if (HAS_ANIM_DICT_LOADED(dict))
	{
		TASK_PLAY_ANIM(_ID, dict, anim, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
		return true;
	}
	return false;
}
void PlayAnimPed(Ped ped, char* dict, char* anim)
{
	AnimDict = dict;
	Anim = anim;
	ped_anim_id = ped;
	play_anim_for_ped = true;
}
bool PlayAnimForPed()
{
	REQUEST_ANIM_DICT(AnimDict);
	if (HAS_ANIM_DICT_LOADED(AnimDict))
	{
		TASK_PLAY_ANIM(ped_anim_id, AnimDict, Anim, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
		return true;
	}
	return false;
}
bool load_anim_dict(char* dict)
{
	REQUEST_ANIM_DICT(dict);
	if (HAS_ANIM_DICT_LOADED(dict))
		return true;
	return false;
}
void PlayAnim(char *dict, char *anim)
{
	AnimDict = dict;
	Anim = anim;
	play_anim = true;
}
void StopAnim()
{
	CLEAR_PED_TASKS_IMMEDIATELY(_ID);
}
#pragma region PedOptions
int count = 0;
void ClearPedProperties(int id)
{
	peds[id].id = 0;
	peds[id].name = "None";
	peds[id].dancing = false;
	peds[id].invincible = false;
	REMOVE_BLIP(&peds[id].blip);
}
void GuardsKillClient()
{
	if (count != 0)
	{
		for (int i = 0; i < 6; ++i)
		{
			TASK_COMBAT_PED(peds[i].id, GET_PLAYER_PED(SelectedClient), 0, 16);
		}
		PrintMessage(Format("Guards going after %s", players[SelectedClient].name));
	}
	else
		PrintMessage("No guards in your group");
}
void RandomizeGuard()
{
	SET_PED_RANDOM_COMPONENT_VARIATION(peds[selectedped].id, 0);
}
void RemoveAllGuards()
{
	int players;
	if (count != 0)
	{
		for (int i = 0; i < 6; ++i)
		{
			SET_ENTITY_AS_MISSION_ENTITY(peds[i].id, 0, 1);
			REMOVE_PED_FROM_GROUP(peds[i].id);
			ClearPedProperties(i);
		}
		PrintMessage("Removed all guards from your group");
	}
	else
		PrintMessage("~r~Error:~w~ No guards in group");
}
void DeletePed()
{
	SET_ENTITY_AS_MISSION_ENTITY(peds[selectedped].id, 0, 1);
	REMOVE_PED_FROM_GROUP(peds[selectedped].id);
	DELETE_PED(&peds[selectedped].id);
	ClearPedProperties(selectedped);
	count--;
	PrintMessage("Deleted ped");
	WhichMenu = 33;
	Scroll = selectedped;
}
void GivePedGun(int weap)
{
	GIVE_DELAYED_WEAPON_TO_PED(peds[selectedped].id, weap, 999, 999);
	SET_CURRENT_PED_WEAPON(peds[selectedped].id, weap, true);
	PrintMessage("Gave weapon to ped");
}
void BlowUpPed()
{
	Vector3 c = GET_ENTITY_COORDS(GET_PLAYER_PED(peds[selectedped].id), 1);
	ADD_EXPLOSION(c.x, c.y, c.z, 5, 10.0f, true, false, 0);
	PrintMessage(Format("Blew up %s", peds[selectedped].name));
}
void MakePedDance()
{
	if (peds[selectedped].dancing)
	{
		CLEAR_PED_TASKS_IMMEDIATELY(peds[selectedped].id);
		PrintMessage("Stopped ped dance");
		peds[selectedped].dancing = false;
	}
	else
	{
		REQUEST_ANIM_DICT("mini@strip_club@pole_dance@pole_dance1");
		if (HAS_ANIM_DICT_LOADED("mini@strip_club@pole_dance@pole_dance1"))
		{
			TASK_PLAY_ANIM(peds[selectedped].id, "mini@strip_club@pole_dance@pole_dance1", "pd_dance_01", 8.0f, 0.0f, 1, 9, 0, 0, 0, 0);
			PrintMessage(Format("%s is now dancing", peds[selectedped].name));
			peds[selectedped].dancing = true;
		}
	}
}
void KickGuardFromGroup()
{
	SET_ENTITY_AS_MISSION_ENTITY(peds[selectedped].id, 0, 1);
	REMOVE_PED_FROM_GROUP(peds[selectedped].id);
	count--;
	PrintMessage(Format("Kicked %s from group", peds[selectedped].name));
	ClearPedProperties(selectedped);
}
void GivePedsGuns(int weap)
{
	if (count != 0)
	{
		for (int i = 0; i < 6; i++)
		{
			GIVE_DELAYED_WEAPON_TO_PED(peds[i].id, weap, 999, 999);
			SET_CURRENT_PED_WEAPON(peds[i].id, weap, true);
		}
		PrintMessage("Gave all guards weapons");
	}
	else
		PrintMessage("No guards in group");
}
void AllGuardsInvincible()
{
	if (count != 0)
	{
		if (!doallpedsgodmode)
		{
			for (int i = 0; i < 6; i++)
			{
				SET_ENTITY_INVINCIBLE(peds[i].id, true);
				peds[i].invincible = true;
			}
			PrintMessage("Gave god mode to all peds");
			doallpedsgodmode = true;
		}
		else
		{
			for (int i = 0; i < 6; i++)
			{
				SET_ENTITY_INVINCIBLE(peds[i].id, false);
				peds[i].invincible = false;
			}
			PrintMessage("Turned off god mode for all");
			doallpedsgodmode = false;
		}
	}
	else
		PrintMessage("No guards in group");
}
void GuardInvincible()
{
	if (peds[selectedped].invincible)
	{
		SET_ENTITY_INVINCIBLE(peds[selectedped].id, false);
		peds[selectedped].invincible = false;
		PrintMessage(Format("God mode disabled for %s", peds[selectedped].name));
	}
	else
	{
		SET_ENTITY_INVINCIBLE(peds[selectedped].id, true);
		peds[selectedped].invincible = true;
		PrintMessage(Format("God mode enabled for %s", peds[selectedped].name));
	}
}
void DeletePeds()
{
	if (count != 0)
	{
		for (int i = 0; i < 6; i++)
		{
			if (DOES_ENTITY_EXIST(peds[i].id))
			{
				SET_ENTITY_AS_MISSION_ENTITY(peds[i].id, 0, 1);
				REMOVE_PED_FROM_GROUP(peds[i].id);
				DELETE_PED(&peds[i].id);
				ClearPedProperties(i);
			}
			PrintMessage("Deleted all peds");
		}
		count = 0;
	}
	else
		PrintMessage("No guards in group");
}
void AllPedsDance()
{
	if (count != 0)
	{
		if (arepedsdancing)
		{
			for (int i = 0; i < 6; i++)
			{
				CLEAR_PED_TASKS_IMMEDIATELY(peds[i].id);
			}
			PrintMessage("Guards are no longer dancing");
			arepedsdancing = false;
		}
		else
		{
			REQUEST_ANIM_DICT("mini@strip_club@pole_dance@pole_dance1");
			if (HAS_ANIM_DICT_LOADED("mini@strip_club@pole_dance@pole_dance1"))
			{
				for (int i = 0; i < 6; i++) {
					TASK_PLAY_ANIM(peds[i].id, "mini@strip_club@pole_dance@pole_dance1", "pd_dance_01", 8.0f, 0.0f, 1, 9, 0, 0, 0, 0);
				}
				PrintMessage("All guards now dancing");
				arepedsdancing = true;
			}
		}
	}
	else
		PrintMessage("No guards in group");
}
void TeleportAllToMe()
{
	if (count != 0)
	{
		for (int i = 0; i < 6; i++)
		{
			Vector3 c = GET_ENTITY_COORDS(_ID, 1);
			SET_ENTITY_COORDS(peds[selectedped].id, c.x, c.y, c.z, 1, 0, 0, 1);
		}
		PrintMessage("Teleported all guards to you");
	}
	else
		PrintMessage("No guards in group");
}
void TeleportPedToMe()
{
	if (count != 0)
	{
		Vector3 c = GET_ENTITY_COORDS(_ID, 1);
		SET_ENTITY_COORDS(peds[selectedped].id, c.x, c.y, c.z, 1, 0, 0, 1);
		PrintMessage(Format("Teleported %s to you", peds[selectedped].name));
	}
	else
		PrintMessage("No guards in group");
}
#pragma endregion
#pragma region TeleportOptions
void TeleportToWaypoint()
{
	float z;
	bool ground_found = false;
	int way = GET_FIRST_BLIP_INFO_ID(8);
	if (DOES_BLIP_EXIST(way))
	{
		Entity e = PLAYER_PED_ID();
		if (IS_PED_IN_ANY_VEHICLE(e, 1))
			e = GET_VEHICLE_PED_IS_IN(e, 1);

		Vector3 point = GET_BLIP_COORDS(way), coords;
		SET_ENTITY_COORDS_NO_OFFSET(e, point.x, point.y, 0, false, false, true);

		PrintMessage("Teleported to waypoint");
	}
	else
		PrintMessage("No waypoint set");
}
void TeleportAbove()
{
	Vector3 c = GET_ENTITY_COORDS(_ID, 1);
	c.z += 10;
	if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
		SET_ENTITY_COORDS(veh, c.x, c.y, c.z, 1, 0, 0, 1);
	}
	else
		SET_ENTITY_COORDS(_ID, c.x, c.y, c.z, 1, 0, 0, 1);

	PrintMessage("Teleported above");
}
void TeleportForward()
{
	if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
	{
		Vector3 min, max, pos;
		Vector3 offset = { 0, 0, 0 };
		Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
		int model = GET_ENTITY_MODEL(veh);
		GET_MODEL_DIMENSIONS(model, &min, &max);
		offset.y = max.y + 10;
		pos = GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, offset.x, offset.y, offset.z);
		SET_ENTITY_COORDS(veh, pos.x, pos.y, pos.z, 1, 0, 0, 1);
	}
	else
	{
		Vector3 c = { 0, 0, 0 }, pos;
		c.y += 10;
		pos = GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(_ID, c.x, c.y, c.z);
		SET_ENTITY_COORDS(_ID, pos.x, pos.y, pos.z, 1, 0, 0, 1);
	}
	PrintMessage("Teleported forward");
}
#pragma endregion
#pragma region ClientOptions
void SendText(char* msg, int id)
{
	if (GET_PLAYER_PED(id) != _ID)
	{
		NETWORK_HANDLE_FROM_PLAYER(id, NetHandleBuffer, 13);
		NETWORK_SEND_TEXT_MESSAGE(msg, NetHandleBuffer);
	}
}
void SendTextToAll(char *msg)
{
	for (int i = 0; i < 16; i++)
	{
		if (NETWORK_IS_PLAYER_ACTIVE(i))
		{
			if (GET_PLAYER_PED(i) != PLAYER_PED_ID())
			{
				NETWORK_HANDLE_FROM_PLAYER(i, NetHandleBuffer, 13);
				NETWORK_SEND_TEXT_MESSAGE(msg, NetHandleBuffer);
			}
		}
	}
}
void AttachToClient()
{
	if (PLAYER_PED_ID() != GET_PLAYER_PED(SelectedClient)) {
		if (DOES_ENTITY_EXIST(_ID) && DOES_ENTITY_EXIST(GET_PLAYER_PED(SelectedClient)))
		{
			ATTACH_ENTITY_TO_ENTITY(PLAYER_PED_ID(), GET_PLAYER_PED(SelectedClient), -1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 1);
			PrintMessage(Format("Attached to %s", players[SelectedClient].name));
		}
	}
	else
		PrintMessage("Don't attach to yourself! How would that even work?");
}
void AttachToPlayersCar()
{
	if (DOES_ENTITY_EXIST(PLAYER_PED_ID()) && DOES_ENTITY_EXIST(GET_PLAYER_PED(SelectedClient)))
	{
		if (IS_PED_IN_ANY_VEHICLE(GET_PLAYER_PED(SelectedClient), 1))
		{
			Vector3 min, max;
			Vehicle veh = GET_VEHICLE_PED_IS_IN(GET_PLAYER_PED(SelectedClient), 1);
			Entity model = GET_ENTITY_MODEL(veh);
			GET_MODEL_DIMENSIONS(model, &min, &max);
			ATTACH_ENTITY_TO_ENTITY(_ID, veh, -1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 1);
			PrintMessage(Format("Attached to %s's vehicle", players[SelectedClient].name));
		}
		else
			PrintMessage(Format("%s is not in a vehicle", players[SelectedClient].name));
	}
}
void DetachFromEntity()
{
	if (PLAYER_PED_ID() != GET_PLAYER_PED(SelectedClient))
	{
		if (DOES_ENTITY_EXIST(PLAYER_PED_ID()) && DOES_ENTITY_EXIST(GET_PLAYER_PED(SelectedClient)))
		{
			if (IS_ENTITY_ATTACHED(PLAYER_PED_ID()))
			{
				DETACH_ENTITY(_ID, 0, 0);
				CLEAR_PED_TASKS_IMMEDIATELY(_ID);
				PrintMessage("Detached from entity");
			}
		}
	}
}
void Slingshot()
{
	if (IS_PED_IN_ANY_VEHICLE(GET_PLAYER_PED(SelectedClient), 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(GET_PLAYER_PED(SelectedClient), 1);
		if (RequestLoop(veh))
		{
			APPLY_FORCE_TO_ENTITY(veh, 1, 0, 0, 70, 20, 20, 20, 1, 1, 1, 1, 0, 1);
			PrintMessage(Format("Slingshotted %s's vehicle", players[SelectedClient].name));
		}
	}
	else
		PrintMessage("Not in vehicle");
}
void BoostPlayerVehicle()
{
	if (IS_PED_IN_ANY_VEHICLE(GET_PLAYER_PED(SelectedClient), 1)) {
		Vehicle veh = GET_VEHICLE_PED_IS_IN(GET_PLAYER_PED(SelectedClient), 1);
		if (RequestLoop(veh))
		{
			SET_VEHICLE_FORWARD_SPEED(veh, 100.00f);
			PrintMessage(Format("Boosted %s's vehicle", players[SelectedClient].name));
		}
	}
	else
		PrintMessage("Not in vehicle");
}
void FlipCarOver()
{
	if (IS_PED_IN_ANY_VEHICLE(GET_PLAYER_PED(SelectedClient), 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(GET_PLAYER_PED(SelectedClient), 1);
		NETWORK_REQUEST_CONTROL_OF_ENTITY(veh);
		SET_VEHICLE_ON_GROUND_PROPERLY(veh);
		PrintMessage(Format("Set %s's vehicle upright", players[SelectedClient].name));
	}
	else
		PrintMessage("Not in vehicle");
}
void FixNetCar()
{
	if (IS_PED_IN_ANY_VEHICLE(GET_PLAYER_PED(SelectedClient), 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(GET_PLAYER_PED(SelectedClient), 1);
		if (RequestLoop(veh))
		{
			SET_VEHICLE_FIXED(veh);
			PrintMessage(Format("Fixed %s's vehicle", players[SelectedClient].name));
		}
	}
	else {
		PrintMessage("Not in vehicle");
	}
}
void RandomNetCarColor()
{
	if (IS_PED_IN_ANY_VEHICLE(GET_PLAYER_PED(SelectedClient), 1)) {
		Vehicle veh = GET_VEHICLE_PED_IS_IN(GET_PLAYER_PED(SelectedClient), 1);
		if (RequestLoop(veh))
		{
			SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, irand(0, 255), irand(0, 255), irand(0, 255));
			SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, irand(0, 255), irand(0, 255), irand(0, 255));
			PrintMessage(Format("Randomized %s's vehicle color", players[SelectedClient].name));
		}
	}
	else {
		PrintMessage("Not in vehicle");
	}
}
void FuckUpCar()
{
	if (IS_PED_IN_ANY_VEHICLE(GET_PLAYER_PED(SelectedClient), 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(GET_PLAYER_PED(SelectedClient), 1);
		if (RequestLoop(veh))
		{
			SET_VEHICLE_NUMBER_PLATE_TEXT(veh, "ILUVCOX");
			SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 255, 0, 127);
			SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, 255, 0, 127);
			SET_VEHICLE_PETROL_TANK_HEALTH(veh, -1);
			START_VEHICLE_ALARM(veh);
			SET_VEHICLE_DIRT_LEVEL(veh, 100);
			SET_VEHICLE_DOOR_BROKEN(veh, 0, true);
			SET_VEHICLE_DOOR_BROKEN(veh, 1, true);
			SET_VEHICLE_DOOR_BROKEN(veh, 2, true);
			SET_VEHICLE_DOOR_BROKEN(veh, 3, true);
			SET_VEHICLE_IS_WANTED(veh, true);
			SET_VEHICLE_IS_STOLEN(veh, true);
			PrintMessage(Format("Fucked up %s's vehicle", players[SelectedClient].name));
		}
	}
	else
		PrintMessage("Not in vehicle");
}
void UndriveableCar()
{
	if (IS_PED_IN_ANY_VEHICLE(GET_PLAYER_PED(SelectedClient), 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(GET_PLAYER_PED(SelectedClient), 1);
		if (RequestLoop(veh))
		{
			SET_VEHICLE_UNDRIVEABLE(veh, true);
			PrintMessage(Format("%s's vehicle is now undriveable", players[SelectedClient].name));
		}
	}
	else
		PrintMessage("Not in vehicle");
}
void DeleteVehicle()
{
	if (IS_PED_IN_ANY_VEHICLE(GET_PLAYER_PED(SelectedClient), 1)) {
		Vehicle veh = GET_VEHICLE_PED_IS_IN(GET_PLAYER_PED(SelectedClient), 1);
		if (RequestLoop(veh)) {
			SET_ENTITY_AS_MISSION_ENTITY(veh, 0, 1);
			DELETE_VEHICLE(&veh);
			PrintMessage(Format("Deleted %s's vehicle", players[SelectedClient].name));
		}
	}
	else
		PrintMessage("Not in vehicle");
}
void LockPlayersDoors()
{
	if (IS_PED_IN_ANY_VEHICLE(GET_PLAYER_PED(SelectedClient), 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(GET_PLAYER_PED(SelectedClient), 1);
		if (RequestLoop(veh))
		{
			SET_VEHICLE_DOORS_LOCKED(veh, true);
			PrintMessage(Format("Locked %s's doors", players[SelectedClient].name));
		}
	}
	else
		PrintMessage("Not in vehicle");
}
void SupeUpVehicle()
{
	if (IS_PED_IN_ANY_VEHICLE(GET_PLAYER_PED(SelectedClient), 1)) {
		Vehicle veh = GET_VEHICLE_PED_IS_IN(GET_PLAYER_PED(SelectedClient), 1);
		if (RequestLoop(veh)) {
			set_vehicle_mod(GET_PLAYER_PED(SelectedClient), 11, 3);
			set_vehicle_mod(GET_PLAYER_PED(SelectedClient), 13, 2);
			set_vehicle_mod(GET_PLAYER_PED(SelectedClient), 12, 2);
			set_vehicle_mod(GET_PLAYER_PED(SelectedClient), 15, 3);
			set_vehicle_mod(GET_PLAYER_PED(SelectedClient), 4, 3);
			set_vehicle_mod(GET_PLAYER_PED(SelectedClient), 16, 4);
			set_vehicle_tyres_can_burst(GET_PLAYER_PED(SelectedClient));
			set_vehicle_number_plate_text_index(GET_PLAYER_PED(SelectedClient), 5);
			set_vehicle_window_tint(GET_PLAYER_PED(SelectedClient), 5);
			PrintMessage(Format("Suped up %s's vehicle", players[SelectedClient].name));
		}

	}
	else
		PrintMessage("Not in vehicle");
}
void TeleportToClient()
{
	Vector3 c;
	c = GET_ENTITY_COORDS(GET_PLAYER_PED(SelectedClient), 1);
	c.y += 3.0;
	if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
		if (DOES_ENTITY_EXIST(veh))
			SET_ENTITY_COORDS(veh, c.x, c.y, c.z, 0, 0, 0, 1);
	}
	else
		SET_ENTITY_COORDS(_ID, c.x, c.y, c.z, 0, 0, 0, 1);

	PrintMessage(Format("Teleported to %s", players[SelectedClient].name));
}
void TeleportIntoPlayerCar()
{
	if (IS_PED_IN_ANY_VEHICLE(GET_PLAYER_PED(SelectedClient), 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(GET_PLAYER_PED(SelectedClient), 1);
		SetInCar(veh);
	}
	else {
		PrintMessage(Format("%s is not in a vehicle", players[SelectedClient].name));
	}
}
void RemoveAllWeapons()
{

	REMOVE_ALL_PED_WEAPONS(GET_PLAYER_PED(SelectedClient), 1);
	PrintMessage(Format("Took %s's weapons", players[SelectedClient].name));
}
void GiveClientWeapons()
{
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x3656C8C1, 9999, 1); // stun gun
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x99B507EA, 9999, 1); // knife
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x678B81B1, 9999, 1); // night stick
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x4E875F73, 9999, 1); // hammer
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x958A4A8F, 9999, 1); // bat
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x440E4788, 9999, 1); // golf club
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x84BD7BFD, 9999, 1); // crowbar
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x1B06D571, 9999, 5); // pistol
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x5EF9FEC4, 9999, 1); // combat pistol
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x22D8FE39, 9999, 1); // ap pistol
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x99AEEB3B, 9999, 1); // pistol 50.
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x13532244, 9999, 1); // micro smg
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x2BE6766B, 9999, 1); // smg
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0xEFE7E2DF, 9999, 1); // assault smg
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0xBFEFFF6D, 9999, 1); // assault rifle
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x83BF0278, 9999, 1); // carbine rifle
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0xAF113F99, 9999, 1); // advanced rifle
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x9D07F764, 9999, 1); // MG
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x7FD62962, 9999, 1); // combat mg
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x1D073A89, 9999, 1); // pump shotgun
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x7846A318, 9999, 1); // sawnoff shotgun
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0xE284C527, 9999, 1); // assault shotgun
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x9D61E50F, 9999, 1); // bullpupshotgun
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x05FC3C11, 9999, 1); // sniper
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x0C472FE2, 9999, 1); // heavy sniper
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0xA284510B, 9999, 1); // grenade launcher
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0xB1CA77B1, 9999, 1); // rpg
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x42BF8A85, 9999, 1); // minigun
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x93E220BD, 9999, 1); // grenades
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x2C3731D9, 9999, 1); // sticky bomb
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0xFDBC8A50, 9999, 1); // smoke grenade
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x34A67B97, 9999, 1); // petrol can
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x060EC506, 9999, 1); // fire extinguisher
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x24B17070, 9999, 1); // moltovs
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x497FACC3, 9999, 1); // flare
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0xFDBADCED, 9999, 1); // digiscanner
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x687652CE, 9999, 1); // stinger
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 600439132, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x61012683, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0xC0A3098D, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0xD205520E, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0xBFD21232, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x7F229F94, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x92A27487, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0xA89CB99E, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x3AABBBAA, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0xC734385A, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x63AB0442, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0xAB564B93, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x0787F0BB, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0xE232C28C, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0xD04C944D, 9999, 1); // ball
	GIVE_DELAYED_WEAPON_TO_PED(GET_PLAYER_PED(SelectedClient), 0x7F7497E5, 9999, 1);
	PrintMessage(Format("Gave all weapons to %s", players[SelectedClient].name));
}
void KickPlayer()
{
	if (NETWORK_IS_HOST())
	{
		NETWORK_SESSION_KICK_PLAYER(SelectedClient);
		PrintMessage("Kicked player");
	}
	else
		PrintMessage("You need to be host to kick players");
}
void OwnedExplosion()
{
	for (int i = 0; i < 16; i++)
	{
		if (GET_PLAYER_PED(i) != PLAYER_PED_ID())
		{
			Vector3 c = GET_ENTITY_COORDS(GET_PLAYER_PED(i), 1);
			ADD_OWNED_EXPLOSION(GET_PLAYER_PED(SelectedClient), c.x, c.y, c.z, 5, 32, true, false, 0);
		}
	}
	PrintMessage(Format("%s blew everyone up", players[SelectedClient].name));
}
void TeleportVehToSky()
{
	if (IS_PED_IN_ANY_VEHICLE(GET_PLAYER_PED(SelectedClient), 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(GET_PLAYER_PED(SelectedClient), 1);
		Vector3 c = GET_ENTITY_COORDS(veh, 1);
		c.z = 800;
		if (RequestLoop(veh)) {
			SET_ENTITY_COORDS(veh, c.x, c.y, c.z, 1, 0, 0, 1);
			PrintMessage(Format("Sent %s to the sky", players[SelectedClient].name));
		}
	}
	else
		PrintMessage("Not in vehicle");
}
void TeleportVehToMe()
{
	if (IS_PED_IN_ANY_VEHICLE(GET_PLAYER_PED(SelectedClient), 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(GET_PLAYER_PED(SelectedClient), 1);
		Vector3 c = GET_ENTITY_COORDS(_ID, 1);
		if (RequestLoop(veh)) {
			SET_ENTITY_COORDS(veh, c.x, c.y, c.z, 1, 0, 0, 1);
			PrintMessage(Format("Teleported %s to you", players[SelectedClient].name));
		}
	}
	else
		PrintMessage(Format("%s is not in a vehicle", players[SelectedClient].name));
}
void TrollPlayer()
{
	for (int i = 0; i < 16; i++)
	{
		if (NETWORK_IS_PLAYER_ACTIVE(players[i].id))
		{
			if (IS_PED_IN_ANY_VEHICLE(GET_PLAYER_PED(players[i].id), 1)) {
				if (players[i].troll) {
					Vehicle veh = GET_VEHICLE_PED_IS_IN(GET_PLAYER_PED(players[i].id), 1);
					if (RequestLoop(veh))
					{
						SET_ENTITY_AS_MISSION_ENTITY(veh, 0, 1);
						DELETE_VEHICLE(&veh);
					}
				}
			}
		}
		else if (players[i].troll)
		{
			players[i].troll = false;
			PrintMessage(Format("%s is no longer active\nVehicle troll for them has been turned off", players[SelectedClient].name));
		}
	}
}
void FreezePlayerCar()
{
	if (IS_PED_IN_ANY_VEHICLE(GET_PLAYER_PED(SelectedClient), 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_USING(GET_PLAYER_PED(SelectedClient));
		if (RequestLoop(veh))
		{
			FREEZE_ENTITY_POSITION(veh, 1);
			PrintMessage(Format("Froze %s's vehicle", players[SelectedClient].name));
		}
	}
	else
		PrintMessage("Not in vehicle");
}
void UnfreezePlayerCar()
{
	if (IS_PED_IN_ANY_VEHICLE(GET_PLAYER_PED(SelectedClient), 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_USING(GET_PLAYER_PED(SelectedClient));
		if (RequestLoop(veh))
		{
			FREEZE_ENTITY_POSITION(veh, 0);
			SET_VEHICLE_FORWARD_SPEED(veh, 20);
			PrintMessage(Format("Unfroze %s's vehicle", players[SelectedClient].name));
		}
	}
	else
		PrintMessage("Not in vehicle");
}
void RapePlayer()
{
	if (PLAYER_PED_ID() != GET_PLAYER_PED(SelectedClient)) {
		if (DOES_ENTITY_EXIST(_ID) && DOES_ENTITY_EXIST(GET_PLAYER_PED(SelectedClient)))
		{
			Vector3 unk = { 0, -0.5, 0 };
			Vector3 unk2 = { 0, 0, 0 };
			ATTACH_ENTITY_TO_ENTITY(_ID, GET_PLAYER_PED(SelectedClient), -1, 0, -0.5, 0, 0, 0, 0, 1, 1, 0, 0, 2, 1);
			PlayAnim("rcmpaparazzo_2", "shag_loop_a");
			PrintMessage(Format("Sexing %s", players[SelectedClient].name));
		}
	}
	else
		PrintMessage("Why would you want to rape yourself?");
}
void PiggyBackRide()
{
	if (PLAYER_PED_ID() != GET_PLAYER_PED(SelectedClient)) {
		if (DOES_ENTITY_EXIST(_ID) && DOES_ENTITY_EXIST(GET_PLAYER_PED(SelectedClient)))
		{
			Vector3 unk = { 0, -0.5, 0 };
			Vector3 unk2 = { 0, 0, 0 };
			ATTACH_ENTITY_TO_ENTITY(_ID, GET_PLAYER_PED(SelectedClient), -1, 0, -0.5, 0, 0, 0, 0, 1, 1, 0, 0, 2, 1);
			PlayAnim("oddjobs@assassinate@vice@sex", "frontseat_carsex_base_m");
			PrintMessage("Giddy up horsey!");
		}
	}
	else
		PrintMessage("Don't do this on yourself!");
}
void DropCashOnClient()
{
	for (int i = 0; i < 16; i++)
	{
		if (NETWORK_IS_PLAYER_ACTIVE(players[i].id))
		{
			if (players[i].dropcash) {
				int prop = 0x113fd533;
				if (IS_MODEL_IN_CDIMAGE(prop))
					REQUEST_MODEL(prop);
				if (HAS_MODEL_LOADED(prop))
				{
					Vector3 c;
					c = GET_ENTITY_COORDS(GET_PLAYER_PED(players[i].id), 1);
					CREATE_AMBIENT_PICKUP(0xCE6FDD6B, c.x, c.y, c.z + 1, 0, 40000, prop, 0, 1);
				}
			}
		}
		else if (players[i].dropcash)
		{
			players[i].dropcash = false;
			PrintMessage(Format("%s is no longer active\nCash drop for them has been turned off", players[i].name));
		}
	}
}
void steal_ownership()
{
	if (DOES_ENTITY_EXIST(GET_PLAYER_PED(SelectedClient))) {
		if (IS_PED_IN_ANY_VEHICLE(GET_PLAYER_PED(SelectedClient), 1))
		{
			Vehicle veh = GET_VEHICLE_PED_IS_IN(GET_PLAYER_PED(SelectedClient), 1);
			if (RequestLoop(veh))
			{
				DECOR_SET_INT(veh, "Player_Vehicle", GET_HASH_KEY(GET_PLAYER_NAME(SelectedClient)));
				PrintMessage(Format("Removed vehicle ownership from %s's vehicle", players[SelectedClient].name));
			}
		}
		else
			PrintMessage(Format("%s is not in a vehicle", players[SelectedClient].name));
	}
	else
		PrintMessage("Player no longer in game");
}
void give_ownership()
{
	if (DOES_ENTITY_EXIST(GET_PLAYER_PED(SelectedClient))) {
		if (IS_PED_IN_ANY_VEHICLE(GET_PLAYER_PED(SelectedClient), 1))
		{
			Vehicle veh = GET_VEHICLE_PED_IS_IN(GET_PLAYER_PED(SelectedClient), 1);
			int hash = _0xF8D7AF3B(SelectedClient);
			if (RequestLoop(veh))
			{
				SET_ENTITY_AS_MISSION_ENTITY(veh, 0, 1);
				DECOR_REMOVE(veh, "Player_Vehicle");
				DECOR_SET_INT(veh, "Player_Vehicle", hash);
				DECOR_SET_INT(veh, "Veh_Modded_By_Player", hash);
				DECOR_SET_INT(veh, "PV_Slot", 2);
				DECOR_SET_INT(veh, "Previous_Owner", hash);

				PrintMessage("Work in progress\nYou can drive this vehicle into your garage now");
			}
		}
		else
			PrintMessage(Format("%s is not in a vehicle", players[SelectedClient].name));
	}
	else
		PrintMessage("Player no longer in game");
}
void freeze_in_place()
{
	for (int i = 0; i < 16; i++)
	{
		if (players[i].freeze_in_place)
		{
			CLEAR_PED_TASKS_IMMEDIATELY(GET_PLAYER_PED(i));
		}
	}
}
void RemoveRestrictions()
{
	TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("am_armybase");
	TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("restrictedareas");
	TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_armybase");
	TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_lossantosintl");
	TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_prison");
	TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_prisonvanbreak");
}
void DrawBox(int client)
{
	Vector3 c = GET_ENTITY_COORDS(GET_PLAYER_PED(client), 1);
	c.x += 0.5;
	c.z += 0.8;
	Vector3 c11 = { c.x, c.y, c.z };
	Vector3 c1 = GET_ENTITY_COORDS(GET_PLAYER_PED(client), 1);
	c1.x -= 0.5;
	c1.z += 0.8;
	Vector3 c22 = { c1.x, c1.y, c1.z };
	Vector3 c2 = GET_ENTITY_COORDS(GET_PLAYER_PED(client), 1);
	c2.x -= 0.5;
	c2.z -= 0.8;
	Vector3 c33 = { c2.x, c2.y, c2.z };
	Vector3 c3 = GET_ENTITY_COORDS(GET_PLAYER_PED(client), 1);
	c3.x -= 0.5;
	c3.z += 0.8;
	Vector3 c44 = { c3.x, c3.y, c3.z };
	Vector3 c4 = GET_ENTITY_COORDS(GET_PLAYER_PED(client), 1);
	c4.x += 0.5;
	c4.z -= 0.8;
	Vector3 c55 = { c4.x, c4.y, c4.z };
	Vector3 c5 = GET_ENTITY_COORDS(GET_PLAYER_PED(client), 1);
	c5.x += 0.5;
	c5.z += 0.8;
	Vector3 c66 = { c5.x, c5.y, c5.z };
	Vector3 c6 = GET_ENTITY_COORDS(GET_PLAYER_PED(client), 1);
	c6.x += 0.5;
	c6.z -= 0.8;
	Vector3 c77 = { c6.x, c6.y, c6.z };
	Vector3 c7 = GET_ENTITY_COORDS(GET_PLAYER_PED(client), 1);
	c7.x -= 0.5;
	c7.z -= 0.8;
	Vector3 c88 = { c7.x, c7.y, c7.z };
	DRAW_LINE(c11.x, c11.y, c11.z, c22.x, c22.y, c22.z, 255, 0, 0, 255);
	DRAW_LINE(c33.x, c33.y, c33.z, c44.x, c44.y, c44.z, 255, 0, 0, 255);
	DRAW_LINE(c55.x, c55.y, c55.z, c66.x, c66.y, c66.z, 255, 0, 0, 255);
	DRAW_LINE(c77.x, c77.y, c77.z, c88.x, c88.y, c88.z, 255, 0, 0, 255);
}
void ESPClient()
{
	for (int i = 0; i < 16; i++)
	{
		if (NETWORK_IS_PLAYER_ACTIVE(players[i].id))
		{
			if (players[i].esp)
			{
				DrawBox(players[i].id);
			}
		}
		else if (players[i].esp)
		{
			players[i].esp = false;
			PrintMessage(Format("%s is no longer active\nESP has been disabled", players[i].name));
		}
	}
}
void jack_vehicle()
{
	if (IS_PED_IN_ANY_VEHICLE(GET_PLAYER_PED(players[SelectedClient].id), 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(GET_PLAYER_PED(players[SelectedClient].id), 1);
		if (!IS_VEHICLE_SEAT_FREE(veh, -1))
		{
			if (GET_PED_IN_VEHICLE_SEAT(veh, -1) == GET_PLAYER_PED(players[SelectedClient].id), 1)
			{
				CLEAR_PED_TASKS_IMMEDIATELY(GET_PLAYER_PED(SelectedClient));
				CLEAR_PED_SECONDARY_TASK(GET_PLAYER_PED(SelectedClient));
				//SET_PED_INTO_VEHICLE(PLAYER_PED_ID(), veh, -1);
				PrintMessage(Format("Kicked %s out of their vehicle", players[SelectedClient].name));
			}
			else
				PrintMessage(Format("%s is not driving vehicle", players[SelectedClient].name));
		}
		else
			PrintMessage("No one is driving vehicle");
	}
	else
		PrintMessage(Format("%s is not in a vehicle", players[SelectedClient].name));
}
#pragma endregion

#pragma region AllClientOptions
void AllPlayersCash()
{
	int prop = 0x113fd533;
	REQUEST_MODEL(prop);
	if (HAS_MODEL_LOADED(prop))
	{
		Vector3 c;
		for (int i = 0; i < 16; i++)
		{
			if (GET_PLAYER_PED(i) != PLAYER_PED_ID())
			{
				c = GET_ENTITY_COORDS(GET_PLAYER_PED(i), 1);
				CREATE_AMBIENT_PICKUP(0xCE6FDD6B, c.x, c.y, c.z, 0, 40000, prop, 0, 1);
			}
		}
	}
}
void ExplodeAll()
{
	for (int i = 0; i < 16; i++)
	{
		if (PLAYER_PED_ID() != GET_PLAYER_PED(i))
		{
			Vector3 c = GET_ENTITY_COORDS(GET_PLAYER_PED(i), 1);
			ADD_EXPLOSION(c.x, c.y, c.z, 5, 16.0f, false, false, 0);
		}
	}
}
void VehicleColorAll()
{
	for (int i = 0; i < 16; ++i)
	{
		if (IS_PED_IN_ANY_VEHICLE(GET_PLAYER_PED(i), 1))
		{
			Vehicle veh = GET_VEHICLE_PED_IS_IN(GET_PLAYER_PED(i), 1);
			if (RequestLoop(veh)) {
				SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, irand(0, 255), irand(0, 255), irand(0, 255));
				SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, irand(0, 255), irand(0, 255), irand(0, 255));
			}
		}
		else
			continue;
	}
}
void VehicleFixAll()
{
	for (int i = 0; i < 16; ++i)
	{
		if (IS_PED_IN_ANY_VEHICLE(GET_PLAYER_PED(i), 1))
		{
			Vehicle veh = GET_VEHICLE_PED_IS_IN(GET_PLAYER_PED(i), 1);
			if (RequestLoop(veh))
				SET_VEHICLE_FIXED(veh);
		}
		else continue;
	}
}
void SupeUpAllVehicles()
{
	for (int i = 0; i < 16; ++i)
	{
		if (IS_PED_IN_ANY_VEHICLE(GET_PLAYER_PED(i), 1))
		{
			Vehicle veh = GET_VEHICLE_PED_IS_IN(GET_PLAYER_PED(i), 1);
			if (RequestLoop(veh)) {
				set_vehicle_mod(GET_PLAYER_PED(i), 11, 3);
				set_vehicle_mod(GET_PLAYER_PED(i), 13, 2);
				set_vehicle_mod(GET_PLAYER_PED(i), 12, 2);
				set_vehicle_mod(GET_PLAYER_PED(i), 15, 3);
				set_vehicle_mod(GET_PLAYER_PED(i), 4, 3);
				set_vehicle_mod(GET_PLAYER_PED(i), 16, 4);
				set_vehicle_tyres_can_burst(GET_PLAYER_PED(i));
				set_vehicle_number_plate_text_index(GET_PLAYER_PED(i), 5);
				set_vehicle_window_tint(GET_PLAYER_PED(i), 5);
			}
		}
		else continue;
	}
}
#pragma endregion
#pragma region ObjectOptions
void get_current_object_aimed_at()
{
	Object temp;
	if (_GET_AIMED_ENTITY(PLAYER_ID(), &temp))
	{
		if (IS_ENTITY_AN_OBJECT(temp))
		{
			if (DOES_ENTITY_EXIST(temp))
			{
				objects[current_object_index].id = temp;
				FREEZE_ENTITY_POSITION(temp, true);
				PrintMessage(Format("Selected object: %i", objects[current_object_index].id));
			}
			else
				PrintMessage("Object no longer exists");
		}
		else
			PrintMessage("Entity is not an object");
	}
	else
		PrintMessage("Not aiming at entity\nMake sure you're aiming before selecting!");
}
void move_object_pos(int vec_index, float precision)
{
	if (DOES_ENTITY_EXIST(objects[current_object_index].id))
	{
		if (RequestLoop(objects[current_object_index].id))
		{
			Vector3 temp = GET_ENTITY_COORDS(objects[current_object_index].id, 1);
			switch (vec_index)
			{
			case 0:
				temp.x = temp.x + precision;
				break;
			case 1:
				temp.y = temp.y + precision;
				break;
			case 2:
				temp.z = temp.z + precision;
				break;
			}
			SET_ENTITY_COORDS(objects[current_object_index].id, temp.x, temp.y, temp.z, 1, 0, 0, 1);
		}
	}
}
void move_object_rot(int vec_index, float precision)
{
	if (DOES_ENTITY_EXIST(objects[current_object_index].id))
	{
		if (RequestLoop(objects[current_object_index].id))
		{
			Vector3 r = GET_ENTITY_ROTATION(objects[current_object_index].id, 2);
			switch (vec_index)
			{
			case 0:
				r.x = r.x + precision;
				break;
			case 1:
				r.y = r.y + precision;
				break;
			case 2:
				r.z = r.z + precision;
				break;
			}
			SET_ENTITY_ROTATION(objects[current_object_index].id, r.x, r.y, r.z, 2, 1);
		}
	}
}
void ClearObjectProperties(int index)
{
	objects[index].id = 0;
	objects[index].name = "None";
	objects[index].hash = 0;
}
void SpawnReturnObject(Hash hash)
{
	objSet = hash;
	spawn_object_get_return = true;
}
bool CreateReturnObject()
{
	REQUEST_MODEL(objSet);
	if (HAS_MODEL_LOADED(objSet))
	{
		get_returned_object = CREATE_OBJECT(objSet, 0, 0, 0, 1, 0, 0);
		if (DOES_ENTITY_EXIST(get_returned_object) && GET_ENTITY_MODEL(get_returned_object) == objSet)
		{
			return true;
		}
		return false;
	}
	return false;
}
void SpawnObject(Hash hash, char* name)
{
	ObjName = name;
	objSet = hash;
	spawn_object = true;
}
bool CreateObject()
{
	if (objcount < 30)
	{
		if (IS_MODEL_IN_CDIMAGE(objSet))
		{
			REQUEST_MODEL(objSet);
			if (HAS_MODEL_LOADED(objSet))
			{
				Vector3 c = GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER_PED_ID(), 0, 2, 0);
				Object new_object = CREATE_OBJECT(objSet, c.x, c.y, c.z, 1, 0, 0);
				if (DOES_ENTITY_EXIST(new_object))
				{
					for (int i = 0; i < 30; i++)
					{
						if (objects[i].name != "None")
							continue;
						else
						{
							objects[i].id = new_object;
							objects[i].name = ObjName;
							objects[i].hash = objSet;
							current_object_index = i;
							break;
						}
					}
					objcount++;
					FREEZE_ENTITY_POSITION(new_object, true);
					PrintMessage("Spawned object");
					return true;

				}
				else
					return false;
			}
			else
				return false;
		}
		else
		{
			PrintMessage("Model doesn't exist");
			return true;
		}
	}
	else
	{
		PrintMessage("Maximum limit of spawned objects has been reached\nPlease delete some others first");
		return true;
	}
}
void copy_object()
{
	if (DOES_ENTITY_EXIST(objects[current_object_index].id))
	{
		if (objcount < 30)
		{
			SpawnObject(objects[current_object_index].hash, objects[current_object_index].name);
		}
	}
}
void delete_object()
{
	if (objcount > 0)
	{
		if (RequestLoop(objects[current_object_index].id))
		{
			SET_ENTITY_AS_MISSION_ENTITY(objects[current_object_index].id, 0, 1);
			DELETE_OBJECT(&objects[current_object_index].id);
			ClearObjectProperties(current_object_index);
			objcount--;
			WhichMenu = 52;
			Scroll = current_object_index;
			current_object_index = 0;
			PrintMessage("Deleted object");
		}
	}
	else
		PrintMessage("No objects spawned");
}
void LoopSpawnAndAttach(Hash hash, Bone b_index)
{
	attach_object_hash = hash;
	attach_object_bone = b_index;
	spawn_and_attach_object_loop = true;
}
bool SpawnAndAttachObject()
{
	SpawnReturnObject(attach_object_hash);
	if (DOES_ENTITY_EXIST(get_returned_object) && GET_ENTITY_MODEL(get_returned_object) == attach_object_hash)
	{
		int y = 0;
		int index = GET_PED_BONE_INDEX(GET_PLAYER_PED(SelectedClient), attach_object_bone);
		if (attach_object_hash == 0xE0264F5D)
			y = 90;
		ATTACH_ENTITY_TO_ENTITY(get_returned_object, GET_PLAYER_PED(SelectedClient), index, 0, 0, 0, 0, y, 0, 0, 0, 0, 0, 2, 1);
		PrintMessage(Format("Attached object to %s", players[SelectedClient].name));
		return true;
	}
	return false;
}
Hash wheel_object = -1003748966;
Object wheel_object_id = -1;
void CreateWheelObject()
{
	drive_on_wheel = true;
}

bool SpawnFerrisWheel()
{
	REQUEST_MODEL(wheel_object);
	if (HAS_MODEL_LOADED(wheel_object))
	{
		wheel_object_id = CREATE_OBJECT(wheel_object, 0, 0, 0, 1, 0, 0);
		if (DOES_ENTITY_EXIST(wheel_object_id))
		{
			SET_ENTITY_ROTATION(wheel_object_id, 180, 90, 180, 2, 1);
			SET_ENTITY_VISIBLE(wheel_object_id, false);
			FREEZE_ENTITY_POSITION(wheel_object_id, true);
			return true;
		}
		return false;
	}
	return false;
}
void DriveOnWater()
{
	if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
		Vector3 c = GET_ENTITY_COORDS(_ID, 1);
		if (da)
			c.z = 360;
		else if (dw)
			c.z = -0.9;
		SET_ENTITY_COORDS(wheel_object_id, c.x, c.y, c.z, 1, 0, 0, 1);
		SET_ENTITY_VISIBLE(wheel_object_id, false);
		FREEZE_ENTITY_POSITION(wheel_object_id, true);
	}
}
bool CreateBatmobile()
{
	int buffalo = 0xEDD516C6;
	Vector3 c = GET_ENTITY_COORDS(_ID, 1);
	REQUEST_MODEL(buffalo);
	if (HAS_MODEL_LOADED(buffalo)) {
		Vehicle veh = CREATE_VEHICLE(buffalo, c.x, c.y, c.z, 0, 1, 0);
		if (DOES_ENTITY_EXIST(veh)) {
			SET_PED_INTO_VEHICLE(_ID, veh, -1);
			Vector3 ztypexyz = { -0.3, -0.1270, -0.6 };
			Vector3 ztyperot = { 0, 0, 0 };
			float vehheading = GET_ENTITY_HEADING(veh);
			SET_ENTITY_CAN_BE_DAMAGED(veh, false);
			SET_ENTITY_VISIBLE(veh, false);
			int ztype_car = CREATE_OBJECT(267881419, c.x, c.y, c.z, 1, 0, 0);
			ATTACH_ENTITY_TO_ENTITY(ztype_car, veh, -1, -0.3, -0.1270, -0.5, 0, 0, 0, 0, 0, 0, 0, 2, 1);
			SET_ENTITY_HEADING(ztype_car, vehheading);
			PrintMessage("Spawned the Batmobile");
			SET_MODEL_AS_NO_LONGER_NEEDED(buffalo);
			return true;
		}
	}
	return false;
}
void SpawnBatmobile()
{
	bat_loop = true;
}
void SpawnVehicleGetReturn(Hash hash, Vector3 coords)
{
	veh_hash = hash;
	vehicle_spawn_position = coords;
	spawn_veh_return = true;
}
int CreateVehicleGetReturn(Hash hash, Vector3 coords)
{
	REQUEST_MODEL(hash);
	if (HAS_MODEL_LOADED(hash))
	{
		Vehicle vehicle = CREATE_VEHICLE(hash, coords.x, coords.y, coords.z, 0, 1, 0);
		if (DOES_ENTITY_EXIST(vehicle)) {
			SET_ENTITY_HEADING(vehicle, GET_ENTITY_HEADING(_ID));
			SET_MODEL_AS_NO_LONGER_NEEDED(hash);
			return_vehicle = vehicle;
			return true;
		}
	}

	return false;
}
void SpawnVehicle(Hash hash)
{
	veh_hash = hash;
	spawn_veh = true;
}
bool CreateVehicle(Hash hash)
{
	if (customcar) {
		if (!IS_STRING_NULL_OR_EMPTY(keyboard_result)) {
			hash = GET_HASH_KEY(keyboard_result);
		}
	}
	REQUEST_MODEL(hash);
	if (HAS_MODEL_LOADED(hash))
	{
		Vector3 origin;
		if (spawnforclient)
			origin = GET_ENTITY_COORDS(GET_PLAYER_PED(SelectedClient), 1);
		else
			origin = GET_ENTITY_COORDS(_ID, 1);
		origin.y += 3.0;
		Vehicle vehicle = CREATE_VEHICLE(hash, origin.x, origin.y, origin.z, 0, 1, 0);
		if (DOES_ENTITY_EXIST(vehicle)) {
			if (spawnforclient) {
				SET_ENTITY_HEADING(vehicle, GET_ENTITY_HEADING(GET_PLAYER_PED(SelectedClient)));
				if (spawn_invincible_vehicle)
					SET_ENTITY_INVINCIBLE(vehicle, true);
				if (spawn_suped_up_vehicle)
					SupeVehicle(vehicle);
				SET_MODEL_AS_NO_LONGER_NEEDED(hash);
				PrintMessage(Format("Spawned vehicle for %s", players[SelectedClient].name));
			}
			else
			{
				if (spawn_invincible_vehicle)
					SET_ENTITY_INVINCIBLE(vehicle, true);
				if (spawn_inside_vehicle)
					SET_PED_INTO_VEHICLE(_ID, vehicle, -1);
				if (spawn_suped_up_vehicle)
					SupeVehicle(vehicle);

				SET_ENTITY_HEADING(vehicle, GET_ENTITY_HEADING(_ID));
				SET_MODEL_AS_NO_LONGER_NEEDED(hash);
				PrintMessage("Spawned vehicle");
			}
			return true;
		}
	}
	return false;
}
void SpawnBodyguard(Hash hash, const char* name)
{
	guard_hash = hash;
	guard_name = name;
	guard_loop = true;
}
bool CreateBodyguard(Hash hash, const char* name)
{
	if (count < 6) {
		int temp;
		REQUEST_MODEL(hash);
		if (HAS_MODEL_LOADED(hash))
		{
			Vector3 origin = GET_ENTITY_COORDS(_ID, 1);
			origin.y += 2.0f;
			int guard = CREATE_PED(26, hash, origin.x, origin.y, origin.z, 0, 1, 0);
			if (DOES_ENTITY_EXIST(guard))
			{
				for (int i = 0; i < 6; i++)
				{
					if (peds[i].name != "None")
						continue;
					else {
						peds[i].name = name;
						peds[i].id = guard;
						peds[i].dancing = false;
						peds[i].invincible = false;
						temp = i;
						break;
					}
				}
				SET_PED_AS_GROUP_MEMBER(peds[temp].id, GET_PLAYER_GROUP(PLAYER_ID()));
				SET_PED_NEVER_LEAVES_GROUP(peds[temp].id, true);
				SET_PED_ACCURACY(peds[temp].id, 100);
				GIVE_DELAYED_WEAPON_TO_PED(peds[temp].id, 0x83BF0278, 999, 999);
				SET_CURRENT_PED_WEAPON(peds[temp].id, 0x83BF0278, true);
				SET_PED_CAN_SWITCH_WEAPON(peds[temp].id, true);
				peds[temp].blip = ADD_BLIP_FOR_ENTITY(peds[temp].id);
				SET_BLIP_DISPLAY(peds[temp].blip, 1);
				SET_MODEL_AS_NO_LONGER_NEEDED(hash);
				count++;
				PrintMessage(Format("Spawned bodyguard %s", name));
				return true;
			}
		}
		return false;
	}
	else {
		PrintMessage("Error - maximum guard limit reached");
		return false;
	}
}
void SpawnClientGuard(Hash hash)
{
	client_guard_hash = hash;
	client_guard = true;
}
bool CreateClientGuard(Hash hash)
{
	if (players[SelectedClient].guard_count < 3)
	{
		REQUEST_MODEL(hash);
		if (HAS_MODEL_LOADED(hash))
		{
			Vector3 origin = GET_ENTITY_COORDS(GET_PLAYER_PED(players[SelectedClient].id), 1);
			origin.y += 2.0f;
			int guard = CREATE_PED(26, hash, origin.x, origin.y, origin.z, 0, 1, 0);
			if (DOES_ENTITY_EXIST(guard))
			{
				SET_PED_AS_GROUP_MEMBER(guard, GET_PLAYER_GROUP(players[SelectedClient].id));
				SET_PED_NEVER_LEAVES_GROUP(guard, true);
				SET_PED_ACCURACY(guard, 100);
				GIVE_DELAYED_WEAPON_TO_PED(guard, 0x83BF0278, 999, 999);
				SET_CURRENT_PED_WEAPON(guard, 0x83BF0278, true);
				SET_PED_CAN_SWITCH_WEAPON(guard, true);
				players[SelectedClient].guard_count++;
				PrintMessage(Format("Spawned bodyguard for %s", players[SelectedClient].name));
				return true;
			}
		}
		return false;
	}
	else
	{
		PrintMessage(Format("Error - %s has max number of bodyguards", players[SelectedClient].name));
		client_guard = false;
		return false;
	}
}
int chop, chop2, chop3, chop4, chop5, chop6;
bool CreateChops()
{
	int chop_hash = 0x14EC17EA;
	REQUEST_MODEL(chop_hash);
	if (HAS_MODEL_LOADED(chop_hash))
	{
		Vector3 c = GET_ENTITY_COORDS(GET_PLAYER_PED(SelectedClient), 1);
		chop = CREATE_PED(26, chop_hash, c.x, c.y, c.z, 0, 1, 0);
		chop6 = CREATE_PED(26, chop_hash, c.x, c.y, c.z, 0, 1, 0);
		chop2 = CREATE_PED(26, chop_hash, c.x, c.y, c.z, 0, 1, 0);
		chop3 = CREATE_PED(26, chop_hash, c.x, c.y, c.z, 0, 1, 0);
		chop4 = CREATE_PED(26, chop_hash, c.x, c.y, c.z, 0, 1, 0);
		chop5 = CREATE_PED(26, chop_hash, c.x, c.y, c.z, 0, 1, 0);
		SET_PED_RANDOM_COMPONENT_VARIATION(chop, 0);
		SET_PED_RANDOM_COMPONENT_VARIATION(chop2, 0);
		SET_PED_RANDOM_COMPONENT_VARIATION(chop3, 0);
		SET_PED_RANDOM_COMPONENT_VARIATION(chop4, 0);
		SET_PED_RANDOM_COMPONENT_VARIATION(chop5, 0);
		SET_PED_RANDOM_COMPONENT_VARIATION(chop6, 0);
		TASK_COMBAT_PED(chop, GET_PLAYER_PED(SelectedClient), 0, 16);
		TASK_COMBAT_PED(chop2, GET_PLAYER_PED(SelectedClient), 0, 16);
		TASK_COMBAT_PED(chop3, GET_PLAYER_PED(SelectedClient), 0, 16);
		TASK_COMBAT_PED(chop4, GET_PLAYER_PED(SelectedClient), 0, 16);
		TASK_COMBAT_PED(chop5, GET_PLAYER_PED(SelectedClient), 0, 16);
		TASK_COMBAT_PED(chop6, GET_PLAYER_PED(SelectedClient), 0, 16);
		return true;
	}
	return false;
}
void SpawnChops()
{
	chopattack = true;
}
int swat1, swat2, swat3;
bool CreateSWAT()
{
	int swat_hash = 0x8D8F1B10;
	REQUEST_MODEL(swat_hash);
	if (HAS_MODEL_LOADED(swat_hash))
	{
		Vector3 c = GET_ENTITY_COORDS(GET_PLAYER_PED(SelectedClient), 1);
		swat1 = CREATE_PED(26, swat_hash, c.x, c.y, c.z, 0, 1, 0);
		swat2 = CREATE_PED(26, swat_hash, c.x, c.y, c.z, 0, 1, 0);
		swat3 = CREATE_PED(26, swat_hash, c.x, c.y, c.z, 0, 1, 0);
		GIVE_DELAYED_WEAPON_TO_PED(swat1, 0x83BF0278, 999, 999);
		GIVE_DELAYED_WEAPON_TO_PED(swat2, 0x83BF0278, 999, 999);
		GIVE_DELAYED_WEAPON_TO_PED(swat3, 0x83BF0278, 999, 999);
		SET_CURRENT_PED_WEAPON(swat1, 0x83BF0278, 1);
		SET_CURRENT_PED_WEAPON(swat2, 0x83BF0278, 1);
		SET_CURRENT_PED_WEAPON(swat3, 0x83BF0278, 1);
		SET_PED_ACCURACY(swat1, 100);
		SET_PED_ACCURACY(swat2, 100);
		SET_PED_ACCURACY(swat3, 100);
		TASK_COMBAT_PED(swat1, GET_PLAYER_PED(SelectedClient), 0, 16);
		TASK_COMBAT_PED(swat2, GET_PLAYER_PED(SelectedClient), 0, 16);
		TASK_COMBAT_PED(swat3, GET_PLAYER_PED(SelectedClient), 0, 16);
		return true;
	}
	return false;
}
void SpawnSWAT()
{
	swatplayer = true;
}

void GodMode()
{
	SET_ENTITY_CAN_BE_DAMAGED(_ID, false);
}
bool getresult;
void ReturnKeyboard()
{
	if (getresult)
	{
		char *temp = GET_ONSCREEN_KEYBOARD_RESULT();
		if (!IS_STRING_NULL_OR_EMPTY(temp)) {
			keyboard_result = temp;
			getresult = false;
		}
		getresult = false;
	}
	getresult = false;
}
#pragma endregion
#pragma region Tunables
void SetTunable(int index, int value)
{
	if (TunablesAddress != 0)
	{
		int temp = TunablesAddress;
		temp += (index * 4);
		*(int*)temp = value;
	}
}
int FindTunablesPointer()
{
	return TunablesAddress = (*(int*)TunablesPtr) + 4;
}
#pragma endregion
#pragma region MiscOptions
void Chauffeur()
{
	chauf_loop = true;
}
bool SpawnChauffeur()
{
	int way = GET_FIRST_BLIP_INFO_ID(8);
	if (DOES_BLIP_EXIST(way))
	{
		Vector3 point = GET_BLIP_COORDS(way);
		Vehicle vehhash = 0x8B13F083;
		int pedhash = 1498487404;
		Vector3 coords = GET_ENTITY_COORDS(_ID, 1);
		coords.y += 2;
		REQUEST_MODEL(vehhash);
		REQUEST_MODEL(pedhash);
		if (HAS_MODEL_LOADED(vehhash) && HAS_MODEL_LOADED(pedhash))
		{
			int limo = CREATE_VEHICLE(vehhash, coords.x, coords.y, coords.z, 0, 1, 0);
			if (DOES_ENTITY_EXIST(limo))
			{
				SET_MODEL_AS_NO_LONGER_NEEDED(vehhash);
				int driver = CREATE_PED(26, pedhash, coords.x, coords.y, coords.z, 0, 1, 0);
				if (DOES_ENTITY_EXIST(driver))
				{
					SET_PED_INTO_VEHICLE(driver, limo, -1);
					SET_PED_INTO_VEHICLE(_ID, limo, 2);
					TASK_VEHICLE_DRIVE_TO_COORD(driver, limo, point.x, point.y, point.z, 20.0f, 1, vehhash, 786603, -1, -1);
					SET_MODEL_AS_NO_LONGER_NEEDED(pedhash);
					PrintMessage("Enjoy the ride!");
					return true;
				}
				return false;
			}
			return false;
		}
		return false;
	}
	else
	{
		PrintMessage("Set a waypoint first!");
		chauf_loop = false;
		return false;
	}
}
void FreezeProtection()
{
	int ped;
	Vector3 c = GET_ENTITY_COORDS(_ID, 1);
	if (GET_CLOSEST_PED(c.x, c.y, c.z, 5, 1, 1, &ped, 0, 1, -1))
	{
		if (GET_ENTITY_MODEL(ped) == GET_ENTITY_MODEL(_ID))
		{
			if (GET_PED_DRAWABLE_VARIATION(ped, Shirt) == GET_PED_DRAWABLE_VARIATION(_ID, Shirt) && GET_PED_TEXTURE_VARIATION(ped, Shirt) == GET_PED_TEXTURE_VARIATION(_ID, Shirt))
			{
				if (RequestLoop(ped))
				{
					if (DOES_ENTITY_EXIST(ped)) {
						SET_ENTITY_AS_MISSION_ENTITY(ped, 0, 1);
						DELETE_PED(&ped);
						PrintMessage("Stopped freeze attempt");
					}
				}
			}
		}
	}
}
void RandomVehicle()
{
	int ivar = irand(0, 352);
	int model = GET_HASH_KEY(Vehicles[ivar]);
	veh_hash = model;
	spawn_veh = true;
}
void RamWithBus()
{
	bus_loop = true;
}
bool SpawnBus()
{
	int bus = 0xD577C962;
	Vector3 c, offset = { 0, -10, 0 };
	c = GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(GET_PLAYER_PED(SelectedClient), 0, -10, 0);
	REQUEST_MODEL(bus);
	if (HAS_MODEL_LOADED(bus))
	{
		int rammer = CREATE_VEHICLE(bus, c.x, c.y, c.z, 0, 1, 0);
		SET_ENTITY_HEADING(rammer, GET_ENTITY_HEADING(GET_PLAYER_PED(SelectedClient)));
		SET_VEHICLE_FORWARD_SPEED(rammer, 50);
		PrintMessage("SMASHED!");
		SET_MODEL_AS_NO_LONGER_NEEDED(bus);
		return true;
	}
	return false;
}
void GoodieSpawner(Hash hash)
{
	Vector2 pos = get_random_position_on_circumference(2.0);
	Vector3 c = GET_ENTITY_COORDS(GET_PLAYER_PED(SelectedClient), 1);
	if (hash == PICKUP_AMMO_BULLET_MP)
	{
		Hash ammo = GET_HASH_KEY("prop_box_ammo02a");
		REQUEST_MODEL(ammo);
		if (HAS_MODEL_LOADED(ammo))
			CREATE_AMBIENT_PICKUP(hash, c.x + pos.x, c.y + pos.y, c.z, 0, -1, ammo, 0, 1);
	}
	else
		CREATE_AMBIENT_PICKUP(hash, c.x + pos.x, c.y + pos.y, c.z, 0, 2000, 0, 0, 1);
}
int armour_tick = 0, armour_delay = 1;
void ArmourRegen()
{
	if (game_ticks - armour_tick > armour_delay)
	{
		if (DOES_ENTITY_EXIST(_ID))
		{
			ADD_ARMOUR_TO_PED(_ID, 1);
		}
		armour_tick = game_ticks;
	}

}
int health_tick = 0, health_delay = 1;
void HealthRegen()
{
	if (game_ticks - health_tick > health_delay)
	{
		if (DOES_ENTITY_EXIST(_ID))
		{
			if (GET_ENTITY_MAX_HEALTH(_ID) > GET_ENTITY_HEALTH(_ID))
				SET_ENTITY_HEALTH(_ID, GET_ENTITY_HEALTH(_ID) + 1);
		}
		health_tick = game_ticks;
	}
}
void StealOutfit()
{
	if (GET_ENTITY_MODEL(_ID) != GET_ENTITY_MODEL(GET_PLAYER_PED(SelectedClient)))
		set_player_model(GET_ENTITY_MODEL(GET_PLAYER_PED(SelectedClient)));

	for (int i = 0; i < 12; i++) {
		int e_drawable = GET_PED_DRAWABLE_VARIATION(GET_PLAYER_PED(SelectedClient), i);
		int e_texture = GET_PED_TEXTURE_VARIATION(GET_PLAYER_PED(SelectedClient), e_drawable);
		SET_PED_COMPONENT_VARIATION(_ID, i, e_drawable, e_texture, 0);
	}
	PrintMessage(Format("Copied %s's outfit", players[SelectedClient].name));
}
void DrawKeyboard(int length)
{
	DISPLAY_ONSCREEN_KEYBOARD(0, "FMMC_KEY_TIP8", "", "", "", "", "", length + 1);
	_keyboard = true;
}
void ShowKeyboard()
{
	switch (UPDATE_ONSCREEN_KEYBOARD())
	{
	case 1:
		_keyboard = false;
		keyboard_result = GET_ONSCREEN_KEYBOARD_RESULT();
		switch (keyboard_action)
		{
		case 1:
			SpawnVehicle(GET_HASH_KEY(keyboard_result));
			break;
		case 2:
			ChangePlate(keyboard_result);
			break;
		case 3:
			changed_name = keyboard_result;
			ChangeName(keyboard_result);
			break;
		case 4:
			break;
		case 5:
			int cash = _Atoi(keyboard_result);
			NETWORK_EARN_FROM_ROCKSTAR(cash);
			PrintMessage(Format("Added ~y~%i~w~ cash to account", cash));
			break;
		case 6:
			int level = _Atoi(keyboard_result);
			if (level > 8000 || level < 1)
				PrintMessage("Value not within bounds");
			else {
				STAT_SET_INT(GET_HASH_KEY("MP0_CHAR_XP_FM"), Levels[level - 1], 0);
				STAT_SET_INT(GET_HASH_KEY("MP1_CHAR_XP_FM"), Levels[level - 1], 0);
				PrintMessage(Format("Set level %i", level));
			}
			break;
		case 7:
			if (objcount < 30)
				SpawnObject(GET_HASH_KEY(keyboard_result), keyboard_result);
			else
				PrintMessage("Maximum objects value reached");
			break;
		case 8:
			kdr_kills = _Atoi(keyboard_result);
			break;
		case 9:
			kdr_deaths = _Atoi(keyboard_result);
			break;
		case 10:
			cur_win_item = _Atoi(keyboard_result);
			break;
		case 11:
			cur_loss_item = _Atoi(keyboard_result);
			break;
		case 12:
			SendText(keyboard_result, SelectedClient);
			PrintMessage(Format2("Sent `%s` to %s", keyboard_result, players[SelectedClient].name));
			break;
		case 13:
			SendTextToAll(keyboard_result);
			PrintMessage(Format("Sent '%s' to all players", keyboard_result));
			break;
		}
		break;
	case 2:
		_keyboard = false;
		break;
	case 3:
		_keyboard = false;
		break;
	}
}
#pragma endregion
#pragma region Ped Manager

void monitor_manager()
{
	int ent;
	if (_GET_AIMED_ENTITY(PLAYER_ID(), &ent))
	{
		if (IS_ENTITY_A_PED(ent))
		{
			PrintMessage(Format("Ped found: %i\nPress LEFT to modify", ent), 1);
			if (get_left_key_just_pressed(0xCC, 150))
			{
				pm_ent = ent;
				Open = true;
				WhichMenu = 119;
				Scroll = 0;
			}
		}
	}
}
void pm_to_me()
{
	if (DOES_ENTITY_EXIST(pm_ent))
	{
		if (!IS_ENTITY_DEAD(pm_ent))
		{
			if (IS_PED_IN_ANY_VEHICLE(_ID, 1))
			{
				Vehicle veh = GET_VEHICLE_PED_IS_IN(_ID, 1);
				int seat = FindSeat(veh);
				if (seat != -2)
				{
					SET_PED_INTO_VEHICLE(pm_ent, veh, seat);
					PrintMessage("Set ped in vehicle");
				}
				else {
					Vector3 c = GET_ENTITY_COORDS(veh, 1);
					c.x -= 2;
					SET_ENTITY_COORDS(pm_ent, c.x, c.y, c.z, 1, 0, 0, 1);
					PrintMessage("Vehicle is full\nPed spawned next to vehicle");
				}
			}
			else {
				Vector3 c = GET_ENTITY_COORDS(_ID, 1);
				c.z -= 2;
				SET_ENTITY_COORDS(pm_ent, c.x, c.y, c.z, 1, 0, 0, 1);
				PrintMessage("Teleported ped to you");
			}
		}
		else PrintMessage("Ped is dead. Select 'Revive' option to bring them back!", 3500);
	}
	else PrintMessage("Ped doesn't exist");
}
void pm_set_as_guard()
{
	if (DOES_ENTITY_EXIST(pm_ent))
	{
		if (!IS_ENTITY_DEAD(pm_ent))
		{
			if (!IS_PED_GROUP_MEMBER(pm_ent, GET_PLAYER_GROUP(PLAYER_ID())))
			{
				if (count < 6)
				{
					int temp;
					for (int i = 0; i < 6; i++)
					{
						if (peds[i].name != "None")
							continue;
						else {
							peds[i].name = "Selected Ped";
							peds[i].id = pm_ent;
							peds[i].dancing = false;
							peds[i].invincible = false;
							temp = i;
							break;
						}
					}
					SET_PED_AS_GROUP_MEMBER(peds[temp].id, GET_PLAYER_GROUP(PLAYER_ID()));
					SET_PED_NEVER_LEAVES_GROUP(peds[temp].id, true);
					SET_PED_ACCURACY(peds[temp].id, 100);
					GIVE_DELAYED_WEAPON_TO_PED(peds[temp].id, 0x83BF0278, 999, 999);
					SET_CURRENT_PED_WEAPON(peds[temp].id, 0x83BF0278, true);
					SET_PED_CAN_SWITCH_WEAPON(peds[temp].id, true);
					peds[temp].blip = ADD_BLIP_FOR_ENTITY(peds[temp].id);
					SET_BLIP_DISPLAY(peds[temp].blip, 2);
					count++;
					PrintMessage("Set ped as a guard");
				}
				else PrintMessage("Too many guards in group");
			}
			else PrintMessage("Guard is already in group");
		}
		else PrintMessage("Ped is dead. Select 'Revive' option to bring them back!", 3500);
	}
	else PrintMessage("Ped doesn't exist");
}
void pm_waypoint_loop()
{
	pm_waypoint_toggle = true;
}
bool pm_drive_to_waypoint()
{
	if (DOES_ENTITY_EXIST(pm_ent))
	{
		if (!IS_ENTITY_DEAD(pm_ent))
		{
			int way = GET_FIRST_BLIP_INFO_ID(8);
			if (DOES_BLIP_EXIST(way))
			{
				Vector3 point = GET_BLIP_COORDS(way);
				Hash limo = 0x8B13F083;
				Vector3 coords = GET_ENTITY_COORDS(_ID, 1);
				SpawnVehicleGetReturn(limo, coords);
				Vehicle veh = return_vehicle;
				if (veh != -1)
				{
					SET_PED_INTO_VEHICLE(pm_ent, veh, -1);
					SET_PED_INTO_VEHICLE(_ID, veh, 2);
					TASK_VEHICLE_DRIVE_TO_COORD(pm_ent, veh, point.x, point.y, point.z, 20.0f, 1, limo, 786603, -1, -1);
					PrintMessage("LEGGO!");
					return true;
				}
				return false;
			}
			else
			{
				PrintMessage("Set a waypoint first!");
				return true;
			}
		}
		else
		{
			PrintMessage("Ped's dead, baby. Select 'Revive' option to bring them back!", 3500);
			return true;
		}
	}
	else {
		PrintMessage("Ped doesn't exist");
		return true;
	}
}
bool has_switched = false;
int last_player;
void pm_switch_to_entity()
{
	if (DOES_ENTITY_EXIST(pm_ent))
	{
		if (!IS_ENTITY_DEAD(pm_ent))
		{
			last_player = PLAYER_PED_ID();
			CHANGE_PLAYER_PED(GET_PLAYER_INDEX(), pm_ent, true, true);
			has_switched = true;
			PrintMessage("Switched soul! Use R3 + DPAD Right to switch back!", 3500);
		}
		else
			PrintMessage("Ped is dead. Select 'Revive' option to bring them back!", 3500);
	}
}

void pm_ss_monitor()
{
	if (IS_CONTROL_JUST_PRESSED(2, 0xcd) && IS_CONTROL_JUST_PRESSED(2, 0xc9) || IS_DISABLED_CONTROL_JUST_PRESSED(2, 0xcd) && IS_DISABLED_CONTROL_JUST_PRESSED(2, 0xc9))
	{
		CHANGE_PLAYER_PED(GET_PLAYER_INDEX(), last_player, true, true);
		has_switched = false;
		PrintMessage("Switched back to regular player");
	}
}
#pragma endregion
float GetHeadingFromCoords(float SourceX, float SourceY, float SourceZ, float TargetX, float TargetY, float TargetZ)
{
	return ATAN2((TargetY - SourceY), (TargetX - SourceX));
}
int scene = -1;
void jb700_eject()
{
	Vehicle veh = GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 1);
	REQUEST_AMBIENT_AUDIO_BANK("CAR_STEAL_3_SCREAM", 0);
	REQUEST_AMBIENT_AUDIO_BANK("CAR_THEFT_MOVIE_LOT", 0);
	REQUEST_ANIM_DICT("misscarsteal4@actress");
	if (IS_CONTROL_JUST_PRESSED(2, 0xCD) && GET_ENTITY_MODEL(GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 1)) == GET_HASH_KEY("jb700"))
	{
		if (!IS_ENTITY_UPSIDEDOWN(veh) && !IS_SYNCHRONIZED_SCENE_RUNNING(scene))
		{
			scene = CREATE_SYNCHRONIZED_SCENE(0, 0, 0, 0, 0, 0, 2);
			SET_SYNCHRONIZED_SCENE_LOOPED(scene, 0);
			_0x2DE48DA1(scene, 0);
			ATTACH_SYNCHRONIZED_SCENE_TO_ENTITY(scene, veh, _0xE4ECAC22(veh, "seat_pside_f"));
			SET_ENTITY_NO_COLLISION_ENTITY(PLAYER_PED_ID(), veh, 1);
			TASK_SYNCHRONIZED_SCENE(PLAYER_PED_ID(), scene, "misscarsteal4@actress", "eject_girl", 1000, -1000, 129, 512, 1148846080, 0);
			SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(PLAYER_PED_ID(), 1);
			TASK_LOOK_AT_ENTITY(PLAYER_PED_ID(), PLAYER_PED_ID(), 2000, 2048, 3);
			START_AUDIO_SCENE("CAR_3_ACTIVATE_EJECTOR_SEAT");
			SET_AUDIO_FLAG("AllowScriptedSpeechInSlowMo", 1);
			SET_AUDIO_FLAG("DisableAbortConversationForRagdoll", 1);
			SET_AUDIO_FLAG("DisableAbortConversationForDeathAndInjury", 1);
			PLAY_SOUND_FROM_ENTITY(-1, "CAR_THEFT_MOVIE_LOT_EJECT_SEAT", veh, 0, 0, 0);
		}
	}
}
int spike_drop_tick = -1, spike_press_tick = 0, spike_delay = 500;
void jb700_spikes()
{
	Vehicle veh = GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 1);
	Vector3 offset;
	int spike_count = 0;
	if (IS_CONTROL_JUST_PRESSED(2, 0xCB) && GET_GAME_TIMER() - spike_press_tick > spike_delay)
	{
		while (spike_count < 2)
		{
			if (DOES_ENTITY_EXIST(spikes[spike_count]))
			{
				SET_ENTITY_AS_MISSION_ENTITY(spikes[spike_count], 0, 1);
				DELETE_OBJECT(&spikes[spike_count]);
			}
			spike_count++;
		}
		spike_drop_tick = GET_GAME_TIMER();
	}
	if (spike_drop_tick != 0)
	{
		if (GET_GAME_TIMER() - spike_drop_tick > 100)
		{
			if (!DOES_ENTITY_EXIST(spikes[0])) {
				offset = GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, 0, -1.2f, -0.4f);
				spikes[0] = CREATE_OBJECT(GET_HASH_KEY("prop_tyre_spike_01"), offset.x, offset.y, offset.z, 1, 0, 0);
				SET_ENTITY_NO_COLLISION_ENTITY(spikes[0], veh, 1);
				PLAY_SOUND_FROM_ENTITY(-1, "CAR_THEFT_MOVIE_LOT_DROP_SPIKES", veh, 0, 0, 0);
			}
		}
		if (GET_GAME_TIMER() - spike_drop_tick > 200)
		{
			if (!DOES_ENTITY_EXIST(spikes[1])) {
				offset = GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, 0.1f, -1.1f, -0.4f);
				spikes[1] = CREATE_OBJECT(GET_HASH_KEY("prop_tyre_spike_01"), offset.x, offset.y, offset.z, 1, 0, 0);
				SET_ENTITY_NO_COLLISION_ENTITY(spikes[1], veh, 1);
			}
		}
		if (GET_GAME_TIMER() - spike_drop_tick > 300)
		{
			if (!DOES_ENTITY_EXIST(spikes[2])) {
				offset = GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -0.1f, -1, -0.34f);
				spikes[2] = CREATE_OBJECT(GET_HASH_KEY("prop_tyre_spike_01"), offset.x, offset.y, offset.z, 1, 0, 0);
				SET_ENTITY_NO_COLLISION_ENTITY(spikes[2], veh, 1);
			}
			spike_drop_tick = 0;
		}
	}
	spike_count = 0;
	while (spike_count < 2)
	{
		if (DOES_ENTITY_EXIST(spikes[spike_count]))
		{
			if (!DOES_ENTITY_HAVE_PHYSICS(spikes[spike_count]))
			{
				ACTIVATE_PHYSICS(spikes[spike_count]);
				SET_ENTITY_DYNAMIC(spikes[spike_count], 1);
			}
		}
		spike_count++;
	}

}
void jb700_spikes_listener()
{
	for (int i = 0; i < 2; i++)
	{
		if (DOES_ENTITY_EXIST(spikes[i]))
		{
			Vector3 spike_coords = GET_ENTITY_COORDS(spikes[i], 1);
			Vehicle veh = GET_CLOSEST_VEHICLE(spike_coords.x, spike_coords.y, spike_coords.z, 20, 0, 100359);
			if (DOES_ENTITY_EXIST(veh) && !IS_VEHICLE_TYRE_BURST(veh, 0, 0))
			{
				SET_VEHICLE_TYRE_BURST(veh, 0, 1, 1000);
				SET_VEHICLE_TYRE_BURST(veh, 1, 1, 1000);
				PLAY_SOUND_FROM_ENTITY(-1, "CAR_STEAL_3_AGENT_TYRE_BURST", veh, "CAR_STEAL_3_AGENT", 0, 0);

			}
		}
	}
}
void jb700_shoot()
{
	Vehicle veh = GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 1);
	DISABLE_CONTROL_ACTION(0, 64);
	if (IS_CONTROL_PRESSED(2, 0xc8) || IS_CONTROL_JUST_PRESSED(2, 0xc8))
	{
		Vehicle veh = GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 0);
		int distance = 250;
		Hash hash = GET_HASH_KEY("WEAPON_ASSAULTRIFLE");
		float speed = 1500.0f;
		Vector3 coords1 = { 0.6f, 0.6707f, 0.3711f };
		Vector3 getcoords1 = GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, coords1.x, coords1.y, coords1.z);
		Vector3 coords2 = { -0.6f, 0.6707f, 0.3711f };
		Vector3 getcoords2 = GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, coords2.x, coords2.y, coords2.z);
		Vector3 coords3 = { 0.6f, 5.0707f, 0.3711f };
		Vector3 getcoords3 = GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, coords3.x, coords3.y, coords3.z);
		Vector3 coords4 = { -0.6f, 5.0707f, 0.3711f };
		Vector3 getcoords4 = GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, coords4.x, coords4.y, coords4.z);
		Vector3 final1 = { getcoords1.x, getcoords1.y, getcoords1.z };
		Vector3 final2 = { getcoords2.x, getcoords2.y, getcoords2.z };
		Vector3 final3 = { getcoords3.x, getcoords3.y, getcoords3.z };
		Vector3 final4 = { getcoords4.x, getcoords4.y, getcoords4.z };
		SHOOT_SINGLE_BULLET_BETWEEN_COORDS(final1.x, final1.y, final1.z, final3.x, final3.y, final3.z, distance, 0, hash, PLAYER_PED_ID(), 1, 1, speed);
		SHOOT_SINGLE_BULLET_BETWEEN_COORDS(final2.x, final2.y, final2.z, final4.x, final4.y, final4.z, distance, 0, hash, PLAYER_PED_ID(), 1, 1, speed);
		PLAY_SOUND_FROM_ENTITY(-1, "JB700_GUN_PLAYER_MASTER", veh, 0, 0, 0);
	}
}

int name_change_tick = 0, name_change_delay = 500;

size_t len = sizeof(colors) / sizeof(char);
void name_color_cycle()
{
	if (GET_GAME_TIMER() - name_change_tick > name_change_delay)
	{
		char buf[32];
		int rng = irand(0, len);
		strcpy(buf, colors[rng]);
		strcat(buf, GET_PLAYER_NAME(PLAYER_ID()));
		ChangeName(buf);
		name_change_tick = GET_GAME_TIMER();
	}
}
void change_name_color(char* color)
{
	char buf[100];
	strncpy(buf, color, strlen(color));
	strncat(buf, changed_name, strlen(changed_name));
	ChangeName(buf);
}
void developer_mode()
{
	char on[] = { 0x38, 0x80, 0x00, 0x01 };
	char off[] = { 0x38, 0x80, 0x00, 0x00 };
	dev_toggle = !dev_toggle;
	sys_dbg_write_process_memory(dev_mode, dev_toggle ? on : off, 4);
	PrintMessage(dev_toggle ? "Dev mode enabled" : "Dev mode disabled");
}
void suicide()
{
	CLEAR_ENTITY_LAST_DAMAGE_ENTITY(PLAYER_PED_ID());
	SET_ENTITY_HEALTH(PLAYER_PED_ID(), 0);
	PrintMessage("RIP in peace");
}
void set_movement(const char* type)
{
	clipset_name = type;
	request_clipset = true;
}
bool load_clipset()
{
	REQUEST_CLIP_SET(clipset_name);
	if (!HAS_CLIP_SET_LOADED(clipset_name))
		return false;

	SET_PED_MOVEMENT_CLIPSET(PLAYER_PED_ID(), clipset_name, 1048576000);
	return true;
}
void pm_kill()
{
	if (!IS_ENTITY_DEAD(pm_ent))
	{
		CLEAR_ENTITY_LAST_DAMAGE_ENTITY(pm_ent);
		SET_PED_TO_RAGDOLL(pm_ent, 0, 250, 0, 0, 0, 0);
		SET_ENTITY_HEALTH(pm_ent, 0);
		PrintMessage("Killed ped");
	}
	else
		PrintMessage("Ped is already dead");
}
void pm_revive()
{
	if (IS_ENTITY_DEAD(pm_ent))
	{
		RESURRECT_PED(pm_ent);
		REVIVE_INJURED_PED(pm_ent);
		SET_ENTITY_HEALTH(pm_ent, 100);
		CLEAR_PED_TASKS_IMMEDIATELY(pm_ent);
		PrintMessage("Revived ped");
	}
	else
		PrintMessage("Ped is still alive");
}

void monitor_guards()
{
	if (count > 0)
	{
		for (int i = 0; i < count; i++)
		{
			if (DOES_ENTITY_EXIST(peds[i].id))
			{
				if (IS_ENTITY_DEAD(peds[i].id))
				{
					PrintMessage(Format("%s died. Automatically cleared guard slot.", peds[i].name));
					ClearPedProperties(i);
					count--;
				}
			}
		}
	}
}

void shoot_money()
{
	if (IS_PED_SHOOTING(_ID))
	{
		Vector3 bullet;
		if (GET_PED_LAST_WEAPON_IMPACT_COORD(_ID, &bullet))
		{
			Object prop = 0x113fd533;
			REQUEST_MODEL(prop);
			if (!HAS_MODEL_LOADED(prop))
				REQUEST_MODEL(prop);
			CREATE_AMBIENT_PICKUP(0xCE6FDD6B, bullet.x, bullet.y, bullet.z, 0, 40000, prop, 0, 1);
		}
	}
}
bool is_logo_on = false;
void rockstar_logo()
{
	if (!is_logo_on)
	{
		char buf[100];
		strcpy(buf, "∑");
		strcat(buf, GET_PLAYER_NAME(PLAYER_ID()));
		strcat(buf, "\0");
		ChangeName(buf);
		is_logo_on = true;
	}
	else
	{
		char buf[100];
		strcpy(buf, GET_PLAYER_NAME(PLAYER_ID()));
		strcat(buf, "\0");
		ChangeName(buf);
		is_logo_on = false;
	}
}
void explosive_bullets_clients_listener()
{
	for (int i = 0; i < 16; i++)
	{
		if (players[i].explosive_bullets)
		{
			if (IS_PED_SHOOTING(GET_PLAYER_PED(players[i].id)))
			{
				Vector3 bullet;
				if (GET_PED_LAST_WEAPON_IMPACT_COORD(GET_PLAYER_PED(players[i].id), &bullet))
				{
					ADD_EXPLOSION(bullet.x, bullet.y, bullet.z, BLIMP, 7.0f, true, false, 0);
				}
			}
		}
	}
}
Entity grav_entity;
bool grav_toggled = false, grav_target_locked = false;
int last_shoot_time = 0;
void set_gravity_gun()
{
	Ped tempPed;

	tempPed = PLAYER_ID();
	if (last_shoot_time < GET_GAME_TIMER() - 500)
	{
		if (!grav_target_locked) _GET_AIMED_ENTITY(tempPed, &grav_entity);


		if ((IS_PLAYER_FREE_AIMING(tempPed) || IS_PLAYER_TARGETTING_ANYTHING(tempPed)) && DOES_ENTITY_EXIST(grav_entity))
		{
			if (!grav_target_locked) _GET_AIMED_ENTITY(PLAYER_ID(), &grav_entity); grav_target_locked = true;

			Vector3 coords = get_coords_from_cam(7);
			if (RequestLoop(grav_entity))
			{
				FREEZE_ENTITY_POSITION(grav_entity, true);
				SET_ENTITY_COORDS_NO_OFFSET(grav_entity, coords.x, coords.y, coords.z, 0, 0, 0);
				if (IS_ENTITY_A_VEHICLE(grav_entity))
					SET_ENTITY_HEADING(grav_entity, GET_ENTITY_HEADING(PLAYER_PED_ID()) + 90.0f);
			}

			if (IS_PED_SHOOTING(PLAYER_PED_ID()))
			{
				PLAY_SOUND_FROM_ENTITY(-1, "Foot_Swish", grav_entity, "docks_heist_finale_2a_sounds", 0, 0);
				SET_ENTITY_HEADING(grav_entity, GET_ENTITY_HEADING(PLAYER_PED_ID()));
				FREEZE_ENTITY_POSITION(grav_entity, false);
				APPLY_FORCE_TO_ENTITY(grav_entity, 1, 0.0f, 350.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0, 1, 1, 1, 0, 1);
				grav_target_locked = false;
				grav_entity = -1;
				last_shoot_time = GET_GAME_TIMER();
			}
		}
		if (!IS_PLAYER_FREE_AIMING_AT_ENTITY(tempPed, grav_entity) || !IS_PLAYER_TARGETTING_ENTITY(tempPed, grav_entity))
		{
			grav_target_locked = false;
			grav_entity = -1;
		}

	}
}


#pragma endregion