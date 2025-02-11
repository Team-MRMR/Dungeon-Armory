# Dungeon-Armory
2025학년도 상명대학교 게임전공 졸업작품

## 1. 기본적인 폴더 구조
📂 Source/    
├── 📂 ProjectName/ (주요 게임 로직 폴더)    
│ ├── 📂 Core/ (게임의 핵심 시스템, 싱글톤 클래스, 헬퍼 유틸리티 등)    
│ ├── 📂 Characters/ (플레이어 및 NPC 관련 클래스)    
│ ├── 📂 AI/ (AI 컨트롤러, 비헤이비어 트리 관련 클래스)    
│ ├── 📂 Components/ (재사용 가능한 ActorComponent 클래스)    
│ ├── 📂 UI/ (HUD, UMG 위젯 클래스)    
│ ├── 📂 Items/ (무기, 아이템 등 인터랙션 가능한 객체들)    
│ ├── 📂 GameModes/ (게임 모드, 게임 상태 관련 클래스)    
│ ├── 📂 Animations/ (애니메이션 블루프린트 관련 코드)    
│ ├── 📂 Cameras/ (카메라 관리 관련 코드)    
│ ├── 📂 Levels/ (레벨 스크립트 및 로딩 관련 코드)    
│ ├── 📂 Networking/ (네트워크 관련 로직, 리플리케이션 등)    
│ ├── ProjectName.h (프로젝트 전역 헤더 파일)    
│ ├── ProjectName.cpp (주요 C++ 구현 파일)    
│    
├── 📂 ProjectNameEditor/ (에디터 확장 관련 코드 - 필요할 경우)    

---

헤더 파일(```.h```)과 소스 파일(```.cpp```)은 동일한 폴더에 위치하도록 정리한다.     
헤더 파일과 소스 파일의 이름은 동일하게 명명한다.    