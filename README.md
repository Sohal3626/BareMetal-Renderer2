# BareMetal-Renderer2

---
# 프로젝트 개요
CPU 기반 렌더링 파이프라인을 재설계하는 프로젝트입니다.  

## 프로젝트 목표
기존에 렌더링 알고리즘과 파이프라인 학습을 위해 CPU 렌더러 제작 프로젝트를 진행하였으나,  
구현에 급급하여 가독성과 확장성이 뛰어난 코드를 작성하지 못하였습니다.  
이 프로젝트의 목적은 이 전 프로젝트에서 학습한 내용을 복습하고, 보다 나은 구조로 리메이크 하는 것입니다.  
나아가 리메이크가 끝난 이후 더 많은 기능을 추가하고 보다 완성도 높은 렌더러를 구현하는것을 목표로 합니다.  
리메이크 대상 프로젝트는 [여기](https://github.com/Sohal3626/BareMetal-Renderer)에서 확인하실 수 있습니다.

## 현재 진행 상황

### 구현 완료
- Mesh 구현
- Vertex Shader 구현
- Barycentric 기반 래스터라이징
- Depth Buffer 적용

### 예정 기능
- Phong / Gouraud Shading
- .mtl file Parsing
- Texture Mapping
- Alpha blending
  
## 개발 일지
제 코드를 참고하실 분들이 쉽게 이해할 수 있도록 개발 일지를 제공합니다.  
[1일차-Mesh.h](<./docs/개발 일지/1일차.md>)  
[2일차-VertexShader.h](<./docs/개발 일지/2일차.md>)  
[3일차-barycentric & canvas, 4일차 - Rasterizer](<./docs/개발 일지/3,4일차.md>)  
[5일차-Depth Buffer & Renderer](<./docs/개발 일지/5일차.md>)  
[5.5일차-병렬 프로그래밍](<./docs/개발 일지/5.5일차.md>)
[6일차-Material](<./docs/개발 일지/6일차.md>)
---

# 주요 기능

## Mesh.h
모델 데이터를 로드하고 관리합니다.

### `loadObj(...)`
- `.obj` 파일을 파싱하여 정점(Vertex), 인덱스(Index), 서브메시 데이터를 생성합니다.

## VertexShader.h
정점 변환을 처리합니다.

### `vertexShader(...)`
- Model, View, Projection 행렬을 적용하여 정점을 Clip Space로 변환합니다.
- 텍스처 좌표 및 법선 데이터를 다음 단계로 전달합니다.

## Rasterizer.h
삼각형을 픽셀 단위로 변환합니다.

### `fillTriangle(...)`
- 삼각형의 세 정점을 기반으로 bounding box를 계산합니다.
- barycentric 좌표를 이용하여 삼각형 내부 픽셀을 판별하고 색상을 채웁니다.
- Depth Buffer를 사용하여 올바른 가시성을 처리합니다.

## Renderer.h
렌더링 파이프라인의 전체 흐름을 제어합니다.

### `DrawModel(...)`
- Mesh의 인덱스 버퍼를 순회하며 삼각형 단위로 처리합니다.
- 각 정점에 대해 Vertex Shader를 적용합니다.
- Perspective divide 및 viewport 변환을 수행합니다.
- Rasterizer를 호출하여 삼각형을 화면에 렌더링합니다.
- OpenMP를 사용하여 병렬로 렌더링을 수행합니다.
