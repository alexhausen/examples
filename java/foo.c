//gcc -m32 -shared -fpic -o libfoo.so -I /usr/lib/jvm/j2sdk1.4.2_19/include/ -I /usr/lib/jvm/j2sdk1.4.2_19/include/linux/ foo.c
//gcc -shared -fpic -o libfoo.so -I /usr/lib/jvm/jdk1.7.0_21/include/ -I /usr/lib/jvm/jdk1.7.0_21/include/linux/ foo.c
//gcc -m32 -shared -fpic -o libfoo.so -I /home/likewise-open/CERTI/alh/Projects/certi_smart_platform/third_party/jvm/mika/core-vm/include/ -I /home/likewise-open/CERTI/alh/Projects/certi_smart_platform/third_party/jvm/mika/vm-cmp/fp/native/include/ -I /home/likewise-open/CERTI/alh/Projects/certi_smart_platform/third_party/jvm/mika/core-vm/hal/cpu/x86/include/ foo.c 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jni.h>
#include "JNIFoo.h"

JNIEXPORT jstring JNICALL Java_JNIFoo_nativeFoo (JNIEnv *env, jobject obj) {
  char* newstring;
  jstring ret_obj = 0;
  newstring = (char*) malloc(30);
  if(newstring == NULL) {
    return ret_obj;
  }
  memset(newstring, 0, 30);
  strcpy(newstring, "foo: Test program of JNI.");
  ret_obj = (*env)->NewStringUTF(env, newstring);
  free(newstring);

  jclass cls;
  jmethodID method;

  cls = (*env)->FindClass(env, "java/lang/String");
  printf("class String: %d\n", (int)cls);
  method = (*env)->GetMethodID(env, cls, "toString", "()Ljava/lang/String;");
  printf("method String.toString: %d\n", (int)method);
  if ((*env)->ExceptionCheck(env)) {
    puts("exception!");
    (*env)->ExceptionDescribe(env);
  }
  if (method != 0) {
    jobject o = (*env)->CallObjectMethod(env, obj, method);
    printf("obj.toString(): %d\n", (int)o);
  }

//  cls = (*env)->FindClass(env, "JNIFoo"); //doesn't work with mika
  cls = (*env)->FindClass(env, "LJNIFoo;");
  printf("class JNIFoo: %d\n", (int)cls);

  method = (*env)->GetStaticMethodID(env, cls, "print2", "()V");
  printf("method JNIFoo.print2: %d\n", (int)method);
  if ((*env)->ExceptionCheck(env)) {
    puts("exception!");
    (*env)->ExceptionDescribe(env);
  }
  if (method != 0) {
    (*env)->CallStaticVoidMethod(env, cls, method);
  }


  cls = (*env)->FindClass(env, "java/lang/Integer");
  if (!cls) {
    puts("class Integer not found.");
  } else {
    method = (*env)->GetStaticMethodID(env, cls, "toString", "(I)Ljava/lang/String;");
    if (!method) {    
       puts("Integer.toString not found");
    } else {
      jobject o2 = (*env)->CallStaticObjectMethod(env, cls, method, 10);
      if (!o2) {
        puts("?");
      }
      else {
        puts("ok");
      }
    }
  }


  return ret_obj;
}

JNIEXPORT void JNICALL Java_JNIFoo_f(JNIEnv* env, jclass cls, jintArray v) {
    jsize len = (*env)->GetArrayLength(env, v);
    jint* arr = (*env)->GetIntArrayElements(env, v, 0);
    printf("array: ");
    jsize i;
    for (i = 0; i < len; i++) {
        printf("%d ", (int)arr[i]);
    }
    printf("\n");
}
