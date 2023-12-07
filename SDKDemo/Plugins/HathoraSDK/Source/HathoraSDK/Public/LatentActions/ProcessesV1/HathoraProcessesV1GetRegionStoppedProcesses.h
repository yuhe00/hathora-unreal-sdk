// Copyright 2023 Hathora, Inc.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "HathoraTypes.h"
#include "HathoraProcessesV1LatentCommon.h"
#include "HathoraProcessesV1GetRegionStoppedProcesses.generated.h"

UCLASS()
class HATHORASDK_API UHathoraProcessesV1GetRegionStoppedProcesses : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

	// Retrieve 10 most recently stopped process objects for an application.
	// filtered by Region.
	// @param Region Filter the returned processes by the provided region.
	UFUNCTION(
		BlueprintCallable,
		meta =
			(BlueprintInternalUseOnly = "true",
			 Category = "HathoraSDK | ProcessesV1",
			 WorldContext = "WorldContextObject")
	)
	static UHathoraProcessesV1GetRegionStoppedProcesses *GetRegionStoppedProcesses(
		UHathoraSDKProcessesV1 *HathoraSDKProcessesV1,
		UObject *WorldContextObject,
		EHathoraCloudRegion Region
	);

	UPROPERTY(BlueprintAssignable)
	FHathoraProcessesV1OnProcessInfos OnComplete;

	UPROPERTY()
	UHathoraSDKProcessesV1 *HathoraSDKProcessesV1;

	EHathoraCloudRegion Region;
};