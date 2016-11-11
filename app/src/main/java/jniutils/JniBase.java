package jniutils;

/**
 * Created by kason_zhang on 11/11/2016.
 */

public class JniBase {

    static {
        System.loadLibrary("jnilib");
    }

    public native String testDataBseType(boolean boo,byte b, char c,short s, int i, long l,
                                         float f, double d);
}
