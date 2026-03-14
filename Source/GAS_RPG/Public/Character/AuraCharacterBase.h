

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

UCLASS(Abstract)//说明是抽象类，不能为它在关卡中创建实例
class GAS_RPG_API AAuraCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
//规范：	TObjectPtr<>在打包构建中，它和原始指针行为一致，但在编辑器中，它还有访问跟踪（监控指针被访问或解引用的频率）和可选的延迟加载功能（在程序实际需要或使用前不加载资源）
};
