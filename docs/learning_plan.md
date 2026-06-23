# 学习路线

总目标：在 12~20 周内完成从 C++/Linux 开发到边缘 AI 部署与系统集成工程师的能力升级。

## Phase 1（第 1~4 周）：原生 C++ 工程底座

- 智能指针、RAII、右值引用、移动语义
- 线程池、异步日志、事件总线、内存池
- 设计模式与类型擦除
- CMake targets / install / export
- 动态库/静态库/ABI 边界
- 错误处理与配置系统
- 插件式架构

**阶段验收**：每个 day 可独立编译运行；至少标记 2 个可沉淀组件候选

## Phase 2（第 5~8 周）：Linux 系统工程与通信

- Epoll Reactor
- 共享内存 / IPC
- TCP Server
- Half-Sync / Half-Async
- 进程/信号/定时器
- systemd / daemon
- 动态库加载与调试工具链

**阶段验收**：最小网络服务可跑通；至少一次压测记录

## Phase 3（第 9~11 周）：性能基础与数据通路

- 无锁队列
- 内存对齐与 cache 友好布局
- false sharing
- benchmark / perf
- SIMD / 数据布局
- pipeline 延迟 / 吞吐分析

**阶段验收**：至少 2 组 benchmark 数据；一份耗时拆分记录

## Phase 4（第 12~15 周）：通用 AI 推理部署

- ONNX 模型探查
- ONNX Runtime C++
- OpenCV 预处理
- YOLO 后处理与 NMS
- TensorRT（可选平台）
- INT8 量化
- RKNN（可选平台）
- 多模型流水线

**阶段验收**：一条真实模型端到端链路跑通；精度对齐与性能拆分

## Phase 5（第 16~17 周）：数据库与中间件

- Redis 缓存与状态管理
- MySQL 结果持久化
- Docker 容器化部署

## Phase 6（第 18~20 周）：进阶主题

- 交叉编译
- gRPC 服务通信
- Muduo 网络库源码分析
- llama.cpp 边缘 LLM
- ROS2 机器人集成
- Kubernetes 编排
- CI/CD 流水线
- Triton 推理服务
- CUDA 编程

## 组件沉淀（贯穿全程）

学习过程中把高价值代码逐步抽取到 `edge_core/`，包括：
- ThreadPool
- AsyncLogger
- LockFreeQueue / RingBuffer
- EventBus
- Reactor 封装
- Config 模块
- PluginLoader
- InferencePipeline
