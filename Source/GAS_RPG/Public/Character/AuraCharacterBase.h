

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"//必要IAbilitySystemInterface
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)//说明是抽象类，不能为它在关卡中创建实例
class GAS_RPG_API AAuraCharacterBase : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;//very useful,allows us to simply check any actor to see if it has this interface,can easily get its AbilitySystemComponent from it
	UAttributeSet* GetAttributeSet() const { return AttributeSet; };
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
//规范：	TObjectPtr<>在打包构建中，它和原始指针行为一致，但在编辑器中，它还有访问跟踪（监控指针被访问或解引用的频率）和可选的延迟加载功能（在程序实际需要或使用前不加载资源）
	
	//最佳实现
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
};

//Init Ability Actor Info
/*ASC有AbilityActorInfo的概念,有两个变量Owner Actor(实际拥有ASC),Avatar Actor(ASC在游戏世界的化身,可见)
 *对于Enemy,Owner Actor==Avatar Actor
 *对于Player-controlled character,Owner Actor=PlayerState,Avatar Actor=PlayerCharacter 
 */
/*调用UAbilitySystemComponent::InitAbilityActorInfo(AActor* InOwner,AActor* InAvatarActor)时机
 * after possession(the controller has been set for the pawn)
 * 1) Player-Controlled Character
 *		if ASC lives on the pawn,在Pawn的PossessedBy function(On the server)中调用,(On the Client)用AcknowledgePossession(Possession has occurred,the pawn has a valid controller),能确保ASC用AvatarActor和OwnerActor初始化,Owner==Avatar==Pawn
 *		if ASC lives on the PlayerState, (On the sever)PossessedBy,(On the Client)OnRep_PlayerState(这里要保证PlayerState is valid)[RepNotify,由于something being replicated,In this case,the playerstate will have been set on the server,playerstate is a replicated entity ],Owner = PlayerState,Avatar = PawnOrCharacter
 * 2) AI-Controlled Character
 *		ASC lives on the Pawn,(On the Sever and Client)BeginPlay  
 */


