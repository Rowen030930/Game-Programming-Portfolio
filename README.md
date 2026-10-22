# 게임 프로그래밍 포트폴리오 | 오경록

**C++ · Unreal Engine 5.3 · 게임 클라이언트 프로그래머 지원자**

안녕하세요. 게임에서 느낀 재미를 단순히 소비하는 데 그치지 않고, 실제 시스템이 어떻게 동작하는지 이해하고 구현하려는 오경록입니다. C/C++ 프로그래밍을 공부했으며, 현재 Unreal Engine을 활용해 3인칭 슈팅 게임의 전투·AI·UI 기능을 학습하고 구현하고 있습니다.

이 저장소는 **Unreal Engine TPS 포트폴리오**, **C++ Milestone 과제**, **Software Testing 팀 프로젝트**로 구성되어 있습니다. 가장 먼저 확인해 주셨으면 하는 작업은 Unreal TPS 프로젝트입니다.

## 프로젝트 한눈에 보기

| 프로젝트 | 주요 기술 | 핵심 내용 | 자료 |
|---|---|---|---|
| **Unreal TPS Portfolio** | Unreal Engine 5.3.2, C++, Blueprint | 사격·헤드샷, 적 AI·근접 공격, 체력·탄약 UI, 게임 종료 처리 | [상세 README](./Unreal-TPS-Portfolio/README.md) |
| C++ Programming Milestones | C++, OOP, STL | 생산 라인 시뮬레이션, 동적 메모리 및 이동 의미론 | [상세 README](./Cpp-School-Projects/README.md) |
| Software Testing Project | C, Visual Studio, Unit/Integration Test | 화물 배송 프로그램 테스트 설계·코드·결과 문서화 | [상세 README](./Software_Testing_Project/README.md) |

## 1. Unreal TPS Portfolio — 대표 프로젝트

Unreal Engine 5.3.2에서 학습한 내용을 바탕으로 **플레이어 입력 → 전투 판정 → 적 AI 반응 → 게임 결과**로 이어지는 게임플레이 흐름을 구현했습니다.

- **사격 판정:** 카메라에서 조준 지점을 찾고 총구에서 다시 Line Trace를 수행해, 조준 방향과 실제 장애물 충돌을 구분
- **피해 처리:** `FHitResult`의 충돌 정보와 적의 본(Bone) 정보를 활용한 몸통/헤드샷 판정
- **적 AI:** `AIController`, NavMesh 이동, 주기적인 거리 확인 및 근접 공격
- **근접 공격:** Animation Notify 시점과 발 부근의 충돌 검사 및 거리·방향·시야 조건 연계
- **게임 루프:** 체력, 탄약/재장전, 아이템 획득, 적 처치, Victory/Game Over, Retry/Quit

### 플레이 영상

| 확인할 내용 | 영상 |
|---|---|
| 처음부터 끝까지의 플레이 및 Victory | [전체 게임플레이](https://youtu.be/XoBw_GwINzs) |
| 사격 판정 및 헤드샷 | [사격·헤드샷](https://youtu.be/x4qWgP54mxI) |
| 적 추적 AI 및 근접 공격 | [적 AI·근접 공격](https://youtu.be/hm-IxgJQrR8) |
| 플레이어 사망 및 재시작 | [Game Over·Retry](https://youtu.be/yCE8idoXQ3I) |

> 구현 구조, 주요 C++ 파일, 문제 해결 과정은 [TPS 상세 문서](./Unreal-TPS-Portfolio/README.md)에 정리했습니다.

## 2. C++ Programming Milestones — 개인 수업 과제

Seneca Polytechnic C++ 수업의 Milestone 1~3을 진행하면서 문자열 파싱, 클래스 설계, 동적 자원 관리, 이동 생성자·이동 대입 연산자, STL을 활용했습니다. 최종 단계에서는 여러 작업대를 통해 주문이 처리되는 생산 라인 흐름을 구성했습니다.

→ [과제별 설계 및 구현 설명](./Cpp-School-Projects/README.md)

## 3. Software Testing Project — 6인 팀 수업 과제

Seneca Polytechnic의 SFT221 수업에서 **제공받은 C 언어 화물 배송 프로그램을 검증**했습니다. 테스트 계획서의 일부 항목, 함수 명세, `convertStrToPoint` 단위 테스트, 좌표 변환 관련 통합 테스트와 결과 문서화에 참여했습니다.

→ [테스트 전략·기여·결과 설명](./Software_Testing_Project/README.md)

## 기술 및 도구

| 분야 | 경험 |
|---|---|
| 언어 | C, C++ |
| 게임 개발 | Unreal Engine 5.3.2, Blueprint, UMG, Enhanced Input |
| 개발 환경 | Visual Studio, JetBrains Rider |
| 버전 관리·협업 | Git, GitHub, Jira |
| 검증 | Line Trace 디버깅, Unit Test, Integration Test, 테스트 케이스 및 결과 문서화 |

## 작업 방식

게임 기능을 구현할 때는 **예상 동작을 먼저 정리하고, 실제 플레이에서 문제가 나타나는 조건을 좁혀 가며 수정**하려고 합니다. 학교 테스팅 프로젝트에서 배운 입력 조건·기대 결과·실제 결과의 구분을 게임플레이 디버깅에도 적용하고 있습니다.

## 프로젝트 출처 및 기여 범위

- **Unreal TPS:** Unreal Engine 학습 및 실습을 기반으로, C++ 기능 구현과 에디터 설정·테스트·문제 수정 과정을 수행한 개인 학습 포트폴리오입니다. 기본 템플릿과 교육 자료를 활용했습니다.
- **C++ Milestones:** Seneca Polytechnic 수업에서 수행한 개인 과제입니다.
- **Software Testing:** 교수님이 제공한 프로그램을 대상으로 한 6인 팀 테스트 프로젝트입니다. 팀 성과와 개인 담당 업무를 상세 README에서 구분했습니다.

실제 코드와 실행 영상을 함께 살펴봐 주시면 감사하겠습니다.
