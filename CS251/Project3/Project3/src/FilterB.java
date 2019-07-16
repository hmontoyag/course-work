import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

import edu.princeton.cs.algs4.BinarySearchST;
import edu.princeton.cs.algs4.Quick;


public class FilterB {
	Integer n;
	Integer[] iniX;
	Integer[][] xSy;
	Map<Integer,Integer> map;
	
	public FilterB(int n){

		this.n=n;
		this.iniX = new Integer[n];
		this.xSy = new Integer[n][2];
		map = new HashMap<Integer,Integer>(n);
	}
	
	public void organize(){
		Quick.sort(iniX);
		for(int i=0;i!=n;i++){
			int k = map.get(iniX[i]);
			xSy[i][0]=iniX[i];
			xSy[i][1]=k;
		}

	}

	public void check(){
		int max=xSy[n-1][1];
		for(int i=n-1;i!=0;i--){
//			if(xSy[i][0]==null){continue;}
			if(max<xSy[i-1][1]){
				max = xSy[i-1][1];
			} else {
				xSy[i-1][0]=null;
			}
		}
	}
	

	
	public void toDel(int x, int y){
		
	}
	
	public static void main(String[] args){
		Integer n = StdIn.readInt();
		FilterB b = new FilterB(n);
		int i = 0;
		Stopwatch timer = new Stopwatch();
		while(StdIn.isEmpty()==false){
			Integer x = StdIn.readInt();
			Integer y = StdIn.readInt();
			b.iniX[i] = x;
			i++;
			b.map.put(x,y);

		}
		b.organize();
		b.check();
		double time = timer.elapsedTime();
	
//		b.organize();
//		b.check();
		for(int j=0;j!=n;j++){
			if(b.xSy[j][0]==null){continue;}
			StdOut.println(b.xSy[j][0] + " " + b.xSy[j][1]);
			
		}
//		
		StdOut.println(time);
		
		
	}
}
