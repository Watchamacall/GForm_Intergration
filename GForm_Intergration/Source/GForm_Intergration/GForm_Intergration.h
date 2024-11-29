#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**
 * Main module class for GForm_Intergration.
 */
class FGForm_IntergrationModule : public IModuleInterface
{
public:
    /** Called when the module is starting up */
    virtual void StartupModule() override;

    /** Called when the module is shutting down */
    virtual void ShutdownModule() override;
};