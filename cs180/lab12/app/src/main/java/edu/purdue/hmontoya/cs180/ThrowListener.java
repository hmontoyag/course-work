package edu.purdue.hmontoya.cs180;

/**
 * Created by hmontoya on 11/12/15.
 */
import android.view.View;
import android.widget.TextView;

import java.util.Random;

public class ThrowListener implements View.OnClickListener {
    private TextView num;
    private TextView sum;

    public ThrowListener(TextView num, TextView sum) {
        this.num = num;
        this.sum = sum;

    }

    @Override
    public void onClick(View view) {
        int n = new Random().nextInt(6) +1;
        num.setText(String.valueOf(n));
        int currentSum = Integer.parseInt(sum.getText().toString());
        int newSum = currentSum + n;
        sum.setText(String.valueOf(newSum));

    }
}
