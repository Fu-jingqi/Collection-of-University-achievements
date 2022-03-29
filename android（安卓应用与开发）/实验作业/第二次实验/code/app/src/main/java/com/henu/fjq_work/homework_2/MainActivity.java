package com.henu.fjq_work.homework_2;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.view.menu.ShowableListMenu;

import android.content.DialogInterface;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.os.Bundle;

import java.util.List;

public class MainActivity extends AppCompatActivity {

    private Spinner eduzy = null;
    private ArrayAdapter<CharSequence> adaptereduzy ;
    private List<CharSequence> dataclassid = null ;

    private Button Submit_f=null;
    private EditText nameis=null;
    RadioGroup sexis=null;
    CheckBox music=null;
    CheckBox sport=null;
    CheckBox swimming=null;
    CheckBox reading=null;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        this.eduzy = (Spinner) super.findViewById(R.id.spin_2);
        this.eduzy.setPrompt("选择专业");
        this.adaptereduzy = ArrayAdapter.createFromResource(this, R.array.eduzy, android.R.layout.simple_spinner_item);
        this.adaptereduzy.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        this.eduzy.setAdapter(this.adaptereduzy);

        this.Submit_f=super.findViewById(R.id.Submit_f);
        this.nameis=MainActivity.super.findViewById(R.id.nameis);
        this.sexis=super.findViewById(R.id.sexis);
        this.music=super.findViewById(R.id.music);
        this.sport=super.findViewById(R.id.sport);
        this.swimming=super.findViewById(R.id.swimming);
        this.reading=super.findViewById(R.id.reading);

        Submit_f.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                String YourName=nameis.getText().toString();
                if(YourName.isEmpty()||YourName.trim().equals("")||YourName==null){
                    Toast.makeText(MainActivity.this,"请输入姓名！",Toast.LENGTH_SHORT).show();
                }else{
                    int count = sexis.getChildCount();
                    for(int i = 0 ;i < count;i++){
                        RadioButton rb = (RadioButton)sexis.getChildAt(i);
                        if(rb.isChecked()){
                            String smajor=eduzy.getSelectedItem().toString();
                            String content="";
                            if(music.isChecked())content+="音乐，";else{content=content.replace("音乐，","");}
                            if(sport.isChecked())content+="运动，";else{content=content.replace("运动，","");}
                            if(swimming.isChecked())content+="游泳，";else{content=content.replace("游泳，","");}
                            if(reading.isChecked())content+="阅读，";else{content=content.replace("阅读，","");}
                            if(!content.isEmpty())content=content.substring(0,content.length()-1);
                            if(content.isEmpty())content+="无";
                            content+="！";
                            String tag=rb.getTag().toString();
                            Toast.makeText(MainActivity.this,"你好，2012020028 "+YourName.trim()+"！\n你的性别是："+tag+"！\n你的专业是"+smajor.trim()+"！\n你的个人爱好有："+content,Toast.LENGTH_LONG).show();
                            break;
                        }else if(i==count-1){
                            Toast.makeText(MainActivity.this,"请选择您的性别！",Toast.LENGTH_SHORT).show();
                        }
                    }
                }
            }
        });
    }


}

