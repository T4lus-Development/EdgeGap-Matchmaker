#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

#include "EdgeGapMatchmakerError.h"
#include "EdgeGapMatchmakerDataModels.h"

namespace EdgeGap
{
	class EDGEGAPMATCHMAKER_API UEdgeGapMatchmaker
	{
	public:
		DECLARE_DELEGATE_OneParam(FCreateTicketDelegate, const MatchmakerModels::FCreateTicketResponse&);
		DECLARE_DELEGATE_OneParam(FGetTicketDelegate, const MatchmakerModels::FGetTicketResponse&);
		DECLARE_DELEGATE_OneParam(FDeleteTicketDelegate, const MatchmakerModels::FDeleteTicketResponse&);


		UEdgeGapMatchmaker();
		~UEdgeGapMatchmaker();

		int GetPendingCalls() const;

		void SetMatchmakerURL(FString URL);
		void SetMatchmakerAPIToken(FString Token);


		bool CreateTicket(MatchmakerModels::FCreateTicketRequest& request, const FCreateTicketDelegate& SuccessDelegate = FCreateTicketDelegate(), const FEdgeGapErrorDelegate& ErrorDelegate = FEdgeGapErrorDelegate());

		bool GetTicket(MatchmakerModels::FGetTicketRequest& request, const FGetTicketDelegate& SuccessDelegate = FGetTicketDelegate(), const FEdgeGapErrorDelegate& ErrorDelegate = FEdgeGapErrorDelegate());

		bool DeleteTicket(MatchmakerModels::FDeleteTicketRequest& request, const FDeleteTicketDelegate& SuccessDelegate = FDeleteTicketDelegate(), const FEdgeGapErrorDelegate& ErrorDelegate = FEdgeGapErrorDelegate());

	private:
		void OnCreateTicketResult(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FCreateTicketDelegate SuccessDelegate, FEdgeGapErrorDelegate ErrorDelegate);
		void OnGetTicketResult(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FGetTicketDelegate SuccessDelegate, FEdgeGapErrorDelegate ErrorDelegate);
		void OnDeleteTicketResult(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FDeleteTicketDelegate SuccessDelegate, FEdgeGapErrorDelegate ErrorDelegate);

	protected:
		FString MatchmakerURL = "";
		FString MatchmakerAPIToken = "";

	};

}