package com.detecttext;

import org.opencv.core.Mat;

import android.content.res.AssetManager;

public class DetectTextNative {
	
    static { 
		System.loadLibrary("run_detection");
	}
	
	private long detectPtr = 0;
	
    public DetectTextNative(AssetManager am) {
    	detectPtr = create();
    }

	private native long create();
	private native void destroy(long detectPtr);
	private native int[] getBoundingBoxes(long detectPtr, long matAddress);

	@Override
	protected void finalize() throws Throwable {
		if(detectPtr != 0) {
			destroy(detectPtr);
		}
		super.finalize();
	}
	
	public int[] getBoundingBoxes(long matAddress) {
		return getBoundingBoxes(detectPtr, matAddress);
	}
}