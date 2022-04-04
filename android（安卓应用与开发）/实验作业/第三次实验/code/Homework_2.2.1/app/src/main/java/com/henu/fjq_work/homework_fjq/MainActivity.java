package com.henu.fjq_work.homework_fjq;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.HashMap;

public class MainActivity extends AppCompatActivity {
    private String listdata[] = {
            "移动应用开发技术","计算机组成原理","数据结构与算法","操作系统","计算机网络","高等数学","线性代数"
    };
    private ListView listview;
    private TextView textview;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ArrayList<HashMap<String,String>>list = new ArrayList<HashMap<String,String>>();

        HashMap<String ,String > map1 = new HashMap<String , String>();

        this.textview = (TextView) super.findViewById(R.id.title) ;
        this.listview = (ListView) super.findViewById(R.id.Mylistview);


        this.listview.setAdapter(new ArrayAdapter<String>(this,
                android.R.layout.simple_expandable_list_item_1,
                this.listdata));

        listview.setOnItemClickListener(new AdapterView.OnItemClickListener(){
            @Override
            public void onItemClick(AdapterView<?> arg0,View arg1,int arg2,long arg3)
            {
                String text = (String) listview.getItemAtPosition(arg2);
                textview.setText(text);
            }
        });
    }
}