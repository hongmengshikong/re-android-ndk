package com.example.xposed;

import android.util.Log;

import de.robv.android.xposed.IXposedHookLoadPackage;
import de.robv.android.xposed.XC_MethodHook;
import de.robv.android.xposed.XposedHelpers;
import de.robv.android.xposed.callbacks.XC_LoadPackage;

public class Hook implements IXposedHookLoadPackage {
    @Override
    public void handleLoadPackage(XC_LoadPackage.LoadPackageParam loadPackageParam) throws Throwable {

        if(!loadPackageParam.packageName.equals("com.zjzy.calendartime")){
            return;
        }
        XposedHelpers.findAndHookMethod("com.app.modelintegral.data.ZhttpIntegral", loadPackageParam.classLoader, "getMD5Hash", "java.lang.String", new XC_MethodHook() {
            @Override
            protected void beforeHookedMethod(MethodHookParam param) throws Throwable {
                super.beforeHookedMethod(param);
                Log.d("kong",param.args[0].toString());
                // 打印堆栈信息
                Log.d("kong", "【调用堆栈开始】");
                StackTraceElement[] stackTraces = new Throwable("stack_logs").getStackTrace();
                for (StackTraceElement element : stackTraces) {
                    Log.d("kong", "  " + element.toString());
                }
                Log.d("kong", "【调用堆栈结束】");
            }
            @Override
            protected void afterHookedMethod(MethodHookParam param) throws Throwable {
                super.afterHookedMethod(param);
                // 获取返回值
                Object result = param.getResult();
                if (result != null) {
                    Log.d("kong", "MD5 返回值: " + result.toString());
                } else {
                    Log.d("kong", "返回值为 null");
                }
            }
        });
        XposedHelpers.findAndHookMethod("com.umeng.commonsdk.statistics.common.DataHelper", loadPackageParam.classLoader, "encrypt", "byte[]", "byte[]", new XC_MethodHook() {
            @Override
            protected void beforeHookedMethod(MethodHookParam param) throws Throwable {
                super.beforeHookedMethod(param);
                byte[] plaintext = (byte[]) param.args[0];
                byte[] key = (byte[]) param.args[1];

                Log.d("kong","=== [AES 加密] 开始 ===");
                Log.d("kong","[明文] " + safeToString(plaintext));
                Log.d("kong","[密钥] " + safeToString(key));
            }
            @Override
            protected void afterHookedMethod(MethodHookParam param) throws Throwable {
                super.afterHookedMethod(param);
                byte[] ciphertext = (byte[]) param.getResult();
                Log.d("kong","[密文 HEX] " + bytesToHex(ciphertext));
                Log.d("kong","=== [AES 加密] 结束 ===");
            }
        });
        XposedHelpers.findAndHookMethod("com.umeng.commonsdk.statistics.common.DataHelper", loadPackageParam.classLoader, "decrypt", "byte[]", "byte[]", new XC_MethodHook() {
            @Override
            protected void beforeHookedMethod(MethodHookParam param) throws Throwable {
                super.beforeHookedMethod(param);
                byte[] ciphertext = (byte[]) param.args[0];
                byte[] key = (byte[]) param.args[1];

                Log.d("kong","=== [AES 解密] 开始 ===");
                Log.d("kong","[密文 HEX] " + bytesToHex(ciphertext));
                Log.d("kong","[密钥] " + safeToString(key));
            }
            @Override
            protected void afterHookedMethod(MethodHookParam param) throws Throwable {
                super.afterHookedMethod(param);
                byte[] plaintext = (byte[]) param.getResult();
                Log.d("kong","[明文] " + safeToString(plaintext));
                Log.d("kong","=== [AES 解密] 结束 ===");
            }
        });
    }
    private static String safeToString(byte[] bytes) {
        if (bytes == null) return "null";
        try {
            return new String(bytes, "UTF-8");
        } catch (Exception e) {
            return "（无法转换为字符串）";
        }
    }
    private static String bytesToHex(byte[] bytes) {
        if (bytes == null) return "null";
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            sb.append(String.format("%02X", b));
        }
        return sb.toString();
    }

}