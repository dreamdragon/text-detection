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
	jlong Java_com_detecttext_DetectTextNative_create(JNIEnv* env, jobject jobj) {
		DetectText* dt = new DetectText();
		return reinterpret_cast<jlong>(dt);
	}

	void Java_com_detecttext_DetectTextNative_destroy(JNIEnv* env, jobject jobj, jlong detectPtr) {
		delete toDetectTextNative(detectPtr);
	}

	void Java_com_detecttext_DetectTextNative_readLetterCorrelation(JNIEnv * env, jobject jobj, jlong detectPtr, jobject assetManager, jstring correlationFile) {

		const char * correlationFileNative = env->GetStringUTFChars(correlationFile, 0);

		AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
		assert(NULL != mgr);
		AAsset* asset = AAssetManager_open(mgr, (const char *) correlationFileNative, AASSET_MODE_UNKNOWN);

		env->ReleaseStringUTFChars(correlationFile, correlationFileNative);;

		if (NULL == asset) {
			return;
		}

		__android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "Correlation");

		off_t start, length;
		int fd = AAsset_openFileDescriptor(asset, &start, &length);

		toDetectTextNative(detectPtr)->readLetterCorrelation(fd);
	}

	void Java_com_detecttext_DetectTextNative_readWordList(JNIEnv* env, jobject jobj, jlong detectPtr, jobject assetManager, jstring wordFile) {
		const char * wordFileNative = env->GetStringUTFChars(wordFile, 0);

		AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
		assert(NULL != mgr);
		AAsset* asset = AAssetManager_open(mgr, (const char *) wordFileNative, AASSET_MODE_UNKNOWN);

		env->ReleaseStringUTFChars(wordFile, wordFileNative);;

		if (NULL == asset) {
			return;
		}

		off_t start, length;
		int fd = AAsset_openFileDescriptor(asset, &start, &length);

		toDetectTextNative(detectPtr)->readWordList(fd);
	}

	void Java_com_detecttext_DetectTextNative_detect(JNIEnv* env, jobject jobj, jlong detectPtr, jlong matAddress) {
		Mat* pMatGr=(Mat*)matAddress;
		toDetectTextNative(detectPtr)->detect(*pMatGr);
	}
}
