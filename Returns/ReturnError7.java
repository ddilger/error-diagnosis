/* Example of where logically the program will always return, but
  the diagnosis machine flags a potential issue
 */
public class ReturnError7
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
	if (x == 5)
	    {
		return x+1;
	    }

    }
    public static void main(String[] args)
    {
	System.out.println(adder(5));
    }
}