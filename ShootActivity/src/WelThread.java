package com.example.shootactivity;

import com.example.shootactivity.WelcomeView;
import android.graphics.Canvas;			//引入相关类
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.util.Log;
import android.view.SurfaceHolder;		//引入相关类

public class WelThread extends Thread {
	boolean flag=true;
	WelcomeView welcomeView;			
	SurfaceHolder holder;
	Canvas c;
	public WelThread(WelcomeView myView){	
		welcomeView = myView;	
		holder=myView.surfaceHolder;
	}
	 @Override
     public void run()
     {
         while(flag)
         {
             try
             {
                    c = holder.lockCanvas();
                    welcomeView.OnDraw(c);
             }
             catch (Exception e) {
                 // TODO: handle exception
                 e.printStackTrace();
             }
             finally
             {
                 if(c!= null)
                 {
                    holder.unlockCanvasAndPost(c);

                }
             }
             try {
				Thread.sleep(33);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
         }
     }
}
