package com.example.crypto;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;


public class MainActivity extends AppCompatActivity {
    TextView ciphertext;
    Button button,button2,button3,button4;
    EditText plaintext;

    // Used to load the 'crypto' library on application startup.
    static {
        System.loadLibrary("crypto");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        init();
        crypto();

    }
    private void init(){
        ciphertext=findViewById(R.id.ciphertext);
        button=findViewById(R.id.button);
        button2=findViewById(R.id.button2);
        button3=findViewById(R.id.button3);
        button4=findViewById(R.id.button4);
        plaintext=findViewById(R.id.editText);
    }

    private void crypto(){
        final View.OnClickListener cl=v ->{
            String input = plaintext.getText().toString();
            if (input.isEmpty()) {
                ciphertext.setText("请输入待加密的明文");
                return;
            }
            String result;
            if (v.getId() == R.id.button) {
                result = Base64Encode(input);
            } else if (v.getId() == R.id.button2) {
                result = XorEncode(input);
            }else if (v.getId() == R.id.button3) {
                result = TEAEncode(input);
            }else if (v.getId() == R.id.button4) {
                result = AESEncode(input);
            } else {
                return; // 不处理其他按钮
            }
            ciphertext.setText(result);
        };
        button.setOnClickListener(cl);
        button2.setOnClickListener(cl);
        button3.setOnClickListener(cl);
        button4.setOnClickListener(cl);
    }

    /**
     * A native method that is implemented by the 'base64' native library,
     * which is packaged with this application.
     */
    private native String Base64Encode(String str);
    private native String XorEncode(String str);
    private native String TEAEncode(String string);
    private native String AESEncode(String ststringr);
}