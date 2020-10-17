package com.jeffmony.audiosdk;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private Button mNativeThreadBtn;
    private Button mNativeThreadBtn2;
    private Button mNativeJavaBtn;
    private Button mSoundTouchBtn;
    private Button mAudioPlayBtn;

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mNativeThreadBtn = findViewById(R.id.native_thread_btn);
        mNativeThreadBtn2 = findViewById(R.id.native_thread_btn2);
        mNativeJavaBtn = findViewById(R.id.native_java_btn);
        mSoundTouchBtn = findViewById(R.id.soundtouch_btn);
        mAudioPlayBtn = findViewById(R.id.audio_play_btn);

        mNativeThreadBtn.setOnClickListener(this);
        mNativeThreadBtn2.setOnClickListener(this);
        mNativeJavaBtn.setOnClickListener(this);
        mSoundTouchBtn.setOnClickListener(this);
        mAudioPlayBtn.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        if (v == mNativeThreadBtn) {

        } else if (v == mNativeThreadBtn2) {

        } else if (v == mNativeJavaBtn) {

        } else if (v == mSoundTouchBtn) {
            Intent intent = new Intent(this, SoundTouchActivity.class);
            startActivity(intent);
        } else if (v == mAudioPlayBtn) {
            Intent intent = new Intent(this, AudioPlayerActivity.class);
            startActivity(intent);
        }
    }
}
