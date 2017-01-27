struct opd_s
{
	int32_t sub;
	int32_t toc;
};

typedef struct RGBA
{
	float R, G, B, A;
};
typedef struct _peds {
	const char *name;
	int id;
	bool dancing;
	bool invincible;
	int blip;
};
typedef struct Objects {
	char *name;
	Object id;
	Hash hash;
};
typedef struct Players {
	char *name;
	int id;
	bool dropcash;
	bool troll;
	bool esp;
	int guard_count;
	bool explosive_bullets;
	bool freeze_in_place;
	bool honk_boost;
};
typedef struct MaxMods
{
	Mod maxarmour;
	Mod	maxbrakes;
	Mod	maxbodywork;
	Mod	maxfbumper;
	Mod	maxrbumper;
	Mod	maxengine;
	Mod	maxexhaust;
	Mod	maxfender;
	Mod	maxgrille;
	Mod	maxhood;
	Mod	maxroof;
	Mod	maxskirts;
	Mod	maxspoiler;
	Mod	maxsuspension;
	Mod	maxtransmission;
};
typedef struct VehicleMods
{
	Mod armour;
	Mod	brakes;
	Mod	bodywork;
	Mod	fbumper;
	Mod	rbumper;
	Mod	engine;
	Mod	exhaust;
	Mod	fender;
	Mod	grille;
	Mod	hood;
	Mod	roof;
	Mod	skirts;
	Mod	spoiler;
	Mod	suspension;
	Mod	transmission;
	Mod plates;
	Mod tint;
	bool xenons;
	bool bulletproof;
	bool turbo;
};