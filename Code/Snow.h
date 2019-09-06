// Copyright (C) 2019 Ilya Chernetsov. All rights reserved. Contacts: <chernecoff@gmail.com>
// License: https://github.com/afrostalin/CEVSnow/blob/master/LICENSE

#pragma once

#include <CryEntitySystem/IEntityComponent.h>
#include <CryEntitySystem/IEntity.h>


class CSnow final : public IEntityComponent
{
public:
	CSnow() = default;
	virtual ~CSnow() {};
public:
	// IEntityComponent
	virtual Cry::Entity::EventFlags GetEventMask() const override;
	virtual void   ProcessEvent(const SEntityEvent& event) override;
	// ~IEntityComponent
public:
	static void ReflectType(Schematyc::CTypeDesc<CSnow>& desc)
	{
		desc.SetGUID("{F813DA76-9FE2-421A-9F50-3788A5FF3EC1}"_cry_guid);
		desc.SetEditorCategory("Effects");
		desc.SetLabel("Snow");
		desc.SetDescription("Snow");
		desc.SetComponentFlags({ IEntityComponent::EFlags::Transform });

		desc.AddMember(&CSnow::m_options, 'opt', "Options", "Options", "Snow options", CSnow::SOptions());
	}

	struct SOptions
	{
		inline bool operator==(const SOptions &rhs) const { return 0 == memcmp(this, &rhs, sizeof(rhs)); }

		static void ReflectType(Schematyc::CTypeDesc<SOptions>& desc)
		{
			desc.SetGUID("{1D619FFE-D7A3-4C14-B1C1-6AB15605D950}"_cry_guid);

			desc.AddMember(&CSnow::SOptions::m_isEnabled, 'enbl', "IsEnabled", "IsEnabled", nullptr, true);
			desc.AddMember(&CSnow::SOptions::m_radius, 'rads', "Radius", "Radius", nullptr, 50.0f);
			desc.AddMember(&CSnow::SOptions::m_snowAmmount, 'snam', "SnowAmmount", "SnowAmmount", nullptr, 10.0f);
			desc.AddMember(&CSnow::SOptions::m_frostAmmount, 'frst', "FrostAmmount", "FrostAmmount", nullptr, 1.0f);
			desc.AddMember(&CSnow::SOptions::m_surfaceFreezing, 'frs0', "SurfaceFreezing", "SurfaceFreezing", nullptr, 1.0f);
			desc.AddMember(&CSnow::SOptions::m_snowFlakeCount, 'flkc', "SnowFlakeCount", "SnowFlakeCount", nullptr, 100);
			desc.AddMember(&CSnow::SOptions::m_snowFlakeSize, 'flk0', "SnowFlakeSize", "SnowFlakeSize", nullptr, 1.0f);
			desc.AddMember(&CSnow::SOptions::m_snowFallBrightness, 'flbr', "SnowFallBrightness", "SnowFallBrightness", nullptr, 1.0f);
			desc.AddMember(&CSnow::SOptions::m_snowFallGravityScale, 'flgs', "SnowFallGravityScale", "SnowFallGravityScale", nullptr, 0.1f);
			desc.AddMember(&CSnow::SOptions::m_snowFallWindScale, 'wnsl', "SnowFallWindScale", "SnowFallWindScale", nullptr, 0.1f);
			desc.AddMember(&CSnow::SOptions::m_snowFallTurbulence, 'fltb', "SnowFallTurbulence", "SnowFallTurbulence", nullptr, 0.5f);
			desc.AddMember(&CSnow::SOptions::m_snowFallTurbulenceFreq, 'ftbf', "SnowFallTurbulenceFreq", "SnowFallTurbulenceFreq", nullptr, 0.1f);
		}

		bool  m_isEnabled = true;
		float m_radius = 50.0f;
		float m_snowAmmount = 10.0f;
		float m_frostAmmount = 1.0f;
		float m_surfaceFreezing = 1.0f;
		int   m_snowFlakeCount = 100;
		float m_snowFlakeSize = 1.0f;
		float m_snowFallBrightness = 1.0f;
		float m_snowFallGravityScale = 0.1f;
		float m_snowFallWindScale = 0.1f;
		float m_snowFallTurbulence = 0.5f;
		float m_snowFallTurbulenceFreq = 0.1f;
	};
protected:
	void Reset();
private:
	SOptions m_options;
};