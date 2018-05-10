package com.ndk.demo.myapplication;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.util.Locale;

public class NdkDemoActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ndk_demo);
        final TextView textView = (TextView) findViewById(R.id.sample_text);
        final EditText editText = (EditText) findViewById(R.id.edit_text);
        Button button = (Button) findViewById(R.id.button);

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //jni打log
                NativeBridge.nativeLog("string from java:" + editText.getText().toString());

                //传递对象
                BeanDemo bean = new BeanDemo();
                bean.setString("hello");
                bean.setInteger(17);
                bean.setBool(true);
                bean.setFloat(12313.78768f);
                bean.setDouble(1231231.123d);
                bean.setChar('c');
                bean.setShort((short) 345);
                bean.setByte((byte) 100);
                NativeBridge.setObject(bean);

                //给jni传数组
                float[] intArray = {5.3f, 2.4f, 0f, 1f, -4f, 100000f, -4000.001f};
                NativeBridge.setArray(intArray, intArray.length);

                //从jni获取字符串
                String jniString = NativeBridge.stringFromJNI();

                //从jni执行运算
                int jniResult = NativeBridge.nativeAdd(3, 9);
                textView.setText(String.format(Locale.getDefault(), "%s  Add result:%d", jniString, jniResult));

                //区别静态方法和成员方法
                NativeBridge bridge = new NativeBridge();
                bridge.classOrInstance();
            }
        });
    }
}
