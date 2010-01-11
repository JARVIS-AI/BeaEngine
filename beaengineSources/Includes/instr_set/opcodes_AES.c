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
 *      0x 0f 38 db
 * ==================================================================== */
void __bea_callspec__ aesimc(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = AES_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "aesimc ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}

/* ====================================================================
 *      0x 0f 38 dc
 * ==================================================================== */
void __bea_callspec__ aesenc(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = AES_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "aesenc ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}

/* ====================================================================
 *      0x 0f 38 dd
 * ==================================================================== */
void __bea_callspec__ aesenclast(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = AES_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "aesenclast ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}

/* ====================================================================
 *      0x 0f 38 de
 * ==================================================================== */
void __bea_callspec__ aesdec(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = AES_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "aesdec ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}

/* ====================================================================
 *      0x 0f 38 df
 * ==================================================================== */
void __bea_callspec__ aesdeclast(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = AES_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "aesdeclast ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
    }
    else {
        FailDecode(pMyDisasm);
    }
}

/* ====================================================================
 *      0x 0f 3a df
 * ==================================================================== */
void __bea_callspec__ aeskeygen(PDISASM pMyDisasm)
{
    /* ========== 0x66 */
    if (OperandSize == 16) {
        OperandSize = OriginalOperandSize;
        (*pMyDisasm).Prefix.OperandSize = MandatoryPrefix;
        OpSize = 108;
        (*pMyDisasm).Instruction.Category = AES_INSTRUCTION;
        (void) strcpy ((*pMyDisasm).Instruction.Mnemonic, "aeskeygen-assist ");
        SSE_ = 1;
        GxEx(pMyDisasm);
        SSE_ = 0;
        EIP_++;
        if (!Security(0)) return;
        third_arg = 1;
        (*pMyDisasm).Instruction.Immediat = *((UInt8*) (EIP_- 1));
        (void) CopyFormattedNumber((char*) (*pMyDisasm).Argument3.ArgMnemonic, "%.2X", *((UInt8*) (EIP_- 1)));
        (*pMyDisasm).Argument3.ArgType = CONSTANT_TYPE + ABSOLUTE_;
        (*pMyDisasm).Argument3.ArgSize = 8;
        ImmediatSize = 8;

    }
    else {
        FailDecode(pMyDisasm);
    }

}
