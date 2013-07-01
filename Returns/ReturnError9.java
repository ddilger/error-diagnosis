/*  Loop related error
 */
public class ReturnError9
{
    public int adder(int x)
    {
	while(x==x)
	    {

	    }
	return x+1;
    }
    public static void main(String[] args)
    {
	System.out.println(adder(5));
    }
}