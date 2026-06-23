# Transition Roadmap

## 迁移记录

原仓库：`Cpp-Linux-GameServer-Lab`
新仓库：`personal-edge-ai-transition-plan`

### 变更

- 目标从"游戏服务器"改为"边缘 AI 转型工程"
- 目录结构按阶段能力分层，参照 EdgeAIproject 六阶段 + edge_core
- 保留 git 历史（从原仓库拷贝 .git 元数据）
- 迁移资产：ThreadPool / AsyncLogger / ConfigSystem

### 迁移资产映射

| 原位置 | 新位置 |
|--------|--------|
| `day24_ThreadPool/` | `Phase_01/day03_ThreadPool/` |
| `day19_AsyncLog/` | `Phase_01/day05_AsyncLogger/` |
| `day14_CfgManager/` | `Phase_01/day08_ConfigAndSerialization/` |

### 淘汰

- `Daily_Code/Phase_04_GameServer/`
- 所有 Game / MonsterLib 子目录
- 游戏语义的配置字段和注释
- `Phase_03_AI_Engine/` 空壳
- `Phase_04_GameServer/` 空壳
