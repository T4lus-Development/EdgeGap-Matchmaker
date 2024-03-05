# EdgeGap-Matchmaker

the most usefull way to use this matchmaker is to use it in a GameInstanceSubsystem

MatchmakingSubsystem.h:

    // T4lus Development - All Rights Reserved
    
    #pragma once
    
    #include "CoreMinimal.h"
    #include "Subsystems/GameInstanceSubsystem.h"
    
    #include "EdgeGapMatchmakerModule.h"
    #include "EdgeGapMatchmakerError.h"
    #include "EdgeGapMatchmakerDataModels.h"
    
    #include "MatchmakingSubsystem.generated.h"
    
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMatchmakingStarted);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMatchmakingCanceled);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMatchmakingCompleted);
    
    UCLASS()
    class EDGEGAPGAME_API UMatchmakingSubsystem : public UGameInstanceSubsystem
    {
    	GENERATED_BODY()
    	
    public:
    	UMatchmakingSubsystem() { }
    
    	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    	virtual void Deinitialize() override;
    	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
    
    	void OnEdgeGapError(const EdgeGap::FEdgeGapError& ErrorResult);
    
    	UFUNCTION(BlueprintCallable, Category = "Subsystem|Matchmaking")
    	bool StartMatchmaking();
    	void OnStartMatchmakingSuccess(const EdgeGap::MatchmakerModels::FCreateTicketResponse& Result);
    
	    UFUNCTION(BlueprintCallable, Category = "Subsystem|Matchmaking")
    	bool CancelMatchmaking();
    	void OnCancelMatchmakingSuccess(const EdgeGap::MatchmakerModels::FDeleteTicketResponse& Result);
    
    	bool GetTicketStatus();
    	void OnGetTicketSuccess(const EdgeGap::MatchmakerModels::FGetTicketResponse& Result);
    
    	void PollTicketStatus();
    
    public:
    	UPROPERTY(BlueprintAssignable, Category = "Subsystem|Matchmaking")
    	FOnMatchmakingStarted OnMatchmakingStartedDelegate;
    
    	UPROPERTY(BlueprintAssignable, Category = "Subsystem|Matchmaking")
    	FOnMatchmakingCanceled OnMatchmakingCanceledDelegate;
    
    	UPROPERTY(BlueprintAssignable, Category = "Subsystem|Matchmaking")
    	FOnMatchmakingCompleted OnMatchmakingCompletedDelegate;
    
    public:
    	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    	bool bInQueue;
    
    protected:
    	EdgeGapMatchmakerPtr EdgeGapMatchmaker;
    
    private:
    	FString TicketId;
    	FTimerHandle PollTicketStatusTimerHandle;
    };

MatchmakingSubsystem.cpp:

    // T4lus Development - All Rights Reserved
    
    #include "MatchmakingSubsystem.h"
    
    #include "EdgeGapMatchmaker.h"
    
    void UMatchmakingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
    {
    	Super::Initialize(Collection);
    
    	EdgeGapMatchmaker = IEdgeGapMatchmakerModuleInterface::Get().GetMatchmaker();
    	EdgeGapMatchmaker->SetMatchmakerURL("https://supermatchmaker-a979815d099f47.edgegap.net");
    	EdgeGapMatchmaker->SetMatchmakerAPIToken("ABCDEF12345");
    }
    
    void UMatchmakingSubsystem::Deinitialize()
    {
    	Super::Deinitialize();
    
    }
    
    bool UMatchmakingSubsystem::ShouldCreateSubsystem(UObject* Outer) const
    {
    	TArray<UClass*> ChildClasses;
    	GetDerivedClasses(GetClass(), ChildClasses, false);
    
    	return ChildClasses.Num() == 0;
    }
    
    void UMatchmakingSubsystem::OnEdgeGapError(const EdgeGap::FEdgeGapError& ErrorResult)
    {
    	UE_LOG(LogTemp, Error, TEXT("Something went wrong with your API call.\nHere's some debug information:\n%s"), *ErrorResult.GenerateErrorReport());
    	bInQueue = false;
    	TicketId = "";
    }
    
    bool UMatchmakingSubsystem::StartMatchmaking()
    {
    	if (EdgeGapMatchmaker && !bInQueue)
    	{
    		EdgeGap::MatchmakerModels::FCreateTicketRequest Request;
    		Request.ProfileId = "ffa";
    		Request.MatchmakingData = MakeShared<EdgeGap::MatchmakerModels::FMatchmakingData>();
    		Request.MatchmakingData->SelectorData = MakeShared<EdgeGap::MatchmakerModels::FSelectorData>();
    		Request.MatchmakingData->SelectorData->Data.Add("mode", "rank");
    		Request.MatchmakingData->SelectorData->Data.Add("map", "Dust II");
    		Request.MatchmakingData->FilterData = MakeShared<EdgeGap::MatchmakerModels::FFilterData>();
    		Request.MatchmakingData->FilterData->Data.Add("elo", 734);
    
    		EdgeGapMatchmaker->CreateTicket(Request,
    			EdgeGap::UEdgeGapMatchmaker::FCreateTicketDelegate::CreateUObject(this, &UMatchmakingSubsystem::OnStartMatchmakingSuccess),
    			EdgeGap::FEdgeGapErrorDelegate::CreateUObject(this, &UMatchmakingSubsystem::OnEdgeGapError)
    		);
    		return true;
    	}
    	return false;
    }
    
    void UMatchmakingSubsystem::OnStartMatchmakingSuccess(const EdgeGap::MatchmakerModels::FCreateTicketResponse& Result)
    {
    	bInQueue = true;
    	TicketId = Result.TicketId;
    
    	OnMatchmakingStartedDelegate.Broadcast();
    	PollTicketStatus();
    }
    
    bool UMatchmakingSubsystem::CancelMatchmaking()
    {
    	if (EdgeGapMatchmaker && bInQueue)
    	{
    		GetWorld()->GetTimerManager().ClearTimer(PollTicketStatusTimerHandle);
    
    		EdgeGap::MatchmakerModels::FDeleteTicketRequest Request;
    		Request.TicketId = TicketId;
    
    		EdgeGapMatchmaker->DeleteTicket(
    			Request,
    			EdgeGap::UEdgeGapMatchmaker::FDeleteTicketDelegate::CreateUObject(this, &UMatchmakingSubsystem::OnCancelMatchmakingSuccess),
    			EdgeGap::FEdgeGapErrorDelegate::CreateUObject(this, &UMatchmakingSubsystem::OnEdgeGapError)
    		);
    		return true;
    	}
    	return false;
    }
    
    void UMatchmakingSubsystem::OnCancelMatchmakingSuccess(const EdgeGap::MatchmakerModels::FDeleteTicketResponse& Result)
    {
    	bInQueue = false;
    	TicketId = "";
    
    	OnMatchmakingCanceledDelegate.Broadcast();
    }
    
    bool UMatchmakingSubsystem::GetTicketStatus()
    {
    	if (EdgeGapMatchmaker && bInQueue)
    	{
    		EdgeGap::MatchmakerModels::FGetTicketRequest Request;
    		Request.TicketId = TicketId;
    
    		EdgeGapMatchmaker->GetTicket(
    			Request,
    			EdgeGap::UEdgeGapMatchmaker::FGetTicketDelegate::CreateUObject(this, &UMatchmakingSubsystem::OnGetTicketSuccess),
    			EdgeGap::FEdgeGapErrorDelegate::CreateUObject(this, &UMatchmakingSubsystem::OnEdgeGapError)
    		);
    		return true;
    	}
    	return false;
    }
    
    void UMatchmakingSubsystem::OnGetTicketSuccess(const EdgeGap::MatchmakerModels::FGetTicketResponse& Result)
    {
    	if (Result.Assignement.IsValid())
    	{
    		GetWorld()->GetTimerManager().ClearTimer(PollTicketStatusTimerHandle);
    		OnMatchmakingCompletedDelegate.Broadcast();
    	}
    }
    
    void UMatchmakingSubsystem::PollTicketStatus()
    {
    	if (GetTicketStatus() && !PollTicketStatusTimerHandle.IsValid())
    	{
    		GetWorld()->GetTimerManager().SetTimer(PollTicketStatusTimerHandle, this, &UMatchmakingSubsystem::PollTicketStatus, 6, true);
    	}
    }
