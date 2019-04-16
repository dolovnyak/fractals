__kernel void test(__global int* message)
{
int	gid = get_global_id(0);
printf ("gid0: %d\n", gid);
message[gid] += gid;
printf ("gid1: %d\n\n", get_global_id(1));
}
