package com.example.android.jnilesson;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

import jniutils.JniBase;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        JniBase jniBase = new JniBase();
        byte b= 1;
        short s = 10;
        Log.i(TAG, "onCreate: -->"+jniBase.testDataBseType(true,b,'a',s,10,100,1000.0f,10000.0));
    }
}
