package com.example.shootactivity;

import com.example.shootactivity.R;
import android.app.AlertDialog;
import com.example.shootactivity.ShootActivity;
import java.io.*;
import java.util.HashMap;

import org.apache.http.util.EncodingUtils;

import android.widget.EditText;
import android.widget.Toast;
import android.os.Bundle;
import android.app.Activity;
import android.app.AlertDialog.Builder;
import android.app.Dialog;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Display;
import android.view.SurfaceHolder;
import android.view.SurfaceHolder.Callback;
import android.view.SurfaceView;
import android.view.Window;
import android.view.WindowManager;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.os.Vibrator;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;
import android.media.SoundPool;
import android.content.Context;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.content.DialogInterface.OnClickListener;
import android.content.SharedPreferences.Editor;
import android.content.Intent;

public class ShootActivity extends Activity 
 {
	GameView gameView;
	WelcomeView welcomeView;
	String[] names = new String[6];
	MediaPlayer myPlayer;
	SoundPool sp;
	int flag = 0;
	Boolean turn = true;
	int screenWidth,screenHeight; 
	HashMap<Integer, Integer> map;
	Vibrator vibrator = null;
	Handler myHandler = new Handler(){
        public void handleMessage(Message msg) {
        	if(msg.what == 1){//欢迎界面发送的消息
        		if(welcomeView != null){
        			welcomeView = null;
        		}
        		ShootActivity.this.myPlayer.pause();
        		initGameView();
        		ShootActivity.this.setContentView(gameView);
        	}
        	else if(msg.what == 2){
        		if(gameView != null){
        			gameView = null;
        		}
        		if(turn)
        		ShootActivity.this.myPlayer.start();
        		initWelcomeView();
        		ShootActivity.this.setContentView(welcomeView);
        	}
        	else if(msg.what == 3){
        		if(welcomeView != null)
        			welcomeView = null; 
        		if(turn)
        		//ShootActivity.this.myPlayer.pause();
        		ShootActivity.this.ScoreDialog();
        		
        	}else if(msg.what == 4){
        		int pid = android.os.Process.myPid();
        		android.os.Process.killProcess(pid);
        	}else if(msg.what == 5){
        		if(turn)
            		ShootActivity.this.myPlayer.start();
        		InfoDialog();
        	}
        }
	};
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(
				WindowManager.LayoutParams.FLAG_FULLSCREEN ,  
	            WindowManager.LayoutParams.FLAG_FULLSCREEN);   
        DisplayMetrics dm = new DisplayMetrics();       
        getWindowManager().getDefaultDisplay().getMetrics(dm);       
        screenWidth = dm.widthPixels;       
        screenHeight = dm.heightPixels;   
        readText();
        initSoundPool();  
        vibrator = (Vibrator) getSystemService(Context.VIBRATOR_SERVICE);
        welcomeView=new WelcomeView(this);
        setContentView(welcomeView);
        myPlayer = MediaPlayer.create(this, R.raw.sound);
        myPlayer.setLooping(true);
        myPlayer.start();
    }       
	
    @Override
	protected void onRestart() {
		// TODO Auto-generated method stub
    	if(turn)
			myPlayer.start();
		if(flag == 2)
    	{
    		gameView = null;
    		gameView = new GameView(this);
    		setContentView(gameView);
    	}
		else
		{
			welcomeView = null;
			welcomeView = new WelcomeView(this);
			setContentView(welcomeView);
		}
		super.onRestart();
	}

	@Override
	protected void onStop() {
		// TODO Auto-generated method stub
		myPlayer.pause();
    	if(welcomeView != null)
			flag = 1;
		if(gameView != null)
			flag = 2;
		welcomeView = null;
		gameView = null;
		super.onStop();
	}

	public void initGameView(){
    	gameView=new GameView(this);
    }
    public void initWelcomeView(){
    	welcomeView=new WelcomeView(this);
    }
   
    public void readText()
    {
    	SharedPreferences sp = getSharedPreferences("soft", Context.MODE_PRIVATE);
		//提取数据时可以直接通过sp提取数据，这一点和添加数据时不同
		names[0] = sp.getString("name0", "");
		names[1] = sp.getString("name1", "");
		names[2] = sp.getString("name2", "");
		names[3] = sp.getString("name3", "");
		names[4] = sp.getString("name4", "");
		names[5] = sp.getString("name5", "");
    }
    public void writeText()
    {
    	SharedPreferences sp =  getSharedPreferences("soft", Context.MODE_PRIVATE);
		//创建编辑器editor,通过编辑器把数据存放到sp中
		Editor editor = sp.edit();
		editor.putString("name0", names[0]);
		editor.putString("name1", names[1]);
		editor.putString("name2", names[2]);
		editor.putString("name3", names[3]);
		editor.putString("name4", names[4]);
		editor.putString("name5", names[5]);
		editor.commit();//提交变更
    }

	@Override
	public void onBackPressed() {
		if(welcomeView != null)
			System.exit(0);
		gameView = null;
		welcomeView = null;
		if(turn)
		myPlayer.start();
		this.initWelcomeView();
		this.setContentView(welcomeView);
	}
	public void ZD(){
		vibrator.vibrate(100);  
	}
	public void initSoundPool(){
		sp = new SoundPool(5, AudioManager.STREAM_MUSIC, 0);
		map = new HashMap<Integer, Integer>(); 
		map.put(1, sp.load(this, R.raw.sound1, 1));
	}
	public void playSound(int sound, int number){
		AudioManager am = (AudioManager)this.getSystemService(this.AUDIO_SERVICE);
		float maxv = am.getStreamMaxVolume(AudioManager.STREAM_MUSIC);
		float currentv = am.getStreamVolume(AudioManager.STREAM_MUSIC);
		sp.play(map.get(sound), currentv, currentv, 1, number, 1);
	}
	
	public void ScoreDialog()
	{
		String[] content = new String[3];
		String ns;
		readText();
		for(int i = 0; i < 3; i++)
		{
			content[i] = ns = "";
			ns = names[i * 2];
			switch(ns.length())
			{
			case 0:
				content[i] += "000";
				break;
			case 1:
				content[i] += "00" + ns;
				break;
			case 2:
				content[i] += "0" + ns;
				break;
			case 3:
				content[i] += ns;
				break;
				default:
					content[i] = "000";
					break;
			}
			content[i] += "              ";
			content[i] += names[i*2 + 1];
		}
		new AlertDialog.Builder(this).setTitle("Scoreboard").setItems(
			content, null).setPositiveButton("Delete", new OnClickListener(){
				public void onClick(DialogInterface dialog, int which){
					names[0] = names[1] = names[2] = names[3]
					=names[4] =names[5] = "";
					writeText();
				}
			}).setNegativeButton(
			"Yes", null).show();
	}
	
	public void InfoDialog()
	{
		final EditText editText = new EditText(this);
		new AlertDialog.Builder(this).setTitle("InPut your name").setView(
			 editText).setPositiveButton("Yes", new OnClickListener() {
				   public void onClick(DialogInterface dialog, int which) {
				    String nichen = editText.getText().toString();
				    int i,j=10;
					String str = "";
					for(i=0;i<6;i+=2){
						if(names[i].length() == 0){
							j = i;
							break;
						}
						try{
						if( gameView.scores>Integer.parseInt(names[i])){
							j = i;
							break;
						}
					}
					catch(NumberFormatException e){
						e.printStackTrace();
					}
					}
					for(i=4;i>0&&i>j;i-=2){
						names[i] = names[i-2];
						names[i+1] = names[i-1];
					}
					if(j != 10)
					{
					names[j]= String.valueOf(gameView.scores);
					names[j+1] = nichen;
					}
					str = names[0] + ' ' + names[1] + ' ' + names[2] + ' '
							+ names[3] + ' '+ names[4] + ' '+names[5]+' ';
					writeText();
	        		if(gameView != null){
	        			gameView = null;
	        		}
	        		if(turn)
	        		ShootActivity.this.myPlayer.start();
	        		initWelcomeView();
	        		ShootActivity.this.setContentView(welcomeView);
				   }
				  })
			      .show();
	}
}
