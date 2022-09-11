// Copyright Epic Games, Inc. All Rights Reserved.


#include "TDProject/Public/TDProjectGameMode.h"
#include "TDProject/Public/TDProjectPlayerController.h"
#include "UObject/ConstructorHelpers.h"

ATDProjectGameMode::ATDProjectGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATDProjectPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TDP/Blueprints/Character/BP_Character_Player"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}