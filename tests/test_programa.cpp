#include "gtest/gtest.h"

#include "../src/Programa.hpp"

TEST(test_programa, programa_1_Instruccion) {
    Programa p;
    Instruccion i;
    i.IPUSH(1);
    p.AgInstruccion("s",i);
    ASSERT_EQ(p.longitud("s"), 1);

}

TEST(test_programa, programa_vacio) {
    Programa p;

    ASSERT_EQ(p.longitud("s"), 0);

}

TEST(test_programa, programa_2rutinas) {
    vector<string> prueba;
    prueba.push_back("s");
    prueba.push_back("a");
    Programa p;
    Instruccion i;
    i.IPUSH(1);
    p.AgInstruccion("s",i);
    ASSERT_EQ(p.longitud("s"), 1);
    Instruccion a;
    a.IJUMPZ("s");
    Instruccion b;
    b.IJUMPZ("d");
    p.AgInstruccion("a",a);
    p.AgInstruccion("a",b);
    ASSERT_EQ(p.longitud("a"), 2);
    ASSERT_EQ(p.Rutinas(), prueba);

}
TEST(test_programa, programa_sin_rutinas) {
    vector<string> prueba;
    Programa p;

    ASSERT_EQ(p.Rutinas(), prueba);
}

TEST(test_programa, programa_get_instruccion) {

    Programa p;
    Instruccion i;
    Instruccion c;
    i.IPUSH(1);
    c.IJUMPZ("s");
    p.AgInstruccion("a",c);
    p.AgInstruccion("s",i);

    ASSERT_EQ(p.Instrucciones("a", 0).OP(),c.OP());
    ASSERT_EQ(p.Instrucciones("a", 0).nombreRutina(),c.nombreRutina());

}

TEST(test_programa, programaVacio_get_instruccion) {

    Programa p;
    Instruccion c;

    ASSERT_EQ(p.Instrucciones("a", 5).OP(),c.OP());

}