#include "SDK.h"

//-------------------------------------------------- CBaseEntity

Vec3 CBaseEntity::GetViewOffset()
{
	DYNVAR_RETURN(Vec3, this, "DT_BasePlayer", "localdata", "m_vecViewOffset[0]");
}

CUserCmd *CBaseEntity::GetCurrentCommand()
{
	DYNVAR_RETURN(CUserCmd *, (this - 0x4), "DT_BasePlayer", "localdata", "m_hConstraintEntity");
}

void CBaseEntity::SetCurrentCmd(CUserCmd *cmd)
{
	DYNVAR_SET(CUserCmd *, (this - 0x4), cmd, "DT_BasePlayer", "localdata", "m_hConstraintEntity");
}

Vec3 CBaseEntity::GetVecOrigin()
{
	DYNVAR_RETURN(Vec3, this, "DT_BaseEntity", "m_vecOrigin");
}

void CBaseEntity::SetVecOrigin(Vec3 &vOrigin)
{
	DYNVAR_SET(Vec3, this, vOrigin, "DT_BaseEntity", "m_vecOrigin");
}

Vec3 &CBaseEntity::GetAbsOrigin()
{
	typedef Vec3 &(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 9)(this);
}

Vec3 &CBaseEntity::GetShootPos()
{
	static auto Weapon_ShootPositionFn = reinterpret_cast<float *(__thiscall *)(PVOID, Vec3 *)>(
		gPattern.FindInClient("55 8B EC 56 8B 75 08 57 8B F9 56 8B 07 FF 90")); //this is ripped straight out of csgo x)

	Vec3 vOut;
	Weapon_ShootPositionFn(this, &vOut);

	return vOut;
}

const char *CBaseEntity::GetModelName()
{
	return gInts.ModelInfo->GetModelName(this->GetModel());
}

int CBaseEntity::GetAmmo()
{
	DYNVAR_RETURN(int, (this + 4), "DT_BasePlayer", "localdata", "m_iAmmo");
}

bool CBaseEntity::IsBaseCombatWeapon()
{
	typedef bool(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 137)(this);
}

bool CBaseEntity::IsWearable()
{
	typedef bool(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 138)(this);
}

int CBaseEntity::GetHitboxSet()
{
	DYNVAR_RETURN(int, this, "DT_BaseAnimating", "m_nHitboxSet");
}

int CBaseEntity::GetTickBase()
{
	DYNVAR_RETURN(int, this, "DT_BasePlayer", "localdata", "m_nTickBase");
}

void CBaseEntity::IncreaseTickBase()
{
	static CDynamicNetvar<int>n("DT_BasePlayer", "localdata", "m_nTickBase");
	n.SetValue(this, n.GetValue(this) + 1);
}

float CBaseEntity::flSimulationTime()
{
	DYNVAR_RETURN(float, this, "DT_BaseEntity", "m_flSimulationTime");
}

int CBaseEntity::GetOwner()
{
	DYNVAR_RETURN(int, this, "DT_BaseEntity", "m_hOwnerEntity");
}

Vec3 &CBaseEntity::GetAbsAngles()
{
	typedef Vec3 &(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 10)(this);
}

Vec3 CBaseEntity::GetWorldSpaceCenter()
{
	Vec3 vMin, vMax;

	this->GetRenderBounds(vMin, vMax);
	Vec3 vWorldSpaceCenter = this->GetAbsOrigin();
	vWorldSpaceCenter.z += (vMin.z + vMax.z) / 2.0f;

	return vWorldSpaceCenter;
}

DWORD *CBaseEntity::GetModel()
{
	PVOID pRenderable = (PVOID)(this + 0x4);
	typedef DWORD *(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(pRenderable, 9)(pRenderable);
}

int CBaseEntity::DrawModel(int flags)
{
	void *renderable = (PVOID)(this + 0x4);
	typedef int(__thiscall *FN)(PVOID, int);
	return GetVFunc<FN>(renderable, 10)(renderable, flags);
}

bool CBaseEntity::SetupBones(matrix3x4 *pBoneToWorldOut, int nMaxBones, int nBoneMask, float fCurrentTime)
{
	PVOID pRenderable = (PVOID)(this + 0x4);
	typedef bool(__thiscall *FN)(PVOID, matrix3x4 *, int, int, float);
	return GetVFunc<FN>(pRenderable, 16)(pRenderable, pBoneToWorldOut, nMaxBones, nBoneMask, fCurrentTime);
}

CClientClass *CBaseEntity::GetClientClass()
{
	PVOID pNetworkable = (PVOID)(this + 0x8);
	typedef CClientClass *(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(pNetworkable, 2)(pNetworkable);
}

bool CBaseEntity::IsDormant()
{
	PVOID pNetworkable = (PVOID)(this + 0x8);
	typedef bool(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(pNetworkable, 8)(pNetworkable);
}

int CBaseEntity::GetIndex()
{
	PVOID pNetworkable = (PVOID)(this + 0x8);
	typedef int(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(pNetworkable, 9)(pNetworkable);
}

void CBaseEntity::GetRenderBounds(Vec3 &vMins, Vec3 &vMaxs)
{
	PVOID pRenderable = (PVOID)(this + 0x4);
	typedef void(__thiscall *FN)(PVOID, Vec3 &, Vec3 &);
	GetVFunc<FN>(pRenderable, 20)(pRenderable, vMins, vMaxs);
}

matrix3x4 &CBaseEntity::GetRgflCoordinateFrame()
{
	PVOID pRenderable = (PVOID)(this + 0x4);
	typedef matrix3x4 &(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(pRenderable, 34)(pRenderable);
}

Vec3 CBaseEntity::GetVelocity()
{
	typedef void(__thiscall *EstimateAbsVelocityFn)(CBaseEntity *, Vec3 &);
	static DWORD dwFn = gPattern.FindInClient("E8 ? ? ? ? F3 0F 10 4D ? 8D 85 ? ? ? ? F3 0F 10 45 ? F3 0F 59 C9 56 F3 0F 59 C0 F3 0F 58 C8 0F 2F 0D ? ? ? ? 76 07") + 0x1;
	static DWORD dwEstimate = ((*(PDWORD)(dwFn)) + dwFn + 0x4);
	EstimateAbsVelocityFn vel = (EstimateAbsVelocityFn)dwEstimate;
	Vec3 v;
	vel(this, v);
	return v;
}

int CBaseEntity::GetMaxHealth()
{
	typedef int(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 107)(this);
}

int CBaseEntity::GetHealth()
{
	DYNVAR_RETURN(int, this, "DT_BasePlayer", "m_iHealth");
}

int CBaseEntity::GetTeamNum()
{
	DYNVAR_RETURN(int, this, "DT_BaseEntity", "m_iTeamNum");
}

int CBaseEntity::GetFlags()
{
	DYNVAR_RETURN(int, this, "DT_BasePlayer", "m_fFlags");
}

void CBaseEntity::SetFlags(int nFlags)
{
	DYNVAR_SET(int, this, nFlags, "DT_BasePlayer", "m_fFlags");
}

BYTE CBaseEntity::GetLifeState()
{
	DYNVAR_RETURN(BYTE, this, "DT_BasePlayer", "m_lifeState");
}

int CBaseEntity::GetClassId()
{
	return this->GetClientClass()->iClassID;
}

int CBaseEntity::GetClassNum()
{
	DYNVAR_RETURN(int, this, "DT_TFPlayer", "m_PlayerClass", "m_iClass");
}

const char *CBaseEntity::szGetClass()
{
	int nClassNum = this->GetClassNum();

	switch (nClassNum)
	{
		case TF2_Scout:
			return "scout";

		case TF2_Soldier:
			return "soldier";

		case TF2_Pyro:
			return "pyro";

		case TF2_Demoman:
			return "demoman";

		case TF2_Heavy:
			return "heavy";

		case TF2_Engineer:
			return "engineer";

		case TF2_Medic:
			return "medic";

		case TF2_Sniper:
			return "sniper";

		case TF2_Spy:
			return "spy";

		default: return "unknown";
	}
}

int CBaseEntity::GetCond()
{
	DYNVAR_RETURN(int, this, "DT_TFPlayer", "m_Shared", "m_nPlayerCond");
}

int CBaseEntity::GetCondEx()
{
	DYNVAR_RETURN(int, this, "DT_TFPlayer", "m_Shared", "m_nPlayerCondEx");
}

void CBaseEntity::RemoveCond(int cond)
{
	static DWORD offset = gNetVars.get_offset("DT_TFPlayer", "m_Shared", "m_nPlayerCond");

	if (*reinterpret_cast<int *>(this + offset) & cond)
		*reinterpret_cast<DWORD *>(this + offset) &= ~cond;
}

Vec3 CBaseEntity::GetCollideableMins()
{
	DYNVAR_RETURN(Vec3, this, "DT_BaseEntity", "m_Collision", "m_vecMins");
}

Vec3 CBaseEntity::GetCollideableMaxs()
{
	DYNVAR_RETURN(Vec3, this, "DT_BaseEntity", "m_Collision", "m_vecMaxs");
}

Vec3 CBaseEntity::GetEyeAngles()
{
	DYNVAR_RETURN(Vec3, this, "DT_TFPlayer", "tfnonlocaldata", "m_angEyeAngles[0]");
}

void CBaseEntity::SetEyeAngles(Vec3 &v)
{
	DYNVAR(n, Vec3, "DT_TFPlayer", "tfnonlocaldata", "m_angEyeAngles[0]");
	n.SetValue(this, v);
}

byte CBaseEntity::GetWaterLevel()
{
	DYNVAR_RETURN(byte, this, "DT_TFPlayer", "m_nWaterLevel");
}

bool CBaseEntity::IsOnGround()
{
	return (this->GetFlags() & FL_ONGROUND);
}

bool CBaseEntity::IsInWater()
{
	return (this->GetFlags() & FL_INWATER); //it's better to use IsSwimming method cuz this one doesn't work iirc.
}

bool CBaseEntity::IsSwimming()
{
	return (this->GetWaterLevel() > 1);
}

Vec3 CBaseEntity::GetHitboxPos(int nHitbox)
{
	DWORD *pModel = GetModel();
	if (!pModel)
		return Vec3();

	studiohdr_t *pHdr = (studiohdr_t *)gInts.ModelInfo->GetStudioModel(pModel);
	if (!pHdr)
		return Vec3();

	matrix3x4 BoneMatrix[128];
	if (!this->SetupBones(BoneMatrix, 128, 0x100, gInts.Globals->curtime))
		return Vec3();

	mstudiohitboxset_t *pSet = pHdr->GetHitboxSet(this->GetHitboxSet());
	if (!pSet)
		return Vec3();

	mstudiobbox_t *pBox = pSet->pHitbox(nHitbox);
	if (!pBox)
		return Vec3();

	Vec3 vPos = (pBox->bbmin + pBox->bbmax) * 0.5f;
	Vec3 vOut = Vec3();

	Math::VectorTransform(vPos, BoneMatrix[pBox->bone], vOut);

	return vOut;
}

int CBaseEntity::GetNumOfHitboxes()
{
	DWORD *pModel = GetModel();
	if (!pModel)
		return 0;

	studiohdr_t *pHdr = (studiohdr_t *)gInts.ModelInfo->GetStudioModel(pModel);
	if (!pHdr)
		return 0;

	mstudiohitboxset_t *pSet = pHdr->GetHitboxSet(this->GetHitboxSet());
	if (!pSet)
		return 0;

	return pSet->numhitboxes;
}

Vec3 CBaseEntity::GetBonePos(int nBone)
{
	matrix3x4 matrix[128];

	if (this->SetupBones(matrix, 128, 0x100, GetTickCount64()))
		return Vec3(matrix[nBone][0][3], matrix[nBone][1][3], matrix[nBone][2][3]);

	return Vec3(0.0f, 0.0f, 0.0f);
}

CBaseCombatWeapon *CBaseEntity::GetActiveWeapon()
{
	DYNVAR(pHandle, int, "DT_BaseCombatCharacter", "m_hActiveWeapon");
	return reinterpret_cast<CBaseCombatWeapon *>(gInts.EntityList->GetClientEntityFromHandle(pHandle.GetValue(this)));
}

void CBaseEntity::ForceTauntCam(bool b)
{
	DYNVAR_SET(bool, this, b, "DT_TFPlayer", "m_nForceTauntCam");
}

bool CBaseEntity::IsAlive()
{
	return (this->GetLifeState() == LIFE_ALIVE);
}

bool CBaseEntity::IsVulnerable()
{
	return !(this->GetCond() & TFCond_Ubercharged || this->GetCond() & TFCond_Bonked);
}

bool CBaseEntity::IsCritBoosted()
{
	int nCond = this->GetCond();
	int nCondEx = this->GetCondEx();

	return (nCond & TFCond_Kritzkrieged
		|| nCondEx & TFCondEx_CritCanteen
		|| nCondEx & TFCondEx_CritOnFirstBlood
		|| nCondEx & TFCondEx_CritOnWin
		|| nCondEx & TFCondEx_HalloweenCritCandy
		|| nCondEx & TFCondEx_PyroCrits);
}

bool CBaseEntity::IsPlayer()
{
	return (this->GetClientClass()->iClassID == CTFPlayer);
}

bool CBaseEntity::IsBuilding()
{
	return (this->GetClientClass()->iClassID == CObjectDispenser
		|| this->GetClientClass()->iClassID == CObjectSentrygun
		|| this->GetClientClass()->iClassID == CObjectTeleporter);
}

bool CBaseEntity::IsPickup()
{
	return (this->GetClientClass()->iClassID == CBaseAnimating && this->GetModelName()[24] != 'h' || this->GetClientClass()->iClassID == CTFAmmoPack);
}

bool CBaseEntity::IsScoped()
{
	return (this->GetCond() & TFCond_Zoomed);
}

int CBaseEntity::GetFov()
{
	DYNVAR_RETURN(int, this, "DT_BasePlayer", "m_iFOV");
}

void CBaseEntity::SetFov(int nFov)
{
	DYNVAR_SET(int, this, nFov, "DT_BasePlayer", "m_iFOV");
}

bool CBaseEntity::IsTaunting()
{
	return (this->GetCond() & TFCond_Taunting);
}

bool CBaseEntity::IsDucking()
{
	return (this->GetFlags() & FL_DUCKING);
}

bool CBaseEntity::IsUbered()
{
	return (this->GetCond() & TFCond_Ubercharged);
}

bool CBaseEntity::IsBonked()
{
	return (this->GetCond() & TFCond_Bonked);
}

bool CBaseEntity::IsCloaked()
{
	return (this->GetCond() & TFCond_Cloaked);
}

int CBaseEntity::GetObserverTarget()
{
	DYNVAR_RETURN(int, this, "DT_BasePlayer", "m_hObserverTarget");
}

int CBaseEntity::GetObserverMode()
{
	DYNVAR_RETURN(int, this, "DT_BasePlayer", "m_iObserverMode");
}

void CBaseEntity::RemoveEffect(EffectFlags_t Effect)
{
	*reinterpret_cast<byte *>(this + 0x7C) &= ~Effect;

	if (Effect == EF_NODRAW) {
		static auto AddToLeafSystemFn = reinterpret_cast<int(__thiscall *)(PVOID, int)>(gPattern.FindInClient("55 8B EC 56 FF 75 08 8B F1 B8"));

		if (AddToLeafSystemFn)
			AddToLeafSystemFn(this, RENDER_GROUP_OPAQUE_ENTITY);
	}
}

//-------------------------------------------------- Glow Stuff

void CBaseEntity::SetGlowEnabled(bool bState) {
	DYNVAR_SET(bool, this, bState, "DT_TFPlayer", "m_bGlowEnabled");
}

bool CBaseEntity::IsGlowEnabled() {
	DYNVAR_RETURN(bool, this, "DT_TFPlayer", "m_bGlowEnabled");
}

bool CBaseEntity::HasGlowEffect(int &GlowObjectIdx)
{
	for (int n = 0; n < gInts.GlowObject->m_GlowObjectDefinitions.Size(); n++) {
		if (gInts.EntityList->GetClientEntityFromHandle(gInts.GlowObject->m_GlowObjectDefinitions[n].m_hEntity) == this) {
			GlowObjectIdx = n;
			return true;
		}
	}

	return false;
}

int CBaseEntity::RegisterGlowObject(Vec3 &vGlowColor, float flGlowAlpha, bool bRenderWhenOccluded, bool bRenderWhenUnoccluded, int nSplitScreenSlot)
{
	typedef int(__thiscall *RegisterGlowObjectFn)(CGlowObjectManager *, CBaseEntity *, Vec3 &, float, bool, bool, int);
	static DWORD dwFn = gPattern.FindInClient("55 8B EC 51 53 56 8B F1 57 8B 5E 14");
	static RegisterGlowObjectFn Register = (RegisterGlowObjectFn)dwFn;

	return Register(gInts.GlowObject, this, vGlowColor, flGlowAlpha, bRenderWhenOccluded, bRenderWhenUnoccluded, nSplitScreenSlot);
}

int CBaseEntity::RegisterGlow(Vec3 &vGlowColor, float fAlpha) {
	int temp = 0;
	if (HasGlowEffect(temp))
		return -1;

	return RegisterGlowObject(vGlowColor, fAlpha, true, true, -1);
}

void CBaseEntity::UnregisterGlow() {
	int idx = -1;

	if (HasGlowEffect(idx))
		gInts.GlowObject->m_GlowObjectDefinitions.Remove(idx);
}

void CBaseEntity::UpdateGlowEffect() {
	typedef void(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 226)(this);
}

//-------------------------------------------------- CTraceFilter

bool CTraceFilter::ShouldHitEntity(void *pEntityHandle, int nContentsMask)
{
	CBaseEntity *pEntity = reinterpret_cast<CBaseEntity *>(pEntityHandle);

	switch (pEntity->GetClientClass()->iClassID) {
		case 55:
		case 64:
		case 117:
		case 225:
			return false;
	}

	return !(pEntityHandle == pSkip);

	return true;
}

TraceType_t CTraceFilter::GetTraceType() const {
	return TRACE_EVERYTHING;
}

//-------------------------------------------------- CObject

CBaseEntity *CObject::GetOwner()
{
	DYNVAR_RETURN(CBaseEntity *, this, "DT_BaseObject", "m_hBuilder");
}

int CObject::GetLevel()
{
	DYNVAR_RETURN(int, this, "DT_BaseObject", "m_iUpgradeLevel");
}

bool CObject::IsSapped()
{
	DYNVAR_RETURN(bool, this, "DT_BaseObject", "m_bHasSapper");
}

int CObject::GetHealth()
{
	DYNVAR_RETURN(int, this, "DT_BaseObject", "m_iHealth");
}

int CObject::GetMaxHealth()
{
	DYNVAR_RETURN(int, this, "DT_BaseObject", "m_iMaxHealth");
}

bool CObject::IsCarried()
{
	DYNVAR_RETURN(int, this, "DT_BaseObject", "m_bCarried");
}

//-------------------------------------------------- CBaseCombatWeapon

int CBaseCombatWeapon::GetSlot()
{
	typedef int(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 327)(this);
}

float CBaseCombatWeapon::GetChargeTime()
{
	DYNVAR_RETURN(float, this, "DT_WeaponPipebombLauncher", "PipebombLauncherLocalData", "m_flChargeBeginTime");
}

float CBaseCombatWeapon::GetChargeDamage()
{
	DYNVAR_RETURN(float, this, "DT_TFSniperRifle", "SniperRifleLocalData", "m_flChargedDamage");
}

int CBaseCombatWeapon::GetItemDefinitionIndex()
{
	DYNVAR_RETURN(int, this, "DT_EconEntity", "m_AttributeManager", "m_Item", "m_iItemDefinitionIndex");
}

float CBaseCombatWeapon::GetLastFireTime()
{
	DYNVAR_RETURN(float, this, "DT_TFWeaponBase", "LocalActiveTFWeaponData", "m_flLastFireTime");
}

float CBaseCombatWeapon::GetSwingRange(CBaseEntity *pLocal)
{
	typedef int(__thiscall *FN)(CBaseEntity *);
	return (static_cast<float>(GetVFunc<FN>(this, 451)(pLocal)));
}

bool CBaseCombatWeapon::DoSwingTrace(CGameTrace &Trace)
{
	typedef int(__thiscall *FN)(CGameTrace &);
	return GetVFunc<FN>(this, 453)(Trace);
}

Vec3 &CBaseCombatWeapon::GetBulletSpread()
{
	typedef Vec3 &(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 286)(this);
}

int CBaseCombatWeapon::GetDamageType()
{
	typedef int(__thiscall * FN)(void *);
	return GetVFunc<FN>(this, 378)(this);
}

bool CBaseCombatWeapon::CanFireCriticalShot(bool bHeadShot)
{
	typedef bool(__thiscall * FN)(void *, bool, CBaseEntity *);
	return GetVFunc<FN>(this, 421)(this, bHeadShot, nullptr);
}

bool CBaseCombatWeapon::CanWeaponHeadShot()
{
	CBaseEntity *owner = gInts.EntityList->GetClientEntityFromHandle(this->GetOwner());

	if (!owner)
		return false;

	switch (owner->GetClassNum())
	{
		case TF2_Sniper: {
			static float timer = gInts.Globals->curtime;

			if (owner->IsScoped()) {
				if ((gInts.Globals->curtime - timer) > 0.2f)
					return true;
			}

			else timer = gInts.Globals->curtime;
		}

		case TF2_Spy: {
			return (this->GetDamageType() & DMG_USE_HITLOCATIONS && this->CanFireCriticalShot(true));
		}
	}

	return false;
}

//-------------------------------------------------- ScreenSize_t

void ScreenSize_t::Update() {
	gInts.Engine->GetScreenSize(this->w, this->h);
}

ScreenSize_t gScreenSize;

//-------------------------------------------------- Draw_t

Draw_t::Draw_t() {}

Draw_t::Draw_t(const char *font, int tall, int weight, int flags) {
	dwFont = gInts.Surface->CreateFont();
	gInts.Surface->SetFontGlyphSet(dwFont, font, tall, weight, 0, 0, flags);
}

void Draw_t::String(int x, int y, RGBA_t &clr, const char *str, ...)
{
	if (str == 0)
		return;

	va_list va_alist;
	char cbuffer[1024] = { '\0' };
	wchar_t wstr[1024] = { '\0' };

	va_start(va_alist, str);
	vsprintf_s(cbuffer, str, va_alist);
	va_end(va_alist);

	wsprintfW(wstr, L"%S", cbuffer);

	gInts.Surface->SetTextPos(x, y);
	gInts.Surface->SetTextFont(dwFont);
	gInts.Surface->SetTextColor(clr.R(), clr.G(), clr.B(), clr.A());
	gInts.Surface->PrintText(wstr, wcslen(wstr));
}

void Draw_t::Line(int x, int y, int x1, int y1, RGBA_t &clr)
{
	gInts.Surface->SetDrawColor(clr.R(), clr.G(), clr.B(), clr.A());
	gInts.Surface->DrawLine(x, y, x1, y1);
}

void Draw_t::Rect(int x, int y, int w, int h, RGBA_t &clr)
{
	gInts.Surface->SetDrawColor(clr.R(), clr.G(), clr.B(), clr.A());
	gInts.Surface->DrawFilledRect(x, y, x + w, y + h);
}

void Draw_t::OutlinedRect(int x, int y, int w, int h, RGBA_t &clr)
{
	gInts.Surface->SetDrawColor(clr.R(), clr.G(), clr.B(), clr.A());
	gInts.Surface->DrawOutlinedRect(x, y, x + w, y + h);
}

void Draw_t::GradientRect(int x, int y, int x1, int y1, RGBA_t &top_clr, RGBA_t &bottom_clr)
{
	gInts.Surface->SetDrawColor(top_clr.R(), top_clr.G(), top_clr.B(), top_clr.A());
	gInts.Surface->DrawFilledRectFade(x, y, x + x1, y + y1, 255, 255, false);
	gInts.Surface->SetDrawColor(bottom_clr.R(), bottom_clr.G(), bottom_clr.B(), bottom_clr.A());
	gInts.Surface->DrawFilledRectFade(x, y, x + x1, y + y1, 0, 255, false);
}

void Draw_t::OutlinedCircle(int x, int y, float radius, int segments, RGBA_t &clr)
{
	float Step = 3.141 * 2.0 / segments;

	for (float a = 0; a < (3.141 * 2.0); a += Step) {
		float x1 = radius * cos(a) + x;
		float y1 = radius * sin(a) + y;
		float x2 = radius * cos(a + Step) + x;
		float y2 = radius * sin(a + Step) + y;
		Line(x1, y1, x2, y2, clr);
	}
}

//-------------------------------------------------- KeyValues

bool CKeyVals::LoadFromBuffer(KeyValues *key_value, char const *resource_name, const char *buffer, IFileSystem *file_system, const char *path_id)
{
	using FN = int(__thiscall *)(KeyValues *, char const *, const char *, IFileSystem *, const char *);
	static FN load_from_the_buffer = (FN)gPattern.FindInEngine("55 8B EC 83 EC 38 53 8B 5D 0C");

	return load_from_the_buffer(key_value, resource_name, buffer, file_system, path_id);
}

KeyValues *CKeyVals::Initialize(KeyValues *key_value, char *name)
{
	using FN = KeyValues * (__thiscall *)(KeyValues *, char *);
	static FN initialize = (FN)(gPattern.FindInEngine("FF 15 ? ? ? ? 83 C4 08 89 06 8B C6") - 0x42);

	return initialize(key_value, name);
}

CKeyVals gKeyVals;

//-------------------------------------------------- MatHelper_t

void MatHelper_t::Initialize()
{
	shaded		= CreateMaterial(false, false, false, true);
	flat		= CreateMaterial(false, true, false, false);
	wireframe	= CreateMaterial(false, true, true, false); //how does add shine work? :thinking:
}

IMaterial *MatHelper_t::CreateMaterial(bool ignorez, bool flat, bool wireframe, bool add_shine)
{
	static int created = 0;
	static const char tmp[] =
	{
		"\"%s\"\
			\n{\
			\n\t\"$basetexture\" \"vgui/white_additive\"\
			\n\t\"$envmap\" \"%s\"\
			\n\t\"$normalmapalphaenvmapmask\" \"%i\"\
			\n\t\"$envmapcontrast\" \"%i\"\
			\n\t\"$model\" \"1\"\
			\n\t\"$flat\" \"1\"\
			\n\t\"$nocull\" \"0\"\
			\n\t\"$selfillum\" \"1\"\
			\n\t\"$halflambert\" \"1\"\
			\n\t\"$nofog\" \"0\"\
			\n\t\"$ignorez\" \"%i\"\
			\n\t\"$znearer\" \"0\"\
			\n\t\"$wireframe\" \"%i\"\
			\n}\n"
	};

	const char *baseType = (flat ? "UnlitGeneric" : "VertexLitGeneric");
	char material[512];
	sprintf_s(material, sizeof(material), tmp, baseType, add_shine ? "env_cubemap" : "", add_shine ? 1 : 0, add_shine ? 1 : 0, (ignorez) ? 1 : 0, (wireframe) ? 1 : 0);

	char name[512];
	sprintf_s(name, sizeof(name), "#textured_cham_material%i.vmt", created);
	created++;

	KeyValues *keyvalues = (KeyValues *)malloc(sizeof(KeyValues));
	gKeyVals.Initialize(keyvalues, (char *)"UnlitGeneric");
	gKeyVals.LoadFromBuffer(keyvalues, name, material);

	IMaterial *created_material = gInts.MatSystem->CreateMaterial(name, keyvalues);

	if (!created_material)
		return nullptr;

	created_material->IncrementReferenceCount();
	return created_material;
}

void MatHelper_t::ResetMaterial()
{
	static const float flDefault[3] = { 1, 1, 1 };
	gInts.RenderView->SetBlend(1.0f);
	gInts.RenderView->SetColorModulation(flDefault);
	gInts.ModelRender->ForcedMaterialOverride(nullptr);
}

void MatHelper_t::ForceMaterial(IMaterial *material, RGBA_t &color, float alpha_override)
{
	if (!material)
		return;

	float clr[3] = { color.R_flt(), color.G_flt(), color.B_flt() };
	float alpha = (alpha_override < 1.0f ? alpha_override : color.A_flt());
	gInts.RenderView->SetBlend(alpha);
	gInts.RenderView->SetColorModulation(clr);
	gInts.ModelRender->ForcedMaterialOverride(material);
}

MatHelper_t gMatHelper;

//-------------------------------------------------- LocalInfo_t

LocalInfo_t gLocalInfo;