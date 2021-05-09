#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"

UENUM(BlueprintType)
enum class ECharacterSpeed : uint8
{
	Walk, Run, Sprint, Max
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_ZOMBIEHUNT_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Stats")
		float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Stats")
		float MaxStamina = 100.0f;

private: //Scene Component
	UPROPERTY(EditAnywhere, Category = "Speed")
		float Speed[(int32)ECharacterSpeed::Max] = { 200, 400, 600 };


public:
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }
	FORCEINLINE float GetHealth() { return Health; }
	FORCEINLINE float GetMaxStamina() { return MaxStamina; }
	FORCEINLINE float GetStamina() { return Stamina; }

	FORCEINLINE float GetWalkSpeed() { return Speed[(int32)ECharacterSpeed::Walk]; }
	FORCEINLINE float GetRunSpeed() { return Speed[(int32)ECharacterSpeed::Run]; }
	FORCEINLINE float GetSprintSpeed() { return Speed[(int32)ECharacterSpeed::Sprint]; }

	FORCEINLINE bool CanMove() { return bCanMove; }
	
public:
	UCStatusComponent();

	void AddHealth(float InAmount);
	void SubHealth(float InAmount);

	void AddStamina(float InAmount);
	void SubStamina(float InAmount);

	void SetMove();
	void SetStop();

	void SetSpeed(ECharacterSpeed InSpeed);

protected:
	virtual void BeginPlay() override;

private:
	float Health;
	float Stamina;
	bool bCanMove = true;
		
};
