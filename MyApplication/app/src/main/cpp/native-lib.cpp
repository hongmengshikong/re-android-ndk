#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

//C层访问了Java层的实例字段
extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_myapplication_MainActivity_GetTest1(JNIEnv *env, jobject obj) {

    //参数为类的路径，包名+类名，把点换成斜杠
    jclass j_class = env->FindClass("com/example/myapplication/MainActivity");
    //第一个参数是哪个类，第二个参数是要获取的java层的字段的字段名，第三个参数是该字段的数据类型
    jfieldID j_fieldID= env->GetFieldID(j_class, "test1", "Ljava/lang/String;");
    jobject str= env->GetObjectField(obj, j_fieldID);
    return str;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_myapplication_MainActivity_GetTest2(JNIEnv *env, jobject obj) {
    //参数为类的路径，包名+类名，把点换成斜杠
    jclass j_class = env->FindClass("com/example/myapplication/MainActivity");
    //第一个参数是哪个类，第二个参数是要获取的java层的字段的字段名，第三个参数是该字段的数据类型
    jfieldID j_fieldID= env->GetStaticFieldID(j_class, "test2", "Ljava/lang/String;");
    jobject str= env->GetStaticObjectField(j_class, j_fieldID);
    return str;

    // TODO: implement GetTest2()
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_JavaToC(JNIEnv *env, jobject obj) {

    jclass j_class = env->FindClass("com/example/myapplication/MainActivity");
    jmethodID id= env->GetMethodID(j_class, "_method", "()V");
    env->CallVoidMethod(obj, id);
    return env->NewStringUTF("123");
    // TODO: implement JavaToC()
}