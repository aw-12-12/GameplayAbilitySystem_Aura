


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;//属性复制，数据同步
	//多人游戏中，复制是当服务器上的实体发生变化时，服务器上的变化会复制或发送到所有连接的客户端，使在多台机器上进行更改【一台服务器，其余是客户端】
	//响应服务器上的数据更新，并将这些更新发送给客户端
	
	
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);//条件不满足时停止执行，检查是否设置了AuraContest
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	//子系统是单例模式，在程序运行期间只存在一个
	check(Subsystem);
	//添加AuraContext
	Subsystem->AddMappingContext(AuraContext,0);
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}
