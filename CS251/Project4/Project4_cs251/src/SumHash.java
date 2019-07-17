import java.util.ArrayList;
import java.util.HashMap;


public class SumHash{
	int n;
	
	Integer list[];
	Integer sums[][];
	HashMap<Integer,Integer[][]> map;
	int count = 0;
	
	public SumHash(int n){
		this.n = n;	
		list = new Integer[n];
		sums = new Integer[n*(n-1)/2][3];
		map = new HashMap<Integer,Integer[][]>();
	}
	
	
	public void doSums(){
		int c=0;
		for(int i=0;i!=n-1;i++){
			for(int j=i+1;j!=n;j++){				
				sums[c][0] = list[i]+list[j];
				sums[c][1] = i;
				sums[c][2] = j;
				c++;
			}
		}
//		for(int i=0;i!=10;i++){
//			for(int j=0;j!=sums[i].length;j++){
//				StdOut.print("[" + sums[i][j] + "] ");
//			}
//			StdOut.println();
//		}
		evalh(c);
	}
	
	public void evalh(int c){
		for(int i=0; i!=c;i++){
			
			if(map.containsKey(sums[i][0])){  //if sum was previously in map
				Integer tbr[][] = map.get(sums[i][0]);	//get the array of indexes attached to the sum key
				int l = tbr.length;	//get its length
				
				Integer np[][] = new Integer[l+1][2];	//create a new array for it, with one more length for indexes
				int k;
				for(k=0;k!=l;k++){
					np[k][0] = tbr[k][0];
					np[k][1] = tbr[k][1];
				}							//copy values over
				np[k][0]=sums[i][1];
				np[k][1] = sums[i][2];	//fill the new space created with the values of the new matching indexes
				
				map.put(sums[i][0], np); //replace the old array attached to sumkey with new one
				
			} else {
				
				Integer fp[][] = new Integer [1][2];
				fp[0][0] = sums[i][1];
				fp[0][1] = sums[i][2];
				map.put(sums[i][0], fp);
				
			}
			
			
		}
	}

	public void check(){
		
		ArrayList<String> output = new ArrayList<String>();
		for(int i=0;i!=n-1;i++){
			for(int j=i+1;j!=n;j++){				
				
				Integer s = list[i]+list[j];
			
					Integer[][] matches = map.get(s);
					if (matches.length == 1){
						continue;
					}
					for(int k=0;k!=matches.length;k++){
						int a = i;
						int b = j;
						int x = matches[k][0].intValue();
						int y = matches[k][1].intValue();
						
						if((a!=b)&&(a!=x)&&(a!=y)&&(b!=x)&&(b!=y)&&(x!=y)){
							if(b>a){
								if(x>a&&y>x){
									output.add(count,a + " " + b + " " + x + " " + y);
									count++;
								}
							}
						}	
					
				}
				
				
			}
		}
		StdOut.println(count);
		for(int i=0;i!=count;i++){
			StdOut.println(output.get(i));
		}
		//StdOut.println(count);
		
	}
	
	
	public static void main (String[] args){
	
		
		int n = StdIn.readInt();
		SumHash sh = new SumHash(n);
		for(int i=0;i!=n;i++){
			sh.list[i]=StdIn.readInt();
		}
		sh.doSums();
		sh.check();
		
		
	
		
	}

}
