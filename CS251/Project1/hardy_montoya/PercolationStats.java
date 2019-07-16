import edu.princeton.cs.algs4.QuickFindUF;
import edu.princeton.cs.algs4.WeightedQuickUnionUF;



public class PercolationStats{
	int n;
	int t;
	String method;
	int mm;
	int grid[][];
	int opened[];
	QuickFindUF qf;
	Percolation p;
	WeightedQuickUnionUF uf;
	
	PercolationStats(int n, int t, String method){
		
		this.n = n;
		this.t = t;
	//	this.grid=new int[n][n];
		this.opened = new int[n*n];
	//	for(int i =0;i!=n;i++){for(int j=0;j!=n;j++){this.grid[n-1-i][j]=-1;}}//i*n+j;}}
	//	for(int i=0;i!=n*n;i++){opened[i]=-1;}
		if(method.equals("slow")){ 
			mm = 0;
			qf = new QuickFindUF(n*n+2);
		}
		
		
		if(method.equals("fast")){ 
			mm = 1;
			uf = new WeightedQuickUnionUF(n*n+2);
		}
	}
	
	//n*n-> abajo, n*n+1-> arriba
	
	public void reset(){
	
		//this.grid=new int[n][n];
		this.opened = new int[n*n];
		//for(int i =0;i!=n;i++){for(int j=0;j!=n;j++){this.grid[n-1-i][j]=-1;}}//i*n+j;}}
		//for(int i=0;i!=n*n;i++){opened[i]=-1;}
		qf = new QuickFindUF(n*n+2);
		uf = new WeightedQuickUnionUF(n*n+2);
	}

	public boolean isOpen(int x, int y){
		if(this.opened[x+n*y]==x+n*y){
			return true;
		}
		return false;
	}
	
	public void open(int x, int y){		
		if(isOpen(x,y)){
			//StdOut.println("Opened before.");
			return;
		}
		opened[x+n*y]=x+y*n;
		//conversion para orientacion:
		
		//Check boundaries
		if(x!=0){if(isOpen(x-1,y)){	uf.union(x+y*n, x-1+(y)*n);}}
		if(x!=n-1){if(isOpen(x+1,y)){	uf.union(x+y*n, x+1+(y)*n);}}
		if(y!=0){if(isOpen(x,y-1)){	uf.union(x+y*n, x+(y-1)*n);}} else { uf.union(x+y*n,n*n);}
		if(y!=n-1){if(isOpen(x,y+1)){	uf.union(x+y*n, x+(y+1)*n);}} else { uf.union(x+y*n,n*n+1);}
		
	}

	public boolean isFull(int x,int y){
		
		if(uf.connected(x+y*n,n*n+1)){
			return true;
		}
		return false;
	}
		
	
	public boolean percolates(){
		if(uf.connected(n*n,n*n+1)){
			return true;
		}
		return false;
		
	}
	
	public boolean isOpenS(int x, int y){
		if(this.opened[x+n*y]==x+n*y){
			return true;
		}
		return false;
	}

	
	public void openS(int x, int y){
		if(isOpenS(x,y)){
			//StdOut.println("Opened before.");
			return;
		}
		opened[x+n*y]=x+y*n;
		////
		//grid[x][y]=i+j*n;;
		
		//Check boundaries
		if(x!=0){if(isOpenS(x-1,y)){	qf.union(x+y*n, x-1+(y)*n);}}
		if(x!=n-1){if(isOpenS(x+1,y)){	qf.union(x+y*n, x+1+(y)*n);}}
		if(y!=0){if(isOpenS(x,y-1)){	qf.union(x+y*n, x+(y-1)*n);}}else { qf.union(x+y*n,n*n);}
		if(y!=n-1){if(isOpenS(x,y+1)){	qf.union(x+y*n, x+(y+1)*n);}}else { qf.union(x+y*n,n*n+1);}
		
	}

	public boolean isFullS(int x,int y){
		if(qf.connected(x+y*n,n*n+1)){
			return true;
		}
		return false;
	}

	public boolean percolatesS(){
		if(qf.connected(n*n,n*n+1)){
			return true;
		}
		return false;
		
	}
	
	
	public static void main (String[] args){
		
		
		if(args.length<2){
			StdOut.print("Invalid arguments");
			return;
			
		}
		int n = Integer.parseInt(args[0]);
		int t = Integer.parseInt(args[1]);
		String s;
		if(args[2].equals("slow")){
			 s = "slow";
		} else if(args[2].equals("fast")){
			s = "fast";
		} else {
			StdOut.print("Invalid arguments");
			return;
		}
		
		

		
		PercolationStats ps = new PercolationStats(n, t, s);
		
		int count = 0;
		double quantity = 0;
		double nn = (double) n;
		double est[] = new double[t];
		double times[] = new double[t];
		
		
		if(ps.mm==1){
			
			for(int i=0;i!=t;i++){
				Stopwatch time1= new Stopwatch();
				while(ps.percolates()==false){
					int x = StdRandom.uniform(n);
					int y = StdRandom.uniform(n);
					if(ps.isOpen(x,y)){
						continue;
					}
					ps.open(x,y);
					quantity++;
				}
				//StdOut.println(ps.p.percolates());
				//StdOut.println(quantity);
				est[i]=quantity/(nn*nn);
				quantity = 0;
				ps.reset();
				times[i]=time1.elapsedTime();
				
			}
			
		}
		if(ps.mm==0){
			for(int i=0;i!=t;i++){
				Stopwatch time2= new Stopwatch();
				while(ps.percolatesS()==false){
					int x = StdRandom.uniform(n);
					int y = StdRandom.uniform(n);
					if(ps.isOpenS(x,y)){
						continue;
					}
					ps.openS(x,y);
					quantity++;
				}
				//StdOut.println(ps.percolatesS());
				est[i]=quantity/(nn*nn);
				quantity = 0;
				ps.reset();
				times[i]=time2.elapsedTime();
				
			}
		}
		
		double meanEst = StdStats.mean(est);
		double stdEst = StdStats.stddev(est);
		double sumOfTimes=0;
		for(int i=0; i!=t;i++){
			sumOfTimes = sumOfTimes + times[i];
		}
		double meanTime = StdStats.mean(times);
		double stdTime = StdStats.stddev(times);
		//StdArrayIO.print(est);
		StdOut.println("mean threshold= " + meanEst);
		StdOut.println("std dev= " + stdEst);
		StdOut.println("time= " + sumOfTimes);
		StdOut.println("mean time= " + meanTime);
		StdOut.println("stddev time= " + stdTime);
		
	
		
	}
}
