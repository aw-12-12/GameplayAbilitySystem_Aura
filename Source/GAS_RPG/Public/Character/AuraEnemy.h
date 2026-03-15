

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"//使用接口应该包含
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API AAuraEnemy : public AAuraCharacterBase,public IEnemyInterface//使用接口本质上就是一种多重继承。在 Unreal Engine (UE) 的特殊框架下，你需要将接口理解为唯一被引擎允许的多重继承特例
{
	GENERATED_BODY()
public:
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;
};
