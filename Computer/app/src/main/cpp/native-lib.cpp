#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jfloat JNICALL
Java_com_example_computer_MainActivity_addmethod(JNIEnv *env, jobject thiz, jfloat one,
                                                 jfloat two) {
    // TODO: implement addmethod()
    return one+two;
}
extern "C"
JNIEXPORT jfloat JNICALL
Java_com_example_computer_MainActivity_submethod(JNIEnv *env, jobject thiz, jfloat one,
                                                 jfloat two) {
    // TODO: implement submethod()
    return one-two;
}
extern "C"
JNIEXPORT jfloat JNICALL
Java_com_example_computer_MainActivity_mulmethod(JNIEnv *env, jobject thiz, jfloat one,
                                                 jfloat two) {
    // TODO: implement mulmethod()
    return one*two;
}
extern "C"
JNIEXPORT jfloat JNICALL
Java_com_example_computer_MainActivity_divmethod(JNIEnv *env, jobject thiz, jfloat one,
                                                 jfloat two) {
    // TODO: implement divmethod()
    return one/two;
}