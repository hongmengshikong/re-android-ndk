package com.example.xposed;

import android.util.Log;

import de.robv.android.xposed.IXposedHookLoadPackage;
import de.robv.android.xposed.XC_MethodHook;
import de.robv.android.xposed.XposedHelpers;
import de.robv.android.xposed.callbacks.XC_LoadPackage;

public class Hook implements IXposedHookLoadPackage {
    @Override
    public void handleLoadPackage(XC_LoadPackage.LoadPackageParam loadPackageParam) throws Throwable {

        if (!loadPackageParam.packageName.equals("com.qyj.chinese")) {
            return;
        }
        XposedHelpers.findAndHookMethod("com.qyj.chinese.http.AESTools", loadPackageParam.classLoader, "encryptionByAES", "java.lang.String", new XC_MethodHook() {
            @Override
            protected void beforeHookedMethod(MethodHookParam param) throws Throwable {
                super.beforeHookedMethod(param);
                String plaintext = (String) param.args[0];
                String key = (String) XposedHelpers.getStaticObjectField(
                        XposedHelpers.findClass("com.qyj.chinese.http.AESTools", loadPackageParam.classLoader),
                        "KEY"
                );
                Log.d("wg","[AES 加密] 明文: " + plaintext);
                Log.d("wg","[AES 加密] 密钥: " + key);
            }
            @Override
            protected void afterHookedMethod(MethodHookParam param) throws Throwable {
                super.afterHookedMethod(param);
                String ciphertext = (String) param.getResult();
                Log.d("wg","[AES 加密] 密文: " + ciphertext);
            }
        });

        XposedHelpers.findAndHookMethod("com.qyj.chinese.http.AESTools", loadPackageParam.classLoader, "decryptByAES", "java.lang.String", new XC_MethodHook() {
            @Override
            protected void beforeHookedMethod(MethodHookParam param) throws Throwable {
                super.beforeHookedMethod(param);
                String ciphertext = (String) param.args[0];
                String key = (String) XposedHelpers.getStaticObjectField(
                        XposedHelpers.findClass("com.qyj.chinese.http.AESTools", loadPackageParam.classLoader),
                        "KEY"
                );
                Log.d("wg","[AES 解密] 密文: " + ciphertext);
                Log.d("wg","[AES 解密] 密钥: " + key);
            }
            @Override
            protected void afterHookedMethod(MethodHookParam param) throws Throwable {
                super.afterHookedMethod(param);
                String plaintext = (String) param.getResult();
                Log.d("wg","[AES 解密] 明文: " + plaintext);
            }
        });

    }
}