package com.example.pausegametest;

import android.media.MediaPlayer;
import android.os.Bundle;
import android.app.Activity;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuItem;
import android.view.Window;
import android.view.WindowManager;
import android.support.v4.app.NavUtils;

public class MainActivity extends Activity {
	MediaPlayer mediaPlayer;
	FishingSurfaceView surfaceView;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        this.requestWindowFeature(Window.FEATURE_NO_TITLE);
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
        					 WindowManager.LayoutParams.FLAG_FULLSCREEN);
        surfaceView = new FishingSurfaceView(this);
        setContentView(surfaceView);
        
        mediaPlayer = MediaPlayer.create(this, R.raw.boss_bgm_01);
        mediaPlayer.setLooping(true);
        mediaPlayer.start();
    }
	@Override
	protected void onPause() {
		super.onPause();
		Log.v("ui", "onPause");
		mediaPlayer.pause();
		surfaceView.stopThread();
	}
	@Override
	protected void onRestart() {
		super.onRestart();
		Log.v("ui", "onRestart");
	}
	@Override
	protected void onResume() {
		super.onResume();
		Log.v("ui", "onResume");
		mediaPlayer.start();
		surfaceView.restartThread();
	}
	@Override
	protected void onStart() {
		super.onStart();
		Log.v("ui", "onStart");
	}
	@Override
	protected void onStop() {
		super.onStop();
		Log.v("ui", "onStop");
	}
    
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if(keyCode == KeyEvent.KEYCODE_BACK){
			mediaPlayer.stop();
			this.finish();
		}
		return false;
	}

    
}
