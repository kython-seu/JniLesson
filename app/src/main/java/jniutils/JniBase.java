package jniutils;

import android.os.Handler;
import android.os.Message;
import android.util.Log;

import java.util.ArrayList;

import entity.Person;

/**
 * Created by kason_zhang on 11/11/2016.
 */

public class JniBase {
    private static final String TAG = "JniBase";
    public ArrayList<Person> persons;
    private String javaIn;
    public static String staticString;
    private Handler mHandler;
    public JniBase(Handler mHandler){
        this.mHandler = mHandler;
    }
    static {
        System.loadLibrary("jnilib");
    }

    public native String testDataBseType(boolean boo,byte b, char c,short s, int i, long l,
                                         float f, double d);
    public native void javeToC(String str);

    public native byte getByte();
    public native short getShort();
    public native boolean getBoolean();

    //public native void addPerson(Person person);
    public native ArrayList<Person> getPersons();
    public native void setJavaIn();//通过JNI访问内部变量，然后通过JAVA去调用变量
    public native void accessStaticField();
    public String getJavaIn() {
        return javaIn;
    }
    //测试访问C回调JAVA方法
    public native void accessJavaMethod();
    public void cVisitJavaMethod(int what,String obj){
        Message message = new Message();
        message.what = what;
        message.obj = "I hava add this"+obj;
        mHandler.sendMessage(message);
    }
    //测试C访问JAVA静态代码

    public native void accessJavaStaticMethod();
    public static void cVisitJavaStaticMethod(int what,String obj){
        Log.i(TAG, "cVisitJavaStaticMethod: what is: "+what+" obj is: "+obj);
    }
}
