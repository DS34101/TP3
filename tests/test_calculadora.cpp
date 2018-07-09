#include "../src/Calculadora.hpp"
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