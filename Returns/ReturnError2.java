/* Doesn't always return
   cause: if statement */
public class ReturnError2
{
    public int adder(int x)
    {
	if (x == 5)
	    {
		
	    }
	else
	    {
		return x+1;
	    }
    }
    public static void main(String[] args)
    {
	System.out.println(adder(5));
    }
}