/* No error
 */
public class ReturnError5
{
    public int adder(int x)
    {
	if (x == 5)
	    {

	    }
	else
	    {

	    }
	switch(x)
	    {
	    case 1:
		break;
	    case 5:
		break;
	    default:
		return x+1;
	    }
    }
    public static void main(String[] args)
    {
	System.out.println(adder(5));
    }
}