import java.util.HashMap;
import java.util.Map;


public class Ferry {
	int n;
	Integer q[];
	HashMap<Integer,Integer> hist;
	int left =0;
	int k =0;
	int max;
	int right =0;
	
	public Ferry (int s, int l){
		n = s;
		this.q = new Integer [n];
		hist = new HashMap<Integer,Integer>(s);
		max = l;
	}
	
	public void start(){
		if(q[0]>max){
			return;
		}
		hist.put(k+1,q[0]);
		right = right + q[0];
		k++;
	}
	boolean pass = false;
	public void eval(){
		if(q[0]>max){
			max = 0;
			return;
		}
		for(int i=1;i!=n;i++){
			pass = false;
			//case 1, go to right
			if(right + q[i] <= max){
				hist.put(k+1,right+q[i]);
				k++;
				right = right+q[i];
				pass = true;
			}
			
			//case 2, go to left
			else if (left + q[i] <= max){
				hist.put(k+1, right);
				k++;
				left = left + q[i];
				pass = true;
			}
			
			//case 3, none, so we check if switching the previous scenario fixes this
			else {
				int v1 = hist.get(k); //curr val in right actually
				int v2 = hist.get(k-1); //previous value in right
				int dif = v1 - v2;  // last number added to right;
				//check if this fixed the problem for case 1
				if(right-dif+q[i] <= max){
					if(left + dif <= max){
						hist.put(k,right-dif+q[i]);
						left = left + dif;
						k++;
						pass = true;
					}
				}
				
			}	
			if ( pass == false){
				return;
			}
		}
	}
	
	public static void main (String[] args){
		
		if(args.length!=1){
			StdOut.println("Bad arguments.");
			return;
		}
		
		int length = Integer.parseInt(args[0]);
		int s = StdIn.readInt();
		Ferry f = new Ferry(s, length);
		for(int i=0; i!=s;i++){
			int a =StdIn.readInt();
			Integer b = a;
			f.q[i] = b;
	
		}
		f.start();
		f.eval();
		StdOut.println(f.k);
	
	}
	
	
}
