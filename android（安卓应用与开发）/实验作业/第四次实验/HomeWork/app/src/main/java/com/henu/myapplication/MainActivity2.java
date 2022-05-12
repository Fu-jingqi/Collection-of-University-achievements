package com.henu.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity2 extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);

        // 获得Mainactivity.java提供过来的参数
        Intent it = super.getIntent();
        String info = it.getStringExtra("sendinfo");                // listview的内容
        int position = it.getIntExtra("value",1);       // 点击的数组索引

        // 对xml中的布局变量进行注册
        Button btn1= (Button) findViewById(R.id.fir);
        Button btn2 = (Button) findViewById(R.id.sec);
        TextView txt = (TextView) findViewById(R.id.txt);


        txt.setText("删除 "+info+" 的记录吗?");

        // 调用两个按钮的点击事件
        // 确定按钮
        btn1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // 向main activity 返回点击的状态，从而执行删除操作
                getIntent().putExtra("return",position);
                setResult(RESULT_OK,MainActivity2.this.getIntent());
                finish();
            }
        });
        // 取消按钮
        btn2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // 按钮2 是取消操作
                Intent it2 = new Intent();
                setResult(RESULT_CANCELED,it2);
                finish();
            }
        });
    }
}