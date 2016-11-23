package com.example.android.jnilesson;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

public class SecondActivity extends AppCompatActivity {
    private static final String TAG = "SecondActivity";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_second);

        Log.i(TAG, "onCreate: SecondActivity Thread: "+Thread.currentThread().getName()
                +"id:"+Thread.currentThread().getId());
    }
}
