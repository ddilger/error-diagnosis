/* No error */
public class ReturnError14
{
    public static int add1(int x)
    {
	if(x%2 == 0)
	    {
		if(x%4 == 0)
		    {

		    }
		else
		    {
			return x+1;			
		    }
		return x+1;			
	    }
	else
	    {
		return x+1;
	    }
    }
    public static void main(String[] args)
    {
	add1(5);
    }
}