
public class Cuckoo{
	
	Coordinate map[];
	private static long a1, a2;
	double _e = 0.05;
	long size;
	boolean verbose;
	int upBound; 
	private int r;
	
	private Cuckoo(){
		r = 256;
		
		verbose = true;
		size = 0;
		_e=0.05;
		map = new Coordinate[r];
	}
	
	public void put(Integer key, Integer value){
		calcNewUpBound();
		if(!conCheck(key)){
			size=size+1;
		}
		if(2*_e*size>r){
			r=r*2;
			doubleUp();
		}
		Coordinate p = new Coordinate(key,value);
		add(p);
	}
	
	public void add(Coordinate c){
		int index1 = hash(c.getKey().hashCode(),a1,r);
		int index2 = hash(c.getKey().hashCode(),a2,r); //get two possible indexes
		if(eval(c,index1)){
			cleanIn(c,index1);
		} else if(eval(c,index2)){   //if all this cases arent checked, it fails for some reason? odd stuff
			cleanIn(c,index2);
		} else if(map[index1]==null){
			cleanIn(c,index1);
		} else if(map[index2]==null){
			cleanIn(c,index2);
			
		} else {
			dislodgeStuff(c,r);  //if all else fails dislodge
		}
	}

	
	public boolean eval(Coordinate c,int index){
		if(map[index]!=null&&map[index].getKey().equals(c.getKey())){
			return true;
		} else {
			return false;
		}
	}
	
	public void cleanIn(Coordinate c, int index){
		if(verbose==true){
			StdOut.println("(" + index + " " + c.getKey() + " " + c.getValue() + ")");
		}
		map[index] = c;
	}

	public void dislodgeStuff(Coordinate c, int r){
		
		int possibleIndex = hash(c.getKey().hashCode(),a1,r);
		int optIn1;
		int optIn2;
		int dCount = 0; //counnt up to upbound
		Coordinate newCo;
		int i = possibleIndex;
		for(newCo = map[i];dCount<=upBound&&newCo!=null;dCount++,c=newCo,newCo=map[i]){
			
			map[i]=c;
			optIn1= hash(newCo.getKey().hashCode(),a1,r);
			optIn2= hash(newCo.getKey().hashCode(),a2,r);
			if(verbose==true){
				StdOut.println("("+i+" "+c.getKey()+" "+c.getValue()+")");
			}
			if(i==optIn1){  //wea para decidir cual a1 o a2 usar para el siguiente intento
				possibleIndex = optIn2;
				i = optIn2;
			} else {
				possibleIndex = optIn1;
				i = optIn1;
			}
			
		}
		
		if(upBound < dCount){
			r = r *2;
			doubleUp();
		}
		
		add(c);
	}
	
	
	public void calcNewUpBound(){
		upBound = (int)(1 + 3 * (Math.log(r) / Math.log(1 + 0.05)));
	}

	public void doubleUp(){
		if(verbose==true){
			StdOut.println("(hash " + a1 + " "+a2+" "+ r+")");
		}
		calcNewUpBound();
		
		Coordinate temp[] = new Coordinate[r];
		int c=0;
		for(int i=0; i!=map.length;i++){
			if(!(map[i]==null)){ //saltea los nulos, no se necesitan para saber el orden
				temp[c++] = map[i]; //si no usas c, vas a dejar espacios vacios
				map[i]=null;
			}
		}
		
		map = new Coordinate[r];
		for(int i=0;i!=temp.length;i++){
			if(!(temp[i]==null)){
				Coordinate t = temp[i];
				add(t);
			}
		}
	}

	public boolean conCheck(Integer k){
		int optIn1 = hash(k.hashCode(),a1,r);
		int optIn2 = hash(k.hashCode(),a2,r);
		
		boolean choice1 = (map[optIn1]!=null&&map[optIn1].getKey().equals(k));
		boolean choice2 = (map[optIn2]!=null&&map[optIn2].getKey().equals(k));
	
		if(choice1||choice2){
			return true;
		}
		return false;
	}
	
	public void contains(Integer k){
		for(int i=0;i!=map.length;i++){
			if(map[i]!=null){
			if(map[i].getKey().equals(k)){
				StdOut.println("yes");
				return;
			}
			}
		}
		StdOut.println("no");
		return;
	}
	
	public void delete(Integer k){
		for(int i=0;i!=map.length;i++){
			if(map[i]!=null){
			if(map[i].getKey().equals(k)){
				map[i]=null;
				size--;
				return;
			}}
		}

		return;
	}

	
	public void get(Integer k){
		for(int i=0;i!=map.length;i++){
			if(map[i]!=null){
			if(map[i].getKey().equals(k)){
				StdOut.println(map[i].getValue());
				return;
			}
			}
		}
		StdOut.println("none");
		return;
	}
	public void size(){
		StdOut.println(size);
	}
	
	public void setVerbose(boolean x) {
		if (x==true) {
			verbose = true;
		} else {
			verbose = false;
		}
	}

	public int hash(int h, long a, int r){
//		int hc = h;
//		long hh = (long) (a*hc);
//		double p = Math.pow(2,16);
//		
//		hh = (long) (hh/p);
//		hh = hh%r;
//		return (int) hh;
		int rr = r;
		 double p = (a * h) / 65536;
	     int result = (int) p % rr;
	     return result;
	}
 
	public static void main (String[] args){
		Cuckoo cc = new Cuckoo();
		
		a1 = StdIn.readLong();
		a2 = StdIn.readLong();
		int n = StdIn.readInt();
		
		
//		StdOut.println(cc.a1);
//		StdOut.println(cc.a2);
//		StdOut.println(n);
		cc.setVerbose(true);
		cc.doubleUp();
		for (int i=0; i!=n;i++){
			String command = StdIn.readLine();
			String line[] = new String[3];
			line = command.split(" ");  //prepara las lineas, 0 es command, 1 y 2 son numerso
		
			
			if(line[0].equals("put")){
				int k = Integer.parseInt(line[1]);
				int v = Integer.parseInt(line[2]);
				cc.put(k,v);
				
			} else  if(line[0].equals("get")){
				int k = Integer.parseInt(line[1]);
				cc.get(k);
				
			} else if (line[0].equals("delete")){
				int k = Integer.parseInt(line[1]);
				cc.delete(k);
				
			} else if (line[0].equals("contains")){
				int k = Integer.parseInt(line[1]);
				cc.contains(k);
			
			} else if(line[0].equals("size")){
				cc.size();
			}
			
			
			
			
		}
	}
}
