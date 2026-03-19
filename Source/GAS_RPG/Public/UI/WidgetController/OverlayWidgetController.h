

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

struct FOnAttributeChangeData;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);//声明委托类型,// 声明一个带有一个 float 参数的动态多播委托 (常用于暴露给蓝图)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature,float,NewMaxHealth);

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class GAS_RPG_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	
	//创建委托对象,实例化动态多播委托
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attributes")//允许在蓝图中为该委托绑定事件（Assign）或监听回调,专门用于 多播动态委托,暴露给蓝图
	FOnHealthChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;
	
	virtual void BindCallbacksToDependencies() override;
	
protected:
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
};
