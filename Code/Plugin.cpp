// Copyright (C) 2019 Ilya Chernetsov. All rights reserved. Contacts: <chernecoff@gmail.com>
// License: https://github.com/afrostalin/CEVSnow/blob/master/LICENSE

#include "StdAfx.h"
#include "Plugin.h"

#include <CrySchematyc/Env/IEnvRegistry.h>
#include <CrySchematyc/Env/EnvPackage.h>
#include <CrySchematyc/Utils/SharedString.h>
#include <CrySchematyc/CoreAPI.h>

// Included only once per DLL module.
#include <CryCore/Platform/platform_impl.inl>

#include "Snow.h"

CSnowPlugin::~CSnowPlugin()
{
	gEnv->pSystem->GetISystemEventDispatcher()->RemoveListener(this);

	if (gEnv->pSchematyc)
	{
		gEnv->pSchematyc->GetEnvRegistry().DeregisterPackage(CSnowPlugin::GetCID());
	}
}

bool CSnowPlugin::Initialize(SSystemGlobalEnvironment& env, const SSystemInitParams& initParams)
{
	gEnv->pSystem->GetISystemEventDispatcher()->RegisterListener(this,"CSnowPlugin");

	return true;
}

void CSnowPlugin::OnSystemEvent(ESystemEvent event, UINT_PTR wparam, UINT_PTR lparam)
{
	switch (event)
	{
	case ESYSTEM_EVENT_REGISTER_SCHEMATYC_ENV:
	{
		if (gEnv->pSchematyc != nullptr)
		{
			gEnv->pSchematyc->GetEnvRegistry().RegisterPackage(
				stl::make_unique<Schematyc::CEnvPackage>(
					CSnowPlugin::GetCID(),
					"CEVSnow",
					"Ilya Chernetsov",
					"Components",
					[this](Schematyc::IEnvRegistrar& registrar) { RegisterComponents(registrar); }
					)
			);
		}
	}
	break;
	}
}

void CSnowPlugin::RegisterComponents(Schematyc::IEnvRegistrar & registrar)
{
	Schematyc::CEnvRegistrationScope scope = registrar.Scope(IEntity::GetEntityScopeGUID());
	{
		{
			Schematyc::CEnvRegistrationScope componentScope = scope.Register(SCHEMATYC_MAKE_ENV_COMPONENT(CSnow));
		}
	}
}

CRYREGISTER_SINGLETON_CLASS(CSnowPlugin)