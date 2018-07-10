//
// Created by dn-01 on 07/07/18.
//
#include <gtest/gtest.h>
#include "../src/Instruccion.h"

TEST(test_instruccion, IPUSH) {
    Instruccion instr;
    instr.IPUSH(47);
ASSERT_EQ(instr.OP(),OPUSH);
ASSERT_EQ(instr.ConstanteNumerica(),47);
}

TEST(test_instruccion, IADD) {
    Instruccion instr;
    instr.IADD();
    ASSERT_EQ(instr.OP(),OADD);
}

TEST(test_instruccion, ISUB) {
    Instruccion instr;
    instr.ISUB();
    ASSERT_EQ(instr.OP(),OSUB);
}


TEST(test_instruccion, IMUL) {
    Instruccion instr;
    instr.IMUL();
    ASSERT_EQ(instr.OP(),OMUL);
}


TEST(test_instruccion, IWRITE) {
    Instruccion instr;
    instr.IWRITE("variable");
    ASSERT_EQ(instr.OP(),OWRITE);
    ASSERT_EQ(instr.nombreVariable(),"variable");
}

TEST(test_instruccion, IREAD) {
    Instruccion instr;
    instr.IREAD("otraVariable");
    ASSERT_EQ(instr.OP(),OREAD);
    ASSERT_EQ(instr.nombreVariable(),"otraVariable");
}

TEST(test_instruccion, IJUMP) {
    Instruccion instr;
    instr.IJUMP("rutina");
    ASSERT_EQ(instr.OP(),OJUMP);
    ASSERT_EQ(instr.nombreRutina(),"rutina");
}

TEST(test_instruccion, IJUMPZ) {
    Instruccion instr;
    instr.IJUMPZ("otraRutina");
    ASSERT_EQ(instr.OP(),OJUMPZ);
    ASSERT_EQ(instr.nombreRutina(),"otraRutina");
}
