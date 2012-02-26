package com.detecttext;

public class DetectText {
	static {
		System.loadLibrary("librun_detection");
	}
	
	private native long create();
	private native void destroy(long detectPtr);
	private native void detect(long detectPtr, String filename);
	
	private long detectPtr = 0;
	
	public DetectText() {
		detectPtr = create();
	}
	
	@Override
	protected void finalize() throws Throwable {
		if(detectPtr != 0) {
			destroy(detectPtr);
		}
		super.finalize();
	}
}
