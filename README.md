# Unreal TPS Portfolio

A third-person shooter prototype developed with C++ and Unreal Engine 5.3.2.

This project focuses on weapon interaction, trace-based shooting, enemy damage handling, and death mechanics.

## Tech Stack

- **Engine:** Unreal Engine 5.3.2
- **Language:** C++
- **Development Environment:** Visual Studio
- **AI Assistance:** Claude Code and ChatGPT for coding guidance and debugging

## Implemented Features

### 1. Weapon Pickup and Equipment
- Implemented weapon pickup detection using collision overlap.
- Attached the weapon to the character when equipped.

### 2. Shooting System
- Implemented camera-direction-based shooting using Line Trace.
- Identified hit actors and applied damage to valid targets.

### 3. Enemy Health and Damage System
- Implemented enemy health management in C++.
- Applied 25 damage per hit in the tested configuration.
- Triggered death handling when the enemy's health reached zero.

### 4. Enemy Death and Ragdoll
- Stopped character movement upon death.
- Disabled capsule collision and enabled ragdoll physics.
- Removed the enemy actor after a five-second delay.

### 5. Collision Debugging
- Investigated shooting failures caused by collision responses.
- Adjusted the enemy mesh's Visibility response to Block.
- Verified hit detection and damage application through gameplay testing and log output.

## Key C++ Classes

| Class | Responsibility |
|---|---|
| `AWeapon` | Weapon equipment, shooting, hit detection, and damage application |
| `AEnemyCharacter` | Enemy health management, damage handling, and death behavior |
| `AU_ClaudPortfCharacter` | Player character functionality |

## What I Learned

- Implementing gameplay systems using Unreal Engine C++ and Blueprint.
- Using Line Trace and collision channels for hit detection.
- Applying damage and managing enemy health.
- Implementing ragdoll physics and actor lifecycle handling.
- Debugging gameplay behavior using Unreal Engine logs.

## Development Notes

Claude Code and ChatGPT were used as development assistants for coding guidance and debugging. Implemented functionality was tested in Unreal Engine.


# MildStone — C++ Project

## Overview

MildStone is a C++ application developed as a college project during my final semester.

## Key Features

- [Describe the main features of the application]
- [Describe another feature or functionality]

## Technologies

- C++

## What I Learned

- Applying C++ programming concepts to a practical project
- Designing and implementing application functionality

## How to Run

Build and run the project using the appropriate C++ development environment.

