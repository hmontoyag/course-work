import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.InputMismatchException;
import java.util.NoSuchElementException;
import edu.princeton.cs.algs4.Quick;

public class Query {
	int n;
	int m; //querys
	Integer[] iniX;
	Integer[][] xSy;
	Map<Integer,Integer> map;
	Integer[][] querys;
	ArrayList<Integer> xList;
	ArrayList<Integer> yList;
	
	public Query (int n){
		this.n=n;
		this.iniX=new Integer[n];
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
	
	public void iniQa(int m){
		this.querys = new Integer[m][2];
	}
	
	public void doQuery(int a, int b){
		xList = new ArrayList<Integer>();
		yList = new ArrayList<Integer>();
		int start=xSy[n-1][0];
		boolean found = false;//where x to start searchin to below
		
		search:{for(int i=0;i!=n;i++){
			if(xSy[i][0]>a){
				start=i;
				found = true;
				break search;
			}
		}}
//		StdOut.println("START:" + start);
		if(found==false){
			StdOut.println("none");
			return;
		}
		for(int i = start;i!=n;i++){
			if(xSy[i][1]>b){
				xList.add(xSy[i][0]);
				yList.add(xSy[i][1]);
			}
		}
		
		if(xList.size()==0||yList.size()==0){
			StdOut.println("none");
			return;
		}
		if(xList.size()!=yList.size()){StdOut.println("rip");}
		
		for(int i=0;i!=xList.size();i++){
			StdOut.println(xList.get(i) + " " + yList.get(i));
		}

	}
	
	public static void main(String[] args){
		Integer n = null;
		try{
			n=StdIn.readInt();
		}catch(InputMismatchException e){
			StdOut.println("Invalid input");
			return;
		}catch(NoSuchElementException ee){
			StdOut.println("Invalid input");
			return;
		}
		if(n<0){
			StdOut.println("n less than 0");
			return;
		}
		Integer x = null;
		Integer y = null;
		Query q = new Query(n);
		for (int i =0; i!=n;i++){
			try{
			 x = StdIn.readInt();
			}catch(InputMismatchException e){
			 StdOut.println("Invalid input");
			 return;
			}catch(NoSuchElementException ee){
			 StdOut.println("Invalid input");
			 return;
			}
			try{
			 y = StdIn.readInt();
			}catch(InputMismatchException o){
			 StdOut.println("Invalid input");			 return;
			}catch(NoSuchElementException oo){
			 StdOut.println("Invalid input");
			return;
			}
			if(x==null||y==null){
				StdOut.println("Invalid input");
				return;	
			}
			q.iniX[i]=x;
//			i++;
			if(x==null||y==null){continue;}
			q.map.put(x, y);
		}
		Integer m = null;
		try{
m=StdIn.readInt();
}catch(NoSuchElementException ee){StdOut.println("Invalid input");
return;}
		if(m==null){StdOut.println("Invalid input");
				return;
		}
		q.m = m;
		if(m<=0){
			StdOut.println("Invalid/0 number of querys requested.");
return;
}
		q.iniQa(q.m);
		int l=0;
		Integer a=null;
		Integer b=null;
		if(StdIn.isEmpty()==true){
			StdOut.println("Invalid input");
			return;
		}
		while(StdIn.isEmpty()==false){
			try{ 
			a = StdIn.readInt();
}catch(NoSuchElementException ee){StdOut.println("Invalid input");
return;}
			try{ 
			b = StdIn.readInt();
}catch(NoSuchElementException ee){StdOut.println("Invalid input");
return;}
			q.querys[l][0]=a;
			q.querys[l][1]=b;
			l++;
		}
		
		
		//start stuff
		q.organize();
//		Stopwatch timer = new Stopwatch();
		for(int i=0;i!=q.m;i++){
			int ax = q.querys[i][0];
			int yb = q.querys[i][1];
			q.doQuery(ax,yb);
		}
//		double time = timer.elapsedTime();
//		for(int j=0;j!=n;j++){
//			if(q.xSy[j][0]==null){continue;}
//			StdOut.println(q.xSy[j][0] + " " + q.xSy[j][1]);
//			
//		}
//		StdOut.println(timer.elapsedTime());
//		StdOut.println(q.m);
//		for(int j=0;j!=q.m;j++){
//			StdOut.println(q.querys[j][0] + " " + q.querys[j][1]);
//			
//		}
	}
}
