package com.example.aescrypto;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.example.aescrypto.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {
    TextView ciphertext;
    Button button;
    EditText plaintext;

    // Used to load the 'crypto' library on application startup.
    static {
        System.loadLibrary("aes");
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
        plaintext=findViewById(R.id.editText);
    }

    private void crypto(){
        final View.OnClickListener cl= v ->{
            String input = plaintext.getText().toString();
            if (input.isEmpty()) {
                ciphertext.setText("请输入待加密的明文");
                return;
            }
            String result;
            if (v.getId() == R.id.button) {
                result = AESEncode(input);
            }else {
                return; // 不处理其他按钮
            }
            ciphertext.setText(result);
        };
        button.setOnClickListener(cl);
    }

    /**
     * A native method that is implemented by the 'base64' native library,
     * which is packaged with this application.
     */
    private native String AESEncode(String string);
}