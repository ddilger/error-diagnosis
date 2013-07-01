/* Doesn't always return
 cause: switch statement */
public class ReturnError4
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
		return x+1;
		break;
	    default:
	    }
    }
    public static void main(String[] args)
    {
	System.out.println(adder(5));
    }
}