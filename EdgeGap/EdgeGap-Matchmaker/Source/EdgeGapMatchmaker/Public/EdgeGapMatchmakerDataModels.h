
#pragma once

#include "CoreMinimal.h"
#include "EdgeGapMatchmakerBaseModel.h"

namespace EdgeGap
{
	namespace MatchmakerModels
	{

        struct EDGEGAPMATCHMAKER_API FSelectorData : public EdgeGap::FEdgeGapBaseModel
        {
            TMap<FString, FString> Data;

            FSelectorData() :
                FEdgeGapBaseModel(),
                Data()
            {}

            FSelectorData(const FSelectorData& src) = default;

            FSelectorData(const TSharedPtr<FJsonObject>& obj) : FSelectorData()
            {
                readFromValue(obj);
            }

            ~FSelectorData();

            void writeJSON(JsonWriter& writer) const override;
            bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
        };

        struct EDGEGAPMATCHMAKER_API FFilterData : public EdgeGap::FEdgeGapBaseModel
        {
            TMap<FString, float> Data;

            FFilterData() :
                FEdgeGapBaseModel(),
                Data()
            {}

            FFilterData(const FFilterData& src) = default;

            FFilterData(const TSharedPtr<FJsonObject>& obj) : FFilterData()
            {
                readFromValue(obj);
            }

            ~FFilterData();

            void writeJSON(JsonWriter& writer) const override;
            bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
        };

        struct EDGEGAPMATCHMAKER_API FMatchmakingData : public EdgeGap::FEdgeGapBaseModel
        {
            TSharedPtr<FSelectorData> SelectorData;

            TSharedPtr<FFilterData> FilterData;

            FMatchmakingData() :
                FEdgeGapBaseModel(),
                SelectorData(),
                FilterData()
            {}

            FMatchmakingData(const FMatchmakingData& src) = default;

            FMatchmakingData(const TSharedPtr<FJsonObject>& obj) : FMatchmakingData()
            {
                readFromValue(obj);
            }

            ~FMatchmakingData();

            void writeJSON(JsonWriter& writer) const override;
            bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
        };

        struct EDGEGAPMATCHMAKER_API FCreateTicketRequest : public EdgeGap::FEdgeGapRequestCommon
        {
            FString ProfileId;

            TSharedPtr<FMatchmakingData> MatchmakingData;

            FCreateTicketRequest() :
                FEdgeGapRequestCommon(),
                ProfileId(),
                MatchmakingData(nullptr)
            {}

            FCreateTicketRequest(const FCreateTicketRequest& src) = default;

            FCreateTicketRequest(const TSharedPtr<FJsonObject>& obj) : FCreateTicketRequest()
            {
                readFromValue(obj);
            }

            ~FCreateTicketRequest();

            void writeJSON(JsonWriter& writer) const override;
            bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
        };

        struct EDGEGAPMATCHMAKER_API FAssignement : public EdgeGap::FEdgeGapBaseModel
        {
          
            FString ConnectionString;

            FAssignement() :
                FEdgeGapBaseModel(),
                ConnectionString()
            {}

            FAssignement(const FAssignement& src) = default;

            FAssignement(const TSharedPtr<FJsonObject>& obj) : FAssignement()
            {
                readFromValue(obj);
            }

            ~FAssignement();

            void writeJSON(JsonWriter& writer) const override;
            bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
        };

        struct EDGEGAPMATCHMAKER_API FCreateTicketResponse : public EdgeGap::FEdgeGapResultCommon
        {
            FString TicketId;

            FCreateTicketResponse() :
                FEdgeGapResultCommon(),
                TicketId()
            {}

            FCreateTicketResponse(const FCreateTicketResponse& src) = default;

            FCreateTicketResponse(const TSharedPtr<FJsonObject>& obj) : FCreateTicketResponse()
            {
                readFromValue(obj);
            }

            ~FCreateTicketResponse();

            void writeJSON(JsonWriter& writer) const override;
            bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
        };

        struct EDGEGAPMATCHMAKER_API FGetTicketRequest : public EdgeGap::FEdgeGapRequestCommon
        {
            FString TicketId;

            FGetTicketRequest() :
                FEdgeGapRequestCommon(),
                TicketId()
            {}

            FGetTicketRequest(const FGetTicketRequest& src) = default;

            FGetTicketRequest(const TSharedPtr<FJsonObject>& obj) : FGetTicketRequest()
            {
                readFromValue(obj);
            }

            ~FGetTicketRequest();

            void writeJSON(JsonWriter& writer) const override;
            bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
        };

        struct EDGEGAPMATCHMAKER_API FGetTicketResponse : public EdgeGap::FEdgeGapResultCommon
        {
            FString TicketId;

            TSharedPtr<FAssignement> Assignement;

            FGetTicketResponse() :
                FEdgeGapResultCommon(),
                TicketId(),
                Assignement()
            {}

            FGetTicketResponse(const FGetTicketResponse& src) = default;

            FGetTicketResponse(const TSharedPtr<FJsonObject>& obj) : FGetTicketResponse()
            {
                readFromValue(obj);
            }

            ~FGetTicketResponse();

            void writeJSON(JsonWriter& writer) const override;
            bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
        };

        struct EDGEGAPMATCHMAKER_API FDeleteTicketRequest : public EdgeGap::FEdgeGapRequestCommon
        {
            FString TicketId;

            FDeleteTicketRequest() :
                FEdgeGapRequestCommon(),
                TicketId()
            {}

            FDeleteTicketRequest(const FDeleteTicketRequest& src) = default;

            FDeleteTicketRequest(const TSharedPtr<FJsonObject>& obj) : FDeleteTicketRequest()
            {
                readFromValue(obj);
            }

            ~FDeleteTicketRequest();

            void writeJSON(JsonWriter& writer) const override;
            bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
        };

        struct EDGEGAPMATCHMAKER_API FDeleteTicketResponse : public EdgeGap::FEdgeGapResultCommon
        {
            FString TicketId;

            FDeleteTicketResponse() :
                FEdgeGapResultCommon(),
                TicketId()
            {}

            FDeleteTicketResponse(const FDeleteTicketResponse& src) = default;

            FDeleteTicketResponse(const TSharedPtr<FJsonObject>& obj) : FDeleteTicketResponse()
            {
                readFromValue(obj);
            }

            ~FDeleteTicketResponse();

            void writeJSON(JsonWriter& writer) const override;
            bool readFromValue(const TSharedPtr<FJsonObject>& obj) override;
        };

	}
}