/* Error in 4-th level */
public class ReturnError15
{
    public static int add1(int x)
    {
	if(x%2 == 0)
	    {
		if(x%4 == 0)
		    {
			if(x%8 == 0)
			    {
				
			    }
			else
			    {
				return x+1;			
			    }
		    }
		else
		    {
			return x+1;			
		    }
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