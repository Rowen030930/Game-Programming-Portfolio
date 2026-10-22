# Unreal TPS Portfolio

**Unreal Engine 5.3.2 · C++ · Blueprint | 3인칭 슈팅 게임플레이 구현**

게임 클라이언트 개발에서 플레이어 입력부터 전투 판정, 적 AI 반응, 게임 종료까지 기능이 어떻게 연결되는지 직접 확인하고자 제작한 학습 포트폴리오입니다.

> **프로젝트 성격:** Unreal Engine 수업에서 익힌 기능과 Third Person 템플릿을 기반으로 구현·수정·디버깅한 개인 학습 작업물입니다. 기존 템플릿이나 강의 내용을 전부 독자 제작했다고 주장하지 않습니다.

## 먼저 확인할 영상

| 기능 | 영상 |
|---|---|
| 전체 플레이 및 Victory | [재생](https://youtu.be/XoBw_GwINzs) |
| 사격 및 헤드샷 | [재생](https://youtu.be/x4qWgP54mxI) |
| 적 AI 및 근접 공격 | [재생](https://youtu.be/hm-IxgJQrR8) |
| Game Over 및 Retry | [재생](https://youtu.be/yCE8idoXQ3I) |

## 사용 기술

- **엔진:** Unreal Engine 5.3.2
- **언어·스크립팅:** C++, Blueprint
- **개발 도구:** JetBrains Rider, Unreal Editor, Git/GitHub
- **기능:** Enhanced Input, Line Trace, AIController/NavMesh, Animation Montage·Notify, Collision/Overlap, ApplyDamage, UMG

## 핵심 구현 내용

### 1. 플레이어 입력·무기 장착·탄약

`AU_ClaudPortfCharacter`는 `Enhanced Input`으로 이동, 시점 조작, 점프, 무기 장착, 발사, 재장전 입력을 연결합니다.

- `AWeapon::Equip()`에서 무기를 캐릭터 컴포넌트의 소켓에 부착하고 장착 중 불필요한 충돌을 비활성화
- `AWeapon::Fire()`에서 탄약 잔량을 검사한 뒤 발사 처리
- `AWeapon::Reload()`에서 탄창의 빈 공간과 예비 탄약을 비교해 실제 보충할 수 있는 수량만 이동
- `AAmmoPickup`은 Overlap으로 획득 가능 여부를 확인한 뒤 예비 탄약을 추가
- UMG의 탄약·체력 정보를 플레이 상태에 맞춰 갱신

C++에서 확인되는 기본 탄창 용량은 `12`, 예비 탄약은 `36`입니다. 에디터의 Blueprint 속성은 C++ 기본값과 다르게 설정할 수 있습니다.

### 2. 카메라와 총구를 나눈 2단계 Line Trace

3인칭 카메라의 조준 위치와 실제 총구 위치는 다릅니다. 카메라 기준으로 한 번만 충돌을 검사하면, 총구 앞에 장애물이 있어도 벽을 통과해 맞는 것처럼 보일 수 있습니다.

**처리 흐름**

```text
발사 입력
  ↓
카메라 방향으로 Trace → 플레이어가 조준한 지점 계산
  ↓
총구 위치에서 조준 지점 방향으로 두 번째 Trace
  ↓
총구 앞 장애물을 포함한 실제 최초 충돌 판정
  ↓
피해 적용 및 이펙트 / HUD 갱신
```

주요 코드: `Weapon.cpp`의 `TraceAimPoint()`, `Fire()`.

- 첫 번째 Trace는 **조준 지점만 결정**하며, 실제 피격 대상으로 확정하지 않음
- 두 번째 Trace는 **총구에서 시작**해 총구와 목표 사이의 장애물 여부를 반영
- `FVector::DotProduct()`를 이용해 총구 기준 발사 방향이 카메라의 전방과 어긋나는 극단적인 경우를 처리
- 디버그 선과 충돌 지점 표시를 통해 조준·실제 탄착 차이를 확인하도록 구성

### 3. 충돌 부위에 따른 헤드샷

`AWeapon::Fire()`에서 적 캐릭터의 피격 정보를 검사하고, `AEnemyCharacter::IsHeadHit()`으로 Head Bone 여부를 구분합니다. 이후 `UGameplayStatics::ApplyDamage()`로 피해를 전달합니다.

- 몸통/머리 부위에 따라 별도 피해 값을 사용
- C++ 기본 설정은 몸통 `10`, 헤드샷 `40`이며 실제 플레이 값은 Blueprint 설정을 우선함
- `AEnemyCharacter::TakeDamage()`에서 체력을 줄이고 `Die()` 및 체력바 갱신으로 연결

*헤드샷이 올바르게 동작하려면 대상 Skeletal Mesh와 Physics Asset의 충돌·Bone 설정이 함께 맞아야 합니다.*

### 4. AI 추적과 발차기 공격

`AEnemyAIController`는 타이머를 사용해 주기적으로 플레이어를 검사하며, 조건에 따라 `MoveToActor()`로 추적하거나 공격으로 전환합니다.

- 감지 반경 기본값: `1500`
- 탐색 주기 기본값: `0.25초`
- NavMesh에 기반한 목표 이동 및 `AcceptanceRadius` 고려
- `AEnemyCharacter`에서 공격 거리·방향·시야 검사
- Montage의 `AttackHit` Notify 시점에 공격 판정 수행
- 발의 `foot_r`~`ball_r` 구간을 활용한 Capsule Overlap으로 접촉 여부 확인
- 플레이어 피해 처리와 넉백 반응 연결

공격 애니메이션이 실행되는 것과 **실제로 판정이 맞는 것**을 별개의 문제로 보고, 거리·방향·충돌 범위를 함께 확인했습니다.

### 5. 게임 종료 상태 관리

`AU_ClaudPortfGameMode`에서 살아 있는 적을 집계하고, 처치 시 중복 카운팅을 방지하도록 관리했습니다.

- 마지막 적 처치 시 `Victory`
- 플레이어 체력 소진 시 `Game Over`
- 게임이 이미 종료되었으면 종료 처리의 중복 실행 차단
- `RestartCurrentLevel()`로 현재 레벨 재시작
- `QuitCurrentGame()`으로 종료 처리

## 디버깅 사례: 적의 근접 공격이 맞지 않는 문제

**현상:** 적이 플레이어를 추적하고 공격 애니메이션까지 재생했지만, 특히 플레이어가 정지해 있을 때 발차기 피해가 정상적으로 발생하지 않는 상황이 있었습니다.

**분석:** 단순히 애니메이션 문제로 보기보다 `AttackRange`, AI 이동 종료 거리, 공격 시점의 방향 조건, 발 부위 충돌 판정 범위를 각각 확인했습니다. 공격 가능 거리 안에 들어왔는지와 발의 충돌 형태가 플레이어 캡슐과 실제로 겹치는지를 구분해 살폈습니다.

**수정·확인:** 공격 거리와 발차기 충돌 반경을 조정하고, 정지한 플레이어를 대상으로 재검증해 피해가 적용되는 모습을 확인했습니다. 해당 사례를 통해 **AI 이동 성공, 애니메이션 재생, 실제 피격 성공은 서로 다른 검증 항목**이라는 점을 배웠습니다.

## 핵심 C++ 파일 안내

| 파일 | 확인할 부분 |
|---|---|
| `U_ClaudPortfCharacter.cpp/.h` | Enhanced Input, 무기 장착, HUD, 체력·사망 |
| `Weapon.cpp/.h` | 카메라/총구 Line Trace, 피격 부위, 재장전 |
| `AmmoPickup.cpp/.h` | 획득 범위 및 예비 탄약 추가 |
| `EnemyAIController.cpp/.h` | 플레이어 감지, 추적·공격 전환 |
| `EnemyCharacter.cpp/.h` | 체력, 공격·Notify, 거리/방향/발 충돌 판정 |
| `U_ClaudPortfGameMode.cpp/.h` | 적 카운트, Victory/Game Over, 재시작·종료 |
| `TargetDummy.cpp/.h` | 타깃 더미 관련 기능 |

프로젝트 폴더 구조에 따라 소스는 Unreal 프로젝트의 `Source/U_ClaudPortf/` 아래에서 확인할 수 있습니다.

## 실행 및 확인 안내

- **플레이 영상을 먼저 확인**하면 주요 기능의 동작을 빠르게 파악할 수 있습니다.
- Unreal 전체 프로젝트(`.uproject`, 필요한 `Content` 에셋 등)가 포함되어 있다면 Unreal Engine **5.3.2**로 열어 확인해 주세요.
- **C++ 소스만 공개된 경우**에는 에셋·레벨·Blueprint 참조가 빠져 있어 소스만으로 동일한 플레이 화면을 재현할 수 없습니다.
- 실행 환경에 따라 엔진 버전, Blueprint 설정, 충돌 프리셋 등을 확인해야 할 수 있습니다.

## 배운 점과 향후 개선

플레이어가 경험하는 결과는 사격 판정, 애니메이션 타이밍, AI 이동, 충돌 프리셋처럼 여러 시스템이 맞물려 결정된다는 것을 체감했습니다. 앞으로는 경계 상황의 테스트를 더 체계화하고, 구조를 분리해 유지보수하기 쉬운 게임플레이 코드를 작성하는 데 집중하려고 합니다.

[← 전체 포트폴리오로 돌아가기](../README.md)
