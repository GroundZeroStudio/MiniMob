#include "FileUtil.h"
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))

static AAssetManager* _assetManager;

void InitAAssetManager(AAssetManager * assetManager)
{
	_assetManager = assetManager;
}

unsigned char* FileUtil::LoadFile(const char* path)
{
	AAsset* asset = AAssetManager_open(_assetManager, path, AASSET_MODE_STREAMING);
	long length = AAsset_getLength(asset);
	unsigned char* data = new unsigned char[length];
	AAsset_read(asset, data, length);
	return data;
}