#include "text_detect.h"
#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>

#define APPNAME "DetectText"

namespace {
	DetectText* toDetectTextNative(jlong detectPtr) {
		return reinterpret_cast<DetectText*>(detectPtr);
	}
}

extern "C" {

	JNIEXPORT jlong JNICALL Java_com_detecttext_DetectTextNative_create(JNIEnv* env, jobject jobj) {
		DetectText* dt = new DetectText();
		return reinterpret_cast<jlong>(dt);
	}

	JNIEXPORT void JNICALL Java_com_detecttext_DetectTextNative_destroy(JNIEnv* env, jobject jobj, jlong detectPtr) {
		delete toDetectTextNative(detectPtr);
	}

	JNIEXPORT jintArray JNICALL Java_com_detecttext_DetectTextNative_getBoundingBoxes(JNIEnv* env, jobject jobj, jlong detectPtr, jlong matAddress) {

		Mat* nativeMat =(Mat*)matAddress;
		vector<Rect> boundingBoxes = toDetectTextNative(detectPtr)->getBoundingBoxes(*nativeMat);

		jintArray result = env->NewIntArray(boundingBoxes.size() * 4);

		if (result == NULL) {
			return NULL;
		}

		jint tmp_arr[boundingBoxes.size() * 4];

		int idx = 0;

		for (int i = 0; i < boundingBoxes.size(); i++) {
			tmp_arr[idx++] = boundingBoxes[i].x;
			tmp_arr[idx++] = boundingBoxes[i].y;
			tmp_arr[idx++] = boundingBoxes[i].width;
			tmp_arr[idx++] = boundingBoxes[i].height;
		}

		env->SetIntArrayRegion(result, 0, boundingBoxes.size() * 4, tmp_arr);

		return result;
	}

}
