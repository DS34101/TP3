#include "../src/Calculadora.h"
#include <gtest/gtest.h>

TEST(test_Calculadora, Push_y_valores) {
    Programa p;
    Instruccion i;
    i.IPUSH(1);
    p.AgInstruccion("s",i);
    ASSERT_EQ(p.longitud("s"), 1);
    Calculadora c;
    c.nuevaCalculadora(p,"s",1);
    ASSERT_EQ(c.IndiceInstruccionActual(),0);
    stack<int> pi;
    ASSERT_EQ(c.Pila(),pi);
    ASSERT_EQ(c.rutinaActual(),"s");
    ASSERT_TRUE(c.ejecutando());
    c.ejecutarUnPaso();
    pi.push(1);
    ASSERT_EQ(c.Pila(),pi);
    ASSERT_EQ(c.rutinaActual(),"s");
    ASSERT_FALSE(c.ejecutando());
    ASSERT_EQ(c.IndiceInstruccionActual(),1);
}

TEST(test_Calculadora, Variables) {
    Programa p;
    Instruccion i;
    i.IPUSH(500);
    Instruccion i2;
    i2.IWRITE("var");
    Instruccion i3;
    i3.IPUSH(1);
    Instruccion i4;
    i4.IPUSH(5);
    Instruccion i5;
    i5.IREAD("var");
    p.AgInstruccion("s",i); //PUSH 500
    p.AgInstruccion("s",i2);//WRITE
    p.AgInstruccion("s",i3);//PUSH 1
    p.AgInstruccion("s",i2);
    p.AgInstruccion("s",i3);
    p.AgInstruccion("s",i2);
    p.AgInstruccion("s",i3);
    p.AgInstruccion("s",i2);
    p.AgInstruccion("s",i4);//PUSH 5
    p.AgInstruccion("s",i2);//WRITE
    p.AgInstruccion("s",i5);//READ
    Calculadora c;
    c.nuevaCalculadora(p,"s",2);
    stack<int> pila;
    c.ejecutarUnPaso();
    pila.push(500);
    EXPECT_EQ(c.Pila(),pila);
    c.ejecutarUnPaso();
    pila.pop();
    EXPECT_EQ(c.Pila(),pila);
    EXPECT_EQ(c.valorHistoricoVariable("var",2),500);
    c.ejecutarUnPaso();
    c.ejecutarUnPaso();
    c.ejecutarUnPaso();
    c.ejecutarUnPaso();
    c.ejecutarUnPaso();
    c.ejecutarUnPaso();
    EXPECT_EQ(c.valorHistoricoVariable("var",7),1);
    EXPECT_EQ(c.valorHistoricoVariable("var",8),1);
    EXPECT_EQ(c.valorHistoricoVariable("var",2),500);
    c.ejecutarUnPaso();
    pila.push(5);
    EXPECT_EQ(c.Pila(),pila);
    c.ejecutarUnPaso();
    EXPECT_EQ(c.valorActualVariable("var"),5);
    c.ejecutarUnPaso();
    EXPECT_EQ(c.Pila().top(),5);
}

TEST(test_Calculadora, rutJumpzyJump) {
    Programa p;
    Instruccion instr1;
    Instruccion instr2;
    Instruccion instr3;
    instr1.IPUSH(0);
    instr2.IJUMPZ("conjumpz");
    instr3.IJUMP("conjump");
    p.AgInstruccion("conjumpz",instr3);
    p.AgInstruccion("conjump",instr2);
    Calculadora c;
    c.nuevaCalculadora(p,"conjump",0);
    c.ejecutarUnPaso();
    EXPECT_EQ(c.rutinaActual(),"conjumpz");
    c.ejecutarUnPaso();
    EXPECT_EQ(c.rutinaActual(),"conjump");
}

TEST(test_calculadora, todaslasOperaciones){
    Programa p;
    Instruccion instr1;
    Instruccion instr2;
    Instruccion instr3;
    Instruccion instr4;
    Instruccion instr5;
    Instruccion instr6;
    Instruccion instr7;
    Instruccion instr8;
    Instruccion instr9;
    instr1.IJUMP("haciaJump");
    instr2.IJUMPZ("haciaJumpz");
    instr3.IADD();
    instr4.IMUL();
    instr5.ISUB();
    instr6.IWRITE("var"),
    instr7.IREAD("var");
    instr8.IPUSH(5);
    instr9.IPUSH(0);
    p.AgInstruccion("inicio",instr6);
    p.AgInstruccion("inicio",instr7);
    p.AgInstruccion("inicio",instr8);
    p.AgInstruccion("inicio",instr6);
    p.AgInstruccion("inicio",instr7);
    p.AgInstruccion("inicio",instr6);
    p.AgInstruccion("inicio",instr8);
    p.AgInstruccion("inicio",instr8);
    p.AgInstruccion("inicio",instr3);
    p.AgInstruccion("inicio",instr8);
    p.AgInstruccion("inicio",instr4);
    p.AgInstruccion("inicio",instr8);
    p.AgInstruccion("inicio",instr5);
    p.AgInstruccion("inicio",instr5);
    p.AgInstruccion("inicio",instr9);
    p.AgInstruccion("inicio",instr2);
    p.AgInstruccion("haciaJumpz",instr1);
    p.AgInstruccion("haciaJump",instr8);
    p.AgInstruccion("haciaJump",instr2);
    Calculadora c;
    c.nuevaCalculadora(p,"inicio",2);
    c.ejecutarUnPaso();
    EXPECT_EQ(c.valorActualVariable("var"),0);
    c.ejecutarUnPaso();
    EXPECT_EQ(c.Pila().top(),0);
    c.ejecutarUnPaso();
    EXPECT_EQ(c.Pila().top(),5);
    c.ejecutarUnPaso();
    EXPECT_EQ(c.valorActualVariable("var"),5);
    c.ejecutarUnPaso();
    EXPECT_EQ(c.Pila().top(),5);
    c.ejecutarUnPaso();
    c.ejecutarUnPaso();
    c.ejecutarUnPaso();
    c.ejecutarUnPaso();
    EXPECT_EQ(c.Pila().top(),10);
    c.ejecutarUnPaso();
    c.ejecutarUnPaso();
    EXPECT_EQ(c.Pila().top(),50);
    c.ejecutarUnPaso();
    c.ejecutarUnPaso();
    EXPECT_EQ(c.Pila().top(),45);
    c.ejecutarUnPaso();
    EXPECT_EQ(c.Pila().top(),-45);
    c.ejecutarUnPaso();
    c.ejecutarUnPaso();
    EXPECT_EQ(c.rutinaActual(),"haciaJumpz");
    c.ejecutarUnPaso();
    EXPECT_EQ(c.rutinaActual(),"haciaJump");
    c.ejecutarUnPaso();
    c.ejecutarUnPaso();
    EXPECT_EQ(c.rutinaActual(),"haciaJump");
    EXPECT_FALSE(c.ejecutando());



}