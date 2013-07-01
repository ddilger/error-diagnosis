/*  Loop related error
 */
public class ReturnError10
{
    public int adder(int x)
    {
	while(x==x)
	    {
		if(x==5)
		    return x+1; 
	    }
	return x+1;
    }
    public static void main(String[] args)
    {
	System.out.println(adder(5));
    }
}