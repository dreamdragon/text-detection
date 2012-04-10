package com.detecttext;

import org.opencv.core.Core;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.core.Point;
import org.opencv.core.Scalar;

import org.opencv.imgproc.Imgproc;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Intent;
import android.content.res.AssetManager;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;

public class DetectText extends Activity {
	
    private static final String TAG = "DetectText::Activity";

    public static final int VIEW_MODE_RGBA  = 0;
    public static int viewMode = VIEW_MODE_RGBA;
    
    private DetectTextNative dtn;
    private AssetManager am;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        Log.i(TAG, "onCreate");
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        
        setContentView(R.layout.layout);
        
        am = getAssets();
        
       	dtn = new DetectTextNative(am);
        
        Button buttonOne = (Button) findViewById(R.id.button);
        buttonOne.setOnClickListener(new Button.OnClickListener() {
            public void onClick(View v) {
            	
                   DetectView dt = (DetectView) findViewById(R.id.myView);
                   Mat frame = dt.getRgbaFrame();
                   Log.i(TAG, "buttonCallback");
                   int [] boxes = dtn.getBoundingBoxes(frame.getNativeObjAddr());
                   System.out.println(boxes);
            }
        });
        
    }


    
}
