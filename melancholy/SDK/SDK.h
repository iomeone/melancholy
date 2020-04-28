#pragma once
#include "../DynamicNetvars/DynamicNetvars.h"

class CBaseEntity
{
public:
	Vec3 GetViewOffset();
	void SetCurrentCmd(CUserCmd *cmd);
	CUserCmd *GetCurrentCommand();
	Vec3 GetVecOrigin();
	void SetVecOrigin(Vec3 &vOrigin);
	Vec3 &GetAbsOrigin();
	Vec3 &GetShootPos();
	const char *GetModelName();
	int GetAmmo();
	bool IsBaseCombatWeapon();
	bool IsWearable();
	int GetHitboxSet();
	int GetTickBase();
	void IncreaseTickBase();
	float flSimulationTime();
	int GetOwner();
	Vec3 &GetAbsAngles();
	Vec3 GetWorldSpaceCenter();
	DWORD *GetModel();
	int DrawModel(int flags);
	bool SetupBones(matrix3x4 *pBoneToWorldOut, int nMaxBones, int nBoneMask, float fCurrentTime);
	CClientClass *GetClientClass();
	bool IsDormant();
	int GetIndex();
	void GetRenderBounds(Vec3 &vMins, Vec3 &vMaxs);
	matrix3x4 &GetRgflCoordinateFrame();
	Vec3 GetVelocity();
	int GetMaxHealth();
	int GetHealth();
	int GetTeamNum();
	int GetFlags();
	void SetFlags(int nFlags);
	BYTE GetLifeState();
	int GetClassId();
	int GetClassNum();
	const char *szGetClass();
	int GetCond();
	int GetCondEx();
	void RemoveCond(int cond);
	Vec3 GetCollideableMins();
	Vec3 GetCollideableMaxs();
	Vec3 GetEyeAngles();
	void SetEyeAngles(Vec3 &v);
	byte GetWaterLevel();
	bool IsOnGround();
	bool IsInWater();
	bool IsSwimming();
	Vec3 GetHitboxPos(int nHitbox);
	int GetNumOfHitboxes();
	Vec3 GetBonePos(int nBone);
	CBaseCombatWeapon *GetActiveWeapon();
	void ForceTauntCam(bool bState);
	bool IsAlive();
	bool IsVulnerable();
	bool IsCritBoosted();
	bool IsPlayer();
	bool IsBuilding();
	bool IsPickup();
	bool IsScoped();
	int GetFov();
	void SetFov(int nFov);
	bool IsTaunting();
	bool IsDucking();
	bool IsUbered();
	bool IsBonked();
	bool IsCloaked();
	int GetObserverTarget();
	int GetObserverMode();
	void RemoveEffect(EffectFlags_t Effect);

	//Glow stuff

	void SetGlowEnabled(bool bState);
	bool IsGlowEnabled();
	bool HasGlowEffect(int &GlowObjectIdx);
	int RegisterGlowObject(Vec3 &vGlowColor, float flGlowAlpha, bool bRenderWhenOccluded, bool bRenderWhenUnoccluded, int nSplitScreenSlot);
	int RegisterGlow(Vec3 &vGlowColor, float fAlpha);
	void UnregisterGlow();
	void UpdateGlowEffect();
};

class CObject : public CBaseEntity
{
public:
	CBaseEntity *GetOwner();
	int GetLevel();
	bool IsSapped();
	int GetHealth();
	int GetMaxHealth();
	bool IsCarried();
};

class CBaseCombatWeapon : public CBaseEntity
{
public:
	int GetSlot();
	float GetChargeTime();
	float GetChargeDamage();
	int GetItemDefinitionIndex();
	float GetLastFireTime();
	float GetSwingRange(CBaseEntity *pLocal);
	bool DoSwingTrace(CGameTrace &Trace);
	Vec3 &GetBulletSpread();
	int GetDamageType();
	bool CanFireCriticalShot(bool bHeadShot = false);
	bool CanWeaponHeadShot();
};


class CTraceFilter : public ITraceFilter
{
public:
	virtual bool ShouldHitEntity(void *pEntityHandle, int nContentsMask);
	virtual TraceType_t	GetTraceType() const;

	CBaseEntity *pSkip = nullptr;
};


struct ScreenSize_t {
	int w = 0, h = 0;
	void Update();
}; extern ScreenSize_t gScreenSize;

struct Draw_t
{
	DWORD dwFont = 0x0;

	Draw_t();
	Draw_t(const char *font, int tall, int weight, int flags);

	void String(int x, int y, RGBA_t &clr, const char *str, ...);
	void Line(int x, int y, int x1, int y1, RGBA_t &clr);
	void Rect(int x, int y, int w, int h, RGBA_t &clr);
	void OutlinedRect(int x, int y, int w, int h, RGBA_t &clr);
	void GradientRect(int x, int y, int x1, int y1, RGBA_t &top_clr, RGBA_t &bottom_clr);
	void OutlinedCircle(int x, int y, float radius, int segments, RGBA_t &clr);
};


class KeyValues
{
public:
	int m_iKeyName;
	char *m_sValue;
	wchar_t *m_wsValue;

	union {
		int m_iValue;
		float m_flValue;
		void *m_pValue;
		unsigned char m_Color[4];
	};

	char m_iDataType;
	char m_bHasEscapeSequences;
	char m_bEvaluateConditionals;
	char unused[1];

	KeyValues *m_pPeer;
	KeyValues *m_pSub;
	KeyValues *m_pChain;
};

class CKeyVals
{
public:
	bool LoadFromBuffer(KeyValues *key_value, char const *resource_name, const char *buffer, IFileSystem *file_system = 0, const char *path_id = 0);
	KeyValues *Initialize(KeyValues *key_value, char *name);
};

extern CKeyVals gKeyVals;


class MatHelper_t
{
public:
	IMaterial *shaded, *flat, *wireframe;

	void Initialize();
	IMaterial *CreateMaterial(bool ignorez, bool flat, bool wireframe, bool add_shine);
	void ResetMaterial();
	void ForceMaterial(IMaterial *material, RGBA_t &color, float alpha_override = 1.0f);
};

extern MatHelper_t gMatHelper;


struct LocalInfo_t {
	bool CanHeadShot		= false;
	int CurrentTargetIndex	= 0;
	bool LevelInitialized	= false;
};

extern LocalInfo_t gLocalInfo;


namespace Math {
	inline bool W2S(Vec3 &vOrigin, Vec3 &vScreen) {
		const matrix3x4 &worldToScreen = gInts.Engine->WorldToScreenMatrix();

		float w = worldToScreen[3][0] * vOrigin[0] + worldToScreen[3][1] * vOrigin[1] + worldToScreen[3][2] * vOrigin[2] + worldToScreen[3][3];
		vScreen.z = 0;

		if (w > 0.001) {
			float fl1DBw = 1 / w;
			vScreen.x = (gScreenSize.w / 2) + (0.5 * ((worldToScreen[0][0] * vOrigin[0] + worldToScreen[0][1] * vOrigin[1] + worldToScreen[0][2] * vOrigin[2] + worldToScreen[0][3]) * fl1DBw) * gScreenSize.w + 0.5);
			vScreen.y = (gScreenSize.h / 2) - (0.5 * ((worldToScreen[1][0] * vOrigin[0] + worldToScreen[1][1] * vOrigin[1] + worldToScreen[1][2] * vOrigin[2] + worldToScreen[1][3]) * fl1DBw) * gScreenSize.h + 0.5);
			return true;
		}

		return false;
	}
}

namespace Utils {
	template <typename T>
	void clamp(T &x, T min, T max)
	{
		if (x < min)
			x = min;

		if (x > max)
			x = max;
	}

	typedef void(__cdecl *MsgFn)(const char *msg, va_list);
	inline void Msg(const char *msg, ...)
	{
		if (msg == nullptr)
			return;

		static MsgFn fn = (MsgFn)GetProcAddress(GetModuleHandle("tier0.dll"), "Msg");

		char buffer[989];
		va_list list;
		va_start(list, msg);
		vsprintf(buffer, msg, list);
		va_end(list);

		fn(buffer, list);
	}

	inline RGBA_t Rainbow()
	{
		static uint32_t cnt = 0;
		float freq = 0.01f;

		RGBA_t color = RGBA_t(
			std::sin(freq * cnt + 0) * 127 + 128,
			std::sin(freq * cnt + 2) * 127 + 128,
			std::sin(freq * cnt + 4) * 127 + 128,
			255);

		if (cnt++ >= (uint32_t)-1)
			cnt = 0;

		return color;
	}

	inline const wchar_t *ToWC(const char *text)
	{
		size_t length = strlen(text) + 1;
		std::wstring wc(length, L'#');
		mbstowcs(&wc[0], text, length);
		return wc.c_str();
	}

	inline RGBA_t GetTeamColor(int TeamNum)
	{
		switch (TeamNum) {
			case 2: { return RGBA_t(251, 82, 79, 255);	}
			case 3: { return RGBA_t(30, 145, 255, 255);	}
			default: { return RGBA_t(255, 255, 255, 255); }
		}
	}

	inline RGBA_t GetHealthColor(int hp, int maxhp)
	{
		hp = std::max(0, std::min(hp, maxhp));

		return RGBA_t(
			std::min((510 * (maxhp - hp)) / maxhp, 255),
			std::min((510 * hp) / maxhp, 255),
			0,
			255);
	}

	inline RGBA_t GetPickupColor(CBaseEntity *pickup)
	{
		const char *model_name = pickup->GetModelName();

		if (model_name[13] == 'm' && model_name[20] == 's'
			|| model_name[33] == 'm' && model_name[40] == 's'
			|| model_name[13] == 'm' && model_name[20] == 'm'
			|| model_name[33] == 'm' && model_name[40] == 'm'
			|| model_name[13] == 'm' && model_name[20] == 'l'
			|| model_name[33] == 'm' && model_name[40] == 'l'
			|| model_name[13] == 'p' && model_name[16] == 't'
			|| model_name[24] == 's' && model_name[28] == 'w')
			return RGBA_t(39, 174, 96, 255); //health

		else if (model_name[13] == 'a' && model_name[22] == 's'
			|| model_name[13] == 'a' && model_name[22] == 'm'
			|| model_name[13] == 'a' && model_name[22] == 'l')
			return RGBA_t(251, 197, 49, 255); //ammo
	}

	inline float GetCurTime(CBaseEntity *pLocal, CUserCmd *pCmd)
	{
		static int tick = 0;
		static CUserCmd *pLastCmd = nullptr;

		if (!pLastCmd || pLastCmd->hasbeenpredicted)
			tick = pLocal->GetTickBase();

		else ++tick;

		pLastCmd = pCmd;
		float curtime = (tick * gInts.Globals->interval_per_tick);
		return curtime;
	}

	inline void LocalPrediction(CBaseEntity *pLocal, CUserCmd *cmd)
	{
		const float curtime	= GetCurTime(pLocal, cmd);
		const float frametime = gInts.Globals->frametime;

		static CMoveData moveData;
		memset(&moveData, 0, sizeof(CMoveData));

		gInts.Globals->curtime = GetCurTime(pLocal, cmd);
		gInts.Globals->frametime = gInts.Globals->interval_per_tick;

		pLocal->SetCurrentCmd(cmd);

		gInts.GameMovement->StartTrackPredictionErrors(pLocal);
		gInts.Prediction->SetupMove(pLocal, cmd, gInts.MoveHelper, &moveData);
		gInts.GameMovement->ProcessMovement(pLocal, &moveData);
		gInts.Prediction->FinishMove(pLocal, cmd, &moveData);
		gInts.GameMovement->FinishTrackPredictionErrors(pLocal);

		gInts.Globals->curtime = curtime;
		gInts.Globals->frametime = frametime;

		pLocal->SetCurrentCmd(nullptr);
	}

	inline float GetMeleeDistance(const Vec3 &src, const Vec3 &dst) {
		return (src.DistTo(dst) * 0.6f); //this syncs up the GetSwingRange result with Vec3's DistTo result (useless)
	}

	inline void FixSilentMovement(CUserCmd *cmd, Vec3 &angs)
	{
		Vec3 move(cmd->forwardmove, cmd->sidemove, cmd->upmove);
		float speed = Math::fsqrt(move.x * move.x + move.y * move.y);
		Vec3 move_ang = Vec3();
		Math::VectorAngles(move, move_ang);
		float yaw = DEG2RAD(angs.y - cmd->viewangles.y + move_ang.y);

		cmd->forwardmove	= (cosf(yaw) * speed);
		cmd->sidemove		= (sinf(yaw) * speed);
		cmd->viewangles		= angs;
	}

	//obsolete
	inline bool CanSniperHS(CBaseEntity *local)
	{
		if (!local || !local->IsAlive())
			return false;

		static float timer = 0.0f;
		static bool started = false;

		if (!local->IsScoped()) {
			started = false;
			timer = 0.0f;
		}

		if (!started) {
			started = true;
			timer = gInts.Globals->curtime;
		}

		if (started)
			if ((gInts.Globals->curtime - timer) > 0.21f)
				return true;

		return false;
	}

	//obsolete
	inline bool CanSpyHS(CBaseEntity *local) {
		if (!local || !local->IsAlive())
			return false;

		return ((gInts.Globals->curtime - local->GetActiveWeapon()->GetLastFireTime()) > 0.930f);
	}

	inline bool CanMeleeHit(CBaseCombatWeapon *pLocalWeapon, Vec3 &vLocalViewAngles, int nEntityIndex)
	{
		if (!pLocalWeapon)
			return false;

		if (pLocalWeapon->GetSlot() != 2)
			return false;

		CBaseEntity *pOwner = gInts.EntityList->GetClientEntityFromHandle(pLocalWeapon->GetOwner());

		if (!pOwner)
			return false;

		float flRange = pLocalWeapon->GetSwingRange(pOwner);

		if (flRange <= 0.0f)
			return false;

		switch (pLocalWeapon->GetItemDefinitionIndex()) {
			case Demoman_t_TheEyelander:
			case Demoman_t_FestiveEyelander:
			case Demoman_t_HorselessHeadlessHorsemannsHeadtaker:
			case Demoman_t_NessiesNineIron:
			case Demoman_t_TheScotsmansSkullcutter:
			case Demoman_t_TheClaidheamhMor:
			case Demoman_t_TheHalfZatoichi:
			case Demoman_t_ThePersianPersuader: {
				flRange *= 1.25f; //magic numbers I found while testing
				break;
			}

			default: {
				flRange *= 1.35f;
				break;
			}
		}

		Vec3 vForward = Vec3();
		Math::AngleVectors(vLocalViewAngles, &vForward);

		Vec3 vTraceStart = pOwner->GetShootPos();
		Vec3 vTraceEnd = (vTraceStart + (vForward * flRange));

		Ray_t ray;
		ray.Init(vTraceStart, vTraceEnd);
		CTraceFilter filter;
		filter.pSkip = pOwner;
		CGameTrace trace;
		gInts.EngineTrace->TraceRay(ray, MASK_SHOT_HULL, &filter, &trace); //not sure if MASK_SHOT_HULL is neccessary

		if (trace.m_pEnt && trace.m_pEnt->GetIndex() == nEntityIndex)
			return true;

		return false;
	}

	inline bool CanBackstab(const Vec3 &from_angle, const Vec3 &to_angle, Vec3 wsc_spy_to_victim)
	{
		wsc_spy_to_victim.z = 0;
		wsc_spy_to_victim.NormalizeInPlace();
		Vec3 eye_spy = Vec3();
		Math::AngleVectors(from_angle, &eye_spy);
		eye_spy.z = 0;
		eye_spy.NormalizeInPlace();
		Vec3 eye_victim = Vec3();
		Math::AngleVectors(to_angle, &eye_victim);
		eye_victim.z = 0;
		eye_victim.NormalizeInPlace();

		if (wsc_spy_to_victim.Dot(eye_victim) <= 0.01f)
			return false;

		if (wsc_spy_to_victim.Dot(eye_spy) <= 0.5f)
			return false;

		if (eye_spy.Dot(eye_victim) <= -0.3f)
			return false;

		return true;
	}

	inline bool Vis_Pos(CBaseEntity *pLocal, CBaseEntity *pEntity, Vec3 &src, Vec3 &dst)
	{
		CTraceFilter filter;
		filter.pSkip = pLocal;

		Ray_t ray;
		ray.Init(src, dst);

		CGameTrace trace;
		gInts.EngineTrace->TraceRay(ray, (MASK_SHOT | CONTENTS_GRATE), &filter, &trace);

		if (trace.m_pEnt != nullptr && trace.m_pEnt->GetIndex() == pEntity->GetIndex())
			return true;

		return false;
	}

	inline bool Vis_Pos_IdOut(CBaseEntity *pLocal, CBaseEntity *pEntity, Vec3 &src, Vec3 &dst, int &id_out)
	{
		CTraceFilter filter;
		filter.pSkip = pLocal;

		Ray_t ray;
		ray.Init(src, dst);

		CGameTrace trace;
		gInts.EngineTrace->TraceRay(ray, (MASK_SHOT | CONTENTS_GRATE), &filter, &trace);

		if (trace.m_pEnt != nullptr && trace.m_pEnt->GetIndex() == pEntity->GetIndex()) {
			id_out = trace.hitbox;
			return true;
		}

		return false;
	}

	inline bool Vis_Pos_Id(CBaseEntity *pLocal, CBaseEntity *pEntity, Vec3 &src, Vec3 &dst, int id)
	{
		CTraceFilter filter;
		filter.pSkip = pLocal;

		Ray_t ray;
		ray.Init(src, dst);

		CGameTrace trace;
		gInts.EngineTrace->TraceRay(ray, (MASK_SHOT | CONTENTS_GRATE), &filter, &trace);

		if (trace.m_pEnt != nullptr && trace.m_pEnt->GetIndex() == pEntity->GetIndex() && trace.hitbox == id)
			return true;

		return false;
	}
}