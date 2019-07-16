package edu.purdue.hmontoya.cs180;

import android.view.View;

import android.widget.TextView;
/**
 * Created by hmontoya on 11/12/15.
 */
public class ClearListener implements View.OnClickListener {
    private TextView sum;
    private TextView num;

    public ClearListener(TextView sum, TextView num) {
        this.sum = sum;
        this.num = num;
    }

    @Override
    public void onClick(View view) {
        int vSum = 0;
        num.setText(String.valueOf(vSum));
        sum.setText(String.valueOf(vSum));

    }
}
