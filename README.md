# Baba Is You 모작

C++와 Win32 API, GDI+로 제작한 개인 퍼즐 게임 프로젝트입니다. 화면에 놓인 단어 블록을 움직여 규칙을 바꾸는 Baba Is You의 핵심 방식을 구현했습니다.

- 개발 기간: 2024.12 ~ 2025.01
- 개발 인원: 1명
- 개발 환경: Windows, Visual Studio 2022, C++17, Win32 API, GDI+
- 사운드: FMOD
- [시연 영상](https://www.youtube.com/watch?v=zk5nufwcb_8)

## 주요 구현

### 단어 블록과 규칙 해석

격자에서 가로·세로로 배치된 명사, 동사, 속성 블록을 찾아 규칙으로 해석합니다. 예를 들어 `BABA IS YOU`는 BABA 오브젝트에 조작 속성을 부여하고, `FLAG IS WIN`은 FLAG를 승리 대상으로 만듭니다. 단어를 밀어 문장을 끊거나 새로 연결하면 적용되는 규칙이 달라집니다.

- 명사·동사·속성 블록의 구분과 가로·세로 문장 탐색
- `IS` 문장에 따른 오브젝트 속성 부여와 명사 변환
- 규칙 활성 상태와 단어 블록 표시 갱신

원작의 모든 문법을 재현한 프로젝트는 아닙니다. `CRule`에는 `AND`, `ON`, `NEAR` 구분이 선언되어 있지만, 핵심 구현 설명은 실제 `CGrid`의 단순 `IS` 문장 처리 범위에 맞췄습니다.

관련 코드: [CGrid.cpp](CGrid.cpp), [CRule.h](CRule.h), [CBlock.cpp](CBlock.cpp), [CWordBlock.h](CWordBlock.h)

### 격자 이동과 블록 상호작용

한 칸에 여러 블록을 담을 수 있는 셀을 사용하고, 현재 규칙이 부여한 속성을 읽어 이동과 상호작용을 판정합니다.

- `YOU` 속성의 오브젝트 이동
- `PUSH` 블록의 연쇄 밀기와 `STOP`에 의한 이동 제한
- `WIN`, `SINK`, `HOT / MELT`, `DEFEAT`에 따른 승리·제거 판정
- 인접 타일에 따른 표시 갱신과 스프라이트 애니메이션

관련 코드: [CGrid.cpp](CGrid.cpp), [CCell.h](CCell.h), [CBlock.cpp](CBlock.cpp)

### 되돌리기와 스테이지

이동 전 격자 상태를 `stack<CGrid>`에 저장하고, 되돌리기 입력 시 이전 상태를 복원합니다. 월드맵에서 스테이지를 선택하며, 각 레벨은 데이터 파일을 읽어 초기 배치를 구성합니다.

- 이동 단위 되돌리기와 레벨 재시작
- 월드맵, 6개 레벨(`CLevel00` ~ `CLevel05`)과 클리어 상태 관리
- 스테이지 진입·복귀·승리 화면 전환

관련 코드: [CLevel.cpp](CLevel.cpp), [CLevel00.cpp](CLevel00.cpp), [CWorldMap.cpp](CWorldMap.cpp), [CInGame.cpp](CInGame.cpp)

### 맵 에디터

격자 크기를 정하고 블록을 배치·삭제할 수 있는 편집 화면을 만들었습니다. 블록 정보와 맵 크기를 Win32 파일 API로 저장하고 다시 불러옵니다.

- 블록 종류 선택과 마우스 배치·삭제
- 격자 너비·높이 조절
- `Data/Level_Temp1.dat` 저장 및 불러오기

관련 코드: [CEdit.cpp](CEdit.cpp), [CBlockManager.cpp](CBlockManager.cpp), [CBlocksPanel.cpp](CBlocksPanel.cpp)

## 빌드와 실행

1. Visual Studio 2022의 **C++를 사용한 데스크톱 개발**, MSVC v143, Windows 10 SDK를 준비합니다.
2. `BabaIsYouClone.sln`을 열고 **Debug / x64** 또는 **Release / x64**를 선택합니다. C++17과 FMOD 경로는 x64 구성에 설정되어 있습니다.
3. `External Libraries/fmod/` 아래의 Core·Studio·FSBank 헤더와 x64 라이브러리를 확인합니다. 프로젝트는 `fmod_vc.lib`, `fmodstudio_vc.lib`, `fsbank_vc.lib`를 링크합니다. 누락된 바이너리는 포함된 헤더와 맞는 FMOD SDK에서 준비합니다.
4. 프로젝트 속성의 **디버깅 → 작업 디렉터리**를 `$(SolutionDir)`로 설정합니다.
5. 빌드 후 실행합니다. x64 빌드 전 이벤트에서 `fmod.dll`을 출력 폴더로 복사합니다. DLL을 찾지 못하면 `External Libraries/fmod/core/lib/x64/fmod.dll`이 실행 파일과 같은 폴더에 있는지 확인합니다.

이미지와 사운드, 맵은 `Assets/`와 `Data/` 상대 경로로 읽습니다. 실행 파일만 다른 폴더로 옮기면 이 파일들을 찾지 못하므로, Visual Studio에서 실행할 때도 작업 디렉터리를 저장소 루트로 맞춰야 합니다.

## 조작 방법

### 메뉴와 게임

- `↑ / ↓`, `Enter`: 메뉴 선택·확정
- 방향키: 게임 오브젝트 또는 월드맵 커서 이동
- `Enter`: 월드맵에서 스테이지 진입
- `Z`: 한 수 되돌리기
- `R`: 현재 레벨 다시 시작
- `Esc`: 레벨에서 월드맵으로 복귀

### 에디터

- 방향키: 격자 너비·높이 변경
- `Enter`: 설정한 크기로 격자 재생성
- `Page Up / Page Down`: 블록 종류 변경
- 마우스 왼쪽 버튼: 선택한 블록 배치
- 마우스 오른쪽 버튼: 블록 삭제
- `S`: `Data/Level_Temp1.dat`에 저장
- `L`: 저장한 맵 불러오기

격자 재생성은 현재 배치를 초기화합니다.

## 코드 구성

- `CGrid`, `CCell`, `CBlock`: 격자, 셀과 블록 상태, 이동·규칙·상호작용
- `CRule`, `CNounBlock`, `CVerbBlock`, `CPropertyBlock`: 규칙 및 단어 블록 표현
- `CLevel`, `CLevel00` ~ `CLevel05`: 레벨 데이터와 되돌리기·재시작
- `CSceneManager`, `CInGame`, `CWorldMap`: 화면 전환과 게임 진행
- `CEdit`, `CBlockManager`, `CBlocksPanel`: 맵 편집과 저장·불러오기
- `CResourceManager`, `CSoundManager`: 이미지·사운드 관리
- `Assets/`, `Data/`: 리소스와 레벨 배치 파일

## 제작 목적

규칙에 따라 오브젝트의 동작이 바뀌는 구조와 격자 기반 퍼즐 로직을 공부하기 위한 학습 및 포트폴리오 프로젝트입니다. 원작 게임의 명칭과 사용 리소스의 권리는 각 권리자에게 있습니다.
