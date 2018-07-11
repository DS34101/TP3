#include <gtest/gtest.h>
#include "../src/diccTrie.hpp"
TEST(test_dicctrie,definir){
    dicc_trie<string> p;
    p.definir("hola","Prueba");
    EXPECT_EQ(p.definido("hola"), true);
    EXPECT_EQ(p.obtener("hola"),"Prueba");
}

TEST(test_dicctrie,definirporPuntero){
    dicc_trie<string> p;
    string* prueba = new string;
    *prueba="funciona";
    p.definirporPuntero("hola",prueba);
    EXPECT_EQ(p.definido("hola"), true);
    EXPECT_EQ(p.obtener("hola"),"funciona");
}

TEST(test_dicctrie,redefinir){
    dicc_trie<string> p;
    p.definir("hola","Prueba");
    p.definir("hola","Prueba2");
    EXPECT_EQ(p.definido("hola"), true);
    EXPECT_EQ(p.obtener("hola"),"Prueba2");
}

TEST(test_dicctrie,definirmuchos){
    dicc_trie<string> p;
    p.definir("hola","Prueba");
    p.definir("holasa","Prueba2");
    p.definir("hole","Prueba4");
    p.definir("holese","Prueba3");
    p.definir("ho","Prueba5");
    EXPECT_TRUE(p.definido("hola"));
    EXPECT_EQ(p.obtener("hola"),"Prueba");
    EXPECT_TRUE(p.definido("holasa"));
    EXPECT_EQ(p.obtener("holasa"),"Prueba2");
    EXPECT_TRUE(p.definido("hole"));
    EXPECT_EQ(p.obtener("hole"),"Prueba4");
    EXPECT_TRUE(p.definido("holese"));
    EXPECT_EQ(p.obtener("holese"),"Prueba3");
    EXPECT_TRUE(p.definido("hola"));
    EXPECT_EQ(p.obtener("ho"),"Prueba5");
    EXPECT_FALSE(p.definido("h"));
    EXPECT_FALSE(p.definido("holasas"));
}