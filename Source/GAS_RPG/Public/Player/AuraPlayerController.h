

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;//在Build.cs中添加"EnhancedInput"
class UInputAction;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class GAS_RPG_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuraPlayerController();
	
protected:
	virtual void BeginPlay() override;	
	virtual void SetupInputComponent() override;//处理输入,区别于Character中的SetupPlayerInputComponent
private:
	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;
	
	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	
	void Move(const FInputActionValue& InputActionValue);//结构体先声明可用struct，或放上面去
};
