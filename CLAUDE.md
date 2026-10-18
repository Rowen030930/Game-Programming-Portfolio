# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project

Unreal Engine 5.3 C++ project (`U_ClaudPortf.uproject`), created from the Third Person template. Single runtime module `U_ClaudPortf`; the only enabled extra plugin is `ModelingToolsEditorMode` (editor-only). No test suite, linter config, or git repo exists yet.

Engine install: `C:\Program Files\Epic Games\UE_5.3` (a UE_5.8 install also exists — don't use it; the project's `EngineAssociation` is `5.3`).

## Build / Run

Paths contain spaces and parentheses — always quote them. Close the editor (or disable Live Coding) before a command-line build of the Editor target, otherwise UBT refuses to build.

```bash
# Build editor target (what you normally need after C++ changes)
"/c/Program Files/Epic Games/UE_5.3/Engine/Build/BatchFiles/Build.bat" U_ClaudPortfEditor Win64 Development -Project="C:/Unreal Engine(5.3.2)/U_ClaudPortf/U_ClaudPortf.uproject" -WaitMutex

# Build standalone game target
"/c/Program Files/Epic Games/UE_5.3/Engine/Build/BatchFiles/Build.bat" U_ClaudPortf Win64 Development -Project="C:/Unreal Engine(5.3.2)/U_ClaudPortf/U_ClaudPortf.uproject" -WaitMutex

# Regenerate project files (after adding/removing source files or modules)
"/c/Program Files/Epic Games/UE_5.3/Engine/Build/BatchFiles/Build.bat" -projectfiles -project="C:/Unreal Engine(5.3.2)/U_ClaudPortf/U_ClaudPortf.uproject" -game -rocket -progress

# Launch editor
"/c/Program Files/Epic Games/UE_5.3/Engine/Binaries/Win64/UnrealEditor.exe" "C:/Unreal Engine(5.3.2)/U_ClaudPortf/U_ClaudPortf.uproject"
```

When adding a new engine module dependency, add it to `PublicDependencyModuleNames` in `Source/U_ClaudPortf/U_ClaudPortf.Build.cs`.

## Architecture

The gameplay setup is split between C++ and Blueprint assets, so reading the source alone doesn't give the full picture:

- `AU_ClaudPortfGameMode` (set as `GlobalDefaultGameMode` in `Config/DefaultEngine.ini`) loads its default pawn by path: `/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter`. Renaming/moving that asset breaks pawn spawning.
- `AU_ClaudPortfCharacter` is the C++ base: spring-arm camera, movement tuning, and Enhanced Input binding (Move/Look/Jump). The input assets (`DefaultMappingContext`, `MoveAction`, `LookAction`, `JumpAction`) and the skeletal mesh/anim BP are **not** set in C++ — they are assigned on `BP_ThirdPersonCharacter`, which derives from this class. Input assets live in `Content/ThirdPerson/Input/` (`IMC_Default`, `IA_*`).
- Default/startup map: `/Game/ThirdPerson/Maps/ThirdPersonMap` (uses World Partition one-file-per-actor, hence `Content/__ExternalActors__`).
- `DefaultEngine.ini` contains `ActiveGameNameRedirects`/`ActiveClassRedirects` from the `TP_ThirdPerson` template names; keep them so template assets resolve.

`.uasset`/`.umap` files are binary and can't be edited directly — changes to Blueprint defaults, input mappings, or maps must be done in the editor (tell the user what to change). Generated folders (`Binaries`, `Intermediate`, `DerivedDataCache`, `Saved`, `.vs`, `.idea`) should not be edited.
