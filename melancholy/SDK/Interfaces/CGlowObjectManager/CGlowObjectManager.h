#pragma once
#include "../../Defines.h"

class CGlowObjectManager {
public:
	CUtlVector<GlowObjectDefinition_t> m_GlowObjectDefinitions;
	int m_nFirstFreeSlot;
};