/*
 *fix the gcc complain about no <raise>
 */
int raise(int signum)
{
	return 0;
}
