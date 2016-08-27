package com.example.shootactivity;

import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Matrix;
import android.graphics.Paint;
import com.example.shootactivity.WelThread;
public class WelcomeView extends SurfaceView implements SurfaceHolder.Callback{
	ShootActivity activity;
	SurfaceHolder surfaceHolder;
	WelThread welThread = null;
	int turn = 0;
	Bitmap background,b1,on1,off1,on,off;
	double x,y;
	public WelcomeView(ShootActivity activity) {
		super(activity);
		this.activity = activity;
		surfaceHolder=this.getHolder();
		getHolder().addCallback(this);
		b1=BitmapFactory.decodeResource(getResources(), R.drawable.emain);
		on1 = BitmapFactory.decodeResource(getResources(), R.drawable.turnon);
		on = handBitmaps(on1, 60, 60);
		off1 = BitmapFactory.decodeResource(getResources(), R.drawable.turnoff);
		off = handBitmaps(off1, 60, 60);
		background = handBitmaps(b1, 1280, 800);
		welThread=new WelThread(this);
		if(activity.turn)
			turn = 0;
		else
			turn = 1;
	}
	public void OnDraw(Canvas canvas){
		Paint p = new Paint();
		canvas.drawColor(Color.WHITE);
		canvas.drawBitmap(background, 0, 0, p);
		if(turn == 0)
			canvas.drawBitmap(on, 1200, 30, p);
		else
			canvas.drawBitmap(off, 1200, 30, p);
//		p.setColor(Color.RED);
//		p.setTextSize(40);
//		canvas.drawText("x是"+x+"y是"+y, 230, 423, p);
	}
	public Bitmap handBitmaps(Bitmap tar, int newWidth, int newHeight){
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
	public boolean onTouchEvent(MotionEvent event) {
		if(event.getAction() == MotionEvent.ACTION_DOWN){
			 x = event.getX();
			 y = event.getY();
			if(x>820 && x<1130 && y>387 && y<451)
				activity.myHandler.sendEmptyMessage(1);
			if(x>850 && x<1170 && y>500 && y< 580)
				activity.myHandler.sendEmptyMessage(3);
			if(x>880 && x<1200 && y>620 && y<690){
				welThread.flag = false;
				activity.myHandler.sendEmptyMessage(4);		
			}
			if(x > 1200 && x <1270 && y >30 && y < 100){
				turn = (turn+1)%2;
				if(turn == 1){
					activity.myPlayer.pause();
					activity.turn = false;
				}
				else
				{
					activity.myPlayer.start();
					activity.turn = true;
				}
			}
		}
		return super.onTouchEvent(event);
	}
	public void surfaceChanged(SurfaceHolder arg0, int arg1, int arg2, int arg3){}
	public void surfaceCreated(SurfaceHolder arg0) {
		welThread.flag=true;
		welThread.start();
		System.out.println("create");
	}
	public void surfaceDestroyed(SurfaceHolder arg0) {
        welThread.flag =  false;
        //int pid = android.os.Process.myPid();
		//android.os.Process.killProcess(pid);
        System.out.println("execute");
	}
}
