/* No error
 */
public class ReturnError21
{
    public int add1(int x)
    {
	for(int i=0; i<5; i++)
	    {
		if(x%2==0)
		    {
			if(x%4==0)
			    {
				if(x%8==0)
				    {
					break;
				    }
				else
				    {
					return x+1;
				    }
			    }
			else if(x%3==0)
			    {
				return x+1;
			    }
			else
			    {
				return x+1;
			    }
		    }
	    }
	return x+1;
    }
    public static void main(String[] args)
    {
	add1(5);
    }
}