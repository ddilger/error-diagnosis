/* No error
 */
public class ReturnError6
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