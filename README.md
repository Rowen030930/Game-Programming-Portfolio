\# Unreal TPS Portfolio



A third-person shooter prototype developed with C++ and Unreal Engine 5.3.2.



\## Tech Stack

\- Unreal Engine 5.3.2

\- C++

\- Visual Studio

\- Claude Code and ChatGPT for development assistance



\## Implemented Features



\### Weapon System

\- Weapon pickup and equipment

\- Collision overlap for pickup detection

\- Camera-direction-based shooting using Line Trace



\### Enemy Combat System

\- Enemy health management in C++

\- Damage application using `ApplyDamage()`

\- 25 damage per hit in the tested configuration

\- Death handling when health reaches zero



\### Death and Ragdoll

\- Stop character movement upon death

\- Disable capsule collision

\- Enable ragdoll physics

\- Automatically remove the enemy after 5 seconds



\### Debugging

\- Investigated collision channel settings

\- Fixed enemy hit detection by adjusting the Mesh Visibility response

\- Verified damage and death behavior through gameplay testing and logs



\## Key C++ Classes



\- `AWeapon`: Weapon pickup, equipment, shooting, and damage application

\- `AEnemyCharacter`: Health management, damage handling, and death behavior

\- `AU\_ClaudPortfCharacter`: Player character functionality



\## AI-Assisted Development



Claude Code and ChatGPT were used for coding guidance, debugging, and implementation support. Implemented features were tested in Unreal Engine.





