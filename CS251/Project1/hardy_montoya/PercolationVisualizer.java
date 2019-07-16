


public class PercolationVisualizer extends Percolation{
	Percolation p;
	
	public PercolationVisualizer(int n){
		super(n);		
	}
	
	
	
	public static void main (String[] args){
		
		//int n = StdIn.readInt();
		//PercolationVisualizer p = new PercolationVisualizer(n);
//		StdDraw.setPenRadius(0.05);
//		            StdDraw.setPenColor(StdDraw.BLUE);
//		            StdDraw.point(0.5, 0.5);
//		           StdDraw.setPenColor(StdDraw.MAGENTA);
//		           StdDraw.line(0.2, 0.2, 0.8, 0.2);
//		
		double n=StdIn.readDouble();
		Percolation p = new Percolation((int) n);
		//
		double c = 1/n;
		double fr = c/2;
		//
		StdDraw.setPenColor(StdDraw.BLACK);
		
		//
		for(int i = 0; i!=n;i++){
			for(int j=0;j!=n;j++){
			StdDraw.filledSquare(c*i+fr,c*j+fr,fr+0.001);
			}
		}
		//
		while(StdIn.isEmpty()==false){
			int x = StdIn.readInt();
			int y = StdIn.readInt();
			if(!p.isOpen(x,y)){
				p.open(x,y);
				StdDraw.setPenColor(StdDraw.WHITE);
				StdDraw.filledSquare(c*x+fr,c*y+fr,fr-0.005);
			}
			for(int i=0;i!=n;i++){
				for(int j=0;j!=n;j++){
					if(p.isFull(i, j)){
						StdDraw.setPenColor(StdDraw.CYAN);
						StdDraw.filledSquare(c*i+fr,c*j+fr,fr-0.005);
					}
				}
			}
			try        
			{
			    Thread.sleep(400);
			} 
			catch(InterruptedException ex) 
			{
			    Thread.currentThread().interrupt();
			}
		}
		//StdOut.print(p.percolates());
		
//		StdDraw.setPenColor(StdDraw.WHITE);
//		for(int i = 0; i!=n;i++){
//			for(int j=0;j!=n;j++){
//			StdDraw.filledSquare(c*i+fr,c*j+fr,fr-0.005);
//			}
//		}
		
		//StdDraw.filledSquare(0.5+0.25, 0.5+0.25, 0.25-0.005);
		//StdDraw.filledSquare(0.0+0.25, 0.5+0.25, 0.25-0.005);
		
	}

}
