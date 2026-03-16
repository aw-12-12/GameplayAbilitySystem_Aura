


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "GAS_RPG/GAS_RPG.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	/*EGameplayEffectReplicationMode:(1)Minimal:只复制最基本的游戏效果(GE)信息，这对拥有ASC的拥有者不起作用
	 * (2)Mixed:只复制最基本的GE信息到模拟代理，但向拥有者和自主代理复制完整信息
	 * (3)Full:向所有人复制完整的游戏信息
	*/
	
	
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");;
	 
}

void AAuraEnemy::HighlightActor()
{
	//bHighlighted = true;
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	
}

void AAuraEnemy::UnHighlightActor()
{
	//bHighlighted = false;
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}
