# CompleteShooterGame
Shooter Game from Stephen Ulibarri tutorial

Version 0.0.01
- Initial setup of the repository

Version 0.8.01
- Character Class added

Version 0.9.01
- UE_LOG added for BeginPlay() called

Version 0.9.02
- Converted project to UE version 4.27

Version 0.13.01 
- Added follow camera and spring arm

Version 0.15.01
- Added Move Forward and Move Right capability

Version 0.17.01
- Added turn and look up capability to keyboard

Version 0.18.01
- Added mouse turning and jumping capability

Version 0.19.01
- Added Paragon: Lt Belica asset to project ( large commit )
- Set Character Mesh to Belica

Version 0.20.01
- Created the Anim Instance c++ Class

Version 0.21.01
- Added Run animations and ABP_Shooter animation blueprint

Version 0.22.01
- Trimmed the Jog_Fwd_start and _stop animations to look better in our use case

Version 0.22.02
- Converted project to UE5.2 Version

Version 0.22.03
- Added the Houdini Plugin to the project

Version 0.22.04 thru 0.22.06
- converted input system to use Enhanced Input
- implemented move, look and jumping in Enhanced Input System

Version 0.23.01
- set up character to face direction of movement

Version 0.26.01
- Added IA_FireWeapon with left mouse button press
- Added sound assets to project
- Added sounds for weapon fire

Version 0.27.01
- Added socket to weapon barrel for muzzle flash
- Added Muzzle Flash particle system
- Added particle system to FireWeapon function

Version 0.28.01
- Created AM_HipFireMontage
- Added new montage to ABP_Shooter

Version 0.29.01
- Created Layered Blend in ABP_Shooter to blend Weapons Fire with Ground Locomotion

Version 0.30.01
- Perform Line trace for bullet hits
- Draw debug line and debug point to show line trace

Version 0.31.01
- Added Impact Particles for bullet hits

Version 0.32.01
- Added Smoke Beam assets to project
- Added Smoke Beam (SmokeTrail_Faded) particle system to FireWeapon()
  and set in blueprint
  
Version 0.34.01
- Added crosshair assets to project
- Placed crosshair on screen via HUD

Version 0.35.01
- Perform line trace from crosshair to point in world under the crosshair

Version 0.36.01
- Perform a second line trace from the weapon barrel to check for LOS from the muzzle

Version 0.37.01
- Refactored FireWeapon() to move beam end calculation to it's own function 
  GetBeamEndLocation()
- Code cleanup
