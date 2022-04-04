package com.henu.fjq_work.myapplication_fjq;

import androidx.appcompat.app.AppCompatActivity;

import android.app.ListActivity;
import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;


import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MainActivity extends AppCompatActivity {
    private ListView listView;
    private List<Map<String,Object>> list;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        list = new ArrayList<Map<String,Object>>();
        listView = (ListView) findViewById(R.id.listView);

        Map<String,Object> map1 = new HashMap<String,Object>();
        Map<String,Object> map2 = new HashMap<String,Object>();
        Map<String,Object> map3 = new HashMap<String,Object>();
        Map<String,Object> map4 = new HashMap<String,Object>();
        Map<String,Object> map5 = new HashMap<String,Object>();
        Map<String,Object> map6 = new HashMap<String,Object>();

        map1.put("title","姓名");
        map1.put("info","扶靖棋");
        map1.put("picture",R.drawable.img_1);
        list.add(map1);
        map2.put("title","性别");
        map2.put("info","男");
        map2.put("picture",R.drawable.img);
        list.add(map2);

        map3.put("title","学号");
        map3.put("info","2012020028");
        map3.put("picture",R.drawable.img);
        list.add(map3);
        map4.put("title","年龄");
        map4.put("info","20");
        map4.put("picture",R.drawable.img);
        list.add(map4);
        map5.put("title","居住地");
        map5.put("info","开封");
        map5.put("picture",R.drawable.img);
        list.add(map5);
        map6.put("title","邮箱");
        map6.put("info","1070673506@qq.com");
        map6.put("picture",R.drawable.img);
        list.add(map6);

        MyAdapter adapter = new MyAdapter(this,list,R.layout.user);
        listView.setAdapter(adapter);
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                adapter.setCurrentItem(i);
                adapter.setClick(true);
                adapter.notifyDataSetChanged();
            }
        });

    }
    class MyAdapter extends BaseAdapter {
        private Context context;
        private int resource;
        private List<Map<String,Object>> list;
        private int mCurrentItem=0;
        private boolean isClick=false;

        public MyAdapter(Context context, List<Map<String, Object>> list, int resource) {
            this.context = context;
            this.list = list;
            this.resource = resource;
        }

        @Override
        public int getCount() {
            return list.size();
        }

        @Override
        public Object getItem(int i) {
            return list.get(i);
        }

        @Override
        public long getItemId(int i) {
            return i;
        }

        @Override
        public View getView(int i, View view, ViewGroup viewGroup) {
            // 声明内部类
            Util util = null;

            final int flag = i;

            if(view == null){
                util = new Util();
                // 给xml布局文件创建java对象
                LayoutInflater inflater = LayoutInflater.from(context);
                view = inflater.inflate(resource, null);
                // 指向布局文件内部组件
                util.picture = (ImageView) view.findViewById(R.id.picture);
                util.info = (TextView) view.findViewById(R.id.info);
                util.title = (TextView) view.findViewById(R.id.title);
                // 增加额外变量
                view.setTag(util);
            }
            else {
                util = (Util) view.getTag();
            }
            // 获取数据显示在各组件
            Map<String, Object> map = list.get(i);
            util.info.setText((String) map.get("info"));
            util.title.setText((String) map.get("title"));
            util.picture.setImageResource((Integer) map.get("picture"));


            LinearLayout parent= (LinearLayout) view.findViewById(R.id.parent1);

            if (mCurrentItem==i&&isClick){
                parent.setBackgroundColor(Color.parseColor("#FF03DAC5"));
            }else{
                parent.setBackgroundColor(Color.parseColor("#6495ED"));
            }

            return view;
        }



        public void setCurrentItem(int currentItem){
            this.mCurrentItem=currentItem;
        }

        public void setClick(boolean click){
            this.isClick=click;
        }

        class Util{
            TextView title;
            TextView info;
            ImageView picture;
        }
    }
}