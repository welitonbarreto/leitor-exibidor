package com.company;

@Deprecated
public class Teste implements InterfaceA, InterfaceB {
    public static int a = 10000000;
    public static float b = 10f;
    public static double d = 10.0;
    public static String e = "10";
    public static Object f = new Object();
    @Deprecated
    public final static long c = 10l;

    public class TesteInnerClass1{
        public int metodoInnerClass1() {
            return 0;
        }
    }

    public static void metodoQueUsaInterface(){
        InterfaceQualquer classeQueImplementaInterface = new ClasseQueImplementaInterface();
        classeQueImplementaInterface.metodoDaInterfaceA();
    }

    @Deprecated
    private static int  metodoDeTeste(int j) throws Exception{
        int valorContado = 0;

        for (int i = 0; i < j; i++) {
            valorContado += j;
        }

        try{
            throw new Exception();
        } catch (Exception e) {
            valorContado = 0;
        }

        return valorContado;
    }



}
