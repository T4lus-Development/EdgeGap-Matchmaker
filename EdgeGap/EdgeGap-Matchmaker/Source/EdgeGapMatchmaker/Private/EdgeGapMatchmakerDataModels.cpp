
#include "EdgeGapMatchmakerDataModels.h"


using namespace EdgeGap;
using namespace EdgeGap::MatchmakerModels;

EdgeGap::MatchmakerModels::FSelectorData::~FSelectorData()
{

}

void EdgeGap::MatchmakerModels::FSelectorData::writeJSON(JsonWriter& writer) const
{
    writer->WriteObjectStart();

    if (Data.Num() != 0)
    {
        for (TMap<FString, FString>::TConstIterator It(Data); It; ++It)
        {
            writer->WriteIdentifierPrefix((*It).Key);
            writer->WriteValue((*It).Value);
        }
    }

    writer->WriteObjectEnd();
}

bool EdgeGap::MatchmakerModels::FSelectorData::readFromValue(const TSharedPtr<FJsonObject>& obj)
{
    bool HasSucceeded = true;

    for (TMap<FString, TSharedPtr<FJsonValue>>::TConstIterator It(obj->Values); It; ++It)
    {
        Data.Add(It.Key(), It.Value()->AsString());
    }

    return HasSucceeded;
}

EdgeGap::MatchmakerModels::FFilterData::~FFilterData()
{

}

void EdgeGap::MatchmakerModels::FFilterData::writeJSON(JsonWriter& writer) const
{
    writer->WriteObjectStart();

    if (Data.Num() != 0)
    {
        for (TMap<FString, float>::TConstIterator It(Data); It; ++It)
        {
            writer->WriteIdentifierPrefix((*It).Key);
            writer->WriteValue((*It).Value);
        }
    }

    writer->WriteObjectEnd();
}

bool EdgeGap::MatchmakerModels::FFilterData::readFromValue(const TSharedPtr<FJsonObject>& obj)
{
    bool HasSucceeded = true;

    for (TMap<FString, TSharedPtr<FJsonValue>>::TConstIterator It(obj->Values); It; ++It)
    {
        Data.Add(It.Key(), It.Value()->AsNumber());
    }

    return HasSucceeded;
}

EdgeGap::MatchmakerModels::FMatchmakingData::~FMatchmakingData()
{
    //if (Trade != nullptr) delete Trade;

}

void EdgeGap::MatchmakerModels::FMatchmakingData::writeJSON(JsonWriter& writer) const
{
    writer->WriteObjectStart();

    if (SelectorData.IsValid())
    {
        writer->WriteIdentifierPrefix(TEXT("selector_data"));
        SelectorData->writeJSON(writer);
    }
    else
    {
        writer->WriteIdentifierPrefix(TEXT("selector_data"));
        writer->WriteObjectStart();
        writer->WriteObjectEnd();
    }

    if (FilterData.IsValid())
    {
        writer->WriteIdentifierPrefix(TEXT("filter_data"));
        FilterData->writeJSON(writer);
    }
    else
    {
        writer->WriteIdentifierPrefix(TEXT("filter_data"));
        writer->WriteObjectStart();
        writer->WriteObjectEnd();
    }

    writer->WriteObjectEnd();
}

bool EdgeGap::MatchmakerModels::FMatchmakingData::readFromValue(const TSharedPtr<FJsonObject>& obj)
{
    bool HasSucceeded = true;

    const TSharedPtr<FJsonValue> SelectorDataValue = obj->TryGetField(TEXT("selector_data"));
    if (SelectorDataValue.IsValid() && !SelectorDataValue->IsNull())
    {
        SelectorData = MakeShareable(new FSelectorData(SelectorDataValue->AsObject()));
    }

    const TSharedPtr<FJsonValue> FilterDataValue = obj->TryGetField(TEXT("filter_data"));
    if (FilterDataValue.IsValid() && !FilterDataValue->IsNull())
    {
        FilterData = MakeShareable(new FFilterData(FilterDataValue->AsObject()));
    }

    return HasSucceeded;
}

EdgeGap::MatchmakerModels::FCreateTicketRequest::~FCreateTicketRequest()
{

}

void EdgeGap::MatchmakerModels::FCreateTicketRequest::writeJSON(JsonWriter& writer) const
{
    writer->WriteObjectStart();

    if (!ProfileId.IsEmpty() == false)
    {
        UE_LOG(LogEdgeGapMatchmaker, Error, TEXT("This field is required: CreateTicketRequest::ProfileId"));
    }
    else
    {
        writer->WriteIdentifierPrefix(TEXT("edgegap_profile_id"));
        writer->WriteValue(ProfileId);
    }

    if (MatchmakingData.IsValid())
    {
        writer->WriteIdentifierPrefix(TEXT("matchmaking_data"));
        MatchmakingData->writeJSON(writer);
    }

    writer->WriteObjectEnd();
}

bool EdgeGap::MatchmakerModels::FCreateTicketRequest::readFromValue(const TSharedPtr<FJsonObject>& obj)
{
    bool HasSucceeded = true;

    const TSharedPtr<FJsonValue> ProfileIdValue = obj->TryGetField(TEXT("edgegap_profile_id"));
    if (ProfileIdValue.IsValid() && !ProfileIdValue->IsNull())
    {
        FString TmpValue;
        if (ProfileIdValue->TryGetString(TmpValue)) { ProfileId = TmpValue; }
    }

    const TSharedPtr<FJsonValue> MatchmakingDataValue = obj->TryGetField(TEXT("matchmaking_data"));
    if (MatchmakingDataValue.IsValid() && !MatchmakingDataValue->IsNull())
    {
        MatchmakingData = MakeShareable(new FMatchmakingData(MatchmakingDataValue->AsObject()));
    }

    return HasSucceeded;
}

EdgeGap::MatchmakerModels::FAssignement::~FAssignement()
{

}

void EdgeGap::MatchmakerModels::FAssignement::writeJSON(JsonWriter& writer) const
{
    writer->WriteObjectStart();

    if (ConnectionString.IsEmpty() == false)
    {
        writer->WriteIdentifierPrefix(TEXT("server_host"));
        writer->WriteValue(ConnectionString);
    }

    writer->WriteObjectEnd();
}

bool EdgeGap::MatchmakerModels::FAssignement::readFromValue(const TSharedPtr<FJsonObject>& obj)
{
    bool HasSucceeded = true;

    const TSharedPtr<FJsonValue> ConnectionStringValue = obj->TryGetField(TEXT("server_host"));
    if (ConnectionStringValue.IsValid() && !ConnectionStringValue->IsNull())
    {
        FString TmpValue;
        if (ConnectionStringValue->TryGetString(TmpValue)) { ConnectionString = TmpValue; }
    }

    return HasSucceeded;
}

EdgeGap::MatchmakerModels::FCreateTicketResponse::~FCreateTicketResponse()
{

}

void EdgeGap::MatchmakerModels::FCreateTicketResponse::writeJSON(JsonWriter& writer) const
{
    writer->WriteObjectStart();

    if (TicketId.IsEmpty() == false)
    {
        writer->WriteIdentifierPrefix(TEXT("ticket_id"));
        writer->WriteValue(TicketId);
    }

    writer->WriteObjectEnd();
}

bool EdgeGap::MatchmakerModels::FCreateTicketResponse::readFromValue(const TSharedPtr<FJsonObject>& obj)
{
    bool HasSucceeded = true;

    const TSharedPtr<FJsonValue> TicketIdValue = obj->TryGetField(TEXT("ticket_id"));
    if (TicketIdValue.IsValid() && !TicketIdValue->IsNull())
    {
        FString TmpValue;
        if (TicketIdValue->TryGetString(TmpValue)) { TicketId = TmpValue; }
    }
    
    return HasSucceeded;
}

EdgeGap::MatchmakerModels::FGetTicketRequest::~FGetTicketRequest()
{

}

void EdgeGap::MatchmakerModels::FGetTicketRequest::writeJSON(JsonWriter& writer) const
{
    writer->WriteObjectStart();

    if (TicketId.IsEmpty() == false)
    {
        writer->WriteIdentifierPrefix(TEXT("ticket_id"));
        writer->WriteValue(TicketId);
    }

    writer->WriteObjectEnd();
}

bool EdgeGap::MatchmakerModels::FGetTicketRequest::readFromValue(const TSharedPtr<FJsonObject>& obj)
{
    bool HasSucceeded = true;

    const TSharedPtr<FJsonValue> TicketIdValue = obj->TryGetField(TEXT("ticket_id"));
    if (TicketIdValue.IsValid() && !TicketIdValue->IsNull())
    {
        FString TmpValue;
        if (TicketIdValue->TryGetString(TmpValue)) { TicketId = TmpValue; }
    }

    return HasSucceeded;
}

EdgeGap::MatchmakerModels::FGetTicketResponse::~FGetTicketResponse()
{

}

void EdgeGap::MatchmakerModels::FGetTicketResponse::writeJSON(JsonWriter& writer) const
{
    writer->WriteObjectStart();

    if (TicketId.IsEmpty() == false)
    {
        writer->WriteIdentifierPrefix(TEXT("ticket_id"));
        writer->WriteValue(TicketId);
    }

    if (Assignement.IsValid())
    {
        writer->WriteIdentifierPrefix(TEXT("assignment"));
        Assignement->writeJSON(writer);
    }

    writer->WriteObjectEnd();
}

bool EdgeGap::MatchmakerModels::FGetTicketResponse::readFromValue(const TSharedPtr<FJsonObject>& obj)
{
    bool HasSucceeded = true;

    const TSharedPtr<FJsonValue> TicketIdValue = obj->TryGetField(TEXT("ticket_id"));
    if (TicketIdValue.IsValid() && !TicketIdValue->IsNull())
    {
        FString TmpValue;
        if (TicketIdValue->TryGetString(TmpValue)) { TicketId = TmpValue; }
    }

    const TSharedPtr<FJsonValue> AssignmentDataValue = obj->TryGetField(TEXT("assignment"));
    if (AssignmentDataValue.IsValid() && !AssignmentDataValue->IsNull())
    {
        Assignement = MakeShareable(new FAssignement(AssignmentDataValue->AsObject()));
    }

    return HasSucceeded;
}

EdgeGap::MatchmakerModels::FDeleteTicketRequest::~FDeleteTicketRequest()
{

}

void EdgeGap::MatchmakerModels::FDeleteTicketRequest::writeJSON(JsonWriter& writer) const
{
    writer->WriteObjectStart();

    if (TicketId.IsEmpty() == false)
    {
        writer->WriteIdentifierPrefix(TEXT("ticket_id"));
        writer->WriteValue(TicketId);
    }

    writer->WriteObjectEnd();
}

bool EdgeGap::MatchmakerModels::FDeleteTicketRequest::readFromValue(const TSharedPtr<FJsonObject>& obj)
{
    bool HasSucceeded = true;

    const TSharedPtr<FJsonValue> TicketIdValue = obj->TryGetField(TEXT("ticket_id"));
    if (TicketIdValue.IsValid() && !TicketIdValue->IsNull())
    {
        FString TmpValue;
        if (TicketIdValue->TryGetString(TmpValue)) { TicketId = TmpValue; }
    }

    return HasSucceeded;
}

EdgeGap::MatchmakerModels::FDeleteTicketResponse::~FDeleteTicketResponse()
{

}

void EdgeGap::MatchmakerModels::FDeleteTicketResponse::writeJSON(JsonWriter& writer) const
{
    writer->WriteObjectStart();

    if (TicketId.IsEmpty() == false)
    {
        writer->WriteIdentifierPrefix(TEXT("ticket_id"));
        writer->WriteValue(TicketId);
    }

    writer->WriteObjectEnd();
}

bool EdgeGap::MatchmakerModels::FDeleteTicketResponse::readFromValue(const TSharedPtr<FJsonObject>& obj)
{
    bool HasSucceeded = true;

    const TSharedPtr<FJsonValue> TicketIdValue = obj->TryGetField(TEXT("ticket_id"));
    if (TicketIdValue.IsValid() && !TicketIdValue->IsNull())
    {
        FString TmpValue;
        if (TicketIdValue->TryGetString(TmpValue)) { TicketId = TmpValue; }
    }

    return HasSucceeded;
}