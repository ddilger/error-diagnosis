/* A loop which shouldn't cause an error (only limited cases of this to build in)
 */
public class ReturnError12
{
    public int adder(int x)
    {
	for(int i=0; i<5; i++)
	    {
		
	    }
	return x+1;
    }
    public static void main(String[] args)
    {
	System.out.println(adder(5));
    }
}