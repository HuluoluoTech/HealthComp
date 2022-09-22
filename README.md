# HealthComp

## Gameplay 第一课： Adding Components to an Actor  

### 知识点：  
1.三种基本Components  

1.1 Actor Components(UActorComponent)  
useful for abstract behaviors such as movement, inventory or attribute management, and other non-physical concepts.
Actor Components do not have a Transform property.

1.2 Scene Components(USceneComponent, a child of UActorComponent)  
support location-based behaviors that do not require a geometric representation. 
This includes spring arms, cameras, physical forces and constraints (not physical objects), and audio.

1.3 Primitive Components(UPrimitive Component  a child of USceneComponent)  
 geometric representation, which are generally used to render visual elements, or to collide or overlap with physical objects
This includes Static or Skeletal Meshes, sprites, billboards, and particle systems as well as box, capsule, and sphere collision volumes.

---

2. 添加 Input Action Mapping
3. 添加 DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams
4. 设置回调
```c
MyOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleTakeAnyDamage);
```
5. 添加 utility helper functions
```c
#include "Kismet/GameplayStatics.h"
```
6. Apply Damege
```c
UGameplayStatics::ApplyDamage(this, 20.0f, GetInstigatorController(),this,GenericDamageType);
```

---

## Gameplay 第二课：Event Dispatch and Delegates
### 知识点：
1.  给 BossActor 添加代理
```c
DECLARE_DELEGATE(FOnBossDiedDelegate);
```

2.  设置简单的碰撞体 UBoxComponent
```c
	BoxComp->SetVisibility(true);
	BoxComp->SetHiddenInGame(false);
```

3.  实现 NotifyActorBeginOverlap
4.  给 DoorActor 实现开门效果
4.1 UTimelineComponent 、 FOnTimelineFloat 和 UCurveFloat 配合使用
5. 最后，通过设置 Door 的 Z 旋转，开启门的效果
```c
    FRotator DoorNewRotation = FRotator(0.0f, Output, 0.f);
    Door->SetRelativeRotation(DoorNewRotation);
```
## Gameplay 第三课：Interface
### 知识点：
1.  创建 Interface

2. 多个Component的话，创建一个底层 USceneComponent ;Useful as a 'dummy' component in the hierarchy to offset others.
```c
    // SceneComponent has a transform and supports attachment
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
    PointLightComp = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComp"));

    //StaticMeshComp->SetupAttachment(RootComponent);

    PointLightComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    PointLightComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    PointLightComp->SetWorldLocation(FVector(0, 0, -130));
```
3. 当 character 进入房间，打开 light; OtherActor 开关按钮
```c
	if (IInteractInterface* ActorCheck = Cast<IInteractInterface>(OtherActor))
	{
		ActorCheck->OnInteract();
	}
```

## Gameplay 第四课：Finding Actors
### 知识点：
1.  引入声音模块、和粒子系统
```c
UAudioComponent
UParticleSystemComponent
```

2. 添加Tag
```c
Tags.Add(FName("FindActorTag"));
```

3. 查找带有Tag的Actor
```c
	TArray<AActor*> ActorsToFind;
	if (UWorld* World = GetWorld())
	{
		//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFireEffect::StaticClass(), ActorsToFind);
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AFireEffect::StaticClass(), FName("FindActorTag"), ActorsToFind);
	}

	for (AActor* FireEffectActor : ActorsToFind)
	{
		//Is this Actor of type FireEffect class?
		AFireEffect* FireEffectCast = Cast<AFireEffect>(FireEffectActor);
		if (FireEffectCast)
		{
			//Get the Particle Fire Component and deactivate it.            
			FireEffectCast->GetParticleFireComponent()->Deactivate();

			//Get the Fire Audio Component and deactivate it.           
			FireEffectCast->GetFireAudioComponent()->Deactivate();
		}
	}
```

## Gameplay 第五课：Respawn
### 知识点：
1.  创建基于 GameModeBase 的 gamemode
2.  把默认的GameMode 修改 新的GameMode；Edit->Project Setting->General->Maps&Modes
3.  绑定R键，模拟Actor Destroy操作
4.  RestartPlayer
```c
GameMode->RestartPlayer(CortollerRef);
```
5.  覆盖默认的GameMode
https://docs.unrealengine.com/5.0/en-US/setting-up-a-game-mode-in-unreal-engine/
Window -> World Setting -> GameMode -> GameMode Override 中选择

## Gameplay 第六课：Posses pawn
### 知识点：
1. 创建2个Role
2. 选中2个，open level blueprint
3. Create References to 2 selected Actors
4. 添加input 按键
5. 链接 possess 事件


---

https://docs.unrealengine.com/5.0/en-US/adding-components-to-an-actor-in-unreal-engine/
