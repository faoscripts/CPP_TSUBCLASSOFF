#include "Teleporter.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATeleporter::ATeleporter()
{
	PrimaryActorTick.bCanEverTick = true;

	TeleportMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TeleportMesh"));
	RootComponent = TeleportMesh;

	TeleportTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TeleportTrigger"));
	TeleportTrigger->SetupAttachment(RootComponent);
	TeleportTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATeleporter::OnOverlapBegin);
	TeleportTrigger->OnComponentEndOverlap.AddDynamic(this, &ATeleporter::OnOverlapEnd);

	TeleportPoint = CreateDefaultSubobject<UBoxComponent>(TEXT("TeleportPoint"));
	TeleportPoint->SetupAttachment(RootComponent);

	TeleportEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TeleportEffect"));
	TeleportEffect->SetupAttachment(RootComponent);

	TeleportSound = CreateDefaultSubobject<UAudioComponent>(TEXT("TeleportSound"));
	TeleportSound->SetupAttachment(RootComponent);
}

FVector ATeleporter::GetTeleportPoint()
{
	return TeleportPoint->GetComponentLocation();
}

void ATeleporter::OnTeleport()
{
	CanTeleport = false;
	if (TeleportEffect)
	{
		TeleportEffect->ActivateSystem();
	}
	if (TeleportSound)
	{
		TeleportSound->Play();
	}
}

void ATeleporter::BeginPlay()
{
	Super::BeginPlay();

	CanTeleport = true;
}

void ATeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATeleporter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (TargetTeleporter && OtherActor && CanTeleport)
	{
		//Check if actor in the list of allowed
		bool bIsAllowed = EnabledClass.ContainsByPredicate([OtherActor](const TSubclassOf<AActor>& AllowedClass)
		{
			return OtherActor->IsA(AllowedClass);
		});

		if (bIsAllowed)
		{
			UE_LOG(LogTemp, Display, TEXT("TELEPORT"));

			TargetTeleporter->OnTeleport();
			OtherActor->SetActorLocation(TargetTeleporter->GetTeleportPoint());

			if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
			{
				if (PlayerController->GetPawn() == OtherActor)
				{
					PerformFade(OtherActor);
				}
			}
		}
	}
}

void ATeleporter::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Display, TEXT("FUNCIONA"));
	CanTeleport = true;
}

void ATeleporter::PerformFade(AActor* PlayerActor)
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
	{
		APlayerCameraManager* CameraManager = PlayerController->PlayerCameraManager;
		if (CameraManager)
		{
			CameraManager->StartCameraFade(0.f, 1.f, 0.5f, FLinearColor::Black, false, true);
			GetWorld()->GetTimerManager().SetTimerForNextTick([CameraManager]()
			{
				CameraManager->StartCameraFade(1.f, 0.f, 0.5f, FLinearColor::Black, false, true);
			});
		}
	}
}

#if WITH_EDITOR
void ATeleporter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    // Verifica si la propiedad modificada es TargetTeleporter
    FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
    if (PropertyName == GET_MEMBER_NAME_CHECKED(ATeleporter, TargetTeleporter))
    {
        if (TargetTeleporter)
        {
            // Asigna el teletransportador inverso
            TargetTeleporter->TargetTeleporter = this;
        }
    }
}
#endif

