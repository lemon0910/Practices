package com.example.pausegametest;



import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.SurfaceHolder.Callback;

public class FishingSurfaceView extends SurfaceView implements Callback ,Runnable{
	public SurfaceHolder surfaceHolder;
	public Paint refreshPainter;
	public Paint targetPainter;
	public Paint timePainter;
	
	
	public int time;
	public Thread timer;
	public Thread targetShowTimer;
	public Object waitObject;
	
	public Bitmap timePic;
	public Bitmap time0;
	public Bitmap time1;
	public Bitmap time2;
	public Bitmap time3;
	public Bitmap time4;
	public Bitmap time5;
	public Bitmap time6;
	public Bitmap time7;
	public Bitmap time8;
	public Bitmap time9;

	
	public boolean threadFlag = false;
	public Canvas canvas;
	public int ScreenWidth,ScreenHeight;
	
	public int curState;
	
	public FishingSurfaceView(Context context) {
		super(context);
		surfaceHolder = this.getHolder();
		surfaceHolder.addCallback(this);
		
		time = 0;
		
		waitObject = new Object();
		
		refreshPainter = new Paint();
		refreshPainter.setAntiAlias(true);
		
		
		timePainter = new Paint();
		timePainter.setAntiAlias(true);
	
		
		loadTexture(context);
		loadRaw(context);
	}
	/*
	 *加载音频资源 
	 */
	private void loadRaw(Context context) {
		
	}
	/*
	 * 加载图片资源
	 * */
	private void loadTexture(Context context) {
		timePic = BitmapFactory.decodeResource(getResources(), R.drawable.time);
		time0 = BitmapFactory.decodeResource(getResources(), R.drawable.a0);
		time1 = BitmapFactory.decodeResource(getResources(), R.drawable.a1);
		time2 = BitmapFactory.decodeResource(getResources(), R.drawable.a2);
		time3 = BitmapFactory.decodeResource(getResources(), R.drawable.a3);
		time4 = BitmapFactory.decodeResource(getResources(), R.drawable.a4);
		time5 = BitmapFactory.decodeResource(getResources(), R.drawable.a5);
		time6 = BitmapFactory.decodeResource(getResources(), R.drawable.a6);
		time7 = BitmapFactory.decodeResource(getResources(), R.drawable.a7);
		time8 = BitmapFactory.decodeResource(getResources(), R.drawable.a8);
		time9 = BitmapFactory.decodeResource(getResources(), R.drawable.a9);
		
	}

	@Override
	public void surfaceChanged(SurfaceHolder arg0, int arg1, int arg2, int arg3) {
		
	}
	
	public void stopThread(){
		if(threadFlag)
			threadFlag = false;
	}
	
	public void restartThread(){
		if(!threadFlag){
			threadFlag = true;
			new Thread(this).start();
		}
	}

	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		Log.v("ui", "surfaceCreated");
		ScreenHeight = this.getHeight();
		ScreenWidth = this.getWidth();
		if(!threadFlag){
			threadFlag = true;
			new Thread(this).start();
		}
	}
	
	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		Log.v("ui", "surfaceDestroyed");
		if(threadFlag)
			threadFlag = false;
	}
	

	public void draw(){
		try {
			canvas = surfaceHolder.lockCanvas();
			canvas.drawColor(Color.BLACK);
			drawTime();	
		} catch (Exception e) {
			e.printStackTrace();
		}finally{
			if(canvas != null){
				surfaceHolder.unlockCanvasAndPost(canvas);
			}
			
		}
	}
	
	private void drawTime(){
		
		canvas.drawBitmap(timePic, 1020 + 100, 10, timePainter);
		int min = time / 60;
		int min_ten = min / 10;
		drawNumberWithTime(canvas, min_ten, 1020, 10, timePainter);
		int min_one = min - 10 * min_ten;
		drawNumberWithTime(canvas, min_one, 1020+50, 10, timePainter);
		
		int sec = time % 60;
		int sec_ten = sec / 10;
		drawNumberWithTime(canvas, sec_ten, 1020+150, 10, timePainter);
		int sec_one = sec - 10 * sec_ten;
		drawNumberWithTime(canvas, sec_one, 1020+200, 10, timePainter);
		
	}
	
	private void drawNumberWithTime(Canvas canvas, int i,int x, int y, Paint paint){
		switch (i) {
		case 0:
			canvas.drawBitmap(time0, x, y, paint);
			break;
		case 1:
			canvas.drawBitmap(time1, x, y, paint);
			break;
		case 2:
			canvas.drawBitmap(time2, x, y, paint);
			break;
		case 3:
			canvas.drawBitmap(time3, x, y, paint);
			break;
		case 4:
			canvas.drawBitmap(time4, x, y, paint);
			break;
		case 5:
			canvas.drawBitmap(time5, x, y, paint);
			break;
		case 6:
			canvas.drawBitmap(time6, x, y, paint);
			break;
		case 7:
			canvas.drawBitmap(time7, x, y, paint);
			break;
		case 8:
			canvas.drawBitmap(time8, x, y, paint);
			break;
		case 9:
			canvas.drawBitmap(time9, x, y, paint);
			break;
		default:
			break;
		}
	}
	
	@Override
	public void run() {
		while(threadFlag){
			this.draw();		
			time++;
			try{
					Thread.sleep(1000);
			}catch(Exception e){
				e.printStackTrace();
			}
		}
		Log.v("ui", "thread die...");
	}
	
}
