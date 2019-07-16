package edu.purdue.hmontoya.cs180;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.TextView;


public class MainActivity extends Activity {
    private TextView num;
    private TextView sum;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        this.num = (TextView) findViewById(R.id.num);
        this.sum = (TextView) findViewById(R.id.sum);
        Button throwButton = (Button) findViewById((R.id.throwButton));
        Button clearButton = (Button) findViewById((R.id.resetButton));

        throwButton.setOnClickListener(new ThrowListener(num, sum));
        clearButton.setOnClickListener(new ClearListener(num,sum));



    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
