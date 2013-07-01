/* Doesn't always return
 cause: switch statement */
public class ReturnError3
{
    public int adder(int x)
    {
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