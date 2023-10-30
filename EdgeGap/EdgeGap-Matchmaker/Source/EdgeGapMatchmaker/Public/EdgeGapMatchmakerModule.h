
#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "UObject/StrongObjectPtr.h"

DECLARE_LOG_CATEGORY_EXTERN(LogEdgeGapMatchmaker, Log, All);

namespace EdgeGap
{
    template<typename T>
    TSharedPtr<T> MakeSharedUObject()
    {
        TSharedRef< TStrongObjectPtr<T> > SharedRefToStrongObjPtr = MakeShared< TStrongObjectPtr<T> >(NewObject<T>());
        return TSharedPtr<T>(SharedRefToStrongObjPtr, SharedRefToStrongObjPtr->Get());
    }

    class UEdgeGapMatchmaker;
}

typedef TSharedPtr<class EdgeGap::UEdgeGapMatchmaker> EdgeGapMatchmakerPtr;

class IEdgeGapMatchmakerModuleInterface : public IModuleInterface
{
public:

    /**
    * Singleton-like access to this module's interface.  This is just for convenience!
    * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
    *
    * @return Returns singleton instance, loading the module on demand if needed
    */
    static inline IEdgeGapMatchmakerModuleInterface& Get()
    {
        if (IsAvailable())
        {
            return FModuleManager::GetModuleChecked<IEdgeGapMatchmakerModuleInterface>("EdgeGapMatchmaker");
        }
        return FModuleManager::LoadModuleChecked<IEdgeGapMatchmakerModuleInterface>("EdgeGapMatchmaker");
    }

    /**
    * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
    *
    * @return True if the module is loaded and ready to use
    */
    static inline bool IsAvailable()
    {
        return FModuleManager::Get().IsModuleLoaded("EdgeGapMatchmaker");
    }

    virtual EdgeGapMatchmakerPtr GetMatchmaker() const = 0;
};
