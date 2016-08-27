package com.example.shootactivity;

import java.util.Random;

import com.example.shootactivity.R;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.media.MediaPlayer;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import com.example.shootactivity.GameThread;

public class GameView extends SurfaceView implements SurfaceHolder.Callback {
	ShootActivity activity;
	Bitmap background,b1,gun,gameover,g1,heart,heart1,booms,boom1;
	Bitmap[] tar,tar1,tar2;
	SurfaceHolder surfaceHolder;
	int px,py,scores,life,firstnum;
	GameThread myThread;
	public GameView(ShootActivity activity){
		super(activity);
		this.activity=activity;
		surfaceHolder=this.getHolder();
		getHolder().addCallback(this);
		b1 = BitmapFactory.decodeResource(getResources(), R.drawable.bs);
		background = handBitmap(b1, activity.screenWidth, activity.screenHeight);
		gun = BitmapFactory.decodeResource(getResources(), R.drawable.as);
		g1 = BitmapFactory.decodeResource(getResources(), R.drawable.gameover);
		gameover= handBitmap(g1, activity.screenWidth, activity.screenHeight);
		heart = BitmapFactory.decodeResource(getResources(), R.drawable.heart);
		scores = 0;
		px=0;
		py=0;
		try{
		firstnum = Integer.parseInt(activity.names[0]);
		}catch(NumberFormatException e){
			e.printStackTrace();
		}
		life = 5;
		tar = new Bitmap[3];
		tar1 = new Bitmap[3];
		tar2 = new Bitmap[3];
		initTar();
		myThread=new GameThread(this);
	}
	public Bitmap handBitmap(Bitmap tar, int newWidth, int newHeight){
		Bitmap tar1 = null;
		Matrix matrix = null;
		
		int width = tar.getWidth(); 
        int height = tar.getHeight(); 

        //计算缩放率，新尺寸除原始尺寸
        float scaleWidth = ((float) newWidth) / width; 
        float scaleHeight = ((float) newHeight) / height; 

        // 创建操作图片用的matrix对象
        matrix = new Matrix(); 

        // 缩放图片动作
        matrix.postScale(scaleWidth, scaleHeight); 

        // 创建新的图片
        tar1 = Bitmap.createBitmap(tar, 0, 0, 
                          width, height, matrix, true); 
		return tar1;
	}
	public void initTar(){
		tar[0] = BitmapFactory.decodeResource(getResources(), R.drawable.plate);
        tar1[0] = handBitmap(tar[0], 100, 100);
        tar2[0] = handBitmap(tar[0], 70, 70); 
        tar[1] = BitmapFactory.decodeResource(getResources(), R.drawable.red);
        tar1[1] = handBitmap(tar[1], 100, 100);
        tar2[1] = handBitmap(tar[1], 70, 70); 
        tar[2] = BitmapFactory.decodeResource(getResources(), R.drawable.yellow);
        tar1[2] = handBitmap(tar[2], 100, 100);
        tar2[2] = handBitmap(tar[2], 70, 70); 
        booms = BitmapFactory.decodeResource(getResources(), R.drawable.boom);
		boom1 = handBitmap(booms, 100, 100); 
		heart1 = handBitmap(heart, 60, 60);
	}
	public void OnDraw(Canvas canvas) {//绘制方法
		Paint p = new Paint();
		canvas.drawColor(Color.WHITE);//背景色
		canvas.drawBitmap(background, 0, 0, p);
		int i,k = 60;
		for( i = 0; i < life; i++)
			canvas.drawBitmap(heart1, 1160 - (i+1) * k, 20, p);
		if(life == 0)
			canvas.drawBitmap(gameover, 0, 0, p);
		else{
		canvas.drawBitmap(gun, 600, 550, p);
		p.setColor(Color.RED);
		p.setTextSize(50);
		canvas.drawText("Highest Record: " + firstnum, 50, 60, p);
		canvas.drawText("Current: " + scores, 50, 130, p);
		}
	}
	public void DrawPlate(Canvas canvas, int x, int y, int index, int id)
	{
		Paint p = new Paint();
		if( myThread.fs[id] <= 0 && life != 0)
		{
			if(y>100)
				canvas.drawBitmap(tar1[index], x, y, p);
			else
				canvas.drawBitmap(tar2[index], x, y, p);
		}
		if(myThread.fs[id] > 0 && life != 0)
		canvas.drawBitmap(boom1, x, y, p);
	}
	public void hand(){
		myThread.flag = false;
		activity.myHandler.sendEmptyMessage(5);
	}
	public boolean onTouchEvent(MotionEvent event) {
		if(event.getAction() == MotionEvent.ACTION_DOWN){
			px =(int) event.getX();
			py =(int) event.getY();
			if(px<=(myThread.x[0]+100)&&px>=(myThread.x[0]-30)&&py>=(myThread.y[0]-30)&&py<=(myThread.y[0]+100)&&py<650&&myThread.fs[0] <= 0){
			myThread.fs[0] = 1;
			//if(myThread.index[0] != 1)
			scores++;
			if(activity.turn)
			{
			activity.ZD();
            activity.playSound(1, 0);
			}
			}
			if(scores > 3 && px<=(myThread.x[1]+100)&&px>=(myThread.x[1]-30)&&py>=(myThread.y[1]-30)&&py<=(myThread.y[1]+100)&&py<650&&myThread.fs[1] <= 0){
				myThread.fs[1] = 1;
				//if(myThread.index[1] != 1)
				scores++;
				if(activity.turn)
				{
				activity.ZD();
	            activity.playSound(1, 0);
				}
			}
		}
		return super.onTouchEvent(event);
	}	
	
	
	public void surfaceChanged(SurfaceHolder arg0, int arg1, int arg2, int arg3){}
	public void surfaceCreated(SurfaceHolder arg0) {
		myThread.flag=true;
		myThread.start();
	}
	public void surfaceDestroyed(SurfaceHolder arg0) {
	        this.myThread.flag =  false;
	        /*int pid = android.os.Process.myPid();
    		android.os.Process.killProcess(pid);*/
	        System.out.println("gameView destroy");
	}	
}
