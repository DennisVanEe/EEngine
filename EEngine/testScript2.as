void _step(float frame_time)
{
	Request @read_test_int = Request("read test int", "write test data", READ_DATA, "test int");
	requestQueue.add_request("test container", read_test_int);
	scriptEngine.waitForRequestQueueComp();
	consolePrintLine("" + read_test_int.get_double());
}