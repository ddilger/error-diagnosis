/*  Another case when it is logically necessary that the 
    program terminates, but the program doesn't know that
 */
public class ReturnError11
{
    public int adder(int x)
    {
	while(x==x)
	    {
		if(x==5)
		    return x+1;
		else
		    return x+2; 
	    }
    }
    public static void main(String[] args)
    {
	System.out.println(adder(5));
    }
}