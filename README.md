# OpenGL Practice Collection 🎨  
C++ / OpenGL Practice Projects  
C++ / OpenGL 演習プロジェクト集  
C++ / OpenGL 练习项目集合

---

## 📘 Overview / 概要 / 概述

This repository records my step-by-step learning progress in modern OpenGL using C++ (Visual Studio + GLFW + GLAD).  
本リポジトリでは、C++（Visual Studio + GLFW + GLAD）を使って現代的な OpenGL を学習する過程を段階的に記録しています。  
本仓库记录了我使用 C++（Visual Studio + GLFW + GLAD）学习现代 OpenGL 的全过程。

My goal is to build a strong foundation in computer graphics and understand rendering pipelines, shaders, textures, lighting, and 3D math through hands-on practice.  
目標は、実際のコードを書きながら、レンダリングパイプライン、シェーダー、テクスチャ、ライティング、3D 数学などを理解し、グラフィックスの基礎を確立することです。  
我的目标是通过动手实践掌握渲染管线、着色器、纹理、光照、3D 数学等核心内容，建立扎实的图形学基础。

---

## 📁 Project Structure / プロジェクト構成 / 项目结构

opengl-practice/
├── firstopengl/ # First OpenGL demo / 最初のデモ / 第一个示例
├── （more demos will be added）/ （今後追加予定）/（未来会持续添加）
├── README.md
└── .gitignore

yaml
复制代码

Each demo has its own folder and source code.  
各デモは独立したフォルダにまとめています。  
每个 Demo 都有独立的文件夹。

---

## 🧪 Completed Practices / 完了した演習 / 已完成的练习

### **1. firstopengl — Basic Texture Demo  
基本テクスチャ描画デモ  
基础纹理绘制示例**

**Features / 機能 / 功能：**
- Initialize GLFW & GLAD  
  GLFW と GLAD の初期化  
  初始化 GLFW 与 GLAD
- Create window and render loop  
  ウィンドウ作成とレンダーループ  
  创建窗口与渲染循环
- Load textures using stb_image  
  stb_image を使用したテクスチャ読み込み  
  使用 stb_image 加载纹理
- Mix multiple textures  
  テクスチャのブレンド  
  混合多张纹理
- Basic shader pipeline  
  基本的なシェーダーパイプライン  
  基础着色器流程
- Use VAO / VBO / EBO  
  VAO / VBO / EBO の利用  
  使用 VAO / VBO / EBO

(If I upload screenshots later, I will include them here.)  
（後でスクリーンショットを追加予定。）  
（未来会加入截图。）

---

## 🧭 Learning Roadmap / 学習ロードマップ / 学习路线图

### **Phase 1: Basics / 基礎 / 基础**
- [x] Window creation  
- [x] Shader compilation  
- [x] Texture loading  
- [ ] Keyboard/mouse input  
- [ ] Camera system

### **Phase 2: 3D**
- [ ] Model/View/Projection matrices  
- [ ] Depth testing  
- [ ] Free-look camera (WASD + mouse)

### **Phase 3: Lighting / ライティング / 光照**
- [ ] Phong lighting  
- [ ] Multiple light sources  
- [ ] Material properties

### **Phase 4: Model Loading / モデル読み込み / 模型加载**
- [ ] Assimp integration  
- [ ] Mesh & Material system

### **Phase 5: Advanced Rendering / 高度なレンダリング / 高级渲染**
- [ ] Shadow mapping  
- [ ] HDR  
- [ ] Bloom  
- [ ] PBR shading

---

## 🔧 Development Environment  
開発環境  
开发环境

- **Language:** C++17  
- **IDE:** Visual Studio 2022  
- **Libraries:**  
  - GLFW  
  - GLAD  
  - stb_image  
- **Platform:** Windows 10/11  

---

## 🎯 Long-Term Goal / 長期目標 / 长期目标

To deepen understanding of real-time rendering, build practical graphics skills, and eventually explore:  
リアルタイムレンダリングの理解を深め、最終的には以下にも挑戦したい：  
加深对实时渲染的理解，未来进一步挑战：

- Game engine development / ゲームエンジン開発 / 游戏引擎开发  
- Vulkan / DirectX  
- Advanced shader techniques  
- Physics-based rendering (PBR)  

---

Continually updated as I learn more.  
今後も学習に合わせて更新していきます。  
将随着学习持续更新。
