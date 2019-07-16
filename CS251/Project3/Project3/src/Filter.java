
import java.util.HashMap;
import java.util.Map;
import java.util.InputMismatchException;
import java.util.NoSuchElementException;
import edu.princeton.cs.algs4.Quick;


public class Filter {
	Integer n;
	Integer[] iniX;
	Integer[][] xSy;
	Map<Integer,Integer> map;	
	public Filter(int n){		
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
	public static void main(String[] args){
		Integer n = null;
		if(StdIn.isEmpty()==true){
			StdOut.println("Empty.");
			return;
		}
		try{
			 n = StdIn.readInt();
		} catch (InputMismatchException e){
			StdOut.println("Invalid input.");
return;		
} catch (NoSuchElementException ee){ StdOut.println("Invalid input.");
return;
}
		if(n<0){
			StdOut.println("Invalid number of pairs (less than 0)");
return;		
}
		Filter b = new Filter(n);
		int i = 0;
		Integer x = null;
		Integer y = null;		
		while(StdIn.isEmpty()==false){
			try{ x = StdIn.readInt();}catch(InputMismatchException e){StdOut.println("Invalid input");
return;
}catch(NoSuchElementException ee){StdOut.println("Invalid input.");
return;
}
			try{ y = StdIn.readInt();}catch(InputMismatchException e){StdOut.println("Invalid input");
return;
}catch(NoSuchElementException ee){StdOut.println("Invalid input.");
return;
}
			if(x==null||y==null){
				StdOut.println("Invalid input.");
				return;
			}
			b.iniX[i] = x;
			i++;
			if(x==null||y==null){
				continue;
			}
			b.map.put(x,y);
		}
	//	Stopwatch timer = new Stopwatch();
		if(n==null||b.n==null){StdOut.println("Invalid input.");
return;}
		b.organize();
		b.check();
	//	double time = timer.elapsedTime();
//		b.organize();
//		b.check();
		for(int j=0;j!=n;j++){
			if(b.xSy[j][0]==null){continue;}
			StdOut.println(b.xSy[j][0] + " " + b.xSy[j][1]);
			
		}
//		
//		StdOut.println(time);
		
		
	}
}
