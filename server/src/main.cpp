#include <strx/kernel/Kernel.h>

INITIALIZE_EASYLOGGINGPP

int main()
{
	using namespace strx;

	nya::init_logs("config/log.conf");

	try
	{
		Kernel::Run("config/strategix.json");
	}
	catch (exception& e)
	{
		error_log << "\n\t" << e.what();
	}
	Kernel::Finish();
}
