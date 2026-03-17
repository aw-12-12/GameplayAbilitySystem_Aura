 


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;//将旋转朝向运动
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	//开启平面限制开关
	GetCharacterMovement()->bConstrainToPlane = true;//这行代码的作用是：将角色的移动限制在一个 2D 平面上（禁止角色在某个轴向上的移动）
	//游戏开始时，自动纠正位置，吸附到平面上
	GetCharacterMovement()->bSnapToPlaneAtStart = true;//强行把角色“吸附”（Snap）到你限制的那个 2D 平面上。
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)//Has a valid player controller
{
	Super::PossessedBy(NewController);
	//Init ability actor info for the Server
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//Init ability actor info for the Client
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState =GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();
	AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState,this);
}
//MixedReplicationMode:当你的 OwnerActor 是 PlayerState 时，虚幻引擎的底层网络架构会自动将这个 PlayerState 的 Owner 设置为对应的 PlayerController