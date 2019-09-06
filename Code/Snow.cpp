// Copyright (C) 2019 Ilya Chernetsov. All rights reserved. Contacts: <chernecoff@gmail.com>
// License: https://github.com/afrostalin/CEVSnow/blob/master/LICENSE

#pragma once

#include "StdAfx.h"
#include "Snow.h"

Cry::Entity::EventFlags CSnow::GetEventMask() const
{
	return EEntityEvent::EditorPropertyChanged | EEntityEvent::Update | EEntityEvent::Remove | EEntityEvent::Hidden;
}

void CSnow::ProcessEvent(const SEntityEvent & event)
{
	switch (event.event)
	{
	case EEntityEvent::EditorPropertyChanged:
	{
		if (!m_options.m_isEnabled)
		{
			Reset();
		}

		break;
	}
	case EEntityEvent::Update:
	{
		if (m_options.m_isEnabled)
		{
			const Vec3 vCamPos = GetISystem()->GetViewCamera().GetPosition();
			Vec3 vR = (GetEntity()->GetWorldPos() - vCamPos) / max(m_options.m_radius, 1e-3f);

			// todo: only update when things have changed.
			gEnv->p3DEngine->SetSnowSurfaceParams(GetEntity()->GetWorldPos(), m_options.m_radius, m_options.m_snowAmmount, m_options.m_frostAmmount, m_options.m_surfaceFreezing);
			gEnv->p3DEngine->SetSnowFallParams(m_options.m_snowFlakeCount, m_options.m_snowFlakeSize, m_options.m_snowFallBrightness, m_options.m_snowFallGravityScale, m_options.m_snowFallWindScale, m_options.m_snowFallTurbulence, m_options.m_snowFallTurbulenceFreq);
		}

		break;
	}
	case EEntityEvent::Remove:
	case EEntityEvent::Hidden:
	{
		Reset();
		break;
	}
	default:
		break;
	}
}

void CSnow::Reset()
{
	if (gEnv && gEnv->p3DEngine)
	{
		static const Vec3 vZero(ZERO);
		gEnv->p3DEngine->SetSnowSurfaceParams(vZero, 0, 0, 0, 0);
		gEnv->p3DEngine->SetSnowFallParams(0, 0, 0, 0, 0, 0, 0);
	}

}
