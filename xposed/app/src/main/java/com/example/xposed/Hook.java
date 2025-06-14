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
    }

}