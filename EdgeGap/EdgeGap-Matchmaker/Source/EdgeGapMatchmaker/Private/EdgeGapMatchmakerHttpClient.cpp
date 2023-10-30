#include "EdgeGapMatchmakerHttpClient.h"
#include "EdgeGapMatchmakerModule.h"
#include "Serialization/JsonSerializer.h"

using namespace EdgeGap;

int EdgeGapHttpClient::pendingCalls = 0;

int EdgeGapHttpClient::GetPendingCalls()
{
    return EdgeGapHttpClient::pendingCalls;
}

TSharedRef<IHttpRequest> EdgeGapHttpClient::SendRequest(const FString& urlBase, const FString& urlPath, const FString& callBody, const FString& authKey, const FString& authValue)
{
    FString fullUrl = urlBase + urlPath;
    return SendFullUrlRequest(fullUrl, callBody, authKey, authValue);
}

TSharedRef<IHttpRequest> EdgeGapHttpClient::SendFullUrlRequest(const FString& fullUrl, const FString& callBody, const FString& authKey, const FString& authValue)
{
    EdgeGapHttpClient::pendingCalls += 1;

    TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb(TEXT("POST"));
    HttpRequest->SetURL(fullUrl);
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
    HttpRequest->SetTimeout(30);

    if (authKey != TEXT(""))
        HttpRequest->SetHeader(authKey, authValue);

    HttpRequest->SetContentAsString(callBody);
    return HttpRequest;
}

TSharedRef<IHttpRequest> EdgeGapHttpClient::PostRequest(const FString& fullUrl, const FString& callBody, const FString& authKey, const FString& authValue)
{
    EdgeGapHttpClient::pendingCalls += 1;

    TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb(TEXT("POST"));
    HttpRequest->SetURL(fullUrl);
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
    HttpRequest->SetTimeout(30);

    if (authKey != TEXT(""))
        HttpRequest->SetHeader(authKey, authValue);

    HttpRequest->SetContentAsString(callBody);
    return HttpRequest;
}

TSharedRef<IHttpRequest> EdgeGapHttpClient::GetRequest(const FString& fullUrl, const FString& authKey, const FString& authValue)
{
    EdgeGapHttpClient::pendingCalls += 1;

    TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb(TEXT("GET"));
    HttpRequest->SetURL(fullUrl);
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
    HttpRequest->SetTimeout(30);

    if (authKey != TEXT(""))
        HttpRequest->SetHeader(authKey, authValue);

    return HttpRequest;
}

TSharedRef<IHttpRequest> EdgeGapHttpClient::DeleteRequest(const FString& fullUrl, const FString& authKey, const FString& authValue)
{
    EdgeGapHttpClient::pendingCalls += 1;

    TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb(TEXT("DELETE"));
    HttpRequest->SetURL(fullUrl);
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
    HttpRequest->SetTimeout(30);

    if (authKey != TEXT(""))
        HttpRequest->SetHeader(authKey, authValue);

    return HttpRequest;
}

bool EdgeGapHttpClient::DecodeRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, EdgeGap::FEdgeGapResultCommon& OutResult, EdgeGap::FEdgeGapError& OutError)
{
    EdgeGapHttpClient::pendingCalls -= 1;

    FString ResponseStr, ErrorStr;
    if (bSucceeded && HttpResponse.IsValid())
    {
        if (EHttpResponseCodes::IsOk(HttpResponse->GetResponseCode()))
        {
            // Create the Json parser
            ResponseStr = HttpResponse->GetContentAsString();
            TSharedPtr<FJsonObject> JsonObject;
            TSharedRef<TJsonReader<> > JsonReader = TJsonReaderFactory<>::Create(ResponseStr);

            if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
            {
                if (EdgeGapHttpClient::DecodeError(JsonObject, OutError))
                {
                    return false;
                }

                bool HasSucceeded = false;

                const TSharedPtr<FJsonObject>* DataJsonObject;
                if (JsonObject->TryGetObjectField(TEXT("data"), DataJsonObject))
                {
                    HasSucceeded = OutResult.readFromValue(*DataJsonObject);
                }

                const TSharedPtr<FJsonValue> RequestIdValue = JsonObject->TryGetField(TEXT("ticket_id"));
                if (RequestIdValue.IsValid() && !RequestIdValue->IsNull())
                {
                    FString TmpValue;
                    if (RequestIdValue->TryGetString(TmpValue)) { OutResult.RequestId = TmpValue; }
                }

                return HasSucceeded;
            }
        }
        else
        {
            // Create the Json parser
            ResponseStr = HttpResponse->GetContentAsString();
            TSharedPtr<FJsonObject> JsonObject;
            TSharedRef<TJsonReader<> > JsonReader = TJsonReaderFactory<>::Create(ResponseStr);

            if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
            {
                if (EdgeGapHttpClient::DecodeError(JsonObject, OutError))
                {
                    return false;
                }
            }
        }
    }

    // If we get here, we failed to connect meaningfully to the server - Assume a timeout
    OutError.HttpCode = 408;
    OutError.ErrorCode = EdgeGapErrorConnectionTimeout;
    // For text returns, use the non-json response if possible, else default to no response
    OutError.ErrorName = OutError.ErrorMessage = OutError.HttpStatus = TEXT("Request Timeout or null response");

    return false;
}

bool EdgeGapHttpClient::DecodeError(TSharedPtr<FJsonObject> JsonObject, EdgeGap::FEdgeGapError& OutError)
{
    // check if returned json indicates an error
    if (JsonObject->HasField(TEXT("errorCode")))
    {
        // deserialize the FEdgeGapError object 
        JsonObject->TryGetNumberField(TEXT("errorCode"), OutError.ErrorCode);
        JsonObject->TryGetNumberField(TEXT("code"), OutError.HttpCode);
        JsonObject->TryGetStringField(TEXT("status"), OutError.HttpStatus);
        JsonObject->TryGetStringField(TEXT("error"), OutError.ErrorName);
        JsonObject->TryGetStringField(TEXT("errorMessage"), OutError.ErrorMessage);

        const TSharedPtr<FJsonObject>* obj;
        if (JsonObject->TryGetObjectField(TEXT("errorDetails"), obj))
        {
            auto vals = (*obj)->Values;
            for (auto val : vals)
            {
                if (val.Value->AsArray().Num() > 0)
                {
                    for (const auto& item : val.Value->AsArray())
                    {
                        OutError.ErrorDetails.Add(val.Key, item->AsString());
                    }
                }
                else
                {
                    OutError.ErrorDetails.Add(val.Key, val.Value->AsString());
                }
            }
        }

        // TODO: handle global error delegate here

        // We encountered no errors parsing the error
        return true;
    }

    return false;
}
