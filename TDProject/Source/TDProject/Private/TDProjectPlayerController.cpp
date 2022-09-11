// Copyright Epic Games, Inc. All Rights Reserved.

#include "TDProject/Public/TDProjectPlayerController.h"

#include "DrawDebugHelpers.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "TDProject/TDProject.h"
#include "TDProject/Public/TDProjectCharacter.h"

ATDProjectPlayerController::ATDProjectPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ATDProjectPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	RotatePawnToMouseCursor();
	
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void ATDProjectPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ATDProjectPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ATDProjectPlayerController::OnSetDestinationReleased);
}

void ATDProjectPlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (IsValid(MyPawn->GetCursorToWorld()))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, GetMouseWorldLocation());
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}


void ATDProjectPlayerController::RotatePawnToMouseCursor()
{
	if (IsValid(MyPawn->GetCursorToWorld()))
	{
		FRotator PawnRotation = MyPawn->GetActorRotation();
		PawnRotation.Yaw = UKismetMathLibrary::FindLookAtRotation(MyPawn->GetActorLocation(), GetMouseWorldLocation()).Yaw;
		MyPawn->SetActorRotation(PawnRotation);
	}
}


void ATDProjectPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	if (IsValid(MyPawn))
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ATDProjectPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ATDProjectPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void ATDProjectPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	MyPawn = Cast<ATDProjectCharacter>(GetPawn());
	if (IsValid(MyPawn))
	{
		return;
	}
	UE_LOG(LogTDProject, Error, TEXT("Pawn Possess!"));
}

FVector ATDProjectPlayerController::GetMouseWorldLocation()
{
	return MyPawn->GetCursorToWorld()->GetComponentLocation();
}
