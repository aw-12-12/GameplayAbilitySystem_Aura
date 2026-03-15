
//高亮显示使AuraPlayerController依赖于AuraEnemy，因此为了提高适应性，来创建一个接口类(IEnemyInterface)，当鼠标悬停在一个对象上时，可以检查它是否实现这个接口,接口类调用接口函数，而AuraPlayerController不要知道当悬停是要做什么
//只要知道如果对象实现接口，应该调用接口函数，而actor可以重写并以任何方式实现这些功能【ITargetInterface】【IHighlightInterface】

#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

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
	CurrentMouseCursor = DefaultMouseCursor;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);//增强输入动作要绑定函数，以便处理输入数据，需要将输入组件转换成增强输入组件,使用CastChecked一次性转换和检查
	
	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);//代替旧版本的BindAction和BindAxis
	//参数依次为：Action对象, 触发状态, 响应对象(this), 响应函数名
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f,Rotation.Yaw,0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	//通过FRotationMatrix(Rotation)，你可以瞬时获得该旋转下的所有空间坐标轴.FRotator存储是三个角度（P、Y、R），而FRotationMatrix将这些角度转换成空间中的三根轴（前、右、上）
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
}
