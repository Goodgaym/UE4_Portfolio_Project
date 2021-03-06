#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Characters/ICharacter.h"
#include "GenericTeamAgentInterface.h"
#include "CPlayer.generated.h"

UCLASS()
class UE_ZOMBIEHUNT_API ACPlayer : public ACharacter, public IICharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		uint8 TeamID = 1;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<class UCUserWidget_Ammo> WidgetAmmoClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<class UCUserWidget_StatusBar> StatusBarClass;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
		class USoundCue* HitSound;

private: //Scene Component
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

protected:
	UFUNCTION(BlueprintImplementableEvent)
		void ZoomIn();

	UFUNCTION(BlueprintImplementableEvent)
		void ZoomOut();

private: //Actor Component
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UCOptionComponent* Option;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UCMontagesComponent* Montages;

	UPROPERTY(VisibleDefaultsOnly)
		class UCActionComponent* Action;

	UPROPERTY(VisibleDefaultsOnly)
		class UCInventoryComponent* Inventory;

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);

private:
	void PressedForward();
	void ReleasedForward();
	void PressedSprint();
	void ReleasedSprint();
	void OnSprint();
	void OffSprint();

private:
	void OnEvade();

private:
	void Begin_BackStep();
	void Begin_Roll();

public:
	void End_BackStep();
	void End_Roll();

private:
	void OnFist();
	void OnOneHand();
	void OnRifle();
	void OnShotgun();

	void OnDoAction();
	void OffDoAction();
	void OnAim();
	void OffAim();

	void OnAutoFire();
	void OnReload();

	void OnInteract();

public:
	class ACAttachment* GetAttachment();
	class ACDoAction* GetDoAction();

	UFUNCTION(BlueprintCallable)
		class UCActionComponent* GetActionComponent();

	UFUNCTION(BlueprintCallable)
		class UCStatusComponent* GetStatusComponent();
	
public:
	void AddCurrentAmmo(int Amount);
	void SetCurrentAmmo(int Amount);
	int32 GetCurrentAmmo();

	void UpdateAmmo(uint32 CurrentAmmo);

private:
	void AmmoSelect();

public:
	bool GetRightClick() { return bRightClick; }
	bool GetSprintMode() { return bSprintMode; }

public:
	virtual void GetAimRay(FVector& OutAimStart, FVector& OutAimEnd, FVector& OutAimDirection, float SpreadSize) override;
	virtual float MoveSpeedRatio() override;

	virtual void OnFocus() override;
	virtual void OffFocus() override;

public:
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

private:
	virtual void Hitted() override;
	virtual void Dead() override;

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

private:
	UPROPERTY()
		class UCItem* SelectAmmo;

	TArray<FHitResult> hitResults;

	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;

	class UCUserWidget_Ammo* WidgetAmmo;
	class UCUserWidget_StatusBar* WidgetStatus;

	bool bRightClick;
	bool bSprintMode;
	bool bPushForward;
	bool bPushSprint;

	float SpreadAim;
	float DamageValue;

	//Temp
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSoftObjectPtr<class ACItemSpawner> ItemSpawner;

	void TestButton();
	//Temp
};
