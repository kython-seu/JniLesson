package com.example.android.jnilesson;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import java.util.ArrayList;

import entity.Person;
import jniutils.JniBase;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";
    Button button;
    String text;
    private HandlerThread mHandlerThread;
    private class MyHandler extends Handler{
        public MyHandler(Looper looper) {
            super(looper);
        }

        @Override
        public void handleMessage(Message msg) {
            switch (msg.what){
                case 1:
                    Log.i(TAG, "handleMessage: receive data from c:"+msg.obj);
                    break;
                default:
                    super.handleMessage(msg);
            }
        }
    }
    private MyHandler myHandler;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Log.i(TAG, "onCreate: MainActivity Thread:"+Thread.currentThread().getName()+"id:"+Thread.currentThread().getId());
        mHandlerThread = new HandlerThread("JniHandler");
        mHandlerThread.start();
        myHandler = new MyHandler(mHandlerThread.getLooper());
        final JniBase jniBase = new JniBase(myHandler);
        byte b= 1;
        short s = 10;
        Log.i(TAG, "onCreate: -->"+jniBase.testDataBseType(true,b,'a',s,10,100,1000.0f,10000.0));
        button = (Button)findViewById(R.id.sendStringToJni);
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                jniBase.javeToC("Hi,I am from Java");
            }
        });
        findViewById(R.id.getDataFromC).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Byte b = jniBase.getByte();
                Short s = jniBase.getShort();
                boolean boo = jniBase.getBoolean();
                Log.i(TAG, "onClick: b is"+b+" short is: "+s+" boolean is : "+boo);
            }
        });
        findViewById(R.id.getArrayListPerson).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ArrayList<Person> persons = jniBase.getPersons();
                for (Person p: persons){
                    Log.i(TAG, "onClick: person is "+p);
                }
            }
        });
        findViewById(R.id.cSetField).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                jniBase.setJavaIn();
                Log.i(TAG, "onClick: cSetField: "+jniBase.getJavaIn());
            }
        });

        findViewById(R.id.staticField).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                JniBase.staticString = "I am Static String in Java";
                jniBase.accessStaticField();
                Log.i(TAG, "onClick: c set static field:"+JniBase.staticString);
            }
        });

        findViewById(R.id.cAccessJavaMethod).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                jniBase.accessJavaMethod();
            }
        });

        findViewById(R.id.cAccessJavaStaticMethod).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                jniBase.accessJavaStaticMethod();
            }
        });

        findViewById(R.id.gotoSecondActivity).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent in = new Intent(MainActivity.this,SecondActivity.class);
                startActivity(in);
            }
        });
    }
}
/*InputStream is;

        try {
            is = getAssets().open("loc.txt");
            int size = is.available();
            byte[] buffer = new byte[size];
            is.read(buffer);
            is.close();
            text = new String(buffer);
        } catch (IOException e) {
            e.printStackTrace();
        }
        Toast.makeText(this, text+" this is name stored as city in onMapReady in map activity",Toast.LENGTH_LONG ).show();
        //double lat, lon;
        if (text.equals("Dublin")) {
            Log.i(TAG, "onCreate: come in");
            Toast.makeText(this, text+" getting into dublin in map activity",Toast.LENGTH_LONG ).show();

        }*/