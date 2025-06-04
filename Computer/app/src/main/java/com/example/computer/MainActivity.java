package com.example.computer;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    TextView result;
    Button add,sub,mul,div;
    EditText first,second;
    Float one,two;

    // Used to load the 'computer' library on application startup.
    static {
        System.loadLibrary("computer");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        init();
        compute();
    }
    private void init(){
        first=findViewById(R.id.editText);
        second=findViewById(R.id.editText2);
        result =findViewById(R.id.textView3);
        add=findViewById(R.id.add);
        sub=findViewById(R.id.sub);
        mul=findViewById(R.id.mul);
        div=findViewById(R.id.div);
    }
    private void compute(){
        final View.OnClickListener cl = v -> {
            String strOne = first.getText().toString();
            String strTwo = second.getText().toString();

            if (strOne.isEmpty() || strTwo.isEmpty()) {
                result.setText("请输入两个数字");
                return;
            }

            try {
                one = Float.parseFloat(strOne);
                two = Float.parseFloat(strTwo);

                int id = v.getId();
                float re;

                if (id == R.id.add) {
                    re = addmethod(one, two);
                } else if (id == R.id.sub) {
                    re = submethod(one, two);
                } else if (id == R.id.mul) {
                    re = mulmethod(one, two);
                } else if (id == R.id.div) {
                    if (two == 0) {
                        result.setText("除数不能为0");
                        return;
                    }
                    re = divmethod(one, two);
                } else {
                    result.setText("未知操作");
                    return;
                }

                result.setText(String.valueOf(re));

            } catch (NumberFormatException e) {
                result.setText("请输入有效数字");
            }
        };

        add.setOnClickListener(cl);
        sub.setOnClickListener(cl);
        mul.setOnClickListener(cl);
        div.setOnClickListener(cl);
    }


    /**
     * A native method that is implemented by the 'computer' native library,
     * which is packaged with this application.
     */
    public native float addmethod(float one,float two);
    public native float submethod(float one,float two);
    public native float mulmethod(float one,float two);
    public native float divmethod(float one,float two);
}