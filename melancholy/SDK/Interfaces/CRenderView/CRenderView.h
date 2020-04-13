#pragma once
#include "../IMaterial/IMaterial.h"

class CRenderView
{
public:
	virtual void DrawBrushModel(CBaseEntity *baseentity, model_t *model, const Vec3 &origin, const Vec3 &angles, bool sort) = 0;
	virtual void DrawIdentityBrushModel(IWorldRenderList *pList, model_t *model) = 0;
	virtual void TouchLight(struct dlight_t *light) = 0;
	virtual void Draw3DDebugOverlays(void) = 0;
	virtual void SetBlend(float blend) = 0;
	virtual float GetBlend(void) = 0;
	virtual void SetColorModulation(float const *blend) = 0;
	virtual void GetColorModulation(float *blend) = 0;
	virtual void SceneBegin(void) = 0;
	virtual void SceneEnd(void) = 0;
	virtual void GetVisibleFogVolume(const Vec3 &eyePoint, VisibleFogVolumeInfo_t *pInfo) = 0;
	virtual IWorldRenderList *CreateWorldList() = 0;
	virtual void BuildWorldLists(IWorldRenderList *pList, WorldListInfo_t *pInfo, int iForceFViewLeaf, const VisOverrideData_t *pVisData = nullptr, bool bShadowDepth = false, float *pReflectionWaterHeight = nullptr) = 0;
	virtual void DrawWorldLists(IWorldRenderList *pList, unsigned long flags, float waterZAdjust) = 0;
	virtual int GetNumIndicesForWorldLists(IWorldRenderList *pList, unsigned long nFlags) = 0;
	virtual void DrawTopView(bool enable) = 0;
	virtual void TopViewBounds(Vec3 const &mins, Vec3 const &maxs) = 0;
	virtual void DrawLights(void) = 0;
	virtual void DrawMaskEntities(void) = 0;
	virtual void DrawTranslucentSurfaces(IWorldRenderList *pList, int *pSortList, int sortCount, unsigned long flags) = 0;
	virtual void DrawLineFile(void) = 0;
	virtual void DrawLightmaps(IWorldRenderList *pList, int pageId) = 0;
	virtual void ViewSetupVis(bool novis, int numorigins, const Vec3 origin[]) = 0;
	virtual bool AreAnyLeavesVisible(int *leafList, int nLeaves) = 0;
	virtual void VguiPaint(void) = 0;
	virtual void ViewDrawFade(byte *color, IMaterial *pMaterial) = 0;
	virtual void OLD_SetProjectionMatrix(float fov, float zNear, float zFar) = 0;
	virtual RGBA_t GetLightAtPoint(Vec3 &pos) = 0;
	virtual int GetViewEntity(void) = 0;
	virtual bool IsViewEntity(int entindex) = 0;
	virtual float GetFieldOfView(void) = 0;
	virtual unsigned char **GetAreaBits(void) = 0;
	virtual void SetFogVolumeState(int nVisibleFogVolume, bool bUseHeightFog) = 0;
	virtual void InstallBrushSurfaceRenderer(IBrushRenderer *pBrushRenderer) = 0;
	virtual void DrawBrushModelShadow(IClientRenderable *pRenderable) = 0;
	virtual bool LeafContainsTranslucentSurfaces(IWorldRenderList *pList, int sortIndex, unsigned long flags) = 0;
	virtual bool DoesBoxIntersectWaterVolume(const Vec3 &mins, const Vec3 &maxs, int leafWaterDataID) = 0;
	virtual void SetAreaState(unsigned char chAreaBits[69], unsigned char chAreaPortalBits[69]) = 0;
	virtual void VGui_Paint(int mode) = 0;
};