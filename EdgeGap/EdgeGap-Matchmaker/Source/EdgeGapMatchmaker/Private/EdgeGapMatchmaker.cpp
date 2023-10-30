
#include "EdgeGapMatchmaker.h"

#include "EdgeGapMatchmakerHttpClient.h"
#include "EdgeGapMatchmakerModule.h"

using namespace EdgeGap;

UEdgeGapMatchmaker::UEdgeGapMatchmaker() {}

UEdgeGapMatchmaker::~UEdgeGapMatchmaker() {}

int UEdgeGapMatchmaker::GetPendingCalls() const
{
    return EdgeGapHttpClient::GetPendingCalls();
}

void UEdgeGapMatchmaker::SetMatchmakerURL(FString URL)
{
    MatchmakerURL = URL;
}

void UEdgeGapMatchmaker::SetMatchmakerAPIToken(FString Token)
{
    MatchmakerAPIToken = Token;
}

bool UEdgeGapMatchmaker::CreateTicket(
    MatchmakerModels::FCreateTicketRequest& request,
    const FCreateTicketDelegate& SuccessDelegate,
    const FEdgeGapErrorDelegate& ErrorDelegate)
{
    if (MatchmakerURL.Len() == 0) {
        UE_LOG(LogEdgeGapMatchmaker, Error, TEXT("You must set Matchmaker URL before calling this function"));
        return false;
    }

    if (MatchmakerAPIToken.Len() == 0) {
        UE_LOG(LogEdgeGapMatchmaker, Error, TEXT("You must set Matchmaker API Token before calling this function"));
        return false;
    }


    auto HttpRequest = EdgeGapHttpClient::PostRequest(MatchmakerURL + TEXT("/v1/tickets"), request.toJSONString(), TEXT("Authorization"), MatchmakerAPIToken);
    HttpRequest->OnProcessRequestComplete().BindRaw(this, &UEdgeGapMatchmaker::OnCreateTicketResult, SuccessDelegate, ErrorDelegate);
    return HttpRequest->ProcessRequest();
}

void UEdgeGapMatchmaker::OnCreateTicketResult(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FCreateTicketDelegate SuccessDelegate, FEdgeGapErrorDelegate ErrorDelegate)
{
    MatchmakerModels::FCreateTicketResponse outResult;
    FEdgeGapError errorResult;
    if (EdgeGapHttpClient::DecodeRequest(HttpRequest, HttpResponse, bSucceeded, outResult, errorResult))
    {
        SuccessDelegate.ExecuteIfBound(outResult);
    }
    else
    {
        ErrorDelegate.ExecuteIfBound(errorResult);
    }
}

bool UEdgeGapMatchmaker::GetTicket(
    MatchmakerModels::FGetTicketRequest& request,
    const FGetTicketDelegate& SuccessDelegate,
    const FEdgeGapErrorDelegate& ErrorDelegate)
{
    if (MatchmakerURL.Len() == 0) {
        UE_LOG(LogEdgeGapMatchmaker, Error, TEXT("You must set Matchmaker URL before calling this function"));
        return false;
    }

    if (MatchmakerAPIToken.Len() == 0) {
        UE_LOG(LogEdgeGapMatchmaker, Error, TEXT("You must set Matchmaker API Token before calling this function"));
        return false;
    }


    auto HttpRequest = EdgeGapHttpClient::GetRequest(MatchmakerURL + TEXT("/v1/tickets/") + request.TicketId, TEXT("Authorization"), MatchmakerAPIToken);
    HttpRequest->OnProcessRequestComplete().BindRaw(this, &UEdgeGapMatchmaker::OnGetTicketResult, SuccessDelegate, ErrorDelegate);
    return HttpRequest->ProcessRequest();
}

void UEdgeGapMatchmaker::OnGetTicketResult(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FGetTicketDelegate SuccessDelegate, FEdgeGapErrorDelegate ErrorDelegate)
{
    MatchmakerModels::FGetTicketResponse outResult;
    FEdgeGapError errorResult;
    if (EdgeGapHttpClient::DecodeRequest(HttpRequest, HttpResponse, bSucceeded, outResult, errorResult))
    {
        SuccessDelegate.ExecuteIfBound(outResult);
    }
    else
    {
        ErrorDelegate.ExecuteIfBound(errorResult);
    }
}

bool UEdgeGapMatchmaker::DeleteTicket(
    MatchmakerModels::FDeleteTicketRequest& request,
    const FDeleteTicketDelegate& SuccessDelegate,
    const FEdgeGapErrorDelegate& ErrorDelegate)
{
    if (MatchmakerURL.Len() == 0) {
        UE_LOG(LogEdgeGapMatchmaker, Error, TEXT("You must set Matchmaker URL before calling this function"));
        return false;
    }

    if (MatchmakerAPIToken.Len() == 0) {
        UE_LOG(LogEdgeGapMatchmaker, Error, TEXT("You must set Matchmaker API Token before calling this function"));
        return false;
    }


    auto HttpRequest = EdgeGapHttpClient::DeleteRequest(MatchmakerURL + TEXT("/v1/tickets/") + request.TicketId, TEXT("Authorization"), MatchmakerAPIToken);
    HttpRequest->OnProcessRequestComplete().BindRaw(this, &UEdgeGapMatchmaker::OnDeleteTicketResult, SuccessDelegate, ErrorDelegate);
    return HttpRequest->ProcessRequest();
}

void UEdgeGapMatchmaker::OnDeleteTicketResult(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FDeleteTicketDelegate SuccessDelegate, FEdgeGapErrorDelegate ErrorDelegate)
{
    MatchmakerModels::FDeleteTicketResponse outResult;
    FEdgeGapError errorResult;
    if (EdgeGapHttpClient::DecodeRequest(HttpRequest, HttpResponse, bSucceeded, outResult, errorResult))
    {
        SuccessDelegate.ExecuteIfBound(outResult);
    }
    else
    {
        ErrorDelegate.ExecuteIfBound(errorResult);
    }
}