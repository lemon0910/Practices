package com.example.shootactivity;			

import com.example.shootactivity.GameView;
import 	java.util.Random;

import android.graphics.Canvas;			//引入相关类
import android.view.SurfaceHolder;		//引入相关类

public class GameThread extends Thread{
	boolean flag=true;
	GameView myView;			
	SurfaceHolder surfaceHolder;
	Random r;
	Canvas c;
	int[] x,y,fs,index,dir;
	int v;
	public GameThread(GameView myView){	
		this.myView = myView;	
		surfaceHolder=myView.surfaceHolder;
		r = new Random();
		x = new int [2];
		y = new int [2];
		fs = new int [2];
		dir = new int [2];
		index = new int[2];
		dir[0] = dir[1] = 0;
		x[0] = x[1] = -1;
		fs[0] = fs[1] = -1;
		index[0] = index[1] = 0;	
		y[0] = y[1] = 700;
		v = 20;
	}
	public void run(){		
		while(flag){
				Fly(0);
				if(myView.scores >= 4)
					Fly(1);
            try {                
                synchronized (this.surfaceHolder) {
                	c = this.surfaceHolder.lockCanvas(null);
                	myView.OnDraw(c);
                	if(fs[0] > 0){
                		fs[0] ++;
                		if(fs[0] == 40)
                			fs[0] = 0;
                	}
                	if(myView.scores >= 4 && fs[1] > 0)
                	{
                		fs[1] ++;
                		if(fs[1] == 40)
                			fs[1] = 0;
                	}
                	if(fs[0] < 10)
                		myView.DrawPlate(c, x[0], y[0], index[0], 0);
                	if(myView.scores >= 4 && fs[1] < 10)
                		myView.DrawPlate(c, x[1], y[1], index[1], 1);
                }
            } finally {
                if (c != null) {
                	//更新屏幕显示内容
                    this.surfaceHolder.unlockCanvasAndPost(c);
                }
            }
            try{
            	Thread.sleep(10);
            }
            catch(Exception e){
            	e.printStackTrace();
            }
		}
	}
	public void Fly(int id)
	{
		if(x[id] < 0 || x[id] > 1280 || y[id] <0 || 
		 fs[id] == 1 || fs[id] == 30 || fs[id] == -1)
		{
			if(fs[id] == 0)
			{
				//if(index[id] == 0)
				//{
					if(myView.life > 0)
						myView.life --;
					if(myView.life == 0)
					{
						myView.hand();
						flag = false;
					}
				//}
			}
			if(fs[id] == 1)
			{
				/*if(index[id] == 1)
				{
					if(myView.life > 0)
						myView.life --;
					if(myView.life == 0)
					{
						myView.hand();
						flag = false;
					}
						
				}
				if(index[id] == 2)
				{
					if(myView.life < 5)
						myView.life ++;
				}*/
				if(myView.scores % 4 == 0)
					v += 5;
			}
			if(fs[id] != 1)
			{
				if(fs[id] == -1)
				{
					fs[id] = 0;
					//myView.life = 6;
				}
				if(myView.scores < 4)
				{
					if(r.nextInt(2) == 0)
					{
						x[id] = 0;
						dir[id] = 0;
					}
					else
					{
						x[id] = 1280;
						dir[id] = 1;
					}
				}
				else if(id == 0)
				{
					x[id] = 0;
					dir[id] = 0;
				}
				else
				{
					x[id] = 1280;
					dir[id] = 1;
				}
				int temp = r.nextInt(9);
				if(temp < 6)
					index[id] = 0;
				else if(temp < 8)
					index[id] = 1;
				else
					index[id] = 2;
				y[id] = 650;
			}
		}
		else if(fs[id] == 0)
		{
		        y[id] = y[id] - 15;
		        if(dir[id] == 0)
			        x[id] = x[id] + v + r.nextInt(5);
		        else
			        x[id] = x[id] - v - r.nextInt(5);
		}
	}
}