package com.lvhiei.cgpuimage;

import android.util.Log;

import java.security.PublicKey;

/**
 * Created by lvHiei on 17-4-1.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

public class Logger {
    private static final class LOGLEVEL{
        public static final int VERBOSE = 0;
        public static final int DEBUG = 1;
        public static final int INFO = 2;
        public static final int WARN = 3;
        public static final int ERROR = 4;
        public static final int FATAL = 5;
        public static final int SILENCE = 100;
    }


    private int mLogLevel = LOGLEVEL.DEBUG;
    private String tag;

    public Logger(String tag){
        this.tag = tag;
    }

    public void v(String msg){
        if(mLogLevel <= LOGLEVEL.VERBOSE){
            Log.v(tag, msg);
        }
    }

    public void d(String msg){
        if(mLogLevel <= LOGLEVEL.DEBUG){
            Log.d(tag, msg);
        }
    }


    public void i(String msg){
        if(mLogLevel <= LOGLEVEL.INFO){
            Log.i(tag, msg);
        }
    }


    public void w(String msg){
        if(mLogLevel <= LOGLEVEL.WARN){
            Log.w(tag, msg);
        }
    }


    public void e(String msg){
        if(mLogLevel <= LOGLEVEL.ERROR){
            Log.e(tag, msg);
        }
    }


    public void f(String msg){
        if(mLogLevel <= LOGLEVEL.FATAL){
            Log.wtf(tag, msg);
        }
    }

}
