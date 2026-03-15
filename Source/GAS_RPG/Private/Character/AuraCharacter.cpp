


#include "Character/AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

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
