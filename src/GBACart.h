/*
    Copyright 2019 Arisotura, Raphaël Zumer

    This file is part of melonDS.

    melonDS is free software: you can redistribute it and/or modify it under
    the terms of the GNU General Public License as published by the Free
    Software Foundation, either version 3 of the License, or (at your option)
    any later version.

    melonDS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with melonDS. If not, see http://www.gnu.org/licenses/.
*/

#ifndef GBACART_H
#define GBACART_H

#include "types.h"
#include "Savestate.h"


namespace GBACart_SRAM
{

extern u8* SRAM;
extern u32 SRAMLength;

void Reset();
void DoSavestate(Savestate* file);

u8 Read8(u32 addr);
u16 Read16(u32 addr);
u32 Read32(u32 addr);

void Write8(u32 addr, u8 val);
void Write16(u32 addr, u16 val);
void Write32(u32 addr, u32 val);

}


namespace GBACart
{

struct GPIO
{
    u16 data;
    u16 direction;
    u16 control;
};

extern bool CartInserted;
extern bool HasSolarSensor;
extern u8* CartROM;
extern u32 CartROMSize;
extern u32 CartCRC;

bool Init();
void DeInit();
void Reset();
void Eject();

void DoSavestate(Savestate* file);
bool LoadROM(const char* path, const char* sram);
void RelocateSave(const char* path, bool write);

void WriteGPIO(u32 addr, u16 val);

}


namespace GBACart_SolarSensor
{

extern u8 LightLevel;

void Reset();
void DoSavestate(Savestate* file);
void Process(GBACart::GPIO* gpio);

}

namespace GBACart_RumblePak
{

extern bool RumblePakEnabled;
extern u16 RumbleState;

u16 ReadRumble(u32 addr);
void WriteRumble(u32 addr, u16 val);

}


enum GuitarKeys : int
{
    Green = 0x40,
    Red = 0x20,
    Yellow = 0x10,
    Blue = 0x08,
};

namespace GBACart_GuitarGrip
{

extern bool GuitarGripEnabled;
extern u8 GuitarKeyStatus;

u8 ReadGrip8(u32 addr);
u16 ReadGrip16(u32 addr);

void SetGripKey(GuitarKeys key, bool val);
}

namespace GBACart_MemExpansionPak
{

extern bool MemPakEnabled;
extern u8 MemPakHeader[];
extern u8 MemPakMemory[0x800000];
extern bool MemPakRAMLock;

u8 ReadMemPak8(u32 addr);
void WriteMemPak8(u32 addr, u8 val);

u16 ReadMemPak16(u32 addr);
void WriteMemPak16(u32 addr, u16 val);

u32 ReadMemPak32(u32 addr);
void WriteMemPak32(u32 addr, u32 val);

void DoSavestate(Savestate* file);
}

#endif // GBACART_H
