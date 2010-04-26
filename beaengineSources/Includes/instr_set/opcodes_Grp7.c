/* Copyright 2006-2009, BeatriX
 * File coded by BeatriX
 *
 * This file is part of BeaEngine.
 *
 *    BeaEngine is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    BeaEngine is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with BeaEngine.  If not, see <http://www.gnu.org/licenses/>. */

/* ====================================================================
 *      0f01h
 * ==================================================================== */
void __bea_callspec__ G7_(PDISASM pMyDisasm)
{
    (*pMyDisasm).Instruction.Category = SYSTEM_INSTRUCTION;
    REGOPCODE = ((*((UInt8*)(UIntPtr) (GV.EIP_+1))) >> 3) & 0x7;
    MOD_ = ((*((UInt8*)(UIntPtr) (GV.EIP_+1))) >> 6) & 0x3;
    RM_  = (*((UInt8*)(UIntPtr) (GV.EIP_+1))) & 0x7;
    if (REGOPCODE == 0) {
        if (MOD_ == 0x3) {
            if (RM_ == 0x1) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "vmcall ");
                GV.EIP_+= DECALAGE_EIP+2;
            }
            else if (RM_ == 0x2) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "vmlaunch ");
                GV.EIP_+= DECALAGE_EIP+2;
            }
            else if (RM_ == 0x3) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "vmresume ");
                GV.EIP_+= DECALAGE_EIP+2;
            }
            else if (RM_ == 0x4) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "vmxoff ");
                GV.EIP_+= DECALAGE_EIP+2;
            }
            else {
                FailDecode(pMyDisasm);
            }
        }
        else {
            GV.MemDecoration = Arg1fword;
            MOD_RM(&(*pMyDisasm).Argument1, pMyDisasm);
            (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "sgdt ");
            (*pMyDisasm).Argument2.ArgType = REGISTER_TYPE+MEMORY_MANAGEMENT_REG+REG0;
            (*pMyDisasm).Argument2.ArgSize = 48;
            GV.EIP_+= DECALAGE_EIP+2;
        }
    }
    else if (REGOPCODE == 1) {
        if (MOD_ == 0x3) {
            if (RM_ == 0x00) {
                (*pMyDisasm).Instruction.Category = SSE3_INSTRUCTION+AGENT_SYNCHRONISATION;
                (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "monitor ");
                GV.EIP_+= DECALAGE_EIP+2;
            }
            else if (RM_ == 0x01) {
                (*pMyDisasm).Instruction.Category = SSE3_INSTRUCTION+AGENT_SYNCHRONISATION;
                (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "mwait ");
                GV.EIP_+= DECALAGE_EIP+2;
            }
            else {
                FailDecode(pMyDisasm);
            }
        }
        else {
            GV.MemDecoration = Arg1fword;
            MOD_RM(&(*pMyDisasm).Argument1, pMyDisasm);
            (*pMyDisasm).Instruction.Category = SYSTEM_INSTRUCTION;
            (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "sidt ");
            (*pMyDisasm).Argument2.ArgType = REGISTER_TYPE+MEMORY_MANAGEMENT_REG+REG2;
            (*pMyDisasm).Argument2.ArgSize = 48;
            GV.EIP_+= DECALAGE_EIP+2;
        }
    }
    else if (REGOPCODE == 2) {
        if (MOD_ == 0x3) {
            if (RM_ == 0x0) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "xgetbv ");
                GV.EIP_+= DECALAGE_EIP+2;
            }
            else if (RM_ == 0x1) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "xsetbv ");
                GV.EIP_+= DECALAGE_EIP+2;
            }
            else {
                FailDecode(pMyDisasm);
            }
        }
        else {
            GV.MemDecoration = Arg2fword;
            MOD_RM(&(*pMyDisasm).Argument2, pMyDisasm);
            (*pMyDisasm).Instruction.Category = SYSTEM_INSTRUCTION;
            (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "lgdt ");
            (*pMyDisasm).Argument1.ArgType = REGISTER_TYPE+MEMORY_MANAGEMENT_REG+REG0;
            (*pMyDisasm).Argument1.ArgSize = 48;
            GV.EIP_+= DECALAGE_EIP+2;
        }
    }
    else if (REGOPCODE == 3) {
        if (MOD_ == 0x3) {
            if (RM_ == 0x0) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "vmrun ");
                GV.EIP_+= DECALAGE_EIP+2;
            }
            else if (RM_ == 0x1) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "vmmcall ");
                GV.EIP_+= DECALAGE_EIP+2;
            }
            else if (RM_ == 0x2) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "vmload ");
                GV.EIP_+= DECALAGE_EIP+2;
            }
            else if (RM_ == 0x3) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "vmsave ");
                GV.EIP_+= DECALAGE_EIP+2;
            }
            else if (RM_ == 0x4) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "stgi ");
                GV.EIP_+= DECALAGE_EIP+2;
            }
            else if (RM_ == 0x5) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "clgi ");
                GV.EIP_+= DECALAGE_EIP+2;
            }
            else if (RM_ == 0x6) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "skinit ");
                GV.EIP_+= DECALAGE_EIP+2;
            }
            else if (RM_ == 0x7) {
                (*pMyDisasm).Instruction.Category = VM_INSTRUCTION;
                (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "invlpga ");
                GV.EIP_+= DECALAGE_EIP+2;
            }
            else {
                FailDecode(pMyDisasm);
            }
        }
        else {
            GV.MemDecoration = Arg2fword;
            MOD_RM(&(*pMyDisasm).Argument2, pMyDisasm);
            (*pMyDisasm).Instruction.Category = SYSTEM_INSTRUCTION;
            (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "lidt ");
            (*pMyDisasm).Argument1.ArgType = REGISTER_TYPE+MEMORY_MANAGEMENT_REG+REG2;
            (*pMyDisasm).Argument1.ArgSize = 48;
            GV.EIP_+= DECALAGE_EIP+2;
        }
    }

    else if (REGOPCODE == 4) {
        GV.MemDecoration = Arg2word;
        MOD_RM(&(*pMyDisasm).Argument2, pMyDisasm);
        (*pMyDisasm).Instruction.Category = SYSTEM_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "smsw ");
        (*pMyDisasm).Argument1.ArgType = REGISTER_TYPE+CR_REG+REG0;
        (*pMyDisasm).Argument1.ArgSize = 16;
        GV.EIP_+= DECALAGE_EIP+2;
    }

    else if (REGOPCODE == 6) {
        GV.MemDecoration = Arg1word;
        MOD_RM(&(*pMyDisasm).Argument1, pMyDisasm);
        (*pMyDisasm).Instruction.Category = SYSTEM_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "lmsw ");
        (*pMyDisasm).Argument2.ArgType = REGISTER_TYPE+CR_REG+REG0;
        (*pMyDisasm).Argument2.ArgSize = 16;
        GV.EIP_+= DECALAGE_EIP+2;
    }
    else if (REGOPCODE == 7) {
        if (MOD_ == 0x3) {
            if (Architecture == 64) {
                if (RM_ == 0x0) {
                    (*pMyDisasm).Instruction.Category = SYSTEM_INSTRUCTION;
                    (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "swapgs ");
                    GV.EIP_+= DECALAGE_EIP+2;
                }
                else {
                    FailDecode(pMyDisasm);
                }
            }
            else {
                if (RM_ == 0x1) {
                    (*pMyDisasm).Instruction.Category = SYSTEM_INSTRUCTION;
                    (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "rdtscp ");
                    GV.EIP_+= DECALAGE_EIP+2;
                }
                else {
                    FailDecode(pMyDisasm);
                }
            }
        }
        else {
            GV.MemDecoration = Arg2byte;
            MOD_RM(&(*pMyDisasm).Argument2, pMyDisasm);
            (*pMyDisasm).Instruction.Category = SYSTEM_INSTRUCTION;
            (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "invlpg ");
            GV.EIP_+= DECALAGE_EIP+2;
        }
    }
    else {
        FailDecode(pMyDisasm);
    }


}

