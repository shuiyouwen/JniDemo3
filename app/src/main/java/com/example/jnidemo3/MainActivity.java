package com.example.jnidemo3;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.example.jnidemo3.jni.ICallback;
import com.example.jnidemo3.jni.IThreadCallback;
import com.example.jnidemo3.jni.JNIAccessField;
import com.example.jnidemo3.jni.JNIAccessMethod;
import com.example.jnidemo3.jni.JNIBasicType;
import com.example.jnidemo3.jni.JNIInvokeMethod;
import com.example.jnidemo3.jni.JNIRefrenceType;
import com.example.jnidemo3.jni.JNIStringType;
import com.example.jnidemo3.jni.Person;
import com.example.jnidemo3.load.JNIDynamicLoad;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        final TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());
        final JNIDynamicLoad jniDynamicLoad = new JNIDynamicLoad();
        final JNIBasicType jniBasicType = new JNIBasicType();
        final JNIStringType jniStringType = new JNIStringType();
        final JNIRefrenceType jniRefrenceType = new JNIRefrenceType();
        final JNIAccessField jniAccessField = new JNIAccessField();
        final JNIAccessMethod jniAccessMethod = new JNIAccessMethod();
        final JNIInvokeMethod jniInvokeMethod = new JNIInvokeMethod();
        tv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String[] strings = {"哈哈", "呵呵", "嘻嘻"};
                String firstStr = jniRefrenceType.handleStringArray(strings);
                tv.setText(firstStr);

                Person person = new Person();
                Log.d("jni_proctice", "修改前 person:" + person);
                jniAccessField.accessFile(person);
                Log.d("jni_proctice", "修改后 person:" + person);

                jniAccessMethod.accessMethod(person);
                jniAccessMethod.accessStaticMethod(person);

                jniInvokeMethod.nativeCallback(new ICallback() {
                    @Override
                    public void callback() {
                        Log.d("jni_proctice", "callback");
                    }
                });
                jniInvokeMethod.nativeThreadCallback(new IThreadCallback() {
                    @Override
                    public void threadCallback() {
                        Log.d("jni_proctice", "nativeThreadCallback:" + Thread.currentThread().getName());
                    }
                });
            }
        });
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

}
