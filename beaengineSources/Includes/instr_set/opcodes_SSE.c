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
 *      0x 0f 58
 * ==================================================================== */
void __bea_callspec__ addps_VW(PDISASM pMyDisasm)
{
    /* ========= 0xf2 */
    if (PrefRepne == 1) {
        (*pMyDisasm).Prefix.RepnePrefix = MandatoryPrefix;
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "addsd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========= 0xf3 */
    else if (PrefRepe == 1) {
        (*pMyDisasm).Prefix.RepPrefix = MandatoryPrefix;
        OpSize = 103;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "addss ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========== 0x66 */
    else if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "addpd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "addps ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}

/* ====================================================================
 *      0x 0f d0
 * ==================================================================== */
void __bea_callspec__ addsubpd_(PDISASM pMyDisasm)
{
    /* ========= 0xf2 */
    if (PrefRepne == 1) {
        (*pMyDisasm).Prefix.RepnePrefix = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE3_INSTRUCTION+SIMD_FP_PACKED;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "addsubps ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }

    /* ========== 0x66 */
    else if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE3_INSTRUCTION+SIMD_FP_PACKED;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "addsubpd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}


/* ====================================================================
 *      0x 0f 55
 * ==================================================================== */
void __bea_callspec__ andnps_VW(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+LOGICAL_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "andnpd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+LOGICAL_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "andnps ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 54
 * ==================================================================== */
void __bea_callspec__ andps_VW(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16){
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+LOGICAL_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "andpd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+LOGICAL_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "andps ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 3a 0d
 * ==================================================================== */
void __bea_callspec__ blendpd_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+PACKED_BLENDING_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "blendpd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
        EIP_++;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;

    }
    else {
        FailDecode(pMyDisasm);
    }

}


/* ====================================================================
 *      0x 0f 3a 0c
 * ==================================================================== */
void __bea_callspec__ blendps_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+PACKED_BLENDING_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "blendps ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
        EIP_++;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;
    }
    else {
        FailDecode(pMyDisasm);
    }
}


/* ====================================================================
 *      0x 0f 38 15
 * ==================================================================== */
void __bea_callspec__ blendvpd_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+PACKED_BLENDING_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "blendvpd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }

}


/* ====================================================================
 *      0x 0f 38 14
 * ==================================================================== */
void __bea_callspec__ blendvps_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+PACKED_BLENDING_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "blendvps ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}


/* ====================================================================
 *      0x 0f c2
 * ==================================================================== */
void __bea_callspec__ cmpps_VW(PDISASM pMyDisasm)
{

    /* ========= 0xf2 */
    if (PrefRepne == 1) {
        (*pMyDisasm).Prefix.RepnePrefix = MandatoryPrefix;
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+COMPARISON_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "cmpsd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========== 0xf3 */
    else if (PrefRepe == 1) {
        (*pMyDisasm).Prefix.RepPrefix = MandatoryPrefix;
        OpSize = 103;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+COMPARISON_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "cmpss ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========== 0x66 */
    else if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+COMPARISON_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "cmppd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+COMPARISON_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "cmpps ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    (*pMyDisasm).Argument1.AccessMode = READ;
    EIP_++;
    if (!Security(0)) return;
    third_arg = 1;
    (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
    (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
    (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
    (*pMyDisasm).Argument3.ArgSize = 8;
    ImmediatSize = 8;
}


/* ====================================================================
 *      0x 0f 38 f0
 * ==================================================================== */
void __bea_callspec__ crc32_GvEb(PDISASM pMyDisasm)
{
    /* ========= 0xf2 */
    if (PrefRepne == 1) {
        (*pMyDisasm).Prefix.RepnePrefix = MandatoryPrefix;
        (*pMyDisasm).Instruction.Category = SSE42_INSTRUCTION+ACCELERATOR_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "crc32 ");
        GvEb(pMyDisasm);
    }
    else {
        FailDecode(pMyDisasm);
    }
}

/* ====================================================================
 *      0x 0f 38 f1
 * ==================================================================== */
void __bea_callspec__ crc32_GvEv(PDISASM pMyDisasm)
{
    /* ========= 0xf2 */
    if (PrefRepne == 1) {
        (*pMyDisasm).Prefix.RepnePrefix = MandatoryPrefix;
        (*pMyDisasm).Instruction.Category = SSE42_INSTRUCTION+ACCELERATOR_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "crc32 ");
        GvEv(pMyDisasm);
    }
    else {
        FailDecode(pMyDisasm);
    }
}


/* ====================================================================
 *      0x 0f 2f
 * ==================================================================== */
void __bea_callspec__ comiss_VW(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+COMPARISON_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "comisd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+COMPARISON_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "comiss ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
}

/* ====================================================================
 *      0x 0f 5a
 * ==================================================================== */
void __bea_callspec__ cvtps2pd_(PDISASM pMyDisasm)
{
    /* ========= 0xf2 */
    if (PrefRepne == 1) {
        (*pMyDisasm).Prefix.RepnePrefix = MandatoryPrefix;
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "cvtsd2ss ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========== 0xf3 */
    else if (PrefRepe == 1) {
        (*pMyDisasm).Prefix.RepPrefix = MandatoryPrefix;
        OpSize = 103;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "cvtss2sd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========== 0x66 */
    else if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "cvtpd2ps ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "cvtps2pd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 5b
 * ==================================================================== */
void __bea_callspec__ cvtdq2ps_(PDISASM pMyDisasm)
{
    /* ========== 0xf3 */
    if (PrefRepe == 1) {
        (*pMyDisasm).Prefix.RepPrefix = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "cvttps2dq ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========== 0x66 */
    else if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "cvtps2dq ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "cvtdq2ps ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 2a
 * ==================================================================== */
void __bea_callspec__ cvtpi2ps_(PDISASM pMyDisasm)
{
    /* ========= 0xf2 */
    if (PrefRepne == 1) {
        (*pMyDisasm).Prefix.RepnePrefix = MandatoryPrefix;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "cvtsi2sd ");
        if (REX.W_ == 1) {
            OpSize = 104;
            MOD_RM(&(*pMyDisasm).Argument2);
            SSE_ = 1;
            Reg_Opcode(&(*pMyDisasm).Argument1);
            SSE_ = 0;
            EIP_+= DECALAGE_EIP+2;
        }
        else {
            OpSize = 103;
            MOD_RM(&(*pMyDisasm).Argument2);
            SSE_ = 1;
            Reg_Opcode(&(*pMyDisasm).Argument1);
            SSE_ = 0;
            EIP_+= DECALAGE_EIP+2;
        }
    }
    /* ========== 0xf3 */
    else if (PrefRepe == 1) {
        (*pMyDisasm).Prefix.RepPrefix = MandatoryPrefix;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "cvtsi2ss ");
        if (REX.W_ == 1) {
            OpSize = 104;
            MOD_RM(&(*pMyDisasm).Argument2);
            SSE_ = 1;
            Reg_Opcode(&(*pMyDisasm).Argument1);
            SSE_ = 0;
            EIP_+= DECALAGE_EIP+2;
        }
        else {
            OpSize = 103;
            MOD_RM(&(*pMyDisasm).Argument2);
            SSE_ = 1;
            Reg_Opcode(&(*pMyDisasm).Argument1);
            SSE_ = 0;
            EIP_+= DECALAGE_EIP+2;
        }
    }
    /* ========== 0x66 */
    else if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "cvtpi2pd ");
        OpSize = 104;
        MMX_ = 1;
        MOD_RM(&(*pMyDisasm).Argument2);
        MMX_ = 0;
        SSE_ = 1;
        Reg_Opcode(&(*pMyDisasm).Argument1);
        SSE_ = 0;
        EIP_+= DECALAGE_EIP+2;
    }
    else {
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "cvtpi2ps ");
        OpSize = 104;
        MMX_ = 1;
        MOD_RM(&(*pMyDisasm).Argument2);
        MMX_ = 0;
        SSE_ = 1;
        Reg_Opcode(&(*pMyDisasm).Argument1);
        SSE_ = 0;
        EIP_+= DECALAGE_EIP+2;
    }
}


/* ====================================================================
 *      0x 0f 2d
 * ==================================================================== */
void __bea_callspec__ cvtps2pi_(PDISASM pMyDisasm)
{
    /* ========= 0xf2 */
    if (PrefRepne == 1) {
        (*pMyDisasm).Prefix.RepnePrefix = MandatoryPrefix;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "cvtsd2si ");
        if (REX.W_ == 1) {
            OpSize = 104;
            SSE_ = 1;
            MOD_RM(&(*pMyDisasm).Argument2);
            SSE_ = 0;
            Reg_Opcode(&(*pMyDisasm).Argument1);
            EIP_+= DECALAGE_EIP+2;
        }
        else {
            OpSize = 104;
            SSE_ = 1;
            MOD_RM(&(*pMyDisasm).Argument2);
            SSE_ = 0;
            Reg_Opcode(&(*pMyDisasm).Argument1);
            EIP_+= DECALAGE_EIP+2;
        }
    }
    /* ========== 0xf3 */
    else if (PrefRepe == 1) {
        (*pMyDisasm).Prefix.RepPrefix = MandatoryPrefix;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "cvtss2si ");
        if (REX.W_ == 1) {
            OpSize = 103;
            SSE_ = 1;
            MOD_RM(&(*pMyDisasm).Argument2);
            SSE_ = 0;
            Reg_Opcode(&(*pMyDisasm).Argument1);
            EIP_+= DECALAGE_EIP+2;
        }
        else {
            OpSize = 103;
            SSE_ = 1;
            MOD_RM(&(*pMyDisasm).Argument2);
            SSE_ = 0;
            Reg_Opcode(&(*pMyDisasm).Argument1);
            EIP_+= DECALAGE_EIP+2;
        }
    }
    /* ========== 0x66 */
    else if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "cvtpd2pi ");
        OpSize = 108;
        SSE_ = 1;
        MOD_RM(&(*pMyDisasm).Argument2);
        SSE_ = 0;
        MMX_ = 1;
        Reg_Opcode(&(*pMyDisasm).Argument1);
        MMX_ = 0;
        EIP_+= DECALAGE_EIP+2;
    }
    else {
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "cvtps2pi ");
        OpSize = 108;
        SSE_ = 1;
        MOD_RM(&(*pMyDisasm).Argument2);
        SSE_ = 0;
        MMX_ = 1;
        Reg_Opcode(&(*pMyDisasm).Argument1);
        MMX_ = 0;
        EIP_+= DECALAGE_EIP+2;
    }
}


/* ====================================================================
 *      0x 0f 2c
 * ==================================================================== */
void __bea_callspec__ cvttps2pi_(PDISASM pMyDisasm)
{
    /* ========= 0xf2 */
    if (PrefRepne == 1) {
        (*pMyDisasm).Prefix.RepnePrefix = MandatoryPrefix;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "cvttsd2si ");
        if (REX.W_ == 1) {
            OpSize = 104;
            SSE_ = 1;
            MOD_RM(&(*pMyDisasm).Argument2);
            SSE_ = 0;
            Reg_Opcode(&(*pMyDisasm).Argument1);
            EIP_+= DECALAGE_EIP+2;
        }
        else {
            OpSize = 104;
            SSE_ = 1;
            MOD_RM(&(*pMyDisasm).Argument2);
            SSE_ = 0;
            Reg_Opcode(&(*pMyDisasm).Argument1);
            EIP_+= DECALAGE_EIP+2;
        }
    }
    /* ========== 0xf3 */
    else if (PrefRepe == 1) {
        (*pMyDisasm).Prefix.RepPrefix = MandatoryPrefix;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "cvttss2si ");
        OpSize = 103;
        SSE_ = 1;
        MOD_RM(&(*pMyDisasm).Argument2);
        SSE_ = 0;
        Reg_Opcode(&(*pMyDisasm).Argument1);
        EIP_+= DECALAGE_EIP+2;
    }
    /* ========== 0x66 */
    else if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "cvttpd2pi ");
        OpSize = 108;
        SSE_ = 1;
        MOD_RM(&(*pMyDisasm).Argument2);
        SSE_ = 0;
        MMX_ = 1;
        Reg_Opcode(&(*pMyDisasm).Argument1);
        MMX_ = 0;
        EIP_+= DECALAGE_EIP+2;
    }
    else {
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "cvttps2pi ");
        OpSize = 108;
        SSE_ = 1;
        MOD_RM(&(*pMyDisasm).Argument2);
        SSE_ = 0;
        MMX_ = 1;
        Reg_Opcode(&(*pMyDisasm).Argument1);
        MMX_ = 0;
        EIP_+= DECALAGE_EIP+2;
    }
}


/* ====================================================================
 *      0x 0f e6
 * ==================================================================== */
void __bea_callspec__ cvtpd2dq_(PDISASM pMyDisasm)
{
    /* ========== 0xf2 */
    if (PrefRepne == 1) {
        (*pMyDisasm).Prefix.RepnePrefix = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "cvtpd2dq ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========== 0xf3 */
    else if (PrefRepe == 1) {
        (*pMyDisasm).Prefix.RepPrefix = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "cvtdq2pd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========== 0x66 */
    else if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "cvttpd2dq ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}


/* ====================================================================
 *      0x 0f 3a 41
 * ==================================================================== */
void __bea_callspec__ dppd_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+DOT_PRODUCT;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "dppd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
        EIP_++;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;

    }
    else {
        FailDecode(pMyDisasm);
    }

}

/* ====================================================================
 *      0x 0f 3a 40
 * ==================================================================== */
void __bea_callspec__ dpps_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+DOT_PRODUCT;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "dpps ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
        EIP_++;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;

    }
    else {
        FailDecode(pMyDisasm);
    }

}


/* ====================================================================
 *      0x 0f 5e
 * ==================================================================== */
void __bea_callspec__ divps_VW(PDISASM pMyDisasm)
{
    /* ========= 0xf2 */
    if (PrefRepne == 1) {
        (*pMyDisasm).Prefix.RepnePrefix = MandatoryPrefix;
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "divsd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========= 0xf3 */
    else if (PrefRepe == 1) {
        (*pMyDisasm).Prefix.RepPrefix = MandatoryPrefix;
        OpSize = 103;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "divss ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========== 0x66 */
    else if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "divpd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "divps ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 3a 17
 * ==================================================================== */
void __bea_callspec__ extractps_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 3;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+INSERTION_EXTRACTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "extractps ");
        MOD_RM(&(*pMyDisasm).Argument1);
        SSE_ = 1;
        Reg_Opcode(&(*pMyDisasm).Argument2);
        SSE_ = 0;
        EIP_+= DECALAGE_EIP+2;
        EIP_++;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;

    }
    else {
        FailDecode(pMyDisasm);
    }

}


/* ====================================================================
 *      0x 0f 7c
 * ==================================================================== */
void __bea_callspec__ haddpd_VW(PDISASM pMyDisasm)
{

    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE3_INSTRUCTION+SIMD_FP_HORIZONTAL;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "haddpd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE3_INSTRUCTION+SIMD_FP_HORIZONTAL;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "haddps ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 7d
 * ==================================================================== */
void __bea_callspec__ hsubpd_VW(PDISASM pMyDisasm)
{

    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE3_INSTRUCTION+SIMD_FP_HORIZONTAL;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "hsubpd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE3_INSTRUCTION+SIMD_FP_HORIZONTAL;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "hsubps ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 3a 21
 * ==================================================================== */
void __bea_callspec__ insertps_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+INSERTION_EXTRACTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "insertps ");
        SSE_ = 1;
        MOD_ = ((*((UInt8*)(ULONG_PTR) (EIP_+1))) >> 6) & 0x3;
        if (MOD_ == 0x3) {
            OpSize = 104;
        }
        else {
            OpSize = 103;
        }
        MOD_RM(&(*pMyDisasm).Argument2);


        Reg_Opcode(&(*pMyDisasm).Argument1);
        SSE_ = 0;
        EIP_+= DECALAGE_EIP+2;
        EIP_++;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;

    }
    else {
        FailDecode(pMyDisasm);
    }

}



/* ====================================================================
 *      0x 0f f0
 * ==================================================================== */
void __bea_callspec__ lddqu_(PDISASM pMyDisasm)
{
    /* ========= 0xf2 */
    if (PrefRepne == 1) {
        (*pMyDisasm).Prefix.RepnePrefix = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE3_INSTRUCTION+SPECIALIZED_128bits;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "lddqu ");
        MOD_RM(&(*pMyDisasm).Argument2);
        SSE_ = 1;
        Reg_Opcode(&(*pMyDisasm).Argument1);
        SSE_ = 0;
        EIP_+= DECALAGE_EIP+2;
    }
    else {
        FailDecode(pMyDisasm);
    }

}


/* ====================================================================
 *      0x 0f f7
 * ==================================================================== */
void __bea_callspec__ maskmovq_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CACHEABILITY_CONTROL;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "maskmovdqu ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+CACHEABILITY_CONTROL;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "maskmovq ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 5f
 * ==================================================================== */
void __bea_callspec__ maxps_VW(PDISASM pMyDisasm)
{
    /* ========= 0xf2 */
    if (PrefRepne == 1) {
        (*pMyDisasm).Prefix.RepnePrefix = MandatoryPrefix;
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "maxsd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========= 0xf3 */
    else if (PrefRepe == 1) {
        (*pMyDisasm).Prefix.RepPrefix = MandatoryPrefix;
        OpSize = 103;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "maxss ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========== 0x66 */
    else if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "maxpd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "maxps ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 5d
 * ==================================================================== */
void __bea_callspec__ minps_VW(PDISASM pMyDisasm)
{
    /* ========= 0xf2 */
    if (PrefRepne == 1) {
        (*pMyDisasm).Prefix.RepnePrefix = MandatoryPrefix;
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "minsd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========= 0xf3 */
    else if (PrefRepe == 1) {
        (*pMyDisasm).Prefix.RepPrefix = MandatoryPrefix;
        OpSize = 103;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "minss ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========== 0x66 */
    else if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "minpd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "minps ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}

/* ====================================================================
 *      0x 0f 28
 * ==================================================================== */
void __bea_callspec__ movaps_VW(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+DATA_TRANSFER;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movapd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+DATA_TRANSFER;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movaps ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
}

/* ====================================================================
 *      0x 0f 29
 * ==================================================================== */
void __bea_callspec__ movaps_WV(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 8;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+DATA_TRANSFER;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movapd ");
        SSE_ = 1;
        ExGx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+DATA_TRANSFER;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movaps ");
        SSE_ = 1;
        ExGx(pMyDisasm);
        SSE_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 16
 * ==================================================================== */
void __bea_callspec__ movhps_VM(PDISASM pMyDisasm)
{

    /* ========= 0xf3 */
    if (PrefRepe == 1) {
        (*pMyDisasm).Prefix.RepPrefix = MandatoryPrefix;
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSE3_INSTRUCTION+DATA_TRANSFER;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movshdup ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========== 0x66 */
    else if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+DATA_TRANSFER;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movhpd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+DATA_TRANSFER;
        MOD_ = ((*((UInt8*)(ULONG_PTR) (EIP_+1))) >> 6) & 0x3;
        if (MOD_ == 0x3) {
            (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movlhps ");
        }
        else {
            (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movhps ");
        }
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 17
 * ==================================================================== */
void __bea_callspec__ movhps_MV(PDISASM pMyDisasm)
{

    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 4;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+DATA_TRANSFER;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movhpd ");
        SSE_ = 1;
        ExGx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 4;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+DATA_TRANSFER;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movhps ");
        SSE_ = 1;
        ExGx(pMyDisasm);
        SSE_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 12
 * ==================================================================== */
void __bea_callspec__ movlps_VM(PDISASM pMyDisasm)
{
    /* ========= 0xf2 */
    if (PrefRepne == 1) {
        (*pMyDisasm).Prefix.RepnePrefix = MandatoryPrefix;
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSE3_INSTRUCTION+DATA_TRANSFER;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movddup ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========= 0xf3 */
    else if (PrefRepe == 1) {
        (*pMyDisasm).Prefix.RepPrefix = MandatoryPrefix;
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSE3_INSTRUCTION+DATA_TRANSFER;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movsldup ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========== 0x66 */
    else if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+DATA_TRANSFER;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movlpd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+DATA_TRANSFER;
        if (MOD_ == 0x3) {
            (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movhlps ");
        }
        else {
            (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movlps ");
        }
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 13
 * ==================================================================== */
void __bea_callspec__ movlps_MV(PDISASM pMyDisasm)
{

    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 4;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+DATA_TRANSFER;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movlpd ");
        SSE_ = 1;
        ExGx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 4;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+DATA_TRANSFER;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movlps ");
        SSE_ = 1;
        ExGx(pMyDisasm);
        SSE_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 50
 * ==================================================================== */
void __bea_callspec__ movmskps_(PDISASM pMyDisasm)
{
    MOD_ = ((*((UInt8*)(ULONG_PTR) (EIP_+1))) >> 6) & 0x3;
    if (MOD_ != 0x3) {
        FailDecode(pMyDisasm);
    }
    /* ========== 0x66 */
    else if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+DATA_TRANSFER;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movmskpd ");
        SSE_ = 1;
        MOD_RM(&(*pMyDisasm).Argument2);
        SSE_ = 0;
        Reg_Opcode(&(*pMyDisasm).Argument1);
        EIP_ += DECALAGE_EIP+2;

    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+DATA_TRANSFER;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movmskps ");
        SSE_ = 1;
        MOD_RM(&(*pMyDisasm).Argument2);
        SSE_ = 0;
        Reg_Opcode(&(*pMyDisasm).Argument1);
        EIP_ += DECALAGE_EIP+2;

    }
}


/* ====================================================================
 *      0x 0f 38 2a
 * ==================================================================== */
void __bea_callspec__ movntdqa_(PDISASM pMyDisasm)
{

    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+STREAMING_LOAD;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movntdqa ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}


/* ====================================================================
 *      0x 0f c3
 * ==================================================================== */
void __bea_callspec__ movnti_(PDISASM pMyDisasm)
{
    (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CACHEABILITY_CONTROL;
    (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movnti ");
    EvGv(pMyDisasm);

}


/* ====================================================================
 *      0x 0f 2b
 * ==================================================================== */
void __bea_callspec__ movntps_(PDISASM pMyDisasm)
{
    MOD_ = ((*((UInt8*)(ULONG_PTR) (EIP_+1))) >> 6) & 0x3;
    if (MOD_ == 0x3) {
        FailDecode(pMyDisasm);
    }
    /* ========== 0x66 */
    else if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 8;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CACHEABILITY_CONTROL;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movntpd ");
        SSE_ = 1;
        Reg_Opcode(&(*pMyDisasm).Argument2);
        SSE_ = 0;
        MOD_RM(&(*pMyDisasm).Argument1);
        EIP_ += DECALAGE_EIP+2;

    }
    else {
        OpSize = 4;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CACHEABILITY_CONTROL;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movntps ");
        SSE_ = 1;
        Reg_Opcode(&(*pMyDisasm).Argument2);
        SSE_ = 0;
        MOD_RM(&(*pMyDisasm).Argument1);
        EIP_ += DECALAGE_EIP+2;

    }
}


/* ====================================================================
 *      0x 0f e7
 * ==================================================================== */
void __bea_callspec__ movntq_(PDISASM pMyDisasm)
{
    MOD_ = ((*((UInt8*)(ULONG_PTR) (EIP_+1))) >> 6) & 0x3;
    if (MOD_ == 0x3) {
        FailDecode(pMyDisasm);
    }
    /* ========== 0x66 */
    else if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 8;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+CACHEABILITY_CONTROL;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movntdq ");
        SSE_ = 1;
        ExGx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 4;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+CACHEABILITY_CONTROL;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movntq ");
        MMX_ = 1;
        ExGx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 10
 * ==================================================================== */
void __bea_callspec__ movups_VW(PDISASM pMyDisasm)
{
    /* ========= 0xf2 */
    if (PrefRepne == 1) {
        (*pMyDisasm).Prefix.RepnePrefix = MandatoryPrefix;
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movsd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========= 0xf3 */
    else if (PrefRepe == 1) {
        (*pMyDisasm).Prefix.RepPrefix = MandatoryPrefix;
        OpSize = 103;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movss ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========== 0x66 */
    else if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movupd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movups ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
}



/* ====================================================================
 *      0x 0f 11
 * ==================================================================== */
void __bea_callspec__ movups_WV(PDISASM pMyDisasm)
{
    /* ========= 0xf2 */
    if (PrefRepne == 1) {
        (*pMyDisasm).Prefix.RepnePrefix = MandatoryPrefix;
        OpSize = 4;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movsd ");
        SSE_ = 1;
        ExGx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========= 0xf3 */
    else if (PrefRepe == 1) {
        (*pMyDisasm).Prefix.RepPrefix = MandatoryPrefix;
        OpSize = 3;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movss ");
        SSE_ = 1;
        ExGx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========== 0x66 */
    else if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 8;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movupd ");
        SSE_ = 1;
        ExGx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 8;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "movups ");
        SSE_ = 1;
        ExGx(pMyDisasm);
        SSE_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 3a 42
 * ==================================================================== */
void __bea_callspec__ mpsadbw_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+SAD_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "mpsadbw ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
        EIP_++;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;

    }
    else {
        FailDecode(pMyDisasm);
    }

}


/* ====================================================================
 *      0x 0f 59
 * ==================================================================== */
void __bea_callspec__ mulps_VW(PDISASM pMyDisasm)
{
    /* ========= 0xf2 */
    if (PrefRepne == 1) {
        (*pMyDisasm).Prefix.RepnePrefix = MandatoryPrefix;
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "mulsd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========== 0xf3 */
    else if (PrefRepe == 1) {
        (*pMyDisasm).Prefix.RepPrefix = MandatoryPrefix;
        OpSize = 103;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "mulss ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========== 0x66 */
    else if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "mulpd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "mulps ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 56
 * ==================================================================== */
void __bea_callspec__ orps_VW(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+LOGICAL_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "orpd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+LOGICAL_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "orps ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 38 2b
 * ==================================================================== */
void __bea_callspec__ packusdw_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "packusdw ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;

    }
    else {
        FailDecode(pMyDisasm);
    }

}


/* ====================================================================
 *      0x 0f d4
 * ==================================================================== */
void __bea_callspec__ paddq_(PDISASM pMyDisasm)
{
    (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+SIMD128bits;
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "paddq ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "paddq ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f e0
 * ==================================================================== */
void __bea_callspec__ pavgb_(PDISASM pMyDisasm)
{
    (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+SIMD64bits;
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pavgb ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pavgb ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f e3
 * ==================================================================== */
void __bea_callspec__ pavgw_(PDISASM pMyDisasm)
{
    (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+SIMD64bits;
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pavgw ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pavgw ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 3a 0f
 * ==================================================================== */
void __bea_callspec__ palignr_(PDISASM pMyDisasm)
{
    (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+SIMD64bits;
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "palignr ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
        EIP_++;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;
    }
    else {
        OpSize = 104;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "palignr ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
        EIP_++;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;
    }
}


/* ====================================================================
 *      0x 0f 38 10
 * ==================================================================== */
void __bea_callspec__ pblendvb_(PDISASM pMyDisasm)
{
    (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+PACKED_BLENDING_INSTRUCTION;
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pblendvb ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pblendvb ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 3a 0e
 * ==================================================================== */
void __bea_callspec__ pblendw_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+SAD_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pblendw ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
        EIP_++;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;

    }
    else {
        FailDecode(pMyDisasm);
    }

}


/* ====================================================================
 *      0x 0f 38 29
 * ==================================================================== */
void __bea_callspec__ pcmpeqq_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+PACKED_EQUALITY;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pcmpeqq ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;

    }
    else {
        FailDecode(pMyDisasm);
    }

}


/* ====================================================================
 *      0x 0f 3a 61
 * ==================================================================== */
void __bea_callspec__ pcmpestri_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE42_INSTRUCTION+COMPARISON_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pcmpestri ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
        EIP_++;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;

    }
    else {
        FailDecode(pMyDisasm);
    }

}


/* ====================================================================
 *      0x 0f 3a 60
 * ==================================================================== */
void __bea_callspec__ pcmpestrm_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE42_INSTRUCTION+COMPARISON_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pcmpestrm ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
        EIP_++;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;

    }
    else {
        FailDecode(pMyDisasm);
    }

}


/* ====================================================================
 *      0x 0f 3a 63
 * ==================================================================== */
void __bea_callspec__ pcmpistri_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE42_INSTRUCTION+COMPARISON_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pcmpistri ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
        EIP_++;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;

    }
    else {
        FailDecode(pMyDisasm);
    }

}


/* ====================================================================
 *      0x 0f 3a 62
 * ==================================================================== */
void __bea_callspec__ pcmpistrm_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE42_INSTRUCTION+COMPARISON_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pcmpestrm ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
        EIP_++;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;

    }
    else {
        FailDecode(pMyDisasm);
    }

}


/* ====================================================================
 *      0x 0f 38 37
 * ==================================================================== */
void __bea_callspec__ pcmpgtq_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE42_INSTRUCTION+COMPARISON_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pcmpgtq ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;

    }
    else {
        FailDecode(pMyDisasm);
    }

}


/* ====================================================================
 *      0x 0f 3a 14
 * ==================================================================== */
void __bea_callspec__ pextrb_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+INSERTION_EXTRACTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pextrb ");
        MOD_ = ((*((UInt8*)(ULONG_PTR) (EIP_+1))) >> 6) & 0x3;
        if (MOD_ == 0x3) {
            OpSize = 3;
        }
        else {
            OpSize = 1;
        }
        MOD_RM(&(*pMyDisasm).Argument1);
        SSE_ = 1;
        Reg_Opcode(&(*pMyDisasm).Argument2);
        SSE_ = 0;
        EIP_ += DECALAGE_EIP+3;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;

    }
    else {
        FailDecode(pMyDisasm);
    }

}


/* ====================================================================
 *      0x 0f 3a 16
 * ==================================================================== */
void __bea_callspec__ pextrd_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+INSERTION_EXTRACTION;
        if (REX.W_ == 0x1) {
            (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pextrq ");
            OpSize = 4;
        }
        else {
            (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pextrd ");
            OpSize = 3;
        }
        MOD_RM(&(*pMyDisasm).Argument1);
        SSE_ = 1;
        Reg_Opcode(&(*pMyDisasm).Argument2);
        SSE_ = 0;
        EIP_ += DECALAGE_EIP+3;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;

    }
    else {
        FailDecode(pMyDisasm);
    }

}

/* ====================================================================
 *      0x 0f c5
 * ==================================================================== */
void __bea_callspec__ pextrw_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+SIMD64bits;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pextrw ");
        OpSize = 108;
        SSE_ = 1;
        MOD_RM(&(*pMyDisasm).Argument2);
        SSE_ = 0;
        Reg_Opcode(&(*pMyDisasm).Argument1);
        EIP_ += DECALAGE_EIP+3;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;

    }
    else {
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+SIMD64bits;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pextrw ");
        OpSize = 108;
        MMX_ = 1;
        MOD_RM(&(*pMyDisasm).Argument2);
        MMX_ = 0;
        Reg_Opcode(&(*pMyDisasm).Argument1);
        EIP_ += DECALAGE_EIP+3;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;
    }

}

/* ====================================================================
 *      0x 0f 3a 15
 * ==================================================================== */
void __bea_callspec__ pextrw2_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+INSERTION_EXTRACTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pextrw ");
        MOD_ = ((*((UInt8*)(ULONG_PTR) (EIP_+1))) >> 6) & 0x3;
        if (MOD_ == 0x3) {
            OpSize = 3;
        }
        else {
            OpSize = 2;
        }
        MOD_RM(&(*pMyDisasm).Argument1);
        SSE_ = 1;
        Reg_Opcode(&(*pMyDisasm).Argument2);
        SSE_ = 0;
        EIP_ += DECALAGE_EIP+3;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;

    }
    else {
        FailDecode(pMyDisasm);
    }

}


/* ====================================================================
 *      0x 0f 38 02
 * ==================================================================== */
void __bea_callspec__ phaddd_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSSE3_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "phaddd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSSE3_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "phaddd ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 38 03
 * ==================================================================== */
void __bea_callspec__ phaddsw_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSSE3_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "phaddsw ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSSE3_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "phaddsw ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 38 01
 * ==================================================================== */
void __bea_callspec__ phaddw_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSSE3_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "phaddw ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSSE3_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "phaddw ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 38 41
 * ==================================================================== */
void __bea_callspec__ phminposuw_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+HORIZONTAL_SEARCH;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "phminposuw ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}


/* ====================================================================
 *      0x 0f 38 05
 * ==================================================================== */
void __bea_callspec__ phsubw_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSSE3_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "phsubw ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSSE3_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "phsubw ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 38 06
 * ==================================================================== */
void __bea_callspec__ phsubd_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSSE3_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "phsubd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSSE3_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "phsubd ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 38 07
 * ==================================================================== */
void __bea_callspec__ phsubsw_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSSE3_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "phsubsw ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSSE3_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "phsubsw ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 3a 20
 * ==================================================================== */
void __bea_callspec__ pinsrb_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+INSERTION_EXTRACTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pinsrb ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
        EIP_++;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;

    }
    else {
        FailDecode(pMyDisasm);
    }

}


/* ====================================================================
 *      0x 0f 3a 22
 * ==================================================================== */
void __bea_callspec__ pinsrd_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+INSERTION_EXTRACTION;
        if (REX.W_ == 0x1) {
            (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pinsrq ");
            OpSize = 4;
        }
        else {
            (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pinsrd ");
            OpSize = 3;
        }
        MOD_RM(&(*pMyDisasm).Argument1);
        SSE_ = 1;
        Reg_Opcode(&(*pMyDisasm).Argument2);
        SSE_ = 0;
        EIP_ += DECALAGE_EIP+3;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;

    }
    else {
        FailDecode(pMyDisasm);
    }

}


/* ====================================================================
 *      0x 0f c4
 * ==================================================================== */
void __bea_callspec__ pinsrw_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+SIMD64bits;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pinsrw ");
        OpSize = 108;
        MOD_RM(&(*pMyDisasm).Argument2);
        SSE_ = 1;
        Reg_Opcode(&(*pMyDisasm).Argument1);
        SSE_ = 0;
        EIP_ += DECALAGE_EIP+3;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;

    }
    else {
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+SIMD64bits;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pinsrw ");
        OpSize = 108;
        MOD_RM(&(*pMyDisasm).Argument2);
        MMX_ = 1;
        Reg_Opcode(&(*pMyDisasm).Argument1);
        MMX_ = 0;
        EIP_ += DECALAGE_EIP+3;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;
    }

}


/* ====================================================================
 *      0x 0f 38 3c
 * ==================================================================== */
void __bea_callspec__ pmaxsb_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+PACKED_MINMAX;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmaxsb ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}

/* ====================================================================
 *      0x 0f 38 3d
 * ==================================================================== */
void __bea_callspec__ pmaxsd_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+PACKED_MINMAX;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmaxsd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}

/* ====================================================================
 *      0x 0f 38 3e
 * ==================================================================== */
void __bea_callspec__ pmaxuw_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+PACKED_MINMAX;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmaxuw ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}

/* ====================================================================
 *      0x 0f 38 3f
 * ==================================================================== */
void __bea_callspec__ pmaxud_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+PACKED_MINMAX;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmaxud ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}

/* ====================================================================
 *      0x 0f 38 38
 * ==================================================================== */
void __bea_callspec__ pminsb_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+PACKED_MINMAX;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pminsb ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}

/* ====================================================================
 *      0x 0f 38 39
 * ==================================================================== */
void __bea_callspec__ pminsd_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+PACKED_MINMAX;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pminsd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}

/* ====================================================================
 *      0x 0f 38 3a
 * ==================================================================== */
void __bea_callspec__ pminuw_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+PACKED_MINMAX;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pminuw ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}

/* ====================================================================
 *      0x 0f 38 3b
 * ==================================================================== */
void __bea_callspec__ pminud_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+PACKED_MINMAX;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pminud ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}


/* ====================================================================
 *      0x 0f da
 * ==================================================================== */
void __bea_callspec__ pminub_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+SIMD64bits;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pminub ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+SIMD64bits;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pminub ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f de
 * ==================================================================== */
void __bea_callspec__ pmaxub_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+SIMD64bits;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmaxub ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+SIMD64bits;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmaxub ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f ea
 * ==================================================================== */
void __bea_callspec__ pminsw_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+SIMD64bits;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pminsw ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+SIMD64bits;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pminsw ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f ee
 * ==================================================================== */
void __bea_callspec__ pmaxsw_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+SIMD64bits;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmaxsw ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+SIMD64bits;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmaxsw ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 38 04
 * ==================================================================== */
void __bea_callspec__ pmaddubsw_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSSE3_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmaddubsw ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSSE3_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmaddubsw ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f d7
 * ==================================================================== */
void __bea_callspec__ pmovmskb_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {

        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+SIMD64bits;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmovmskb ");
        OpSize = 108;
        SSE_ = 1;
        MOD_RM(&(*pMyDisasm).Argument2);
        SSE_ = 0;
        Reg_Opcode(&(*pMyDisasm).Argument1);
        EIP_ += DECALAGE_EIP+2;
    }
    else {
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+SIMD64bits;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmovmskb ");
        OpSize = 104;
        MMX_ = 1;
        MOD_RM(&(*pMyDisasm).Argument2);
        MMX_ = 0;
        Reg_Opcode(&(*pMyDisasm).Argument1);
        EIP_ += DECALAGE_EIP+2;
    }

}


/* ====================================================================
 *      0x 0f 38 21
 * ==================================================================== */
void __bea_callspec__ pmovsxbd_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmovsxbd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}


/* ====================================================================
 *      0x 0f 38 22
 * ==================================================================== */
void __bea_callspec__ pmovsxbq_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmovsxbq ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}


/* ====================================================================
 *      0x 0f 38 20
 * ==================================================================== */
void __bea_callspec__ pmovsxbw_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmovsxbw ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}


/* ====================================================================
 *      0x 0f 38 25
 * ==================================================================== */
void __bea_callspec__ pmovsxdq_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmovsxdq ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}


/* ====================================================================
 *      0x 0f 38 23
 * ==================================================================== */
void __bea_callspec__ pmovsxwd_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmovsxwd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}


/* ====================================================================
 *      0x 0f 38 24
 * ==================================================================== */
void __bea_callspec__ pmovsxwq_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmovsxwq ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}


/* ====================================================================
 *      0x 0f 38 31
 * ==================================================================== */
void __bea_callspec__ pmovzxbd_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmovzxbd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}


/* ====================================================================
 *      0x 0f 38 32
 * ==================================================================== */
void __bea_callspec__ pmovzxbq_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmovzxbq ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}


/* ====================================================================
 *      0x 0f 38 30
 * ==================================================================== */
void __bea_callspec__ pmovzxbw_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmovzxbw ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}


/* ====================================================================
 *      0x 0f 38 35
 * ==================================================================== */
void __bea_callspec__ pmovzxdq_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmovzxdq ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}


/* ====================================================================
 *      0x 0f 38 33
 * ==================================================================== */
void __bea_callspec__ pmovzxwd_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmovzxwd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}


/* ====================================================================
 *      0x 0f 38 34
 * ==================================================================== */
void __bea_callspec__ pmovzxwq_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+CONVERSION_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmovzxwq ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}


/* ====================================================================
 *      0x 0f 38 28
 * ==================================================================== */
void __bea_callspec__ pmuldq_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmuldq ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}


/* ====================================================================
 *      0x 0f 38 40
 * ==================================================================== */
void __bea_callspec__ pmulld_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmulld ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}


/* ====================================================================
 *      0x 0f 38 0b
 * ==================================================================== */
void __bea_callspec__ pmulhrsw_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSSE3_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmulhrsw ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSSE3_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmulhrsw ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f e4
 * ==================================================================== */
void __bea_callspec__ pmulhuw_(PDISASM pMyDisasm)
{
    (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+SIMD64bits;
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmulhuw ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmulhuw ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f f4
 * ==================================================================== */
void __bea_callspec__ pmuludq_(PDISASM pMyDisasm)
{
    (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+SIMD64bits;
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmuludq ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pmuludq ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* =======================================
 *      0x 0f b8
 * ======================================= */
void __bea_callspec__ popcnt_(PDISASM pMyDisasm)
{
    (*pMyDisasm).Instruction.Category = SSE42_INSTRUCTION+DATA_TRANSFER;
    (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "popcnt ");
    GvEv(pMyDisasm);
    FillFlags(pMyDisasm,114);
}


/* ====================================================================
 *      0x 0f f6
 * ==================================================================== */
void __bea_callspec__ psadbw_(PDISASM pMyDisasm)
{
    (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+SIMD64bits;
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "psadbw ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "psadbw ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 38 00
 * ==================================================================== */
void __bea_callspec__ pshufb_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSSE3_INSTRUCTION+SHUFFLE_UNPACK;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pshufb ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSSE3_INSTRUCTION+SHUFFLE_UNPACK;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pshufb ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 70
 * ==================================================================== */
void __bea_callspec__ pshufw_(PDISASM pMyDisasm)
{
    (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+SIMD128bits;
    /* ========= 0xf3 */
    if (PrefRepe == 1) {
        (*pMyDisasm).Prefix.RepPrefix = MandatoryPrefix;
        OpSize = 108;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pshufhw ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
        EIP_++;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;
    }
    /* ========= 0xf2 */
    else if (PrefRepne == 1) {
        (*pMyDisasm).Prefix.RepnePrefix = MandatoryPrefix;
        OpSize = 108;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pshuflw ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
        EIP_++;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;
    }

    /* ========== 0x66 */
    else if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pshufd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
        EIP_++;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;
    }
    else {
        OpSize = 104;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "pshufw ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
        EIP_++;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;
    }
}

/* ====================================================================
 *      0x 0f 38 08
 * ==================================================================== */
void __bea_callspec__ psignb_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSSE3_INSTRUCTION+PACKED_SIGN;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "psignb ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSSE3_INSTRUCTION+PACKED_SIGN;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "psignb ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 38 0a
 * ==================================================================== */
void __bea_callspec__ psignd_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSSE3_INSTRUCTION+PACKED_SIGN;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "psignd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSSE3_INSTRUCTION+PACKED_SIGN;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "psignd ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 38 09
 * ==================================================================== */
void __bea_callspec__ psignw_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSSE3_INSTRUCTION+PACKED_SIGN;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "psignw ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSSE3_INSTRUCTION+PACKED_SIGN;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "psignw ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f fb
 * ==================================================================== */
void __bea_callspec__ psubq_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+SIMD128bits;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "psubq ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+SIMD128bits;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "psubq ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 38 17
 * ==================================================================== */
void __bea_callspec__ ptest_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+PACKED_TEST;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "ptest ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }

}

/* ====================================================================
 *      0x 0f 6c
 * ==================================================================== */
void __bea_callspec__ punpcklqdq_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+SIMD128bits;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "punpcklqdq ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }

}

/* ====================================================================
 *      0x 0f 6d
 * ==================================================================== */
void __bea_callspec__ punpckhqdq_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+SIMD128bits;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "punpckhqdq ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }

}


/* ====================================================================
 *      0x 0f 53
 * ==================================================================== */
void __bea_callspec__ rcpps_(PDISASM pMyDisasm)
{
    /* ========== 0xf3 */
    if (PrefRepe == 1) {
        (*pMyDisasm).Prefix.RepPrefix = MandatoryPrefix;
        OpSize = 103;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "rcpss ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "rcpps ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 3a 09
 * ==================================================================== */
void __bea_callspec__ roundpd_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+ROUND_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "roundpd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
        EIP_++;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;
    }
    else {
        FailDecode(pMyDisasm);
    }
}


/* ====================================================================
 *      0x 0f 3a 08
 * ==================================================================== */
void __bea_callspec__ roundps_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+ROUND_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "roundps ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
        EIP_++;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;
    }
    else {
        FailDecode(pMyDisasm);
    }
}


/* ====================================================================
 *      0x 0f 3a 0b
 * ==================================================================== */
void __bea_callspec__ roundsd_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+ROUND_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "roundsd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
        EIP_++;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;
    }
    else {
        FailDecode(pMyDisasm);
    }
}


/* ====================================================================
 *      0x 0f 3a 0a
 * ==================================================================== */
void __bea_callspec__ roundss_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE41_INSTRUCTION+ROUND_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "roundpd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
        EIP_++;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;
    }
    else {
        FailDecode(pMyDisasm);
    }
}


/* ====================================================================
 *      0x 0f 52
 * ==================================================================== */
void __bea_callspec__ rsqrtps_(PDISASM pMyDisasm)
{
    /* ========== 0xf3 */
    if (PrefRepe == 1) {
        (*pMyDisasm).Prefix.RepPrefix = MandatoryPrefix;
        OpSize = 103;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "rsqrtss ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "rsqrtps ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
}


/* ====================================================================
 *      0x 0f c6
 * ==================================================================== */
void __bea_callspec__ shufps_(PDISASM pMyDisasm)
{

    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+SHUFFLE_UNPACK;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "shufpd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+SHUFFLE_UNPACK;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "shufps ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    (*pMyDisasm).Argument1.AccessMode = READ;
    EIP_++;
    if (!Security(0)) return;
    third_arg = 1;
    (*pMyDisasm).Instruction.Immediat = *((UInt8*)(ULONG_PTR) (EIP_- 1));
    (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*)(ULONG_PTR) (EIP_- 1)));
    (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE+ABSOLUTE_;
    (*pMyDisasm).Argument3.ArgSize = 8;
    ImmediatSize = 8;
}


/* ====================================================================
 *      0x 0f 51
 * ==================================================================== */
void __bea_callspec__ sqrtps_VW(PDISASM pMyDisasm)
{
    /* ========= 0xf2 */
    if (PrefRepne == 1) {
        (*pMyDisasm).Prefix.RepnePrefix = MandatoryPrefix;
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "sqrtsd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========= 0xf3 */
    else if (PrefRepe == 1) {
        (*pMyDisasm).Prefix.RepPrefix = MandatoryPrefix;
        OpSize = 103;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "sqrtss ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========== 0x66 */
    else if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "sqrtpd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "sqrtps ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 5c
 * ==================================================================== */
void __bea_callspec__ subps_VW(PDISASM pMyDisasm)
{
    /* ========= 0xf2 */
    if (PrefRepne == 1) {
        (*pMyDisasm).Prefix.RepnePrefix = MandatoryPrefix;
        OpSize = 104;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "subsd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========= 0xf3 */
    else if (PrefRepe == 1) {
        (*pMyDisasm).Prefix.RepPrefix = MandatoryPrefix;
        OpSize = 103;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "subss ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    /* ========== 0x66 */
    else if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "subpd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+ARITHMETIC_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "subps ");
        MMX_ = 1;
        GxEx(pMyDisasm);
        MMX_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 2e
 * ==================================================================== */
void __bea_callspec__ ucomiss_VW(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 103;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+COMPARISON_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "ucomisd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+COMPARISON_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "ucomiss ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 15
 * ==================================================================== */
void __bea_callspec__ unpckhps_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+SHUFFLE_UNPACK;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "unpckhpd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+SHUFFLE_UNPACK;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "unpckhps ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
}

/* ====================================================================
 *      0x 0f 14
 * ==================================================================== */
void __bea_callspec__ unpcklps_(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+SHUFFLE_UNPACK;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "unpcklpd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+SHUFFLE_UNPACK;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "unpcklps ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
}


/* ====================================================================
 *      0x 0f 57
 * ==================================================================== */
void __bea_callspec__ xorps_VW(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE2_INSTRUCTION+LOGICAL_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "xorpd ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = SSE_INSTRUCTION+LOGICAL_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "xorps ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
}
