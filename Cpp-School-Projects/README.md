# C++ Programming Milestones

**Seneca Polytechnic · C++ 수업 개인 과제 · Milestone 1–3**

C++의 기본 문법을 넘어 **문자열 처리 → 객체·자원 관리 → 여러 클래스가 연결되는 프로그램**으로 단계적으로 확장한 수업 과제입니다. 고객 주문이 생산 라인의 여러 작업대(Station/Workstation)를 거쳐 처리되는 과정을 구현했습니다.

> 이 코드는 수업에서 제시한 요구사항을 바탕으로 작성한 **학습 과제**이며, 실제 생산 시스템이나 상용 서비스가 아닙니다.

## 프로젝트 구조

```text
Cpp-School-Projects/
├── ms1/    # Milestone 1 — Utilities, Station
├── ms2/    # Milestone 2 — CustomerOrder 및 이동 의미론
└── ms3/    # Milestone 3 — Workstation, LineManager, 전체 주문 흐름
```

*폴더 안의 Visual Studio 프로젝트 및 파일 이름에는 과제 당시 사용한 `Mildstone` 표기가 남아 있을 수 있습니다.*

## Milestone 1 — 문자열 처리와 작업대 데이터

**핵심 클래스:** `Utilities`, `Station`

- 구분자로 나뉜 문자열을 토큰 단위로 파싱해 필요한 데이터 추출
- `Station`에서 품목명, 시리얼 번호, 현재 재고 수량 등 관리
- 재고 감소와 시리얼 번호 증가처럼 상태가 바뀌는 작업을 멤버 함수로 구성
- 입력 데이터 파일(`Stations1.txt`, `Stations2.txt`)을 읽고 출력 형식 확인

**학습한 점:** 외부 텍스트 데이터를 프로그램 내부의 객체 상태로 옮길 때 파싱 규칙과 상태 관리가 중요하다는 것을 배웠습니다.

## Milestone 2 — CustomerOrder와 메모리 관리

**핵심 클래스:** `CustomerOrder` (Milestone 1 클래스 활용)

- 고객 이름·제품명·주문 항목과 품목별 완료 상태 관리
- 항목 목록에 동적 메모리를 사용하고 소멸자에서 자원 정리
- 복사를 제한하고 **이동 생성자·이동 대입 연산자**를 구현해 자원 소유권 이전
- `fillItem()`에서 작업대 재고에 따라 주문 항목을 처리
- `isOrderFilled()`, `isItemFilled()` 등으로 주문 완료 상태 확인

```cpp
// 사용 개념의 예시: 값 복사 대신 주문 객체의 자원을 이동
CustomerOrder nextOrder = std::move(currentOrder);
```

*위 예시는 이동 의미론을 설명하기 위한 짧은 예시이며, 수업 코드에서 그대로 복사한 한 줄은 아닙니다.*

**학습한 점:** 동적 메모리를 소유한 객체는 단순 복사 시 문제가 생길 수 있고, 이동 연산에서는 옮긴 뒤 원본 객체의 상태까지 안전하게 관리해야 한다는 점을 익혔습니다.

## Milestone 3 — 생산 라인 주문 처리

**핵심 클래스:** `Workstation`, `LineManager`

- `Workstation`에서 각 작업대가 담당 품목을 처리하고 주문을 다음 작업대로 전달
- 설정 파일(`AssemblyLine.txt`)을 바탕으로 작업대 연결 및 순서 구성
- `LineManager`에서 최초 작업대로 주문을 보내고 전체 라인을 진행
- `std::move`로 주문 객체를 전달해 불필요한 복사 방지
- `std::for_each`, `std::all_of` 등 STL 알고리즘으로 작업대 순회와 남은 작업 확인
- 처리 결과에 따라 완료/미완료 주문을 구분

### 처리 흐름

```text
주문 데이터 로드
     ↓
LineManager가 작업대 연결 순서 구성
     ↓
첫 작업대가 주문 수신
     ↓
Workstation이 보유 재고에 따라 주문 항목 처리
     ↓
다음 작업대로 주문 전달
     ↓
라인 종료 → 완료/미완료 결과 분류
```

## 관련 소스 파일

| 파일 | 역할 |
|---|---|
| `Utilities.cpp/.h` | 문자열 토큰 분리 |
| `Station.cpp/.h` | 품목·재고·시리얼 관리 |
| `CustomerOrder.cpp/.h` | 주문 항목·상태·이동 의미론 |
| `Workstation.cpp/.h` | 작업대 간 주문 전달 |
| `LineManager.cpp/.h` | 작업대 순서 및 전체 라인 진행 |
| `ms1.cpp`, `ms2.cpp`, `ms3.cpp` | 과제 단계별 실행 및 동작 확인용 코드 |

## 기술 키워드

`C++` · `OOP` · `RAII/자원 관리 학습` · `Move Constructor` · `Move Assignment` · `STL Containers` · `std::move` · `std::for_each`

## 실행 참고

각 Milestone은 개별 Visual Studio 프로젝트로 작성되었습니다. 해당 폴더의 `.sln` 파일 또는 C++ 프로젝트 파일을 열어 코드와 입력 파일을 확인할 수 있습니다. 과제 당시의 경로·컴파일러 설정에 따라 빌드 옵션 조정이 필요할 수 있습니다.

## 배운 점

Milestone 1에서는 개별 클래스의 기능 구현에 집중했지만, 마지막 단계에서는 각 클래스 사이의 **역할 분담과 데이터 이동**이 전체 동작을 결정한다는 점을 배웠습니다. C++ 게임 클라이언트 개발에서도 객체의 소유권과 상태 변화, 시스템 간 연결을 명확하게 이해하는 것이 중요하다고 생각합니다.

[← 전체 포트폴리오로 돌아가기](../README.md)
