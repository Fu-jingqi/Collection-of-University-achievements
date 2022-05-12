package com.henu.myapplication;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    private String listdata[] = {"夏清华","朱玉玺","于泽洋","李淇","汪圣钦","刁刁"};
    private ListView listView;
    private List<String> list;
    private ArrayAdapter adpter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        listView = (ListView)findViewById(R.id.listview);
        // 将listdata的数据导入到list的 数组中,通过删除数组的元素，来实现删除操作
        list = new ArrayList<String>(Arrays.asList(listdata));

        // 使用ArrayAdapter的适配器
        adpter = new ArrayAdapter<String>(this, android.R.layout.simple_expandable_list_item_1
                ,this.list);
        this.listView.setAdapter(adpter);

        // listview 的点击事件
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                // 向 MainActivity.java传入数据
                String name = (String)listView.getItemAtPosition(i);
                Intent it = new Intent(MainActivity.this,MainActivity2.class);
                it.putExtra("sendinfo",name);
                it.putExtra("value",i);
                startActivityForResult(it,1);
                adpter.notifyDataSetChanged();
            }
        });
    }

    // 定义一个方法，用来删除数据
    public void delete(ArrayAdapter adapterView, int i){
        String text = (String)listView.getItemAtPosition(i);
        // 删除listview 中第i个数据
        adpter.remove(listView.getItemAtPosition(i));
        Toast.makeText(getApplicationContext(),text+"的记录已被删除",Toast.LENGTH_LONG).show();
    }


    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        switch (requestCode) {
            case 1:
                if(resultCode == RESULT_OK)
                {
                    // 返回点击该项的索引
                    int h = data.getIntExtra("return",1);
                    // 调用删除的方法
                    delete(adpter,h);
                }
                else {
                    String text = "取消操作";
                    Toast.makeText(getApplicationContext(),text,Toast.LENGTH_LONG).show();
                }
            default:
                break;
        }
    }
}