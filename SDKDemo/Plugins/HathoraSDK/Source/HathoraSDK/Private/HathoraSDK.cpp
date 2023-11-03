// Copyright 2023 Hathora, Inc.

#include "HathoraSDK.h"
#include "HathoraSDKModule.h"
#include "HathoraSDKDiscoveryV1.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

void UHathoraSDK::GetRegionalPings(const FHathoraOnGetRegionalPings& OnComplete, int32 NumPingsPerRegion)
{
	UHathoraSDK* SDK = UHathoraSDK::CreateHathoraSDK("", FHathoraSDKSecurity());
	SDK->AddToRoot(); // make sure this doesn't get garbage collected
	SDK->OnGetRegionalPingsComplete = OnComplete;
	FHathoraOnGetRegionalPings WrapperCallback;
	WrapperCallback.BindDynamic(SDK, &UHathoraSDK::OnGetRegionalPingsCompleteWrapper);
	SDK->DiscoveryV1->GetRegionalPings(WrapperCallback, NumPingsPerRegion);
}

UHathoraSDK* UHathoraSDK::CreateHathoraSDK(FString AppId, FHathoraSDKSecurity Security)
{
	UHathoraSDK* SDK = NewObject<UHathoraSDK>();
	SDK->DiscoveryV1 = NewObject<UHathoraSDKDiscoveryV1>();

	SDK->SetCredentials(AppId, Security);

	return SDK;
}

void UHathoraSDK::SetCredentials(FString AppId, FHathoraSDKSecurity Security)
{
	DiscoveryV1->SetCredentials(AppId, Security);
}

void UHathoraSDK::OnGetRegionalPingsCompleteWrapper(FHathoraRegionPings Result)
{
	OnGetRegionalPingsComplete.ExecuteIfBound(Result);
	RemoveFromRoot(); // Allow this SDK reference to be garbage collected
}
