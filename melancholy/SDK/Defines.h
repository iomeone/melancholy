#pragma once
#include "../Helpers/Helpers.h"

//dump all your defines here

class CBaseEntity;
class CBaseCombatWeapon;

enum PlayerClasses_t
{
	TF2_Scout = 1,
	TF2_Soldier = 3,
	TF2_Pyro = 7,
	TF2_Demoman = 4,
	TF2_Heavy = 6,
	TF2_Engineer = 9,
	TF2_Medic = 5,
	TF2_Sniper = 2,
	TF2_Spy = 8,
};

enum PlayerLifeStates_t
{
	LIFE_ALIVE = 0,
	LIFE_DEAD = 2
};

enum PlayerFlags_t
{
	FL_ONGROUND = (1 << 0),
	FL_DUCKING = (1 << 1),
	FL_INWATER = (1 << 10)
};

enum PlayerConditions_t
{
	TFCond_Slowed = (1 << 0),		 //Toggled when a player is slowed down. 
	TFCond_Zoomed = (1 << 1),		 //Toggled when a player is zoomed. 
	TFCond_Disguising = (1 << 2),		 //Toggled when a Spy is disguising.  
	TFCond_Disguised = (1 << 3),		 //Toggled when a Spy is disguised. 
	TFCond_Cloaked = (1 << 4),		 //Toggled when a Spy is invisible. 
	TFCond_Ubercharged = (1 << 5),		 //Toggled when a player is ÜberCharged. 
	TFCond_TeleportedGlow = (1 << 6),		 //Toggled when someone leaves a teleporter and has glow beneath their feet. 
	TFCond_Taunting = (1 << 7),		 //Toggled when a player is taunting. 
	TFCond_UberchargeFading = (1 << 8),		 //Toggled when the ÜberCharge is fading. 
	TFCond_CloakFlicker = (1 << 9),		 //Toggled when a Spy is visible during cloak. 
	TFCond_Teleporting = (1 << 10),	 //Only activates for a brief second when the player is being teleported; not very useful. 
	TFCond_Kritzkrieged = (1 << 11),	 //Toggled when a player is being crit buffed by the KritzKrieg. 
	TFCond_TmpDamageBonus = (1 << 12),	 //Unknown what this is for. Name taken from the AlliedModders SDK. 
	TFCond_DeadRingered = (1 << 13),	 //Toggled when a player is taking reduced damage from the Deadringer. 
	TFCond_Bonked = (1 << 14),	 //Toggled when a player is under the effects of The Bonk! Atomic Punch. 
	TFCond_Stunned = (1 << 15),	 //Toggled when a player's speed is reduced from airblast or a Sandman ball. 
	TFCond_Buffed = (1 << 16),	 //Toggled when a player is within range of an activated Buff Banner. 
	TFCond_Charging = (1 << 17),	 //Toggled when a Demoman charges with the shield. 
	TFCond_DemoBuff = (1 << 18),	 //Toggled when a Demoman has heads from the Eyelander. 
	TFCond_CritCola = (1 << 19),	 //Toggled when the player is under the effect of The Crit-a-Cola. 
	TFCond_InHealRadius = (1 << 20),	 //Unused condition, name taken from AlliedModders SDK. 
	TFCond_Healing = (1 << 21),	 //Toggled when someone is being healed by a medic or a dispenser. 
	TFCond_OnFire = (1 << 22),	 //Toggled when a player is on fire. 
	TFCond_Overhealed = (1 << 23),	 //Toggled when a player has >100% health. 
	TFCond_Jarated = (1 << 24),	 //Toggled when a player is hit with a Sniper's Jarate. 
	TFCond_Bleeding = (1 << 25),	 //Toggled when a player is taking bleeding damage. 
	TFCond_DefenseBuffed = (1 << 26),	 //Toggled when a player is within range of an activated Battalion's Backup. 
	TFCond_Milked = (1 << 27),	 //Player was hit with a jar of Mad Milk. 
	TFCond_MegaHeal = (1 << 28),	 //Player is under the effect of Quick-Fix charge. 
	TFCond_RegenBuffed = (1 << 29),	 //Toggled when a player is within a Concheror's range. 
	TFCond_MarkedForDeath = (1 << 30),	 //Player is marked for death by a Fan O'War hit. Effects are similar to TFCond_Jarated. 
	TFCond_NoHealingDamageBuff = (1 << 31),	 //Unknown what this is used for.

	TFCondEx_SpeedBuffAlly = (1 << 0),		 //Toggled when a player gets hit with the disciplinary action. 
	TFCondEx_HalloweenCritCandy = (1 << 1),		 //Only for Scream Fortress event maps that drop crit candy. 
	TFCondEx_CritCanteen = (1 << 2),		 //Player is getting a crit boost from a MVM canteen.
	TFCondEx_CritDemoCharge = (1 << 3),		 //From demo's shield
	TFCondEx_CritHype = (1 << 4),		 //Soda Popper crits. 
	TFCondEx_CritOnFirstBlood = (1 << 5),		 //Arena first blood crit buff. 
	TFCondEx_CritOnWin = (1 << 6),		 //End of round crits. 
	TFCondEx_CritOnFlagCapture = (1 << 7),		 //CTF intelligence capture crits. 
	TFCondEx_CritOnKill = (1 << 8),		 //Unknown what this is for. 
	TFCondEx_RestrictToMelee = (1 << 9),		 //Unknown what this is for. 
	TFCondEx_DefenseBuffNoCritBlock = (1 << 10),	 //MvM Buff.
	TFCondEx_Reprogrammed = (1 << 11),	 //MvM Bot has been reprogrammed.
	TFCondEx_PyroCrits = (1 << 12),	 //Player is getting crits from the Mmmph charge. 
	TFCondEx_PyroHeal = (1 << 13),	 //Player is being healed from the Mmmph charge. 
	TFCondEx_FocusBuff = (1 << 14),	 //Player is getting a focus buff.
	TFCondEx_DisguisedRemoved = (1 << 15),	 //Disguised remove from a bot.
	TFCondEx_MarkedForDeathSilent = (1 << 16),	 //Player is under the effects of the Escape Plan/Equalizer or GRU.
	TFCondEx_DisguisedAsDispenser = (1 << 17),	 //Bot is disguised as dispenser.
	TFCondEx_Sapped = (1 << 18),	 //MvM bot is being sapped.
	TFCondEx_UberchargedHidden = (1 << 19),	 //MvM Related
	TFCondEx_UberchargedCanteen = (1 << 20),	 //Player is receiving ÜberCharge from a canteen.
	TFCondEx_HalloweenBombHead = (1 << 21),	 //Player has a bomb on their head from Merasmus.
	TFCondEx_HalloweenThriller = (1 << 22),	 //Players are forced to dance from Merasmus.
	TFCondEx_BulletCharge = (1 << 26),	 //Player is receiving 75% reduced damage from bullets.
	TFCondEx_ExplosiveCharge = (1 << 27),	 //Player is receiving 75% reduced damage from explosives.
	TFCondEx_FireCharge = (1 << 28),	 //Player is receiving 75% reduced damage from fire.
	TFCondEx_BulletResistance = (1 << 29),	 //Player is receiving 10% reduced damage from bullets.
	TFCondEx_ExplosiveResistance = (1 << 30),	 //Player is receiving 10% reduced damage from explosives.
	TFCondEx_FireResistance = (1 << 31),	 //Player is receiving 10% reduced damage from fire.

	TFCondEx2_Stealthed = (1 << 0),
	TFCondEx2_MedigunDebuff = (1 << 1),
	TFCondEx2_StealthedUserBuffFade = (1 << 2),
	TFCondEx2_BulletImmune = (1 << 3),
	TFCondEx2_BlastImmune = (1 << 4),
	TFCondEx2_FireImmune = (1 << 5),
	TFCondEx2_PreventDeath = (1 << 6),
	TFCondEx2_MVMBotRadiowave = (1 << 7),
	TFCondEx2_HalloweenSpeedBoost = (1 << 8),		//Wheel has granted player speed boost.
	TFCondEx2_HalloweenQuickHeal = (1 << 9),		//Wheel has granted player quick heal.
	TFCondEx2_HalloweenGiant = (1 << 10),	//Wheel has granted player giant mode.
	TFCondEx2_HalloweenTiny = (1 << 11),	//Wheel has granted player tiny mode.
	TFCondEx2_HalloweenInHell = (1 << 12),	//Wheel has granted player in hell mode.
	TFCondEx2_HalloweenGhostMode = (1 << 13),	//Wheel has granted player ghost mode.
	TFCondEx2_Parachute = (1 << 16),	//Player has deployed the BASE Jumper.
	TFCondEx2_BlastJumping = (1 << 17),	//Player has sticky or rocket jumped.

	TFCond_MiniCrits = (TFCond_Buffed | TFCond_CritCola),
	TFCond_IgnoreStates = (TFCond_Ubercharged | TFCond_Bonked),
	TFCondEx_IgnoreStates = (TFCondEx_PyroHeal)
};

enum PlayerHitboxes_t
{
	HITBOX_HEAD,
	HITBOX_NECK,
	HITBOX_LOWER_NECK,
	HITBOX_PELVIS,
	HITBOX_BODY,
	HITBOX_THORAX,
	HITBOX_CHEST,
	HITBOX_UPPER_CHEST,
	HITBOX_RIGHT_THIGH,
	HITBOX_LEFT_THIGH,
	HITBOX_RIGHT_CALF,
	HITBOX_LEFT_CALF,
	HITBOX_RIGHT_FOOT,
	HITBOX_LEFT_FOOT,
	HITBOX_RIGHT_HAND,
	HITBOX_LEFT_HAND,
	HITBOX_RIGHT_UPPER_ARM,
	HITBOX_RIGHT_FOREARM,
	HITBOX_LEFT_UPPER_ARM,
	HITBOX_LEFT_FOREARM,
	HITBOX_MAX
};

enum PlayerWeapons_t
{
	Scout_m_Scattergun = 13,
	Scout_m_ScattergunR = 200,
	Scout_m_ForceANature = 45,
	Scout_m_TheShortstop = 220,
	Scout_m_TheSodaPopper = 448,
	Scout_m_FestiveScattergun = 669,
	Scout_m_BabyFacesBlaster = 772,
	Scout_m_SilverBotkillerScattergunMkI = 799,
	Scout_m_GoldBotkillerScattergunMkI = 808,
	Scout_m_RustBotkillerScattergunMkI = 888,
	Scout_m_BloodBotkillerScattergunMkI = 897,
	Scout_m_CarbonadoBotkillerScattergunMkI = 906,
	Scout_m_DiamondBotkillerScattergunMkI = 915,
	Scout_m_SilverBotkillerScattergunMkII = 964,
	Scout_m_GoldBotkillerScattergunMkII = 973,
	Scout_m_FestiveForceANature = 1078,
	Scout_m_TheBackScatter = 1103,
	Scout_m_NightTerror = 15002,
	Scout_m_TartanTorpedo = 15015,
	Scout_m_CountryCrusher = 15021,
	Scout_m_BackcountryBlaster = 15029,
	Scout_m_SpruceDeuce = 15036,
	Scout_m_CurrentEvent = 15053,
	Scout_m_MacabreWeb = 15065,
	Scout_m_Nutcracker = 15069,
	Scout_m_BlueMew = 15106,
	Scout_m_FlowerPower = 15107,
	Scout_m_ShottoHell = 15108,
	Scout_m_CoffinNail = 15131,
	Scout_m_KillerBee = 15151,
	Scout_m_Corsair = 15157,
	Scout_s_ScoutsPistol = 23,
	Scout_s_PistolR = 209,
	Scout_s_BonkAtomicPunch = 46,
	Scout_s_VintageLugermorph = 160,
	Scout_s_CritaCola = 163,
	Scout_s_MadMilk = 222,
	Scout_s_Lugermorph = 294,
	Scout_s_TheWinger = 449,
	Scout_s_PrettyBoysPocketPistol = 773,
	Scout_s_TheFlyingGuillotine = 812,
	Scout_s_TheFlyingGuillotineG = 833,
	Scout_s_MutatedMilk = 1121,
	Scout_s_FestiveBonk = 1145,
	Scout_s_RedRockRoscoe = 15013,
	Scout_s_HomemadeHeater = 15018,
	Scout_s_HickoryHolepuncher = 15035,
	Scout_s_LocalHero = 15041,
	Scout_s_BlackDahlia = 15046,
	Scout_s_SandstoneSpecial = 15056,
	Scout_s_MacabreWeb = 15060,
	Scout_s_Nutcracker = 15061,
	Scout_s_BlueMew = 15100,
	Scout_s_BrainCandy = 15101,
	Scout_s_ShottoHell = 15102,
	Scout_s_DressedToKill = 15126,
	Scout_s_Blitzkrieg = 15148,
	Scout_s_TheCAPPER = 30666,
	Scout_t_Bat = 0,
	Scout_t_BatR = 190,
	Scout_t_TheSandman = 44,
	Scout_t_TheHolyMackerel = 221,
	Scout_t_TheCandyCane = 317,
	Scout_t_TheBostonBasher = 325,
	Scout_t_SunonaStick = 349,
	Scout_t_TheFanOWar = 355,
	Scout_t_TheAtomizer = 450,
	Scout_t_ThreeRuneBlade = 452,
	Scout_t_TheConscientiousObjector = 474,
	Scout_t_UnarmedCombat = 572,
	Scout_t_TheWrapAssassin = 648,
	Scout_t_FestiveBat = 660,
	Scout_t_TheFreedomStaff = 880,
	Scout_t_TheBatOuttaHell = 939,
	Scout_t_TheMemoryMaker = 954,
	Scout_t_FestiveHolyMackerel = 999,
	Scout_t_TheHamShank = 1013,
	Scout_t_TheNecroSmasher = 1123,
	Scout_t_TheCrossingGuard = 1127,
	Scout_t_Batsaber = 30667,
	Scout_t_PrinnyMachete = 30758,
	Soldier_m_RocketLauncher = 18,
	Soldier_m_RocketLauncherR = 205,
	Soldier_m_TheDirectHit = 127,
	Soldier_m_TheBlackBox = 228,
	Soldier_m_RocketJumper = 237,
	Soldier_m_TheLibertyLauncher = 414,
	Soldier_m_TheCowMangler5000 = 441,
	Soldier_m_TheOriginal = 513,
	Soldier_m_FestiveRocketLauncher = 658,
	Soldier_m_TheBeggarsBazooka = 730,
	Soldier_m_SilverBotkillerRocketLauncherMkI = 800,
	Soldier_m_GoldBotkillerRocketLauncherMkI = 809,
	Soldier_m_RustBotkillerRocketLauncherMkI = 889,
	Soldier_m_BloodBotkillerRocketLauncherMkI = 898,
	Soldier_m_CarbonadoBotkillerRocketLauncherMkI = 907,
	Soldier_m_DiamondBotkillerRocketLauncherMkI = 916,
	Soldier_m_SilverBotkillerRocketLauncherMkII = 965,
	Soldier_m_GoldBotkillerRocketLauncherMkII = 974,
	Soldier_m_FestiveBlackBox = 1085,
	Soldier_m_TheAirStrike = 1104,
	Soldier_m_WoodlandWarrior = 15006,
	Soldier_m_SandCannon = 15014,
	Soldier_m_AmericanPastoral = 15028,
	Soldier_m_SmalltownBringdown = 15043,
	Soldier_m_ShellShocker = 15052,
	Soldier_m_AquaMarine = 15057,
	Soldier_m_Autumn = 15081,
	Soldier_m_BlueMew = 15104,
	Soldier_m_BrainCandy = 15105,
	Soldier_m_CoffinNail = 15129,
	Soldier_m_HighRollers = 15130,
	Soldier_m_Warhawk = 15150,
	Soldier_s_SoldiersShotgun = 10,
	Soldier_s_ShotgunR = 199,
	Soldier_s_TheBuffBanner = 129,
	Soldier_s_Gunboats = 133,
	Soldier_s_TheBattalionsBackup = 226,
	Soldier_s_TheConcheror = 354,
	Soldier_s_TheReserveShooter = 415,
	Soldier_s_TheRighteousBison = 442,
	Soldier_s_TheMantreads = 444,
	Soldier_s_FestiveBuffBanner = 1001,
	Soldier_s_TheBASEJumper = 1101,
	Soldier_s_FestiveShotgun = 1141,
	Soldier_s_PanicAttack = 1153,
	Soldier_s_BackwoodsBoomstick = 15003,
	Soldier_s_RusticRuiner = 15016,
	Soldier_s_CivicDuty = 15044,
	Soldier_s_LightningRod = 15047,
	Soldier_s_Autumn = 15085,
	Soldier_s_FlowerPower = 15109,
	Soldier_s_CoffinNail = 15132,
	Soldier_s_DressedtoKill = 15133,
	Soldier_s_RedBear = 15152,
	Soldier_t_Shovel = 6,
	Soldier_t_ShovelR = 196,
	Soldier_t_TheEqualizer = 128,
	Soldier_t_ThePainTrain = 154,
	Soldier_t_TheHalfZatoichi = 357,
	Soldier_t_TheMarketGardener = 416,
	Soldier_t_TheDisciplinaryAction = 447,
	Soldier_t_TheConscientiousObjector = 474,
	Soldier_t_TheEscapePlan = 775,
	Soldier_t_TheFreedomStaff = 880,
	Soldier_t_TheBatOuttaHell = 939,
	Soldier_t_TheMemoryMaker = 954,
	Soldier_t_TheHamShank = 1013,
	Soldier_t_TheNecroSmasher = 1123,
	Soldier_t_TheCrossingGuard = 1127,
	Soldier_t_PrinnyMachete = 30758,
	Pyro_m_FlameThrower = 21,
	Pyro_m_FlameThrowerR = 208,
	Pyro_m_TheBackburner = 40,
	Pyro_m_TheDegreaser = 215,
	Pyro_m_ThePhlogistinator = 594,
	Pyro_m_FestiveFlameThrower = 659,
	Pyro_m_TheRainblower = 741,
	Pyro_m_SilverBotkillerFlameThrowerMkI = 798,
	Pyro_m_GoldBotkillerFlameThrowerMkI = 807,
	Pyro_m_RustBotkillerFlameThrowerMkI = 887,
	Pyro_m_BloodBotkillerFlameThrowerMkI = 896,
	Pyro_m_CarbonadoBotkillerFlameThrowerMkI = 905,
	Pyro_m_DiamondBotkillerFlameThrowerMkI = 914,
	Pyro_m_SilverBotkillerFlameThrowerMkII = 963,
	Pyro_m_GoldBotkillerFlameThrowerMkII = 972,
	Pyro_m_FestiveBackburner = 1146,
	Pyro_m_DragonsFury = 1178,
	Pyro_m_ForestFire = 15005,
	Pyro_m_BarnBurner = 15017,
	Pyro_m_BovineBlazemaker = 15030,
	Pyro_m_EarthSkyandFire = 15034,
	Pyro_m_FlashFryer = 15049,
	Pyro_m_TurbineTorcher = 15054,
	Pyro_m_Autumn = 15066,
	Pyro_m_PumpkinPatch = 15067,
	Pyro_m_Nutcracker = 15068,
	Pyro_m_Balloonicorn = 15089,
	Pyro_m_Rainbow = 15090,
	Pyro_m_CoffinNail = 15115,
	Pyro_m_Warhawk = 15141,
	Pyro_m_NostromoNapalmer = 30474,
	Pyro_s_PyrosShotgun = 12,
	Pyro_s_ShotgunR = 199,
	Pyro_s_TheFlareGun = 39,
	Pyro_s_TheDetonator = 351,
	Pyro_s_TheReserveShooter = 415,
	Pyro_s_TheManmelter = 595,
	Pyro_s_TheScorchShot = 740,
	Pyro_s_FestiveFlareGun = 1081,
	Pyro_s_FestiveShotgun = 1141,
	Pyro_s_PanicAttack = 1153,
	Pyro_s_ThermalThruster = 1179,
	Pyro_s_GasPasser = 1180,
	Pyro_s_BackwoodsBoomstick = 15003,
	Pyro_s_RusticRuiner = 15016,
	Pyro_s_CivicDuty = 15044,
	Pyro_s_LightningRod = 15047,
	Pyro_s_Autumn = 15085,
	Pyro_s_FlowerPower = 15109,
	Pyro_s_CoffinNail = 15132,
	Pyro_s_DressedtoKill = 15133,
	Pyro_s_RedBear = 15152,
	Pyro_t_FireAxe = 2,
	Pyro_t_FireAxeR = 192,
	Pyro_t_TheAxtinguisher = 38,
	Pyro_t_Homewrecker = 153,
	Pyro_t_ThePowerjack = 214,
	Pyro_t_TheBackScratcher = 326,
	Pyro_t_SharpenedVolcanoFragment = 348,
	Pyro_t_ThePostalPummeler = 457,
	Pyro_t_TheMaul = 466,
	Pyro_t_TheConscientiousObjector = 474,
	Pyro_t_TheThirdDegree = 593,
	Pyro_t_TheLollichop = 739,
	Pyro_t_NeonAnnihilator = 813,
	Pyro_t_NeonAnnihilatorG = 834,
	Pyro_t_TheFreedomStaff = 880,
	Pyro_t_TheBatOuttaHell = 939,
	Pyro_t_TheMemoryMaker = 954,
	Pyro_t_TheFestiveAxtinguisher = 1000,
	Pyro_t_TheHamShank = 1013,
	Pyro_t_TheNecroSmasher = 1123,
	Pyro_t_TheCrossingGuard = 1127,
	Pyro_t_HotHand = 1181,
	Pyro_t_PrinnyMachete = 30758,
	Demoman_m_GrenadeLauncher = 19,
	Demoman_m_GrenadeLauncherR = 206,
	Demoman_m_TheLochnLoad = 308,
	Demoman_m_AliBabasWeeBooties = 405,
	Demoman_m_TheBootlegger = 608,
	Demoman_m_TheLooseCannon = 996,
	Demoman_m_FestiveGrenadeLauncher = 1007,
	Demoman_m_TheBASEJumper = 1101,
	Demoman_m_TheIronBomber = 1151,
	Demoman_m_Autumn = 15077,
	Demoman_m_MacabreWeb = 15079,
	Demoman_m_Rainbow = 15091,
	Demoman_m_SweetDreams = 15092,
	Demoman_m_CoffinNail = 15116,
	Demoman_m_TopShelf = 15117,
	Demoman_m_Warhawk = 15142,
	Demoman_m_ButcherBird = 15158,
	Demoman_s_StickybombLauncher = 20,
	Demoman_s_StickybombLauncherR = 207,
	Demoman_s_TheScottishResistance = 130,
	Demoman_s_TheCharginTarge = 131,
	Demoman_s_StickyJumper = 265,
	Demoman_s_TheSplendidScreen = 406,
	Demoman_s_FestiveStickybombLauncher = 661,
	Demoman_s_SilverBotkillerStickybombLauncherMkI = 797,
	Demoman_s_GoldBotkillerStickybombLauncherMkI = 806,
	Demoman_s_RustBotkillerStickybombLauncherMkI = 886,
	Demoman_s_BloodBotkillerStickybombLauncherMkI = 895,
	Demoman_s_CarbonadoBotkillerStickybombLauncherMkI = 904,
	Demoman_s_DiamondBotkillerStickybombLauncherMkI = 913,
	Demoman_s_SilverBotkillerStickybombLauncherMkII = 962,
	Demoman_s_GoldBotkillerStickybombLauncherMkII = 971,
	Demoman_s_TheTideTurner = 1099,
	Demoman_s_FestiveTarge = 1144,
	Demoman_s_TheQuickiebombLauncher = 1150,
	Demoman_s_SuddenFlurry = 15009,
	Demoman_s_CarpetBomber = 15012,
	Demoman_s_BlastedBombardier = 15024,
	Demoman_s_RooftopWrangler = 15038,
	Demoman_s_LiquidAsset = 15045,
	Demoman_s_PinkElephant = 15048,
	Demoman_s_Autumn = 15082,
	Demoman_s_PumpkinPatch = 15083,
	Demoman_s_MacabreWeb = 15084,
	Demoman_s_SweetDreams = 15113,
	Demoman_s_CoffinNail = 15137,
	Demoman_s_DressedtoKill = 15138,
	Demoman_s_Blitzkrieg = 15155,
	Demoman_t_Bottle = 1,
	Demoman_t_BottleR = 191,
	Demoman_t_TheEyelander = 132,
	Demoman_t_ThePainTrain = 154,
	Demoman_t_TheScotsmansSkullcutter = 172,
	Demoman_t_HorselessHeadlessHorsemannsHeadtaker = 266,
	Demoman_t_UllapoolCaber = 307,
	Demoman_t_TheClaidheamhMor = 327,
	Demoman_t_TheHalfZatoichi = 357,
	Demoman_t_ThePersianPersuader = 404,
	Demoman_t_TheConscientiousObjector = 474,
	Demoman_t_NessiesNineIron = 482,
	Demoman_t_TheScottishHandshake = 609,
	Demoman_t_TheFreedomStaff = 880,
	Demoman_t_TheBatOuttaHell = 939,
	Demoman_t_TheMemoryMaker = 954,
	Demoman_t_TheHamShank = 1013,
	Demoman_t_FestiveEyelander = 1082,
	Demoman_t_TheNecroSmasher = 1123,
	Demoman_t_TheCrossingGuard = 1127,
	Demoman_t_PrinnyMachete = 30758,
	Heavy_m_Minigun = 15,
	Heavy_m_MinigunR = 202,
	Heavy_m_Natascha = 41,
	Heavy_m_IronCurtain = 298,
	Heavy_m_TheBrassBeast = 312,
	Heavy_m_Tomislav = 424,
	Heavy_m_FestiveMinigun = 654,
	Heavy_m_SilverBotkillerMinigunMkI = 793,
	Heavy_m_GoldBotkillerMinigunMkI = 802,
	Heavy_m_TheHuoLongHeater = 811,
	Heavy_m_TheHuoLongHeaterG = 832,
	Heavy_m_Deflector_mvm = 850,
	Heavy_m_RustBotkillerMinigunMkI = 882,
	Heavy_m_BloodBotkillerMinigunMkI = 891,
	Heavy_m_CarbonadoBotkillerMinigunMkI = 900,
	Heavy_m_DiamondBotkillerMinigunMkI = 909,
	Heavy_m_SilverBotkillerMinigunMkII = 958,
	Heavy_m_GoldBotkillerMinigunMkII = 967,
	Heavy_m_KingoftheJungle = 15004,
	Heavy_m_IronWood = 15020,
	Heavy_m_AntiqueAnnihilator = 15026,
	Heavy_m_WarRoom = 15031,
	Heavy_m_CitizenPain = 15040,
	Heavy_m_BrickHouse = 15055,
	Heavy_m_MacabreWeb = 15086,
	Heavy_m_PumpkinPatch = 15087,
	Heavy_m_Nutcracker = 15088,
	Heavy_m_BrainCandy = 15098,
	Heavy_m_MisterCuddles = 15099,
	Heavy_m_CoffinNail = 15123,
	Heavy_m_DressedtoKill = 15124,
	Heavy_m_TopShelf = 15125,
	Heavy_m_ButcherBird = 15147,
	Heavy_s_HeavysShotgun = 11,
	Heavy_s_ShotgunR = 199,
	Heavy_s_Sandvich = 42,
	Heavy_s_TheDalokohsBar = 159,
	Heavy_s_TheBuffaloSteakSandvich = 311,
	Heavy_s_TheFamilyBusiness = 425,
	Heavy_s_Fishcake = 433,
	Heavy_s_RoboSandvich = 863,
	Heavy_s_FestiveSandvich = 1002,
	Heavy_s_FestiveShotgun = 1141,
	Heavy_s_PanicAttack = 1153,
	Heavy_s_SecondBanana = 1190,
	Heavy_s_BackwoodsBoomstick = 15003,
	Heavy_s_RusticRuiner = 15016,
	Heavy_s_CivicDuty = 15044,
	Heavy_s_LightningRod = 15047,
	Heavy_s_Autumn = 15085,
	Heavy_s_FlowerPower = 15109,
	Heavy_s_CoffinNail = 15132,
	Heavy_s_DressedtoKill = 15133,
	Heavy_s_RedBear = 15152,
	Heavy_t_Fists = 5,
	Heavy_t_FistsR = 195,
	Heavy_t_TheKillingGlovesofBoxing = 43,
	Heavy_t_GlovesofRunningUrgently = 239,
	Heavy_t_WarriorsSpirit = 310,
	Heavy_t_FistsofSteel = 331,
	Heavy_t_TheEvictionNotice = 426,
	Heavy_t_TheConscientiousObjector = 474,
	Heavy_t_ApocoFists = 587,
	Heavy_t_TheHolidayPunch = 656,
	Heavy_t_TheFreedomStaff = 880,
	Heavy_t_TheBatOuttaHell = 939,
	Heavy_t_TheMemoryMaker = 954,
	Heavy_t_TheHamShank = 1013,
	Heavy_t_FestiveGlovesofRunningUrgently = 1084,
	Heavy_t_TheBreadBite = 1100,
	Heavy_t_TheNecroSmasher = 1123,
	Heavy_t_TheCrossingGuard = 1127,
	Heavy_t_GlovesofRunningUrgentlyMvM = 1184,
	Heavy_t_PrinnyMachete = 30758,
	Engi_m_EngineersShotgun = 9,
	Engi_m_ShotgunR = 199,
	Engi_m_TheFrontierJustice = 141,
	Engi_m_TheWidowmaker = 527,
	Engi_m_ThePomson6000 = 588,
	Engi_m_TheRescueRanger = 997,
	Engi_m_FestiveFrontierJustice = 1004,
	Engi_m_FestiveShotgun = 1141,
	Engi_m_PanicAttack = 1153,
	Engi_m_BackwoodsBoomstick = 15003,
	Engi_m_RusticRuiner = 15016,
	Engi_m_CivicDuty = 15044,
	Engi_m_LightningRod = 15047,
	Engi_m_Autumn = 15085,
	Engi_m_FlowerPower = 15109,
	Engi_m_CoffinNail = 15132,
	Engi_m_DressedtoKill = 15133,
	Engi_m_RedBear = 15152,
	Engi_s_EngineersPistol = 22,
	Engi_s_PistolR = 209,
	Engi_s_TheWrangler = 140,
	Engi_s_VintageLugermorph = 160,
	Engi_s_Lugermorph = 294,
	Engi_s_TheShortCircuit = 528,
	Engi_s_FestiveWrangler = 1086,
	Engi_s_RedRockRoscoe = 15013,
	Engi_s_HomemadeHeater = 15018,
	Engi_s_HickoryHolepuncher = 15035,
	Engi_s_LocalHero = 15041,
	Engi_s_BlackDahlia = 15046,
	Engi_s_SandstoneSpecial = 15056,
	Engi_s_MacabreWeb = 15060,
	Engi_s_Nutcracker = 15061,
	Engi_s_BlueMew = 15100,
	Engi_s_BrainCandy = 15101,
	Engi_s_ShottoHell = 15102,
	Engi_s_DressedToKill = 15126,
	Engi_s_Blitzkrieg = 15148,
	Engi_s_TheCAPPER = 30666,
	Engi_s_TheGigarCounter = 30668,
	Engi_t_Wrench = 7,
	Engi_t_WrenchR = 197,
	Engi_t_TheGunslinger = 142,
	Engi_t_TheSouthernHospitality = 155,
	Engi_t_GoldenWrench = 169,
	Engi_t_TheJag = 329,
	Engi_t_TheEurekaEffect = 589,
	Engi_t_FestiveWrench = 662,
	Engi_t_SilverBotkillerWrenchMkI = 795,
	Engi_t_GoldBotkillerWrenchMkI = 804,
	Engi_t_RustBotkillerWrenchMkI = 884,
	Engi_t_BloodBotkillerWrenchMkI = 893,
	Engi_t_CarbonadoBotkillerWrenchMkI = 902,
	Engi_t_DiamondBotkillerWrenchMkI = 911,
	Engi_t_SilverBotkillerWrenchMkII = 960,
	Engi_t_GoldBotkillerWrenchMkII = 969,
	Engi_t_TheNecroSmasher = 1123,
	Engi_t_Nutcracker = 15073,
	Engi_t_Autumn = 15074,
	Engi_t_Boneyard = 15075,
	Engi_t_DressedtoKill = 15139,
	Engi_t_TopShelf = 15140,
	Engi_t_TorquedtoHell = 15114,
	Engi_t_Airwolf = 15156,
	Engi_t_PrinnyMachete = 30758,
	Engi_p_ConstructionPDA = 25,
	Engi_p_ConstructionPDAR = 737,
	Engi_p_DestructionPDA = 26,
	Engi_p_PDA = 28,
	Medic_m_SyringeGun = 17,
	Medic_m_SyringeGunR = 204,
	Medic_m_TheBlutsauger = 36,
	Medic_m_CrusadersCrossbow = 305,
	Medic_m_TheOverdose = 412,
	Medic_m_FestiveCrusadersCrossbow = 1079,
	Medic_s_MediGun = 29,
	Medic_s_MediGunR = 211,
	Medic_s_TheKritzkrieg = 35,
	Medic_s_TheQuickFix = 411,
	Medic_s_FestiveMediGun = 663,
	Medic_s_SilverBotkillerMediGunMkI = 796,
	Medic_s_GoldBotkillerMediGunMkI = 805,
	Medic_s_RustBotkillerMediGunMkI = 885,
	Medic_s_BloodBotkillerMediGunMkI = 894,
	Medic_s_CarbonadoBotkillerMediGunMkI = 903,
	Medic_s_DiamondBotkillerMediGunMkI = 912,
	Medic_s_SilverBotkillerMediGunMkII = 961,
	Medic_s_GoldBotkillerMediGunMkII = 970,
	Medic_s_TheVaccinator = 998,
	Medic_s_MaskedMender = 15008,
	Medic_s_WrappedReviver = 15010,
	Medic_s_ReclaimedReanimator = 15025,
	Medic_s_CivilServant = 15039,
	Medic_s_SparkofLife = 15050,
	Medic_s_Wildwood = 15078,
	Medic_s_FlowerPower = 15097,
	Medic_s_DressedToKill = 15121,
	Medic_s_HighRollers = 15122,
	Medic_s_CoffinNail = 15123,
	Medic_s_Blitzkrieg = 15145,
	Medic_s_Corsair = 15146,
	Medic_t_Bonesaw = 8,
	Medic_t_BonesawR = 198,
	Medic_t_TheUbersaw = 37,
	Medic_t_TheVitaSaw = 173,
	Medic_t_Amputator = 304,
	Medic_t_TheSolemnVow = 413,
	Medic_t_TheConscientiousObjector = 474,
	Medic_t_TheFreedomStaff = 880,
	Medic_t_TheBatOuttaHell = 939,
	Medic_t_TheMemoryMaker = 954,
	Medic_t_FestiveUbersaw = 1003,
	Medic_t_TheHamShank = 1013,
	Medic_t_TheNecroSmasher = 1123,
	Medic_t_TheCrossingGuard = 1127,
	Medic_t_FestiveBonesaw = 1143,
	Medic_t_PrinnyMachete = 30758,
	Sniper_m_SniperRifle = 14,
	Sniper_m_SniperRifleR = 201,
	Sniper_m_TheHuntsman = 56,
	Sniper_m_TheSydneySleeper = 230,
	Sniper_m_TheBazaarBargain = 402,
	Sniper_m_TheMachina = 526,
	Sniper_m_FestiveSniperRifle = 664,
	Sniper_m_TheHitmansHeatmaker = 752,
	Sniper_m_SilverBotkillerSniperRifleMkI = 792,
	Sniper_m_GoldBotkillerSniperRifleMkI = 801,
	Sniper_m_TheAWPerHand = 851,
	Sniper_m_RustBotkillerSniperRifleMkI = 881,
	Sniper_m_BloodBotkillerSniperRifleMkI = 890,
	Sniper_m_CarbonadoBotkillerSniperRifleMkI = 899,
	Sniper_m_DiamondBotkillerSniperRifleMkI = 908,
	Sniper_m_SilverBotkillerSniperRifleMkII = 957,
	Sniper_m_GoldBotkillerSniperRifleMkII = 966,
	Sniper_m_FestiveHuntsman = 1005,
	Sniper_m_TheFortifiedCompound = 1092,
	Sniper_m_TheClassic = 1098,
	Sniper_m_NightOwl = 15000,
	Sniper_m_PurpleRange = 15007,
	Sniper_m_LumberFromDownUnder = 15019,
	Sniper_m_ShotintheDark = 15023,
	Sniper_m_Bogtrotter = 15033,
	Sniper_m_Thunderbolt = 15059,
	Sniper_m_PumpkinPatch = 15070,
	Sniper_m_Boneyard = 15071,
	Sniper_m_Wildwood = 15072,
	Sniper_m_Balloonicorn = 15111,
	Sniper_m_Rainbow = 15112,
	Sniper_m_CoffinNail = 15135,
	Sniper_m_DressedtoKill = 15136,
	Sniper_m_Airwolf = 15154,
	Sniper_m_ShootingStar = 30665,
	Sniper_s_SMG = 16,
	Sniper_s_SMGR = 203,
	Sniper_s_TheRazorback = 57,
	Sniper_s_Jarate = 58,
	Sniper_s_DarwinsDangerShield = 231,
	Sniper_s_CozyCamper = 642,
	Sniper_s_TheCleanersCarbine = 751,
	Sniper_s_FestiveJarate = 1083,
	Sniper_s_TheSelfAwareBeautyMark = 1105,
	Sniper_s_FestiveSMG = 1149,
	Sniper_s_WoodsyWidowmaker = 15001,
	Sniper_s_PlaidPotshotter = 15022,
	Sniper_s_TreadplateTormenter = 15032,
	Sniper_s_TeamSprayer = 15037,
	Sniper_s_LowProfile = 15058,
	Sniper_s_Wildwood = 15076,
	Sniper_s_BlueMew = 15110,
	Sniper_s_HighRollers = 15134,
	Sniper_s_Blitzkrieg = 15153,
	Sniper_t_Kukri = 3,
	Sniper_t_KukriR = 193,
	Sniper_t_TheTribalmansShiv = 171,
	Sniper_t_TheBushwacka = 232,
	Sniper_t_TheShahanshah = 401,
	Sniper_t_TheConscientiousObjector = 474,
	Sniper_t_TheFreedomStaff = 880,
	Sniper_t_TheBatOuttaHell = 939,
	Sniper_t_TheMemoryMaker = 954,
	Sniper_t_TheHamShank = 1013,
	Sniper_t_TheNecroSmasher = 1123,
	Sniper_t_TheCrossingGuard = 1127,
	Sniper_t_PrinnyMachete = 30758,
	Spy_m_Revolver = 24,
	Spy_m_RevolverR = 210,
	Spy_m_TheAmbassador = 61,
	Spy_m_BigKill = 161,
	Spy_m_LEtranger = 224,
	Spy_m_TheEnforcer = 460,
	Spy_m_TheDiamondback = 525,
	Spy_m_FestiveAmbassador = 1006,
	Spy_m_FestiveRevolver = 1142,
	Spy_m_PsychedelicSlugger = 15011,
	Spy_m_OldCountry = 15027,
	Spy_m_Mayor = 15042,
	Spy_m_DeadReckoner = 15051,
	Spy_m_Boneyard = 15062,
	Spy_m_Wildwood = 15063,
	Spy_m_MacabreWeb = 15064,
	Spy_m_FlowerPower = 15103,
	Spy_m_TopShelf = 15128,
	Spy_m_CoffinNail = 15129,
	Spy_m_Blitzkrieg = 15149,
	Spy_s_Sapper = 735,
	Spy_s_SapperR = 736,
	Spy_s_TheRedTapeRecorder = 810,
	Spy_s_TheRedTapeRecorderG = 831,
	Spy_s_TheApSapG = 933,
	Spy_s_FestiveSapper = 1080,
	Spy_s_TheSnackAttack = 1102,
	Spy_t_Knife = 4,
	Spy_t_KnifeR = 194,
	Spy_t_YourEternalReward = 225,
	Spy_t_ConniversKunai = 356,
	Spy_t_TheBigEarner = 461,
	Spy_t_TheWangaPrick = 574,
	Spy_t_TheSharpDresser = 638,
	Spy_t_TheSpycicle = 649,
	Spy_t_FestiveKnife = 665,
	Spy_t_TheBlackRose = 727,
	Spy_t_SilverBotkillerKnifeMkI = 794,
	Spy_t_GoldBotkillerKnifeMkI = 803,
	Spy_t_RustBotkillerKnifeMkI = 883,
	Spy_t_BloodBotkillerKnifeMkI = 892,
	Spy_t_CarbonadoBotkillerKnifeMkI = 901,
	Spy_t_DiamondBotkillerKnifeMkI = 910,
	Spy_t_SilverBotkillerKnifeMkII = 959,
	Spy_t_GoldBotkillerKnifeMkII = 968,
	Spy_t_Boneyard = 15062,
	Spy_t_BlueMew = 15094,
	Spy_t_BrainCandy = 15095,
	Spy_t_StabbedtoHell = 15096,
	Spy_t_DressedtoKill = 15118,
	Spy_t_TopShelf = 15119,
	Spy_t_Blitzkrieg = 15143,
	Spy_t_Airwolf = 15144,
	Spy_t_PrinnyMachete = 30758,
	Spy_d_DisguiseKitPDA = 27,
	Spy_w_InvisWatch = 30,
	Spy_w_InvisWatchR = 212,
	Spy_w_TheDeadRinger = 59,
	Spy_w_TheCloakandDagger = 60,
	Spy_w_EnthusiastsTimepiece = 297,
	Spy_w_TheQuackenbirdt = 947,
	Misc_t_FryingPan = 264,
	Misc_t_GoldFryingPan = 1071,
	Misc_t_Saxxy = 423,
};

enum PlayerControls_t
{
	IN_ATTACK = (1 << 0),
	IN_JUMP = (1 << 1),
	IN_DUCK = (1 << 2),
	IN_FORWARD = (1 << 3),
	IN_BACK = (1 << 4),
	IN_USE = (1 << 5),
	IN_CANCEL = (1 << 6),
	IN_LEFT = (1 << 7),
	IN_RIGHT = (1 << 8),
	IN_MOVELEFT = (1 << 9),
	IN_MOVERIGHT = (1 << 10),
	IN_ATTACK2 = (1 << 11),
	IN_RUN = (1 << 12),
	IN_RELOAD = (1 << 13),
	IN_ALT1 = (1 << 14),
	IN_ALT2 = (1 << 15),
	IN_SCORE = (1 << 16),
	IN_SPEED = (1 << 17),
	IN_WALK = (1 << 18),
	IN_ZOOM = (1 << 19),
	IN_WEAPON1 = (1 << 20),
	IN_WEAPON2 = (1 << 21),
	IN_BULLRUSH = (1 << 22)
};

enum EntityClassIds_t
{
	CAI_BaseNPC = 0,
	CBaseAnimating = 1,
	CBaseAnimatingOverlay = 2,
	CBaseAttributableItem = 3,
	CBaseCombatCharacter = 4,
	CBaseCombatWeaponEx = 5,
	CBaseDoor = 6,
	CBaseEntityEx = 7,
	CBaseFlex = 8,
	CBaseGrenade = 9,
	CBaseObjectEx = 10,
	CBaseObjectUpgrade = 11,
	CBaseParticleEntity = 12,
	CBasePlayerEx = 13,
	CBaseProjectile = 14,
	CBasePropDoor = 15,
	CBaseTeamObjectiveResource = 16,
	CBaseTempEntity = 17,
	CBaseViewModel = 18,
	CBeam = 19,
	CBoneFollower = 20,
	CBonusDuckPickup = 21,
	CBonusPack = 22,
	CBonusRoundLogic = 23,
	CBreakableProp = 24,
	CBreakableSurface = 25,
	CCaptureFlag = 26,
	CCaptureFlagReturnIcon = 27,
	CCaptureZone = 28,
	CColorCorrection = 29,
	CColorCorrectionVolume = 30,
	CCurrencyPack = 31,
	CDynamicLight = 32,
	CDynamicProp = 33,
	CEconEntity = 34,
	CEconWearable = 35,
	CEmbers = 36,
	CEntityDissolve = 37,
	CEntityFlame = 38,
	CEntityParticleTrail = 39,
	CEnvDetailController = 40,
	CEnvParticleScript = 41,
	CEnvProjectedTexture = 42,
	CEnvQuadraticBeam = 43,
	CEnvScreenEffect = 44,
	CEnvScreenOverlay = 45,
	CEnvTonemapController = 46,
	CEnvWind = 47,
	CEyeballBoss = 48,
	CFireSmoke = 49,
	CFireTrail = 50,
	CFish = 51,
	CFogController = 52,
	CFuncAreaPortalWindow = 55,
	CFuncConveyor = 56,
	CFuncForceField = 57,
	CFuncLadder = 58,
	CFuncMonitor = 59,
	CFuncOccluder = 60,
	CFuncPasstimeGoal = 61,
	CFuncReflectiveGlass = 62,
	CFuncRespawnRoom = 63,
	CFuncRespawnRoomVisualizer = 64,
	CFuncRotating = 65,
	CFuncSmokeVolume = 66,
	CFuncTrackTrain = 67,
	CFunc_Dust = 53,
	CFunc_LOD = 54,
	CGameRulesProxy = 68,
	CHalloweenGiftPickup = 69,
	CHalloweenPickup = 70,
	CHalloweenSoulPack = 71,
	CHandleTest = 72,
	CHeadlessHatman = 73,
	CHightower_TeleportVortex = 74,
	CInfoLadderDismount = 75,
	CInfoLightingRelative = 76,
	CInfoOverlayAccessor = 77,
	CLaserDot = 78,
	CLightGlow = 79,
	CMannVsMachineStats = 80,
	CMaterialModifyControl = 81,
	CMerasmus = 82,
	CMerasmusDancer = 83,
	CMonsterResource = 84,
	CObjectCartDispenser = 85,
	CObjectDispenser = 86,
	CObjectSapper = 87,
	CObjectSentrygun = 88,
	CObjectTeleporter = 89,
	CParticleFire = 90,
	CParticlePerformanceMonitor = 91,
	CParticleSystem = 92,
	CPasstimeBall = 93,
	CPasstimeGun = 94,
	CPhysBox = 95,
	CPhysBoxMultiplayer = 96,
	CPhysMagnet = 99,
	CPhysicsProp = 97,
	CPhysicsPropMultiplayer = 98,
	CPlasma = 100,
	CPlayerDestructionDispenser = 101,
	CPlayerResource = 102,
	CPointCamera = 103,
	CPointCommentaryNode = 104,
	CPoseController = 105,
	CPrecipitation = 106,
	CPropVehicleDriveable = 107,
	CRagdollManager = 108,
	CRagdollProp = 109,
	CRagdollPropAttached = 110,
	CRobotDispenser = 111,
	CRopeKeyframe = 112,
	CSceneEntity = 113,
	CShadowControl = 114,
	CSlideshowDisplay = 115,
	CSmokeStack = 116,
	CSniperDot = 117,
	CSpotlightEnd = 118,
	CSprite = 119,
	CSpriteOriented = 120,
	CSpriteTrail = 121,
	CSteamJet = 122,
	CSun = 123,
	CTEArmorRicochet = 128,
	CTEBSPDecal = 141,
	CTEBaseBeam = 129,
	CTEBeamEntPoint = 130,
	CTEBeamEnts = 131,
	CTEBeamFollow = 132,
	CTEBeamLaser = 133,
	CTEBeamPoints = 134,
	CTEBeamRing = 135,
	CTEBeamRingPoint = 136,
	CTEBeamSpline = 137,
	CTEBloodSprite = 138,
	CTEBloodStream = 139,
	CTEBreakModel = 140,
	CTEBubbleTrail = 143,
	CTEBubbles = 142,
	CTEClientProjectile = 144,
	CTEDecal = 145,
	CTEDust = 146,
	CTEDynamicLight = 147,
	CTEEffectDispatch = 148,
	CTEEnergySplash = 149,
	CTEExplosion = 150,
	CTEFireBullets = 151,
	CTEFizz = 152,
	CTEFootprintDecal = 153,
	CTEGaussExplosion = 154,
	CTEGlowSprite = 155,
	CTEImpact = 156,
	CTEKillPlayerAttachments = 157,
	CTELargeFunnel = 158,
	CTEMetalSparks = 160,
	CTEMuzzleFlash = 161,
	CTEParticleSystem = 162,
	CTEPhysicsProp = 163,
	CTEPlayerAnimEvent = 164,
	CTEPlayerDecal = 165,
	CTEProjectedDecal = 166,
	CTEShatterSurface = 167,
	CTEShowLine = 168,
	CTESmoke = 170,
	CTESparks = 171,
	CTESprite = 172,
	CTESpriteSpray = 173,
	CTETFBlood = 176,
	CTETFExplosion = 177,
	CTETFParticleEffect = 178,
	CTEWorldDecal = 179,
	CTFAmmoPack = 180,
	CTFBall_Ornament = 181,
	CTFBaseBoss = 182,
	CTFBaseProjectile = 183,
	CTFBaseRocket = 184,
	CTFBat = 185,
	CTFBat_Fish = 186,
	CTFBat_Giftwrap = 187,
	CTFBat_Wood = 188,
	CTFBonesaw = 189,
	CTFBotHintEngineerNest = 190,
	CTFBottle = 191,
	CTFBreakableMelee = 192,
	CTFBreakableSign = 193,
	CTFBuffItem = 194,
	CTFCannon = 195,
	CTFChargedSMG = 196,
	CTFCleaver = 197,
	CTFClub = 198,
	CTFCompoundBow = 199,
	CTFCrossbow = 200,
	CTFDRGPomson = 201,
	CTFDroppedWeapon = 202,
	CTFFireAxe = 203,
	CTFFists = 204,
	CTFFlameManager = 205,
	CTFFlameRocket = 206,
	CTFFlameThrower = 207,
	CTFFlareGun = 208,
	CTFFlareGun_Revenge = 209,
	CTFGameRulesProxy = 210,
	CTFGasManager = 211,
	CTFGenericBomb = 212,
	CTFGlow = 213,
	CTFGrapplingHook = 214,
	CTFGrenadeLauncher = 215,
	CTFGrenadePipebombProjectile = 216,
	CTFHalloweenMinigame = 217,
	CTFHalloweenMinigame_FallingPlatforms = 218,
	CTFHellZap = 219,
	CTFItem = 220,
	CTFJar = 221,
	CTFJarGas = 222,
	CTFJarMilk = 223,
	CTFKatana = 224,
	CTFKnife = 225,
	CTFLaserPointer = 226,
	CTFLunchBox = 227,
	CTFLunchBox_Drink = 228,
	CTFMechanicalArm = 229,
	CTFMedigunShield = 230,
	CTFMiniGame = 231,
	CTFMinigameLogic = 232,
	CTFMinigun = 233,
	CTFObjectiveResource = 234,
	CTFPEPBrawlerBlaster = 240,
	CTFParachute = 235,
	CTFParachute_Primary = 236,
	CTFParachute_Secondary = 237,
	CTFParticleCannon = 238,
	CTFPasstimeLogic = 239,
	CTFPipebombLauncher = 241,
	CTFPistol = 242,
	CTFPistol_Scout = 243,
	CTFPistol_ScoutPrimary = 244,
	CTFPistol_ScoutSecondary = 245,
	CTFPlayer = 246,
	CTFPlayerDestructionLogic = 247,
	CTFPlayerResource = 248,
	CTFPointManager = 249,
	CTFPowerupBottle = 250,
	CTFProjectile_Arrow = 251,
	CTFProjectile_BallOfFire = 252,
	CTFProjectile_Cleaver = 253,
	CTFProjectile_EnergyBall = 254,
	CTFProjectile_EnergyRing = 255,
	CTFProjectile_Flare = 256,
	CTFProjectile_GrapplingHook = 257,
	CTFProjectile_HealingBolt = 258,
	CTFProjectile_Jar = 259,
	CTFProjectile_JarGas = 260,
	CTFProjectile_JarMilk = 261,
	CTFProjectile_MechanicalArmOrb = 262,
	CTFProjectile_Rocket = 263,
	CTFProjectile_SentryRocket = 264,
	CTFProjectile_SpellBats = 265,
	CTFProjectile_SpellFireball = 266,
	CTFProjectile_SpellKartBats = 267,
	CTFProjectile_SpellKartOrb = 268,
	CTFProjectile_SpellLightningOrb = 269,
	CTFProjectile_SpellMeteorShower = 270,
	CTFProjectile_SpellMirv = 271,
	CTFProjectile_SpellPumpkin = 272,
	CTFProjectile_SpellSpawnBoss = 273,
	CTFProjectile_SpellSpawnHorde = 274,
	CTFProjectile_SpellSpawnZombie = 275,
	CTFProjectile_SpellTransposeTeleport = 276,
	CTFProjectile_Throwable = 277,
	CTFProjectile_ThrowableBreadMonster = 278,
	CTFProjectile_ThrowableBrick = 279,
	CTFProjectile_ThrowableRepel = 280,
	CTFPumpkinBomb = 281,
	CTFRagdoll = 282,
	CTFRaygun = 283,
	CTFReviveMarker = 284,
	CTFRevolver = 285,
	CTFRobotArm = 286,
	CTFRobotDestructionLogic = 290,
	CTFRobotDestruction_Robot = 287,
	CTFRobotDestruction_RobotGroup = 288,
	CTFRobotDestruction_RobotSpawn = 289,
	CTFRocketLauncher = 291,
	CTFRocketLauncher_AirStrike = 292,
	CTFRocketLauncher_DirectHit = 293,
	CTFRocketLauncher_Mortar = 294,
	CTFRocketPack = 295,
	CTFSMG = 305,
	CTFScatterGun = 296,
	CTFShotgun = 297,
	CTFShotgunBuildingRescue = 302,
	CTFShotgun_HWG = 298,
	CTFShotgun_Pyro = 299,
	CTFShotgun_Revenge = 300,
	CTFShotgun_Soldier = 301,
	CTFShovel = 303,
	CTFSlap = 304,
	CTFSniperRifle = 306,
	CTFSniperRifleClassic = 307,
	CTFSniperRifleDecap = 308,
	CTFSodaPopper = 309,
	CTFSpellBook = 310,
	CTFStickBomb = 311,
	CTFStunBall = 312,
	CTFSword = 313,
	CTFSyringeGun = 314,
	CTFTankBoss = 315,
	CTFTauntProp = 316,
	CTFTeam = 317,
	CTFThrowable = 318,
	CTFViewModel = 319,
	CTFWeaponBase = 320,
	CTFWeaponBaseGrenadeProj = 321,
	CTFWeaponBaseGun = 322,
	CTFWeaponBaseMelee = 323,
	CTFWeaponBaseMerasmusGrenade = 324,
	CTFWeaponBuilder = 325,
	CTFWeaponFlameBall = 326,
	CTFWeaponInvis = 327,
	CTFWeaponPDA = 328,
	CTFWeaponPDAExpansion_Dispenser = 332,
	CTFWeaponPDAExpansion_Teleporter = 333,
	CTFWeaponPDA_Engineer_Build = 329,
	CTFWeaponPDA_Engineer_Destroy = 330,
	CTFWeaponPDA_Spy = 331,
	CTFWeaponSapper = 334,
	CTFWearable = 335,
	CTFWearableCampaignItem = 336,
	CTFWearableDemoShield = 337,
	CTFWearableItem = 338,
	CTFWearableLevelableItem = 339,
	CTFWearableRazorback = 340,
	CTFWearableRobotArm = 341,
	CTFWearableVM = 342,
	CTFWrench = 343,
	CTeam = 124,
	CTeamRoundTimer = 126,
	CTeamTrainWatcher = 127,
	CTeamplayRoundBasedRulesProxy = 125,
	CTeleportVortex = 159,
	CTesla = 169,
	CTestTraceline = 175,
	CTest_ProxyToggle_Networkable = 174,
	CVGuiScreen = 344,
	CVoteController = 345,
	CWaterBullet = 346,
	CWaterLODControl = 347,
	CWeaponIFMBase = 348,
	CWeaponIFMBaseCamera = 349,
	CWeaponIFMSteadyCam = 350,
	CWeaponMedigun = 351,
	CWorld = 352,
	CZombie = 353,
	DustTrail = 354,
	MovieExplosion = 355,
	NextBotCombatCharacter = 356,
	ParticleSmokeGrenade = 357,
	RocketTrail = 358,
	SmokeTrail = 359,
	SporeExplosion = 360,
	SporeTrail = 361,
};

enum FontFlags_t
{
	FONTFLAG_NONE = 0x000,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400
};

enum ClientFrameStage_t
{
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,
	FRAME_RENDER_START,
	FRAME_RENDER_END
};

enum MoveType_t
{
	MOVETYPE_NONE = 0,
	MOVETYPE_ISOMETRIC,
	MOVETYPE_WALK,
	MOVETYPE_STEP,
	MOVETYPE_FLY,
	MOVETYPE_FLYGRAVITY,
	MOVETYPE_VPHYSICS,
	MOVETYPE_PUSH,
	MOVETYPE_NOCLIP,
	MOVETYPE_LADDER,
	MOVETYPE_OBSERVER,
	MOVETYPE_CUSTOM,
	MOVETYPE_LAST = MOVETYPE_CUSTOM,
	MOVETYPE_MAX_BITS = 4
};

enum ClearFlags_t
{
	VIEW_CLEAR_COLOR = 0x1,
	VIEW_CLEAR_DEPTH = 0x2,
	VIEW_CLEAR_FULL_TARGET = 0x4,
	VIEW_NO_DRAW = 0x8,
	VIEW_CLEAR_OBEY_STENCIL = 0x10,
	VIEW_CLEAR_STENCIL = 0x20,
};

enum StereoEye_t
{
	STEREO_EYE_MONO = 0,
	STEREO_EYE_LEFT = 1,
	STEREO_EYE_RIGHT = 2,
	STEREO_EYE_MAX = 3,
};

class CViewSetup
{
public:
	int			x;
	int			m_nUnscaledX;
	int			y;
	int			m_nUnscaledY;
	int			width;
	int			m_nUnscaledWidth;
	int			height;
	StereoEye_t m_eStereoEye;
	int			m_nUnscaledHeight;
	bool		m_bOrtho;
	float		m_OrthoLeft;
	float		m_OrthoTop;
	float		m_OrthoRight;
	float		m_OrthoBottom;
	float		fov;
	float		fovViewmodel;
	Vec3		origin;
	Vec3		angles;
	float		zNear;
	float		zFar;
	float		zNearViewmodel;
	float		zFarViewmodel;
	bool		m_bRenderToSubrectOfLargerScreen;
	float		m_flAspectRatio;
	bool		m_bOffCenter;
	float		m_flOffCenterTop;
	float		m_flOffCenterBottom;
	float		m_flOffCenterLeft;
	float		m_flOffCenterRight;
	bool		m_bDoBloomAndToneMapping;
	bool		m_bCacheFullSceneState;
	bool        m_bViewToProjectionOverride;
	void		*m_ViewToProjection;
};

enum ObserverModes_t
{
	OBS_MODE_NONE = 0,		// not in spectator mode
	OBS_MODE_DEATHCAM,		// special mode for death cam animation
	OBS_MODE_FREEZECAM,		// zooms to a target, and freeze-frames on them
	OBS_MODE_FIXED,			// view from a fixed camera position
	OBS_MODE_FIRSTPERSON,	// follow a player in first person view
	OBS_MODE_THIRDPERSON,	// follow a player in third person view
	OBS_MODE_ROAMING,		// free roaming
};

enum RenderGroup_t
{
	RENDER_GROUP_OPAQUE_STATIC_HUGE = 0,		// Huge static prop
	RENDER_GROUP_OPAQUE_ENTITY_HUGE = 1,		// Huge opaque entity
	RENDER_GROUP_OPAQUE_STATIC = RENDER_GROUP_OPAQUE_STATIC_HUGE + (4 - 1) * 2, //RENDER_GROUP_CFG_NUM_OPAQUE_ENT_BUCKETS = 4
	RENDER_GROUP_OPAQUE_ENTITY,					// Opaque entity (smallest size, or default)

	RENDER_GROUP_TRANSLUCENT_ENTITY,
	RENDER_GROUP_TWOPASS,						// Implied opaque and translucent in two passes
	RENDER_GROUP_VIEW_MODEL_OPAQUE,				// Solid weapon view models
	RENDER_GROUP_VIEW_MODEL_TRANSLUCENT,		// Transparent overlays etc

	RENDER_GROUP_OPAQUE_BRUSH,					// Brushes

	RENDER_GROUP_OTHER,							// Unclassfied. Won't get drawn.

	// This one's always gotta be last
	RENDER_GROUP_COUNT
};

enum EffectFlags_t
{
	EF_BONEMERGE = 0x1,
	EF_BRIGHTLIGHT = 0x2,
	EF_DIMLIGHT = 0x4,
	EF_NOSHADOW = 0x10,
	EF_NODRAW = 0x20,
	EF_BONEMERGE_FASTCULL = 0x80,
	EF_ITEM_BLINK = 0x100,
	EF_PARENT_ANIMATES = 0x200
};

struct PlayerInfo_t
{
	char			name[32];
	int				userID;
	char			guid[33];
	unsigned long	friendsID;
	char			friendsName[32];
	bool			fakeplayer;
	bool			ishltv;
	unsigned long	customFiles[4];
	unsigned char	filesDownloaded;
};

class CClientClass
{
private:
	char			_chPadding[8];
public:
	char *chName;
	void *Table; //RecvTable*
	CClientClass *pNextClass;
	int				iClassID;
};

class CUserCmd
{
public:
	virtual		~CUserCmd() {};
	int			command_number;
	int			tick_count;
	Vec3		viewangles;
	float		forwardmove;
	float		sidemove;
	float		upmove;
	int			buttons;
	byte		impulse;
	int			weaponselect;
	int			weaponsubtype;
	int			random_seed;
	short		mousedx;
	short		mousedy;
	bool		hasbeenpredicted;
};

class CMoveData
{
public:
	bool m_bFirstRunOfFunctions : 1;
	bool m_bGameCodeMovedPlayer : 1;

	void *m_nPlayerHandle; // edict index on server, client entity handle on client

	int    m_nImpulseCommand; // Impulse command issued.
	Vec3 m_vecViewAngles; // Command view angles (local space)
	Vec3 m_vecAbsViewAngles; // Command view angles (world space)
	int    m_nButtons; // Attack buttons.
	int    m_nOldButtons; // From host_client->oldbuttons;
	float  m_flForwardMove;
	float  m_flSideMove;
	float  m_flUpMove;

	float m_flMaxSpeed;
	float m_flClientMaxSpeed;

	// Variables from the player edict (sv_player) or entvars on the client.
	// These are copied in here before calling and copied out after calling.
	Vec3 m_vecVelocity; // edict::velocity		// Current movement direction.
	Vec3 m_vecAngles; // edict::angles
	Vec3 m_vecOldAngles;

	// Output only
	float  m_outStepHeight; // how much you climbed this move
	Vec3 m_outWishVel; // This is where you tried
	Vec3 m_outJumpVel; // This is your jump velocity

	// Movement constraints	(radius 0 means no constraint)
	Vec3 m_vecConstraintCenter;
	float  m_flConstraintRadius;
	float  m_flConstraintWidth;
	float  m_flConstraintSpeedFactor;

	void        SetAbsOrigin(const Vec3 &vec);
	const Vec3 &GetAbsOrigin() const;

	// private:
	Vec3 m_vecAbsOrigin; // edict::origin
};

struct mstudiobbox_t
{
	int	bone;
	int	group;
	Vec3 bbmin;
	Vec3 bbmax;
	int	szhitboxnameindex;
	int	unused[8];
};

struct mstudiohitboxset_t
{
	int					sznameindex;
	inline char *const	pszName(void) const { return ((char *)this) + sznameindex; }
	int					numhitboxes;
	int					hitboxindex;
	mstudiobbox_t *pHitbox(int i) const { return (mstudiobbox_t *)(((byte *)this) + hitboxindex) + i; };
};

struct mstudiobone_t
{
	int					sznameindex;
	inline char *const pszName(void) const { return ((char *)this) + sznameindex; }
	int		 			parent;
	int					bonecontroller[6];
	Vec3				pos;
	float				quat[4];
	Vec3				rot;
	Vec3				posscale;
	Vec3				rotscale;
	float				poseToBone[3][4];
	float				qAlignment[4];
	int					flags;
	int					proctype;
	int					procindex;
	mutable int			physicsbone;
	inline void *pProcedure() const { if (procindex == 0) return NULL; else return  (void *)(((byte *)this) + procindex); };
	int					surfacepropidx;
	inline char *const pszSurfaceProp(void) const { return ((char *)this) + surfacepropidx; }
	int					contents;
	int					unused[8];

	mstudiobone_t() {}
private:
	// No copy constructors allowed
	mstudiobone_t(const mstudiobone_t &vOther);
};

struct studiohdr_t
{
	int id;
	int version;
	int checksum;
	char name[64];
	int length;
	Vec3 eyeposition;
	Vec3 illumposition;
	Vec3 hull_min;
	Vec3 hull_max;
	Vec3 view_bbmin;
	Vec3 view_bbmax;
	int flags;
	int numbones;
	int boneindex;
	inline mstudiobone_t *GetBone(int i) const { return (mstudiobone_t *)(((byte *)this) + boneindex) + i; };

	int numbonecontrollers;
	int bonecontrollerindex;
	int numhitboxsets;
	int hitboxsetindex;

	mstudiohitboxset_t *GetHitboxSet(int i) const
	{
		return (mstudiohitboxset_t *)(((byte *)this) + hitboxsetindex) + i;
	}

	inline mstudiobbox_t *GetHitbox(int i, int set) const
	{
		mstudiohitboxset_t const *s = GetHitboxSet(set);

		if (!s)
			return NULL;

		return s->pHitbox(i);
	}

	inline int GetHitboxCount(int set) const
	{
		mstudiohitboxset_t const *s = GetHitboxSet(set);

		if (!s)
			return 0;

		return s->numhitboxes;
	}

	int numlocalanim;
	int localanimindex;
	int numlocalseq;
	int localseqindex;
	mutable int activitylistversion;
	mutable int eventsindexed;
	int numtextures;
	int textureindex;
	int numcdtextures;
	int cdtextureindex;
	int numskinref;
	int numskinfamilies;
	int skinindex;
	int numbodyparts;
	int bodypartindex;
	int numlocalattachments;
	int localattachmentindex;
	int numlocalnodes;
	int localnodeindex;
	int localnodenameindex;
	int numflexdesc;
	int flexdescindex;
	int numflexcontrollers;
	int flexcontrollerindex;
	int numflexrules;
	int flexruleindex;
	int numikchains;
	int ikchainindex;
	int nummouths;
	int mouthindex;
	int numlocalposeparameters;
	int localposeparamindex;
	int surfacepropindex;
	int keyvalueindex;
	int keyvaluesize;
	int numlocalikautoplaylocks;
	int localikautoplaylockindex;
	float mass;
	int contents;
	int numincludemodels;
	int includemodelindex;
	mutable void *virtualModel;
	int szanimblocknameindex;
	int numanimblocks;
	int animblockindex;
	mutable void *animblockModel;
	int bonetablebynameindex;
	void *pVertexBase;
	void *pIndexBase;
	byte constdirectionallightdot;
	byte rootLOD;
	byte numAllowedRootLODs;
	byte unused[1];
	int unused4;
	int numflexcontrollerui;
	int	flexcontrolleruiindex;
	float flVertAnimFixedPointScale;
	int	unused3[1];
	int	studiohdr2index;
	int	unused2[1];
};

enum WeaponProficiency_t
{
	WEAPON_PROFICIENCY_POOR = 0,
	WEAPON_PROFICIENCY_AVERAGE,
	WEAPON_PROFICIENCY_GOOD,
	WEAPON_PROFICIENCY_VERY_GOOD,
	WEAPON_PROFICIENCY_PERFECT,
};

struct WeaponProficiencyInfo_t
{
	float spreadscale;
	float bias;
};

// lower bits are stronger, and will eat weaker brushes completely
#define CONTENTS_EMPTY 0 // No contents

#define CONTENTS_SOLID 0x1  // an eye is never valid in a solid
#define CONTENTS_WINDOW 0x2 // translucent, but not watery (glass)
#define CONTENTS_AUX 0x4
#define CONTENTS_GRATE 0x8 // alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
#define CONTENTS_SLIME 0x10
#define CONTENTS_WATER 0x20
#define CONTENTS_BLOCKLOS 0x40 // block AI line of sight
#define CONTENTS_OPAQUE 0x80   // things that cannot be seen through (may be non-solid though)
#define LAST_VISIBLE_CONTENTS 0x80

#define ALL_VISIBLE_CONTENTS ( LAST_VISIBLE_CONTENTS | ( LAST_VISIBLE_CONTENTS - 1 ) )

#define CONTENTS_TESTFOGVOLUME 0x100
#define CONTENTS_UNUSED 0x200

// unused
// NOTE: If it's visible, grab from the top + update LAST_VISIBLE_CONTENTS
// if not visible, then grab from the bottom.
#define CONTENTS_UNUSED6 0x400

#define CONTENTS_TEAM1 0x800  // per team contents used to differentiate collisions
#define CONTENTS_TEAM2 0x1000 // between players and objects on different teams

// ignore CONTENTS_OPAQUE on surfaces that have SURF_NODRAW
#define CONTENTS_IGNORE_NODRAW_OPAQUE 0x2000

// hits entities which are MOVETYPE_PUSH (doors, plats, etc.)
#define CONTENTS_MOVEABLE 0x4000

// remaining contents are non-visible, and don't eat brushes
#define CONTENTS_AREAPORTAL 0x8000

#define CONTENTS_PLAYERCLIP 0x10000
#define CONTENTS_MONSTERCLIP 0x20000

// currents can be added to any other contents, and may be mixed
#define CONTENTS_CURRENT_0 0x40000
#define CONTENTS_CURRENT_90 0x80000
#define CONTENTS_CURRENT_180 0x100000
#define CONTENTS_CURRENT_270 0x200000
#define CONTENTS_CURRENT_UP 0x400000
#define CONTENTS_CURRENT_DOWN 0x800000

#define CONTENTS_ORIGIN 0x1000000 // removed before bsping an entity

#define CONTENTS_MONSTER 0x2000000 // should never be on a brush, only in game
#define CONTENTS_DEBRIS 0x4000000
#define CONTENTS_DETAIL 0x8000000		// brushes to be added after vis leafs
#define CONTENTS_TRANSLUCENT 0x10000000 // auto set if any surface has trans
#define CONTENTS_LADDER 0x20000000
#define CONTENTS_HITBOX 0x40000000 // use accurate hitboxes on trace

#define MASK_ALL ( 0xFFFFFFFF )
// everything that is normally solid
#define MASK_SOLID ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_MONSTER | CONTENTS_GRATE )
// everything that blocks player movement
#define MASK_PLAYERSOLID ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_PLAYERCLIP | CONTENTS_WINDOW | CONTENTS_MONSTER | CONTENTS_GRATE )
// blocks npc movement
#define MASK_NPCSOLID ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTERCLIP | CONTENTS_WINDOW | CONTENTS_MONSTER | CONTENTS_GRATE )
// water physics in these contents
#define MASK_WATER ( CONTENTS_WATER | CONTENTS_MOVEABLE | CONTENTS_SLIME )
// everything that blocks lighting
#define MASK_OPAQUE ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_OPAQUE )
// everything that blocks lighting, but with monsters added.
#define MASK_OPAQUE_AND_NPCS ( MASK_OPAQUE | CONTENTS_MONSTER )
// everything that blocks line of sight for AI
#define MASK_BLOCKLOS ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_BLOCKLOS )
// everything that blocks line of sight for AI plus NPCs
#define MASK_BLOCKLOS_AND_NPCS ( MASK_BLOCKLOS | CONTENTS_MONSTER )
// everything that blocks line of sight for players
#define MASK_VISIBLE ( MASK_OPAQUE | CONTENTS_IGNORE_NODRAW_OPAQUE )
// everything that blocks line of sight for players, but with monsters added.
#define MASK_VISIBLE_AND_NPCS ( MASK_OPAQUE_AND_NPCS | CONTENTS_IGNORE_NODRAW_OPAQUE )
// bullets see these as solid
#define MASK_SHOT ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_HITBOX )
// non-raycasted weapons see this as solid (includes grates)
#define MASK_SHOT_HULL ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_GRATE )
// hits solids (not grates) and passes through everything else
#define MASK_SHOT_PORTAL ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_MONSTER )
// everything normally solid, except monsters (world+brush only)
#define MASK_SOLID_BRUSHONLY ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_GRATE )
// everything normally solid for player movement, except monsters (world+brush only)
#define MASK_PLAYERSOLID_BRUSHONLY ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_PLAYERCLIP | CONTENTS_GRATE )
// everything normally solid for npc movement, except monsters (world+brush only)
#define MASK_NPCSOLID_BRUSHONLY ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_MONSTERCLIP | CONTENTS_GRATE )
// just the world, used for route rebuilding
#define MASK_NPCWORLDSTATIC ( CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_MONSTERCLIP | CONTENTS_GRATE )
// These are things that can split areaportals
#define MASK_SPLITAREAPORTAL ( CONTENTS_WATER | CONTENTS_SLIME )

// UNDONE: This is untested, any moving water
#define MASK_CURRENT ( CONTENTS_CURRENT_0 | CONTENTS_CURRENT_90 | CONTENTS_CURRENT_180 | CONTENTS_CURRENT_270 | CONTENTS_CURRENT_UP | CONTENTS_CURRENT_DOWN )

// everything that blocks corpse movement
// UNDONE: Not used yet / may be deleted
#define MASK_DEADSOLID ( CONTENTS_SOLID | CONTENTS_PLAYERCLIP | CONTENTS_WINDOW | CONTENTS_GRATE )

class __declspec(align(16))VectorAligned : public Vec3
{
public:
	inline VectorAligned(void)
	{

	};

	inline VectorAligned(float X, float Y, float Z)
	{
		Set(X, Y, Z);
	}

	explicit VectorAligned(const Vec3 &vOther)
	{
		Set(vOther.x, vOther.y, vOther.z);
	}

	VectorAligned &operator=(const Vec3 &vOther)
	{
		Set(vOther.x, vOther.y, vOther.z);
		return *this;
	}

	float w;
};

struct Ray_t
{
	VectorAligned m_Start;
	VectorAligned m_Delta;
	VectorAligned m_StartOffset;
	VectorAligned m_Extents;

	bool m_IsRay;
	bool m_IsSwept;

	void Init(Vec3 vStart, Vec3 vEnd)
	{
		m_Delta = vEnd - vStart;

		m_IsSwept = (m_Delta.LengthSqr() != 0);

		m_Extents.Set();
		m_IsRay = true;

		m_StartOffset.Set();
		m_Start = vStart;
	}

	void Init(Vec3 &vStart, Vec3 &vEnd, Vec3 &vMins, Vec3 &vMaxs)
	{
		m_Delta = vEnd - vStart;

		m_IsSwept = (m_Delta.LengthSqr() != 0);

		m_Extents = vMaxs - vMins;
		m_Extents *= 0.5f;
		m_IsRay = (m_Extents.LengthSqr() < 1e-6);

		m_StartOffset = vMins + vMaxs;

		m_StartOffset *= 0.5f;
		m_Start = vStart - m_StartOffset;
		m_StartOffset *= -1.0f;
	}
};

struct cplane_t
{
	Vec3 normal;
	float dist;
	BYTE type;
	BYTE signbits;
	BYTE pad[2];
};

struct csurface_t
{
	const char *name;
	short surfaceProps;
	unsigned short flags;
};

enum SurfaceFlags_t
{
	DISPSURF_FLAG_SURFACE = (1 << 0),
	DISPSURF_FLAG_WALKABLE = (1 << 1),
	DISPSURF_FLAG_BUILDABLE = (1 << 2),
	DISPSURF_FLAG_SURFPROP1 = (1 << 3),
	DISPSURF_FLAG_SURFPROP2 = (1 << 4),
};

enum TraceType_t
{
	TRACE_EVERYTHING,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS,
};

class ITraceFilter
{
public:
	virtual bool ShouldHitEntity(void *pEntity, int contentsMask) = 0;
	virtual TraceType_t	GetTraceType() const = 0;
};

class CBaseTrace
{
public:
	bool IsDispSurface(void) { return ((dispFlags & DISPSURF_FLAG_SURFACE) != 0); }
	bool IsDispSurfaceWalkable(void) { return ((dispFlags & DISPSURF_FLAG_WALKABLE) != 0); }
	bool IsDispSurfaceBuildable(void) { return ((dispFlags & DISPSURF_FLAG_BUILDABLE) != 0); }
	bool IsDispSurfaceProp1(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP1) != 0); }
	bool IsDispSurfaceProp2(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP2) != 0); }

public:
	Vec3			startpos;
	Vec3			endpos;
	cplane_t		plane;
	float			fraction;
	int				contents;
	unsigned short	dispFlags;
	bool			allsolid;
	bool			startsolid;

	CBaseTrace()
	{

	}

private:
	CBaseTrace(const CBaseTrace &vOther);
};

class CGameTrace : public CBaseTrace
{
public:
	bool DidHitWorld() const;
	bool DidHitNonWorldEntity() const;
	int GetEntityIndex() const;

	bool DidHit() const {
		return (fraction < 1 || allsolid || startsolid);
	}

public:
	float			fractionleftsolid;
	csurface_t		surface;
	int				hitgroup;
	short			physicsbone;
	CBaseEntity		*m_pEnt;
	int				hitbox;

	CGameTrace() { }
	CGameTrace(const CGameTrace &vOther);
};

//material stuff for chams mostly

class IMaterialVar;
using VertexFormat_t = unsigned __int64;
using ModelInstanceHandle_t = int;
using MaterialHandle_t = unsigned short;
struct model_t;
struct VisibleFogVolumeInfo_t;
struct VisOverrideData_t;
struct WorldListInfo_t;
class IWorldRenderList;
class IBrushRenderer;
class IClientRenderable;
class IFileSystem;
struct studiohwdata_t;

enum MaterialVarFlags_t
{
	MATERIAL_VAR_DEBUG = (1 << 0),
	MATERIAL_VAR_NO_DEBUG_OVERRIDE = (1 << 1),
	MATERIAL_VAR_NO_DRAW = (1 << 2),
	MATERIAL_VAR_USE_IN_FILLRATE_MODE = (1 << 3),
	MATERIAL_VAR_VERTEXCOLOR = (1 << 4),
	MATERIAL_VAR_VERTEXALPHA = (1 << 5),
	MATERIAL_VAR_SELFILLUM = (1 << 6),
	MATERIAL_VAR_ADDITIVE = (1 << 7),
	MATERIAL_VAR_ALPHATEST = (1 << 8),
	MATERIAL_VAR_ZNEARER = (1 << 10),
	MATERIAL_VAR_MODEL = (1 << 11),
	MATERIAL_VAR_FLAT = (1 << 12),
	MATERIAL_VAR_NOCULL = (1 << 13),
	MATERIAL_VAR_NOFOG = (1 << 14),
	MATERIAL_VAR_IGNOREZ = (1 << 15),
	MATERIAL_VAR_DECAL = (1 << 16),
	MATERIAL_VAR_ENVMAPSPHERE = (1 << 17),
	// OBSOLETE
	MATERIAL_VAR_ENVMAPCAMERASPACE = (1 << 19),
	// OBSOLETE
	MATERIAL_VAR_BASEALPHAENVMAPMASK = (1 << 20),
	MATERIAL_VAR_TRANSLUCENT = (1 << 21),
	MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
	MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = (1 << 23),
	// OBSOLETE
	MATERIAL_VAR_OPAQUETEXTURE = (1 << 24),
	MATERIAL_VAR_ENVMAPMODE = (1 << 25),
	// OBSOLETE
	MATERIAL_VAR_SUPPRESS_DECALS = (1 << 26),
	MATERIAL_VAR_HALFLAMBERT = (1 << 27),
	MATERIAL_VAR_WIREFRAME = (1 << 28),
	MATERIAL_VAR_ALLOWALPHATOCOVERAGE = (1 << 29),
	MATERIAL_VAR_ALPHA_MODIFIED_BY_PROXY = (1 << 30),
	MATERIAL_VAR_VERTEXFOG = (1 << 31),
};

enum MaterialPropertyTypes_t 
{
	MATERIAL_PROPERTY_NEEDS_LIGHTMAP = 0,
	// bool
	MATERIAL_PROPERTY_OPACITY,
	// int (enum MaterialPropertyOpacityTypes_t)
	MATERIAL_PROPERTY_REFLECTIVITY,
	// vec3_t
	MATERIAL_PROPERTY_NEEDS_BUMPED_LIGHTMAPS // bool
};

enum OverrideType_t
{
	OVERRIDE_NORMAL = 0,
	OVERRIDE_BUILD_SHADOWS,
	OVERRIDE_DEPTH_WRITE,
	OVERRIDE_SSAO_DEPTH_WRITE,
};

struct ModelRenderInfo_t
{
	Vec3 origin;
	Vec3 angles;
	PVOID *pRenderable;
	const DWORD *pModel;
	const matrix3x4 *pModelToWorld;
	const matrix3x4 *pLightingOffset;
	const Vec3 *pLightingOrigin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitboxset;
	ModelInstanceHandle_t instance;

	ModelRenderInfo_t() {
		pModelToWorld = nullptr;
		pLightingOffset = nullptr;
		pLightingOrigin = nullptr;
	}
};

struct DrawModelState_t
{
	studiohdr_t *m_pStudioHdr;
	studiohwdata_t *m_pStudioHWData;
	IClientRenderable *m_pRenderable;
	const matrix3x4 *m_pModelToWorld;
	void *m_decals;
	int	m_drawFlags;
	int	m_lod;
};

#define DMG_AIRBOAT	(1 << 25)
#define DMG_USE_HITLOCATIONS (DMG_AIRBOAT)

#define END_OF_FREE_LIST	-1
#define ENTRY_IN_USE		-2

struct GlowObjectDefinition_t {
	int			m_hEntity;
	Vec3		m_vGlowColor;
	float		m_flGlowAlpha;
	bool		m_bRenderWhenOccluded;
	bool		m_bRenderWhenUnoccluded;
	int			m_nSplitScreenSlot;
	int			m_nNextFreeSlot;
};

class ConVar;
class IConVar;
class CCommand;
class ConCommand;
class ConCommandBase;

enum class ConvarFlags
{
	// The default, no flags at all
	FCVAR_NONE = 0,

	// Command to ConVars and ConCommands
	// ConVar Systems
	FCVAR_UNREGISTERED = (1 << 0), // If this is set, don't add to linked list, etc.
	FCVAR_DEVELOPMENTONLY = (1 << 1), // Hidden in released products. Flag is removed automatically if ALLOW_DEVELOPMENT_CVARS is defined.
	FCVAR_GAMEDLL = (1 << 2), // defined by the game DLL
	FCVAR_CLIENTDLL = (1 << 3), // defined by the client DLL
	FCVAR_HIDDEN = (1 << 4), // Hidden. Doesn't appear in find or autocomplete. Like DEVELOPMENTONLY, but can't be compiled out.

							 // ConVar only
	FCVAR_PROTECTED = (1 << 5),  // It's a server cvar, but we don't send the data since it's a password, etc.  Sends 1 if it's not bland/zero, 0 otherwise as value
	FCVAR_SPONLY = (1 << 6),  // This cvar cannot be changed by clients connected to a multiplayer server.
	FCVAR_ARCHIVE = (1 << 7),  // set to cause it to be saved to vars.rc
	FCVAR_NOTIFY = (1 << 8),  // notifies players when changed
	FCVAR_USERINFO = (1 << 9),  // changes the client's info string
	FCVAR_CHEAT = (1 << 14), // Only useable in singleplayer / debug / multiplayer & sv_cheats

	FCVAR_PRINTABLEONLY = (1 << 10), // This cvar's string cannot contain unprintable characters ( e.g., used for player name etc ).
	FCVAR_UNLOGGED = (1 << 11), // If this is a FCVAR_SERVER, don't log changes to the log file / console if we are creating a log
	FCVAR_NEVER_AS_STRING = (1 << 12), // never try to print that cvar

									   // It's a ConVar that's shared between the client and the server.
									   // At signon, the values of all such ConVars are sent from the server to the client (skipped for local
									   //  client, of course )
									   // If a change is requested it must come from the console (i.e., no remote client changes)
									   // If a value is changed while a server is active, it's replicated to all connected clients
	FCVAR_REPLICATED = (1 << 13), // server setting enforced on clients, TODO rename to FCAR_SERVER at some time
	FCVAR_DEMO = (1 << 16), // record this cvar when starting a demo file
	FCVAR_DONTRECORD = (1 << 17), // don't record these command in demofiles
	FCVAR_RELOAD_MATERIALS = (1 << 20), // If this cvar changes, it forces a material reload
	FCVAR_RELOAD_TEXTURES = (1 << 21), // If this cvar changes, if forces a texture reload

	FCVAR_NOT_CONNECTED = (1 << 22), // cvar cannot be changed by a client that is connected to a server
	FCVAR_MATERIAL_SYSTEM_THREAD = (1 << 23), // Indicates this cvar is read from the material system thread
	FCVAR_ARCHIVE_XBOX = (1 << 24), // cvar written to config.cfg on the Xbox

	FCVAR_ACCESSIBLE_FROM_THREADS = (1 << 25), // used as a debugging tool necessary to check material system thread convars

	FCVAR_SERVER_CAN_EXECUTE = (1 << 28), // the server is allowed to execute this command on clients via ClientCommand/NET_StringCmd/CBaseClientState::ProcessStringCmd.
	FCVAR_SERVER_CANNOT_QUERY = (1 << 29), // If this is set, then the server is not allowed to query this cvar's value (via IServerPluginHelpers::StartQueryCvarValue).
	FCVAR_CLIENTCMD_CAN_EXECUTE = (1 << 30), // IVEngineClient::ClientCmd is allowed to execute this command.

	FCVAR_MATERIAL_THREAD_MASK = (FCVAR_RELOAD_MATERIALS | FCVAR_RELOAD_TEXTURES | FCVAR_MATERIAL_SYSTEM_THREAD)
};

#define MAX_FLOWS 2 // in & out
#define MAX_STREAMS 2
#define MAX_OSPATH 260
#define SUBCHANNEL_FREE 0
#define FLOW_OUTGOING 0
#define FLOW_INCOMING 1

class INetMessage;
class INetChannelHandler;
typedef void *FileHandle_t;

typedef struct netadr_s
{
public:
	netadr_s()
	{
		SetIP(0);
		SetPort(0);
		//SetType(NA_IP);
	}

	netadr_s(const char *pch)
	{
		SetFromString(pch);
	}

	void Clear(); // invalids Address

				  //void SetType(netadrtype_t type);
	void SetPort(unsigned short port);
	bool SetFromSockadr(const struct sockaddr *s);
	void SetIP(unsigned int unIP); // Sets IP.  unIP is in host order (little-endian)
	void SetIPAndPort(unsigned int unIP, unsigned short usPort)
	{
		SetIP(unIP);
		SetPort(usPort);
	}
	void SetFromString(const char *pch, bool bUseDNS = false); // if bUseDNS is true then do a DNS lookup if needed

	bool CompareAdr(const netadr_s &a, bool onlyBase = false) const;
	bool CompareClassBAdr(const netadr_s &a) const;
	bool CompareClassCAdr(const netadr_s &a) const;

	//netadrtype_t GetType() const;
	unsigned short GetPort() const;
	const char *ToString(bool onlyBase = false) const; // returns xxx.xxx.xxx.xxx:ppppp
	void ToSockadr(struct sockaddr *s) const;
	unsigned int GetIP() const;

	bool IsLocalhost() const;   // true, if this is the localhost IP
	bool IsLoopback() const;	// true if engine loopback buffers are used
	bool IsReservedAdr() const; // true, if this is a private LAN IP
	bool IsValid() const;		// ip & port != 0
	void SetFromSocket(int hSocket);
	// These function names are decorated because the Xbox360 defines macros for ntohl and htonl
	unsigned long addr_ntohl() const;
	unsigned long addr_htonl() const;
	bool operator==(const netadr_s &netadr) const
	{
		return (CompareAdr(netadr));
	}
	bool operator<(const netadr_s &netadr) const;

public: // members are public to avoid to much changes
		//netadrtype_t type;
	unsigned char ip[4];
	unsigned short port;
} netadr_t;

#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / gInts.Globals->interval_per_tick ) )
#define TICKS_TO_TIME( t )		( gInts.Globals->interval_per_tick *( t ) )

#define MAX_WEAPON_STRING		80
#define MAX_WEAPON_PREFIX		16
#define MAX_WEAPON_AMMO_NAME	32

typedef enum {
	EMPTY,
	SINGLE,
	SINGLE_NPC,
	WPN_DOUBLE,
	DOUBLE_NPC,
	BURST,
	RELOAD,
	RELOAD_NPC,
	MELEE_MISS,
	MELEE_HIT,
	MELEE_HIT_WORLD,
	SPECIAL1,
	SPECIAL2,
	SPECIAL3,
	TAUNT,
	DEPLOY,
	NUM_SHOOT_SOUND_TYPES
} WeaponSound_t;

struct WeaponData_t {
	int			m_nDamage;
	int			m_nBulletsPerShot;
	float		m_flRange;
	float		m_flSpread;
	float		m_flPunchAngle;
	float		m_flTimeFireDelay;		// Time to delay between firing
	float		m_flTimeIdle;			// Time to idle after firing
	float		m_flTimeIdleEmpty;		// Time to idle after firing last bullet in clip
	float		m_flTimeReloadStart;	// Time to start into a reload (ie. shotgun)
	float		m_flTimeReload;			// Time to reload
	bool		m_bDrawCrosshair;		// Should the weapon draw a crosshair
	int			m_iProjectile;			// The type of projectile this mode fires
	int			m_iAmmoPerShot;			// How much ammo each shot consumes
	float		m_flProjectileSpeed;	// Start speed for projectiles (nail, etc.); NOTE: union with something non-projectile
	float		m_flSmackDelay;			// how long after swing should damage happen for melee weapons
	bool		m_bUseRapidFireCrits;
};

class FileWeaponInfo_t {
public:
	FileWeaponInfo_t();
	virtual void Parse(void *pKeyValuesData, const char *szWeaponName);

public:
	bool	bParsedScript;
	bool	bLoadedHudElements;		 
	char	szClassName[MAX_WEAPON_STRING];
	char	szPrintName[MAX_WEAPON_STRING];
	char	szViewModel[MAX_WEAPON_STRING];
	char	szWorldModel[MAX_WEAPON_STRING];
	char	szAnimationPrefix[MAX_WEAPON_PREFIX];
	int		iSlot;
	int		iPosition;
	int		iMaxClip1;
	int		iMaxClip2;
	int		iDefaultClip1;
	int		iDefaultClip2;
	int		iWeight;
	int		iRumbleEffect;
	bool	bAutoSwitchTo;
	bool	bAutoSwitchFrom;
	int		iFlags;
	char	szAmmo1[MAX_WEAPON_AMMO_NAME];
	char	szAmmo2[MAX_WEAPON_AMMO_NAME];
	char	aShootSounds[NUM_SHOOT_SOUND_TYPES][MAX_WEAPON_STRING];
	int		iAmmoType;
	int		iAmmo2Type;
	bool	m_bMeleeWeapon;
	bool	m_bBuiltRightHanded;
	bool	m_bAllowFlipping;
	int		iSpriteCount;
	void	*iconActive;
	void	*iconInactive;
	void	*iconAmmo;
	void	*iconAmmo2;
	void	*iconCrosshair;
	void	*iconAutoaim;
	void	*iconZoomedCrosshair;
	void	*iconZoomedAutoaim;
	void	*iconSmall;
	bool	bShowUsageHint;
};

class CTFWeaponInfo : public FileWeaponInfo_t {
public:
	CTFWeaponInfo();
	~CTFWeaponInfo();

	virtual void Parse(void *pKeyValuesData, const char *szWeaponName);

	WeaponData_t const &GetWeaponData(int iWeapon) const { return m_WeaponData[iWeapon]; }

public:
	WeaponData_t	m_WeaponData[2];
	int				m_iWeaponType;
	bool			m_bGrenade;
	float			m_flDamageRadius;
	float			m_flPrimerTime;
	bool			m_bLowerWeapon;
	bool			m_bSuppressGrenTimer;
	bool			m_bHasTeamSkins_Viewmodel;
	bool			m_bHasTeamSkins_Worldmodel;
	char			m_szMuzzleFlashModel[128];
	float			m_flMuzzleFlashModelDuration;
	char			m_szMuzzleFlashParticleEffect[128];
	char			m_szTracerEffect[128];
	bool			m_bDoInstantEjectBrass;
	char			m_szBrassModel[128];
	char			m_szExplosionSound[128];
	char			m_szExplosionEffect[128];
	char			m_szExplosionPlayerEffect[128];
	char			m_szExplosionWaterEffect[128];
	bool			m_bDontDrop;
};

enum ETFWeaponType {
	TF_WEAPON_NONE = 0,
	TF_WEAPON_BAT,
	TF_WEAPON_BAT_WOOD,
	TF_WEAPON_BOTTLE,
	TF_WEAPON_FIREAXE,
	TF_WEAPON_CLUB,
	TF_WEAPON_CROWBAR,
	TF_WEAPON_KNIFE,
	TF_WEAPON_FISTS,
	TF_WEAPON_SHOVEL,
	TF_WEAPON_WRENCH,
	TF_WEAPON_BONESAW,
	TF_WEAPON_SHOTGUN_PRIMARY,
	TF_WEAPON_SHOTGUN_SOLDIER,
	TF_WEAPON_SHOTGUN_HWG,
	TF_WEAPON_SHOTGUN_PYRO,
	TF_WEAPON_SCATTERGUN,
	TF_WEAPON_SNIPERRIFLE,
	TF_WEAPON_MINIGUN,
	TF_WEAPON_SMG,
	TF_WEAPON_SYRINGEGUN_MEDIC,
	TF_WEAPON_TRANQ,
	TF_WEAPON_ROCKETLAUNCHER,
	TF_WEAPON_GRENADELAUNCHER,
	TF_WEAPON_PIPEBOMBLAUNCHER,
	TF_WEAPON_FLAMETHROWER,
	TF_WEAPON_GRENADE_NORMAL,
	TF_WEAPON_GRENADE_CONCUSSION,
	TF_WEAPON_GRENADE_NAIL,
	TF_WEAPON_GRENADE_MIRV,
	TF_WEAPON_GRENADE_MIRV_DEMOMAN,
	TF_WEAPON_GRENADE_NAPALM,
	TF_WEAPON_GRENADE_GAS,
	TF_WEAPON_GRENADE_EMP,
	TF_WEAPON_GRENADE_CALTROP,
	TF_WEAPON_GRENADE_PIPEBOMB,
	TF_WEAPON_GRENADE_SMOKE_BOMB,
	TF_WEAPON_GRENADE_HEAL,
	TF_WEAPON_GRENADE_STUNBALL,
	TF_WEAPON_GRENADE_JAR,
	TF_WEAPON_GRENADE_JAR_MILK,
	TF_WEAPON_PISTOL,
	TF_WEAPON_PISTOL_SCOUT,
	TF_WEAPON_REVOLVER,
	TF_WEAPON_NAILGUN,
	TF_WEAPON_PDA,
	TF_WEAPON_PDA_ENGINEER_BUILD,
	TF_WEAPON_PDA_ENGINEER_DESTROY,
	TF_WEAPON_PDA_SPY,
	TF_WEAPON_BUILDER,
	TF_WEAPON_MEDIGUN,
	TF_WEAPON_GRENADE_MIRVBOMB,
	TF_WEAPON_FLAMETHROWER_ROCKET,
	TF_WEAPON_GRENADE_DEMOMAN,
	TF_WEAPON_SENTRY_BULLET,
	TF_WEAPON_SENTRY_ROCKET,
	TF_WEAPON_DISPENSER,
	TF_WEAPON_INVIS,
	TF_WEAPON_FLAREGUN,
	TF_WEAPON_LUNCHBOX,
	TF_WEAPON_JAR,
	TF_WEAPON_COMPOUND_BOW,
	TF_WEAPON_BUFF_ITEM,
	TF_WEAPON_PUMPKIN_BOMB,
	TF_WEAPON_SWORD,
	TF_WEAPON_ROCKETLAUNCHER_DIRECTHIT,
	TF_WEAPON_LIFELINE,
	TF_WEAPON_LASER_POINTER,
	TF_WEAPON_DISPENSER_GUN,
	TF_WEAPON_SENTRY_REVENGE,
	TF_WEAPON_JAR_MILK,
	TF_WEAPON_HANDGUN_SCOUT_PRIMARY,
	TF_WEAPON_BAT_FISH,
	TF_WEAPON_CROSSBOW,
	TF_WEAPON_STICKBOMB,
	TF_WEAPON_HANDGUN_SCOUT_SECONDARY,
	TF_WEAPON_SODA_POPPER,
	TF_WEAPON_SNIPERRIFLE_DECAP,
	TF_WEAPON_RAYGUN,
	TF_WEAPON_PARTICLE_CANNON,
	TF_WEAPON_MECHANICAL_ARM,
	TF_WEAPON_DRG_POMSON,
	TF_WEAPON_BAT_GIFTWRAP,
	TF_WEAPON_GRENADE_ORNAMENT_BALL,
	TF_WEAPON_FLAREGUN_REVENGE,
	TF_WEAPON_PEP_BRAWLER_BLASTER,
	TF_WEAPON_CLEAVER,
	TF_WEAPON_GRENADE_CLEAVER,
	TF_WEAPON_STICKY_BALL_LAUNCHER,
	TF_WEAPON_GRENADE_STICKY_BALL,
	TF_WEAPON_SHOTGUN_BUILDING_RESCUE,
	TF_WEAPON_CANNON,
	TF_WEAPON_THROWABLE,
	TF_WEAPON_GRENADE_THROWABLE,
	TF_WEAPON_PDA_SPY_BUILD,
	TF_WEAPON_GRENADE_WATERBALLOON,
	TF_WEAPON_HARVESTER_SAW,
	TF_WEAPON_SPELLBOOK,
	TF_WEAPON_SPELLBOOK_PROJECTILE,
	TF_WEAPON_SNIPERRIFLE_CLASSIC,
	TF_WEAPON_PARACHUTE,
	TF_WEAPON_GRAPPLINGHOOK,
	TF_WEAPON_PASSTIME_GUN,
#ifdef STAGING_ONLY
	TF_WEAPON_SNIPERRIFLE_REVOLVER,
#endif
	TF_WEAPON_COUNT
};

#define TF_WEAPON_PRIMARY_MODE      0
#define TF_WEAPON_SECONDARY_MODE    1