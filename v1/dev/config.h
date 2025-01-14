// NES MK1 v0.wat? - Babushka Custom
// Copyleft Mojon Twins 2013, 2015, 2016

// ============================================================================
// I. General configuration
// ============================================================================

// In this section we define map dimmensions, initial and authomatic ending conditions, etc.

#define MAP_W 					4		//
#define MAP_H					6		// Dimensiones del mapa, en pantallas.
#ifdef DEBUG
#define SCR_INI DEBUG_SCR_INI
#define PLAYER_INI_X DEBUG_INI_X
#define PLAYER_INI_Y DEBUG_INI_Y
#else
#define SCR_INI					20		// Pantalla de inicio
#define PLAYER_INI_X			2		//
#define PLAYER_INI_Y			4		// Coordenadas de inicio del jugador, a nivel de tiles
#endif
#define SCR_END					20		// Pantalla del final. 99 si da igual.
#define PLAYER_END_X			0		//
#define PLAYER_END_Y			8		// Posici�n del jugador para terminar, a nivel de tiles
#define PLAYER_MAX_OBJECTS		0		// N�mero de objetos para terminar el juego
#define PLAYER_LIFE				5		// Vida m�xima (con la que empieza, adem�s)
#define PLAYER_REFILL			1		// Recarga de vida.

// Some flexibility
#define HOTSPOTS_WONT_CHANGE			// Neither coordinates or types of hotspots will change
//#define HOTSPOT_TYPE_OBJECTS	1
#define HOTSPOT_TYPE_KEYS		1
#define HOTSPOT_TYPE_REFILL		2
//#define HOTSPOT_TYPE_AMO		4
//#define HOTSPOT_TYPE_RESONATOR	3
//#define HOTSPOT_TYPE_STAR		5

// ============================================================================
// II. Engine type
// ============================================================================

// This section is used to define the game engine behaviour. Many directives are related,
// and others are mutually exclusive. I think this will be pretty obvious when you look at them. 

// Right now the shooting engine is only compatible with the side-view engine.

// Bounding box size
// -----------------
                                        // Comment both for normal 16x16 bounding box
#define BOUNDING_BOX_8_BOTTOM           // 8x8 aligned to bottom center in 16x16
#define SMALL_COLLISION               	// 8x8 centered collision instead of 12x12

// General directives:
// -------------------

//#define PLAYER_PUSH_BOXES 			// If defined, tile #14 is pushable
//#define FIRE_TO_PUSH
//#define DEACTIVATE_KEYS				// If defined, keys are not present.
#define DEACTIVATE_OBJECTS				// If defined, objects are not present.
#define FULL_BOUNCE						// If defined, evil tile bounces equal MAX_VX, otherwise v/2
//#define DOUBLE_BOUNCE
#define DIE_AND_RESPAWN					// If defined, dying = respawn on latest safe.
#define PLAYER_FLICKERS 			 	// If defined, collisions make player flicker instead.
//#define WALLS_STOP_ENEMIES			// If defined, enemies react to the scenary

//#define ENABLE_PURSUERS				// If defined, type 7 enemies are active
//#define DEATH_COUNT_EXPRESSION	50+(rand8()&63)
//#define TYPE_7_FIXED_SPRITE 	4		// If defined, type 7 enemies are always #

#define ENABLE_FANTY
#define FANTY_BASE_SPRID		24
#define FANTY_A 				4
#define FANTY_MAXV 				64
//#define FANTY_COLLIDES

//#define ENABLE_SAW
#define SAW_BASE_SPRID			20
#define SAW_V_DISPL				4
#define SAW_EMERGING_STEPS		10 		

#define PERSISTENT_ENEMIES
#define PERSISTENT_DEATHS
#define ENABLE_CONVEYORS

#define ENABLE_MONOCOCO
#define BASE_TIME_HIDDEN		150
#define BASE_TIME_APPEARING		50
#define BASE_TIME_ONBOARD		50
#define FIRE_COCO_AT			BASE_TIME_ONBOARD/2

#define ENABLE_COCOS
#define COCOS_MAX				3
#define COCO_V					192
#define COCO_PATTERN			34
#define COCO_FAIR_D				32

//#define ENABLE_PROPELLERS
#define PROPELLER_AY			16	
#define PROPELLER_VY_MAX		256
#define PROPELLER_TILE			32

#define ENABLE_FABOLEES
#define FABOLEES_MAX 			3
#define FABOLEES_AX 			4
#define FABOLEES_AY 			2
#define FABOLEES_VY_MAX 		128
#define FABOLEES_VX_INI			192 

#define ENABLE_QUICKSANDS
#define QUICKSANDS_SINK_VY		16

#define ENABLE_ICE
#define ICE_AX					2
#define ICE_RX					2

// Shooting behaviour
// ------------------
/*
#define PLAYER_CAN_FIRE 				// If defined, shooting engine is enabled.
#define PLAYER_BULLET_SPEED 	4		// Pixels/frame. 
#define MAX_BULLETS 			4		// Max number of bullets on screen. Be careful!.
#define PLAYER_BULLET_Y_OFFSET	6		// vertical offset from the player's top.
#define PLAYER_BULLET_X_OFFSET	0		// vertical offset from the player's left/right.
#define ENEMIES_LIFE_GAUGE		2		// Amount of shots needed to kill enemies.
#define RESPAWN_ON_ENTER				// Enemies respawn when entering screen
#define FIRE_MIN_KILLABLE 		3		// If defined, only enemies >= N can be killed.
#define MAX_AMMO				99		// If defined, ammo is not infinite!
#define AMMO_REFILL				50		// type 3 hotspots refill amo, using tile 20
//#define INITIAL_AMMO 		0			// If defined, ammo = X when entering game.

#define BREAKABLE_WALLS					// Breakable walls
#define BREAKABLE_WALLS_LIFE	2		// Amount of hits to break wall
#define BREAKABLE_ANIM					// Show explosion when breaking
#define MAX_BREAKABLE_FRAMES	8		// Frames to show explosion
*/

// Scripting
// ---------
//#define ACTIVATE_SCRIPTING			// Activates msc scripting and flag related stuff.
//#define FIRE_ON_KILL				// run fire script on enemy kill
/*
//#define ENABLE_EXTERN_CODE		// Enables custom code to be run from the script using EXTERN n
#define ENABLE_FIRE_ZONE			// Allows to define a zone which auto-triggers "FIRE"
*/
// Top view:
// ---------
/*
#define PLAYER_MOGGY_STYLE            // Enable top view.
#define TOP_OVER_SIDE                 // UP/DOWN has priority over LEFT/RIGHT
*/
// Side view:
// ----------

#define PLAYER_HAS_JUMP               	// If defined, player is able to jump.
//#define PLAYER_HAS_JETPAC             // If defined, player can thrust a vertical jetpac
#define PLAYER_KILLS_ENEMIES          	// If defined, stepping on enemies kills them
//#define PLAYER_MIN_KILLABLE     3     // Only kill enemies with id >= PLAYER_MIN_KILLABLE

// ============================================================================
// III. Screen configuration
// ============================================================================

// This sections defines how stuff is rendered, where to show counters, etcetera

#define LIFE_X					29		//
#define LIFE_Y					28		// Life gauge counter character coordinates
#define OBJECTS_X				5		//
#define OBJECTS_Y				28		// Objects counter character coordinates
#define KEYS_X					17		//
#define KEYS_Y					28		// Keys counter character coordinates
#define KILLED_X				23		//
#define KILLED_Y				28		// Kills counter character coordinates
#define AMMO_X					8		// 
#define AMMO_Y					29		// Ammo counter character coordinates
#define PLAYER_SHOW_KILLS

// Text
#define LINE_OF_TEXT			26		// If defined, scripts can show text @ Y = #
#define LINE_OF_TEXT_X			1		// X coordinate.
#define LINE_OF_TEXT_ATTR		71		// Attribute

// ============================================================================
// IV. Player movement configuration
// ============================================================================

// This section is used to define which constants are used in the gravity/acceleration engine.
// If a side-view engine is configured, we have to define vertical and horizontal constants
// separately. If a top-view engine is configured instead, the horizontal values are also
// applied to the vertical component, vertical values are ignored.

// IV.1. Vertical movement. Only for side-view.

#define PLAYER_VY_FALLING_MAX	256		// Velocidad m�xima cuando cae (512/64 = 8 p�xels/frame)
#define PLAYER_G				16		// Aceleraci�n de la gravedad (32/64 = 0.5 p�xeles/frame^2)

#define PLAYER_VY_JUMP_INITIAL	64
#define PLAYER_VY_JUMP_MAX		256		// Velocidad m�xima al saltar (320/64 = 5 p�xels/frame)
#define PLAYER_AY_JUMP 			16		// Aceleraci�n al pulsar "salto" (48/64 = 0.75 p�xeles/frame^2)

#define PLAYER_AY_JETPAC		32		// Incremento al usar el jetpac
#define PLAYER_VY_JETPAC_MAX	256		// M�xima velocidad vertical con jetpac

// IV.2. Horizontal (side view) or general (top view) movement.

#define PLAYER_VX_MAX			128		// Velocidad m�xima horizontal (192/64 = 3 p�xels/frame)
#define PLAYER_VX_SPRINT_MAX	192
#define PLAYER_AX				8		// Aceleraci�n horizontal (24/64 = 0,375 p�xels/frame^2)
#define PLAYER_AX_SPRINT		12
#define PLAYER_RX				8		// Fricci�n horizontal (32/64 = 0,5 p�xels/frame^2)

#define PLAYER_VX_MIN (PLAYER_AX << 2)

// ============================================================================
// V. Tile behaviour
// ============================================================================

// Defines the behaviour for each tile. Remember that if keys are activated, tile #15 is a bolt
// and, therefore, it should be made a full obstacle!

// 0 = Walkable (no action)
// 1 = Walkable and kills.
// 2 = Quicksands (#ifdef ENABLE_QUICKSANDS)
// 4 = Platform (only stops player if falling on it)
// 8 = Full obstacle (blocks player from all directions)
// 10 = special obstacle (pushing blocks OR locks!)
// 16 = Breakable (#ifdef BREAKABLE_WALLS)
// 32 = Slipper (+0 = left, +1 = right)
// 64 = Ice (#ifdef ENABLE_ICE)
// You can add the numbers to get combined behaviours
// Save for 10 (special), but that's obvious, innit?

#ifndef COMPRESSED_LEVELS
unsigned char tbehs [] = {
	0, 0, 0, 0, 8, 8, 8, 8, 0, 8, 0, 0, 1, 4,72,10,
	0, 0, 0, 0, 8, 4, 8, 4,40,41, 1, 1, 1,72,72,10,
	0, 0, 0, 0, 8, 8, 8, 8, 0, 8, 0, 2, 1, 4, 8,10,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
#endif
