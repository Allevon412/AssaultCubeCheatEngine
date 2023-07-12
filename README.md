# AssaultCubeCheatEngine

## Reasoning behind the proj.

### I've read that game hacking is very similar to techniques used by malware authors. Additionally, I've heard that the game hacking scene is usually ahead of the game as far as security goes. Because of this. I wanted to research some game hacking concepts and see what I can learn. It was also just a pretty fun application to the concepts I've picked up in my security journey.
### The hack engine is a DLL that must be loaded using a DLL injection such as the one located at: https://github.com/Allevon412/ReflectiveDLLInjector

### I tried to upload a video of the engine working with the game. However, github requires videos to be 10mb small and it's very had to make a worthy video that last 5 seconds.
### If you have any questions feel free to reach out.

## Current Hacks:
1) Unlimited Ammo
2) Unlimited HP
3) Zero Recoil
4) Change Score to 1337
5) Change Player POS (Really just makes them jump, I did this because I didn't want to attempt to do the programming / math to determine if the coordinates input are valid coordinates or not)
6) One Shot Kills - Sets the damage on all weapons base damage to be 300 - This is incredibly high compared to the pistols 15 base damage. - This will cause all of the players to be pushed back significantly from taking such high damage.

### Example Usage:
1) Launch AssaultCube.exe - https://github.com/assaultcube/AC/releases/tag/v1.2.0.2
2) Use my Reflective Loader to manually load / map the malicious DLL into the process' memory space. - This needs to be ran from an administrator command prompt to ensure high enough privileges to inject into the target process.

PS D:\Training\GuidedHacking\ReflectiveDLLLoader\ReflectiveLoader\Release> .\ReflectiveLoader.exe -d D:\Training\GuidedHacking\ACTrainer\ACTrainer\Release\ACTrainer.dll -p ac_client.exe

[*] Attempting to find Process ID of the Process [ac_client.exe].

[*] Process ID found: [26696]!

[*] Opening a Handle to the Process!

[*] Attempting to open file handle

[*] Allocating memory for the dll.

[*] Memory allocated at location: [0x00ACE438], attempting to read file contents into memory

[*] Allocating memory in the size of: [0xa00c] in remote process.

[*] Memory Allocation successful. Memory located at: [0x005E0000]

[*] Writing the Headers of our DLL into target process

[*] Attempting to write our sections into the remote process

[*] Attempting to write section: [.text] at location: [0x005E1000]

[*] Attempting to write section: [.rdata] at location: [0x005E5000]

[*] Attempting to write section: [.data] at location: [0x005E7000]

[*] Attempting to write section: [.rsrc] at location: [0x005E8000]

[*] Attempting to write section: [.reloc] at location: [0x005E9000]

[*] Sections written into memory.

[*]Attempting to write our mapping data at end of image location: [0x005EA000]

[*] Attemtping to allocate memory in the remote process for our Loader Stub.

[*] Allocation successful. Loaderstub memory location: [0x005F0000]

[*] Attempting to Write LoaderStub

[*] Creating Thread in remote process that will start the loading routine

[*] Checking for completion of the loading routine

[*] Loading routine successfully completed. Cleaning up!

PS D:\Training\GuidedHacking\ReflectiveDLLLoader\ReflectiveLoader\Release>

4) profit.
