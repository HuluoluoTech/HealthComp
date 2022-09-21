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



https://docs.unrealengine.com/5.0/en-US/adding-components-to-an-actor-in-unreal-engine/
