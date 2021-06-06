#include "../CPPToolLib/CPP Tools/stdafx/stdafx.h"
#include "../CPPToolLib/CPP Tools/proc/proc.h"
#include "../CPPToolLib/CPP Tools/mem/mem.h"

void printCheat(bool one = false, bool three = false, bool five = false, bool six = false, bool seven = false, bool eight = false) {
    system("cls");
    std::cout << "        Cheat Program\n";
    std::cout << "Key Press 0: Give 500 Health               " << std::endl;
    std::cout << "Key Press 1: Freeze Health                 " << std::boolalpha << one << '\n';
    std::cout << "Key Press 2: Give All Ammo                 " << std::endl;
    std::cout << "Key Press 3: Unlimited Ammo                " << std::boolalpha << three << '\n';
    std::cout << "Key Press 4: Give 500 Armor                " << std::endl;
    std::cout << "Key Press 5: Unlimited Armor               " << std::boolalpha << five << '\n';
    std::cout << "Key Press 6: No Recoil                     " << std::boolalpha << six << '\n';
    std::cout << "Key Press 7: Fly                           " << std::boolalpha << seven << '\n';
    std::cout << "Key Press 8: No Clip                       " << std::boolalpha << eight << '\n';
    std::cout << "Key Press INSERT: Exit                     " << std::endl;
}

int main()
{
    //Get Handle to Process
    HANDLE hProcess = 0;

    //Get ProcId of the target process
    DWORD procId = proc::GetProcId(L"ac_client.exe");

    // Try to get the process id
    if (procId) hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
    
    // if not then exit
    else exit(0);

    // exit pointer
    DWORD dwExit = 0;

    // initialize bools
    bool bHealth = false, bAmmo = false, bArmor = false, bRecoil = false, bFly = false, bNoClip = false; 

    // local player pointer
    uintptr_t localPlayerPtr = (uintptr_t)((BYTE*)proc::GetModuleBaseAddress(procId, L"ac_client.exe") + 0x10F4F4);

    // Print the chear
    printCheat(bHealth, bAmmo, bArmor, bRecoil, bFly);

    // While loop, keep going till game is closed
    while (GetExitCodeProcess(hProcess, &dwExit) && dwExit == STILL_ACTIVE) {

        // Add Health
        if ((GetAsyncKeyState(VK_NUMPAD0) & 1) || (GetAsyncKeyState(0x30) & 1))
        {
            // Health Value
            int health;

            // Health Pointer
            uintptr_t healthPtr = proc::FindDMAAddyEx(hProcess, localPlayerPtr, { 0xF8 });

            // Read Current Health
            mem::ReadEx((BYTE*)healthPtr, (BYTE*)&health, sizeof(health), hProcess);

            // Add 500 to health
            health += 500;

            // Patch new health
            mem::PatchEx((BYTE*)healthPtr, (BYTE*)&health, sizeof(health), hProcess);

        }

        // Freeze Health
        if ((GetAsyncKeyState(VK_NUMPAD1) & 1) || (GetAsyncKeyState(0x31) & 1))
        {
            // Set health bool
            bHealth = !bHealth;

            // If health
            if (bHealth)
            {
                // Health
                mem::NopEx((BYTE*)((BYTE*)proc::GetModuleBaseAddress(procId, L"ac_client.exe") + 0x29D1F), 3, hProcess);
            }
            else
            {
                // Health
                mem::PatchEx((BYTE*)((BYTE*)proc::GetModuleBaseAddress(procId, L"ac_client.exe") + 0x29D1F), (BYTE*)"\x29\x7B\x04", 3, hProcess);
            }

            // print cheat
            printCheat(bHealth, bAmmo, bArmor, bRecoil, bFly, bNoClip);
        }

        // Give Ammo
        if ((GetAsyncKeyState(VK_NUMPAD2) & 1) || (GetAsyncKeyState(0x32) & 1))
        {
            // Ammo value
            int ammoValue = 5000;

            // Pointers
            uintptr_t pistolAmmoPtr = proc::FindDMAAddyEx(hProcess, localPlayerPtr, { 0x13C });
            uintptr_t rifleAmmoPtr = proc::FindDMAAddyEx(hProcess, localPlayerPtr, { 0x150 });
            uintptr_t grenadeAmmoPtr = proc::FindDMAAddyEx(hProcess, localPlayerPtr, { 0x158 });
            uintptr_t doublePistolAmmoPtr = proc::FindDMAAddyEx(hProcess, localPlayerPtr, { 0x15C });

            // Patch with new value
            mem::PatchEx((BYTE*)pistolAmmoPtr, (BYTE*)&ammoValue, sizeof(ammoValue), hProcess);
            mem::PatchEx((BYTE*)rifleAmmoPtr, (BYTE*)&ammoValue, sizeof(ammoValue), hProcess);
            mem::PatchEx((BYTE*)grenadeAmmoPtr, (BYTE*)&ammoValue, sizeof(ammoValue), hProcess);
            mem::PatchEx((BYTE*)doublePistolAmmoPtr, (BYTE*)&ammoValue, sizeof(ammoValue), hProcess);
        }

        // Freeze Ammo
        if ((GetAsyncKeyState(VK_NUMPAD3) & 1) || (GetAsyncKeyState(0x33) & 1))
        {
            // Set ammo bool
            bAmmo = !bAmmo;

            // If ammo
            if (bAmmo)
            {
                // Ammo
                mem::NopEx((BYTE*)((BYTE*)proc::GetModuleBaseAddress(procId, L"ac_client.exe") + 0x637E9), 2, hProcess);

                // Grenades
                mem::NopEx((BYTE*)((BYTE*)proc::GetModuleBaseAddress(procId, L"ac_client.exe") + 0x63378), 2, hProcess);
            }
            else
            {
                // Ammo
                mem::PatchEx((BYTE*)((BYTE*)proc::GetModuleBaseAddress(procId, L"ac_client.exe") + 0x637E9), (BYTE *)"\xFF\x0E", 2, hProcess);

                // Grenades
                mem::PatchEx((BYTE*)((BYTE*)proc::GetModuleBaseAddress(procId, L"ac_client.exe") + 0x63378), (BYTE*)"\xFF\x08", 2, hProcess);
            }

            // print cheat
            printCheat(bHealth, bAmmo, bArmor, bRecoil, bFly, bNoClip);
        }

        // Give Armor
        if ((GetAsyncKeyState(VK_NUMPAD4) & 1) || (GetAsyncKeyState(0x34) & 1))
        {
            // Armor val
            int armor;

            // Armor pointer
            uintptr_t armorPtr = proc::FindDMAAddyEx(hProcess, localPlayerPtr, { 0xFC });

            // Read armor value
            mem::ReadEx((BYTE*)armorPtr, (BYTE*)&armor, sizeof(armor), hProcess);

            // Add 500 to armor
            armor += 500;

            // Patch armor
            mem::PatchEx((BYTE*)armorPtr, (BYTE*)&armor, sizeof(armor), hProcess);
        }

        // Freeze Armor
        if ((GetAsyncKeyState(VK_NUMPAD5) & 1) || (GetAsyncKeyState(0x35) & 1))
        {
            // Set armor bool
            bArmor = !bArmor;

            // If armor
            if (bArmor)
            {
                // Armor
                mem::NopEx((BYTE*)((BYTE*)proc::GetModuleBaseAddress(procId, L"ac_client.exe") + 0x29D0B), 3, hProcess);
            }
            else
            {
                // Armor
                mem::PatchEx((BYTE*)((BYTE*)proc::GetModuleBaseAddress(procId, L"ac_client.exe") + 0x29D0B), (BYTE*)"\x89\x73\x08", 3, hProcess);
            }

            // print cheat
            printCheat(bHealth, bAmmo, bArmor, bRecoil, bFly, bNoClip);
        }

        // No Recoil
        if ((GetAsyncKeyState(VK_NUMPAD6) & 1) || (GetAsyncKeyState(0x36) & 1))
        {
            // Set recoil bool
            bRecoil = !bRecoil;

            // If recoil
            if (bRecoil)
            {
                // Recoil
                mem::NopEx((BYTE*)((BYTE*)proc::GetModuleBaseAddress(procId, L"ac_client.exe") + 0x63786), 10, hProcess);
            }
            else
            {
                // Recoil
                mem::PatchEx((BYTE*)((BYTE*)proc::GetModuleBaseAddress(procId, L"ac_client.exe") + 0x63786), (BYTE*)"\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2", 10, hProcess);
            }

            // print cheat
            printCheat(bHealth, bAmmo, bArmor, bRecoil, bFly, bNoClip);
        }

        // Fly
        if ((GetAsyncKeyState(VK_NUMPAD7) & 1) || (GetAsyncKeyState(0x37) & 1))
        {
            // Fly bool
            bFly = !bFly;

            // If Fly
            if (bFly)
            {
                // Fly value
                int flyVal = 5;

                // Fly pointer
                uintptr_t flyPtr = proc::FindDMAAddyEx(hProcess, localPlayerPtr, { 0x338 });

                // patch fly value
                mem::PatchEx((BYTE*)flyPtr, (BYTE*)&flyVal, sizeof(flyVal), hProcess);
            }
            else 
            {
                // Fly value
                int flyVal = 0;

                // Fly pointer
                uintptr_t flyPtr = proc::FindDMAAddyEx(hProcess, localPlayerPtr, { 0x338 });

                // Patch fly value
                mem::PatchEx((BYTE*)flyPtr, (BYTE*)&flyVal, sizeof(flyVal), hProcess);
            }

            // print cheat
            printCheat(bHealth, bAmmo, bArmor, bRecoil, bFly, bNoClip);
        }

        // No Clip
        if ((GetAsyncKeyState(VK_NUMPAD8) & 1) || (GetAsyncKeyState(0x38) & 1))
        {
            // Set bool
            bNoClip = !bNoClip;

            // If no clip
            if (bNoClip)
            {
                // No clip value
                int noClipVal = 4;

                // No clip pointer
                uintptr_t noClipPtr = proc::FindDMAAddyEx(hProcess, localPlayerPtr, { 0x82 });

                // Patch value
                mem::PatchEx((BYTE*)noClipPtr, (BYTE*)&noClipVal, sizeof(noClipVal), hProcess);
            }
            else
            {
                // No clip alue
                int noClipVal = 0;

                // No clip pointer
                uintptr_t noClipPtr = proc::FindDMAAddyEx(hProcess, localPlayerPtr, { 0x82 });

                // Patch no clip value
                mem::PatchEx((BYTE*)noClipPtr, (BYTE*)&noClipVal, sizeof(noClipVal), hProcess);
            }

            // print cheat
            printCheat(bHealth, bAmmo, bArmor, bRecoil, bFly, bNoClip);
        }

        // Exit
        if (GetAsyncKeyState(VK_INSERT) & 1) break;
    }

}

