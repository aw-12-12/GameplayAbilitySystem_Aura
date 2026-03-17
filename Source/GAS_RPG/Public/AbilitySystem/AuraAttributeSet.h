

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAuraAttributeSet();
	
	//同步注册变量必备,必须重写才能同步任何变量
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Health,Category = "Vital Attributes")
	FGameplayAttributeData Health;
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxHealth,Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	
	UPROPERTY(BlueprintReadOnly,Replicatedusing = OnRep_Mana,Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	
	UPROPERTY(BlueprintReadOnly,Replicatedusing = OnRep_MaxMana,Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	
	UFUNCTION()//成为一个repnotify，必须是UFUNCTION【回调函数都必须是 UFUNCTION】
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;//可不带参数，也可以带一个必须是复制变量类型的参数，接受旧值有助于比较新旧值
	//OnRep 的职责是响应变化（更新 UI、播放特效、通知其他系统），而不是产生变化。把函数设为 const 是一种强约束，防止你在同步回调里又去改属性，导致逻辑混乱甚至网络死循环。
	
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	
};
//当服务器上的一个变量发生了改变，并同步到客户端时，客户端会自动触发一个特定的回调函数。这个“变量同步 + 触发函数”的组合就叫 RepNotify

//GEchange预测是GAS的内置功能
//延迟补偿
//属性是一个FGameplayAttributeData类型对象，存放在AS中，包含BaseValue,CurrentValue