// Copyright Epic Games, Inc. All Rights Reserved.

#include "CPP_TSUBCLASSOFFGameMode.h"
#include "CPP_TSUBCLASSOFFCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACPP_TSUBCLASSOFFGameMode::ACPP_TSUBCLASSOFFGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
