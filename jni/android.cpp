#include "text_detect.h"
#include <jni.h>

namespace {
	DetectText* toDetectText(jlong detectPtr) {
		return reinterpret_cast<DetectText*>(detectPtr);
	}
}

extern "C" {
	jlong Java_com_detecttext_DetectText_create(JNIEnv* env, jobject jobj) {
		DetectText * dt = new DetectText();
		return reinterpret_cast<jlong>(dt);
	}

	void Java_com_detecttext_DetectText_destroy(JNIEnv* env, jobject jobj, jlong detectPtr) {
		delete toDetectText(detectPtr);
	}

	void Java_com_detecttext_DetectText_detect(JNIEnv* env, jobject jobj, jlong detectPtr, string filename) {
		toDetectText(detectPtr)->detect(filename);
	}

}
