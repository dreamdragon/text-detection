package com.detecttext;

import org.opencv.core.Mat;

import android.content.res.AssetManager;

public class DetectTextNative {
	
    static { 
    	System.loadLibrary("lept");
    	System.loadLibrary("tess");
		System.loadLibrary("run_detection");
	}
	
	private long detectPtr = 0;
	
    public DetectTextNative(AssetManager am) {
    	detectPtr = create();
    	readLetterCorrelation(detectPtr, am, "correlation.mp3");
    	readWordList(detectPtr, am, "full-dictionary.mp3");    
    }

	private native long create();
	private native void destroy(long detectPtr);
	private native void readLetterCorrelation(long detectPtr, AssetManager am, String filename);
	private native void readWordList(long detectPtr, AssetManager am, String filename);
	private native void detect(long detectPtr, long matAddress);

	@Override
	protected void finalize() throws Throwable {
		if(detectPtr != 0) {
			destroy(detectPtr);
		}
		super.finalize();
	}
	
	public void detect(long matAddress) {
		detect(detectPtr, matAddress);
	}
}