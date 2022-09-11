// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TDProjectCharacter.h"
#include "GameFramework/PlayerController.h"
#include "TDProjectPlayerController.generated.h"

UCLASS()
class ATDProjectPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATDProjectPlayerController();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	UPROPERTY(BlueprintReadWrite)
	ATDProjectCharacter* MyPawn;
	
	virtual void PlayerTick(float DeltaTime) override;
	
	virtual void SetupInputComponent() override;
	
	void OnPossess(APawn* InPawn) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FVector GetMouseWorldLocation();
	
	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Rotate player pawn to the current mouse cursor location. */
	void RotatePawnToMouseCursor();
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
};


