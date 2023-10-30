#pragma once

#include "CoreMinimal.h"
#include "EdgeGapMatchmakerBaseModel.h"
#include "EdgeGapMatchmakerError.h"
#include "Http.h"

namespace EdgeGap
{
    class EdgeGapHttpClient
    {
    private:
        static int pendingCalls;

    public:
        static int GetPendingCalls();
        static TSharedRef<IHttpRequest> SendRequest(const FString& urlBase, const FString& urlPath, const FString& callBody, const FString& authKey, const FString& authValue);
        static TSharedRef<IHttpRequest> SendFullUrlRequest(const FString& fullUrl, const FString& callBody, const FString& authKey, const FString& authValue);

        static TSharedRef<IHttpRequest> PostRequest(const FString& fullUrl, const FString& callBody, const FString& authKey, const FString& authValue);
        static TSharedRef<IHttpRequest> GetRequest(const FString& fullUrl, const FString& authKey, const FString& authValue);
        static TSharedRef<IHttpRequest> DeleteRequest(const FString& fullUrl, const FString& authKey, const FString& authValue);

        static bool DecodeRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, EdgeGap::FEdgeGapResultCommon& OutResult, EdgeGap::FEdgeGapError& OutError);
        static bool DecodeError(TSharedPtr<FJsonObject> JsonObject, EdgeGap::FEdgeGapError& OutError);
    };
};
