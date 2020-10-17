package com.jeffmony.audiosdk;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.jeffmony.playerlib.NativePlayer;
import com.jeffmony.playerlib.listener.OnPrepareListener;
import com.jeffmony.playerlib.utils.LogUtils;

public class AudioPlayerActivity extends AppCompatActivity implements View.OnClickListener {

    private Button mPlayBtn;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_audioplayer);

        mPlayBtn = findViewById(R.id.audio_play);

        mPlayBtn.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        if (v == mPlayBtn) {
            doPlay();
        }
    }

    private void doPlay() {
        final NativePlayer player = new NativePlayer();
        player.setDataSource("/sdcard/Download/source.wav");
        player.setOnPreparedListener(new OnPrepareListener() {
            @Override
            public void onPrepared() {
                LogUtils.i("onPrepared");
                player.start();
            }
        });
        player.prepare();

    }
}
