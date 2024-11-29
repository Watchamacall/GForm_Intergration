#include "GForm_Intergration.h"
#include "Modules/ModuleManager.h"

// Implement the primary game module
IMPLEMENT_PRIMARY_GAME_MODULE(FGForm_IntergrationModule, GForm_Intergration, "GForm_Intergration");

void FGForm_IntergrationModule::StartupModule()
{
    // Initialization logic here (e.g., logging, registering components, etc.)
    UE_LOG(LogTemp, Log, TEXT("GForm_Intergration module starting up."));
}

void FGForm_IntergrationModule::ShutdownModule()
{
    // Cleanup logic here
    UE_LOG(LogTemp, Log, TEXT("GForm_Intergration module shutting down."));
}