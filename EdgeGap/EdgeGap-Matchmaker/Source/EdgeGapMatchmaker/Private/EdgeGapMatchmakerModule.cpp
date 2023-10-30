
#include "EdgeGapMatchmakerModule.h"
#include "EdgeGapMatchmaker.h"

DEFINE_LOG_CATEGORY(LogEdgeGapMatchmaker);

class FEdgeGapMatchmakerModule : public IEdgeGapMatchmakerModuleInterface
{
    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    EdgeGapMatchmakerPtr GetMatchmaker() const override { return Matchmaker; };

    EdgeGapMatchmakerPtr Matchmaker;
};

void FEdgeGapMatchmakerModule::StartupModule()
{
    Matchmaker = MakeShareable(new EdgeGap::UEdgeGapMatchmaker());
	
}

void FEdgeGapMatchmakerModule::ShutdownModule()
{

	
}
	
IMPLEMENT_MODULE(FEdgeGapMatchmakerModule, EdgeGapMatchmaker)