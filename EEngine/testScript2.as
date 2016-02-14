void step(uint16 frame_time)
{
	Request @read_test_int = Request("read test int", "write test data", READ_DATA, "test int");
	add_request("test container", read_test_int);
	waitForRequestQueueComp();
	consolePrintLine("" + read_test_int.get_double());
}